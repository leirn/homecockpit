//! Functions to handle simconnect interactions

use std::{thread, time};

/// Main thread function
pub fn simconnect_handler(Receiver<T> rx_to_simconnect, Sender<T> tx_to_arduino) {
    let one_sec = time::Duration::from_millis(1000);
    thread::sleep(one_sec);
}