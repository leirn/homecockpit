//! Functions to handle simconnect interactions

pub mod enumerations;
pub mod events;
pub mod structures;

use std::sync::mpsc::{Receiver, Sender};
use std::{thread, time};

use crate::channel_mgt::{ChannelMessage, MessageTypes};

/// Main thread function
pub fn run(rx_to_simconnect: Receiver<ChannelMessage>, tx_to_arduino: Sender<ChannelMessage>,) {
    let simconnect_handler = SimConnectHandler::new(tx_to_arduino.clone());

    loop {
        for msg in rx_to_simconnect.try_iter() {
            match msg.message_type {
                MessageTypes::SimStart => {
                    simconnect_handler.start();
                }
                MessageTypes::SimStop => {
                    simconnect_handler.stop();
                }
                MessageTypes::SimSendEvent => {
                    simconnect_handler.SimSendEvent();
                }
                _ => {}
            }
        }
        let one_sec = time::Duration::from_millis(1000);
        thread::sleep(one_sec);
    }
}

struct SimConnectHandler {
    tx_to_arduino: Sender<ChannelMessage>,
}

impl SimConnectHandler {
    /// Constructor
    fn new(
        tx_to_arduino: Sender<ChannelMessage>,
    ) -> SimConnectHandler {
        SimConnectHandler {
            _tx_to_arduino: tx_to_arduino,
        }
    }

    pub fn start(&mut self) {
        println!("Not implemented yet !");
    }

    pub fn stop(&mut self) {
        println!("Not implemented yet !");
    }

    pub fn send_event(&mut self) {
        println!("Not implemented yet !");
    }
}
