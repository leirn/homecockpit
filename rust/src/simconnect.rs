//! Functions to handle simconnect interactions

use std::{thread, time};

/// Main thread function
pub fn simconnect_handler(rx_to_simconnect: Receiver<T>, tx_to_arduino: Sender<T>) {
    let one_sec = time::Duration::from_millis(1000);
    thread::sleep(one_sec);
}