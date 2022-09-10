//! Functions to handle simconnect interactions

pub mod enumerations;
pub mod events;
pub mod structures;

use std::sync::mpsc::{Receiver, Sender};
use std::{thread, time};

use crate::channel_mgt::ChannelMessage;

pub struct SimConnectHandler {
    _rx_to_simconnect: Receiver<ChannelMessage>,
    _tx_to_arduino: Sender<ChannelMessage>,
}

impl SimConnectHandler {
    /// Constructor
    pub fn new(
        rx_to_simconnect: Receiver<ChannelMessage>,
        tx_to_arduino: Sender<ChannelMessage>,
    ) -> SimConnectHandler {
        SimConnectHandler {
            _rx_to_simconnect: rx_to_simconnect,
            _tx_to_arduino: tx_to_arduino,
        }
    }

    /// Main thread function
    pub fn run(&mut self) {
        let one_sec = time::Duration::from_millis(1000);
        thread::sleep(one_sec);
    }
}
