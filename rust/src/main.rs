//! Homecockpit server entry file

use serialport::*;

mod protocol;
use protocol::*;

/// Message class
/// This class represents messages used on the serial connection
/// between the computer and the master Arduino module
struct Message {
    category: u8,
    component: u8,
    action: u8,
}

impl message {
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
        Message {
            category: category,
            component: component,
            action: action,
        }
    }

    /// Retrieve the two bytes representing the message
    pub fn get_bytes_message(&self) -> [u8; 2] {
        let buffer = [0: u8; 2];
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

impl fmt::Display for User {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.get_message())
    }
}

/// Program main function
fn main() {
    println!("Hello, world!");

    let ports = available_ports().expect("Failed to list serial ports");

    for port in ports {
        println!("Port name : {}", port.port_name);
    }

    let port = serialport::new("COM3", 9600)
        .open()
        .expect("Failed to open port");

    while true {
        let mut buffer = [0: u8; 2];

        bytes_to_read = port.bytes_to_read()?;
        if (bytes_to_read > 1) {
            port.read_exact(&mut buffer)?;

            let message = Message::new(buffer);

            println!("Message received : {}", message);

            let reponse = match message.category {
                CATEGORY_ELECTRICAL_EVENTS => electrical_events_handler(message),
                CATEGORY_ENGINE_EVENTS => engine_events_handler(message),
                CATEGORY_AUTOPILOT_EVENTS => autopilot_events_handler(message),
                CATEGORY_G1000_PFD_EVENTS => g1000_events_handler(message),
                CATEGORY_G1000_MFD_EVENTS => g1000_events_handler(message),
                CATEGORY_MISC_EVENTS => misc_events_handler(message),
                CATEGORY_RADIO_NAV_EVENTS => radio_nav_events_handler(message),
                _ => {
                    println!("Unrecognized category for message {}", message);
                    0
                }
            };

            if (reponse.get_message() != 0) {
                port.write(reponse.get_bytes_message());
            }
        }
    }
}

/// Manage messages from the serial port where category is CATEGORY_ELECTRICAL_EVENTS
fn electrical_events_handler(message: Message) -> Message {
    let mut response = Message::null();
    response.category = message.category;
    response.component = message.component;
    response.action = match message.action {
        EVENT_GENERAL_OFF => STATUS_GENERAL_OFF,
        EVENT_GENERAL_ON => STATUS_GENERAL_ON,
        _ => STATUS_GENERAL_ERROR,
    };
    response
}

/// Manage messages from the serial port where category is CATEGORY_ENGINE_EVENTS
fn engine_events_handler(message: Message) -> Message {
    Message::null()
}

/// Manage messages from the serial port where category is CATEGORY_AUTOPILOT_EVENTS
fn autopilot_events_handler(message: Message) -> Message {
    Message::null()
}

/// Manage messages from the serial port where category is CATEGORY_G1000_PFD_EVENTS or CATEGORY_G1000_MFD_EVENTS
fn g1000_events_handler(message: Message) -> Message {
    Message::null()
}

/// Manage messages from the serial port where category is CATEGORY_MISC_EVENTS
fn misc_events_handler(message: u16) -> u16 {
    Message::null()
}

/// Manage messages from the serial port where category is CATEGORY_RADIO_NAV_EVENTS
fn radio_nav_events_handler(message: u16) -> u16 {
    Message::null()
}
