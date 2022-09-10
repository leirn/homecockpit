//! Functions to handle serial communications with Arduino

use serialport::*;
use std::fmt;
use std::sync::mpsc::{Receiver, Sender};

use crate::channel_mgt::*;
use crate::protocol::*;

const SERIAL_PORT_SPEED: u32 = 9600;

/// Message class
/// This class represents messages used on the serial connection
/// between the computer and the master Arduino module
struct Message {
    category: u8,
    component: u8,
    action: u8,
}

impl Message {
    /// Creates an empty message with 0 as values
    pub fn null() -> Message {
        Message {
            category: 0,
            component: 0,
            action: 0,
        }
    }

    /// Creates a message based on received bytes from serial port
    pub fn new(received_bytes: [u8; 2]) -> Message {
        let message: u16 = (received_bytes[0] as u16) << 8 + received_bytes[1] as u16;
        let category = ((message & MASK_CATEGORY) >> 12) as u8;
        let component = ((message & MASK_COMPONENT) >> 4) as u8;
        let action = (message & MASK_ACTION) as u8;
        Message {
            category: category,
            component: component,
            action: action,
        }
    }

    /// Retrieve the two bytes representing the message
    pub fn get_bytes_message(&self) -> [u8; 2] {
        let mut buffer = [0, 0];
        let message = self.get_message();
        buffer[0] = ((message & 0xff00) >> 8) as u8;
        buffer[1] = (message & 0xff) as u8;
        buffer
    }

    /// Retrieve the message as u16 value
    pub fn get_message(&self) -> u16 {
        (self.category as u16) << 12 + (self.component as u16) << 4 + self.action as u16
    }
}

impl fmt::Display for Message {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.get_message())
    }
}

pub struct ArduinoCommunicationHandler {
    rx_to_arduino: Receiver<ChannelMessage>,
    tx_to_simconnect: Sender<ChannelMessage>,
    port_id: String,
    port_speed: u32,
    started: bool,
}

impl ArduinoCommunicationHandler {
    pub fn new(
        rx_to_arduino: Receiver<ChannelMessage>,
        tx_to_simconnect: Sender<ChannelMessage>,
    ) -> ArduinoCommunicationHandler {
        ArduinoCommunicationHandler {
            rx_to_arduino: rx_to_arduino,
            tx_to_simconnect: tx_to_simconnect,
            port_id: String::from("COM3"),
            port_speed: SERIAL_PORT_SPEED,
            started: false,
        }
    }

    /// Function to handle all communication received from Arduino
    pub fn run(&mut self) {
        let mut port: Option<Box<dyn SerialPort>> = None;

        loop {
            if self.started & port.as_ref().is_some() {
                let mut buffer: [u8; 2] = [0, 0];

                let bytes_to_read = port.as_ref().unwrap().bytes_to_read().unwrap();
                if bytes_to_read > 1 {
                    port.as_mut().unwrap().read_exact(&mut buffer).unwrap();

                    let message = Message::new(buffer);

                    println!("Message received : {}", message);

                    let responses = match message.category {
                        CATEGORY_ELECTRICAL_EVENTS => self.electrical_events_handler(message),
                        CATEGORY_ENGINE_EVENTS => self.engine_events_handler(message),
                        CATEGORY_AUTOPILOT_EVENTS => self.autopilot_events_handler(message),
                        CATEGORY_G1000_PFD_EVENTS => self.g1000_events_handler(message),
                        CATEGORY_G1000_MFD_EVENTS => self.g1000_events_handler(message),
                        CATEGORY_MISC_EVENTS => self.misc_events_handler(message),
                        CATEGORY_RADIO_NAV_EVENTS => self.radio_nav_events_handler(message),
                        _ => {
                            println!("Unrecognized category for message {}", message);
                            let r: Vec<Message> = Vec::new();
                            r
                        }
                    };

                    for response in responses {
                        let msg_bytes = &(response.get_bytes_message());
                        port.as_mut().unwrap().write(msg_bytes).unwrap();
                    }
                }
            }
            // Check for message on inter-thread channel
            for msg in self.rx_to_arduino.try_iter() {
                match msg.message_type {
                    ListOfMessageTypes::SerialStart => {
                        self.started = true;
                        port = Some(
                            serialport::new(&self.port_id, self.port_speed)
                                .open()
                                .expect("Failed to open port"),
                        );
                    }
                    ListOfMessageTypes::SerialStop => {
                        self.started = false;
                    }
                    ListOfMessageTypes::SerialSend => {
                        if self.started & port.as_ref().is_some() {
                            let mut buffer: [u8; 2] = [0, 0];
                            buffer[0] = ((msg.payload_int >> 8) & 0xff) as u8;
                            buffer[1] = (msg.payload_int & 0xff) as u8;
                            port.as_mut().unwrap().write(&buffer).unwrap();
                        } else {
                            println!("Serial communication has not started, cannot send message");
                        }
                    }
                    ListOfMessageTypes::SerialPort => self.port_id = msg.payload,
                }
            }
        }
    }

