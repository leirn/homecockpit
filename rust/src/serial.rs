//! Functions to handle serial communications with Arduino

use crate::channel_mgt::*;

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

/// Function to handle all communication received from Arduino
pub fn arduino_communication_handler(Receiver<T> rx_to_arduino, Sender<T> tx_to_simconnect) {
    // TODO : List port, select port, start, stop listening with channels
    // https://doc.rust-lang.org/rust-by-example/std_misc/channels.html
    // https://doc.rust-lang.org/book/ch16-02-message-passing.html


    let mut started:bool = false;
    let mut port_id = "COM1";
    let mut port = serialport::new(port_id, 9600)

    loop {
        if started {
            let mut buffer: [u8; 2] = [0, 0];

            let bytes_to_read = port.bytes_to_read().unwrap();
            if bytes_to_read > 1 {
                port.read_exact(&mut buffer).unwrap();

                let message = Message::new(buffer);

                println!("Message received : {}", message);

                let reponses = match message.category {
                    CATEGORY_ELECTRICAL_EVENTS => electrical_events_handler(message),
                    CATEGORY_ENGINE_EVENTS => engine_events_handler(message),
                    CATEGORY_AUTOPILOT_EVENTS => autopilot_events_handler(message),
                    CATEGORY_G1000_PFD_EVENTS => g1000_events_handler(message),
                    CATEGORY_G1000_MFD_EVENTS => g1000_events_handler(message),
                    CATEGORY_MISC_EVENTS => misc_events_handler(message),
                    CATEGORY_RADIO_NAV_EVENTS => radio_nav_events_handler(message),
                    _ => {
                        println!("Unrecognized category for message {}", message);
                        Message::null()
                    }
                };

                for response in responses {
                    port.write(&reponse.get_bytes_message()).unwrap();
                }
            }
        }
        // Check for message on inter-thread channel
        for msg in rx_to_arduino.try_iter() {
            match msg.message_type {
                ListOfMessageTypes::SerialStart => {
                    started = true;
                    port = serialport::new(port_id, 9600)
                        .open()
                        .expect("Failed to open port");
                }
                ListOfMessageTypes::SerialStop => {
                    started = false;
                    port.close();
                }
                ListOfMessageTypes::SerialSend => port.write(msg.payload),
                ListOfMessageTypes::SerialPort => port_id = msg.payload,
            }
            port.write(&buffer).unwrap();
        }
    }
}

/// Manage messages from the serial port where category is CATEGORY_ELECTRICAL_EVENTS
fn electrical_events_handler(message: Message) -> Vec<Message> {
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
fn engine_events_handler(message: Message) -> Vec<Message> {
    let responses: Vec<Message> = Vec::new();
    let response = Message {
        category: CATEGORY_ENGINE_EVENTS,
        component: message.component,
        action: match message.action {
            EVENT_GENERAL_OFF => STATUS_GENERAL_OFF,
            EVENT_GENERAL_ON => STATUS_GENERAL_ON,
            _ => STATUS_GENERAL_ERROR,
        },
    };
    responses
}

/// Manage messages from the serial port where category is CATEGORY_AUTOPILOT_EVENTS
fn autopilot_events_handler(message: Message) -> Vec<Message> {
    let responses: Vec<Message> = Vec::new();
    responses
}

/// Manage messages from the serial port where category is CATEGORY_G1000_PFD_EVENTS or CATEGORY_G1000_MFD_EVENTS
fn g1000_events_handler(message: Message) -> Vec<Message> {
    let responses: Vec<Message> = Vec::new();
    responses
}

/// Manage messages from the serial port where category is CATEGORY_MISC_EVENTS
fn misc_events_handler(message: Message) -> Vec<Message> {
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
fn radio_nav_events_handler(message: Message) -> Vec<Message> {
    let responses: Vec<Message> = Vec::new();
}
