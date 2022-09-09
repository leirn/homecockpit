//! Functions to handle simconnect interactions

use std::{thread, time};

struct SimConnectHandler {
    rx_to_simconnect: Receiver<T>,
    tx_to_arduino: Sender<T>,
}

impl SimConnectHandler {
    /// Constructor
    pub fn new(rx_to_simconnect: Receiver<T>, tx_to_arduino: Sender<T>) -> SimConnectHandler {
        SimConnectHandler {
            rx_to_simconnect: rx_to_simconnect,
            tx_to_arduino: tx_to_arduino,
        }
    }

    /// Main thread function
    pub fn run(&mut self) {
        let one_sec = time::Duration::from_millis(1000);
        thread::sleep(one_sec);
    }
}