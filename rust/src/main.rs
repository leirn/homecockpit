//! Homecockpit server entry file

use serialport::*;
use std::fmt;
use std::sync::mpsc;
use std::thread;

mod protocol;
use crate::protocol::*;
mod serial;
use crate::serial::arduino_communication_handler;

/// Program main function
fn main() {
    println!("Hello, world!");

    let (tx_to_arduino, rx_to_arduino) = mpsc::channel();
    let (tx_to_simconnect, rx_to_simconnect) = mpsc::channel();

    let tx_to_arduino_from_cli = tx_to_arduino.clone();
    // Start thread to handle communication with arduino modules
    let _arduino_thread_handle =
        thread::spawn(|| arduino_communication_handler(rx_to_arduino, tx_to_simconnect));

    // Start thread to handle communication with MSFS via simconnect
    let _simconnect_thread_handle =
        thread::spawn(|| simconnect_handler(rx_to_simconnect, tx_to_arduino));

    // Start CLI
    cli::cli(tx_to_arduino_from_cli);
}