    /// Manage messages from the serial port where category is CATEGORY_ELECTRICAL_EVENTS
    fn electrical_events_handler(&self, message: Message) -> Vec<Message> {
        let mut responses: Vec<Message> = Vec::new();
        let response = Message {
            category: CATEGORY_ELECTRICAL_EVENTS,
            component: message.component,
            action: match message.action {
                EVENT_GENERAL_OFF => STATUS_GENERAL_OFF,
                EVENT_GENERAL_ON => STATUS_GENERAL_ON,
                _ => STATUS_GENERAL_ERROR,
            },
        };
        responses.push(response);
        responses
    }

    /// Manage messages from the serial port where category is CATEGORY_ENGINE_EVENTS
    fn engine_events_handler(&self, message: Message) -> Vec<Message> {
        let mut responses: Vec<Message> = Vec::new();
        let response = Message {
            category: CATEGORY_ENGINE_EVENTS,
            component: message.component,
            action: match message.action {
                EVENT_GENERAL_OFF => STATUS_GENERAL_OFF,
                EVENT_GENERAL_ON => STATUS_GENERAL_ON,
                _ => STATUS_GENERAL_ERROR,
            },
        };
        responses.push(response);
        responses
    }

    /// Manage messages from the serial port where category is CATEGORY_AUTOPILOT_EVENTS
    fn autopilot_events_handler(&self, _message: Message) -> Vec<Message> {
        let responses: Vec<Message> = Vec::new();
        responses
    }

    /// Manage messages from the serial port where category is CATEGORY_G1000_PFD_EVENTS or CATEGORY_G1000_MFD_EVENTS
    fn g1000_events_handler(&self, _message: Message) -> Vec<Message> {
        let responses: Vec<Message> = Vec::new();
        responses
    }

    /// Manage messages from the serial port where category is CATEGORY_MISC_EVENTS
    fn misc_events_handler(&self, message: Message) -> Vec<Message> {
        let mut responses: Vec<Message> = Vec::new();
        match message.component {
            COMPONENT_PITOT_HEAT => {
                let response = Message {
                    category: CATEGORY_MISC_EVENTS,
                    component: COMPONENT_PITOT_HEAT,
                    action: match message.action {
                        EVENT_GENERAL_OFF => STATUS_GENERAL_OFF,
                        EVENT_GENERAL_ON => STATUS_GENERAL_ON,
                        _ => STATUS_GENERAL_ERROR,
                    },
                };
                responses.push(response);
            }
            COMPONENT_LANDING_GEAR => {
                // Center Gear
                let response = Message {
                    category: CATEGORY_MISC_EVENTS,
                    component: COMPONENT_LANDING_GEAR_CENTER,
                    action: match message.action {
                        ACTION_LDG_GEAR_UP => STATUS_LDG_GEAR_UP,
                        ACTION_LDG_GEAR_DOWN => STATUS_LDG_GEAR_DOWN,
                        _ => STATUS_LDG_GEAR_UNKNOWN,
                    },
                };
                responses.push(response);
                // Left Gear
                let response = Message {
                    category: CATEGORY_MISC_EVENTS,
                    component: COMPONENT_LANDING_GEAR_LEFT,
                    action: match message.action {
                        ACTION_LDG_GEAR_UP => STATUS_LDG_GEAR_UP,
                        ACTION_LDG_GEAR_DOWN => STATUS_LDG_GEAR_DOWN,
                        _ => STATUS_LDG_GEAR_UNKNOWN,
                    },
                };
                responses.push(response);
                // Right Gear
                let response = Message {
                    category: CATEGORY_MISC_EVENTS,
                    component: COMPONENT_LANDING_GEAR_LEFT,
                    action: match message.action {
                        ACTION_LDG_GEAR_UP => STATUS_LDG_GEAR_UP,
                        ACTION_LDG_GEAR_DOWN => STATUS_LDG_GEAR_DOWN,
                        _ => STATUS_LDG_GEAR_UNKNOWN,
                    },
                };
                responses.push(response);
            }
            COMPONENT_FLAPS => {
                let response = Message {
                    category: CATEGORY_MISC_EVENTS,
                    component: COMPONENT_FLAPS,
                    action: message.action,
                };
                responses.push(response);
            }
            _ => println!("Unknown component {}", message.component),
        }
        responses
    }

    /// Manage messages from the serial port where category is CATEGORY_RADIO_NAV_EVENTS
    fn radio_nav_events_handler(&self, _message: Message) -> Vec<Message> {
        let responses: Vec<Message> = Vec::new();
        responses
    }
}
