//! Homecockpit server entry file

use std::fmt;
use std::thread;
use serialport::*;

mod protocol;
use crate::protocol::*;

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

/// Program main function
fn main() {
    println!("Hello, world!");


    let serial_thread_handle = thread::spawn(|| {
        // TODO : List port, select port, start, stop listening with channels
        // https://doc.rust-lang.org/rust-by-example/std_misc/channels.html
        // https://doc.rust-lang.org/book/ch16-02-message-passing.html
        let mut port = serialport::new("COM1", 9600)
            .open()
            .expect("Failed to open port");

        loop {
            let mut buffer: [u8; 2] = [0, 0];

            let bytes_to_read = port.bytes_to_read().unwrap();
            if bytes_to_read > 1 {
                port.read_exact(&mut buffer).unwrap();

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
                        Message::null()
                    }
                };

                if reponse.get_message() != 0 {
                    port.write(&reponse.get_bytes_message()).unwrap();
                }
            }
        }
    });

    cli::cli();
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
fn misc_events_handler(message: Message) -> Message {
    Message::null()
}

/// Manage messages from the serial port where category is CATEGORY_RADIO_NAV_EVENTS
fn radio_nav_events_handler(message: Message) -> Message {
    Message::null()
}
