//! Homecockpit server entry file

use std::sync::mpsc;
use std::thread;

mod channel_mgt;
mod cli;
mod protocol;
mod serial;
mod simconnect;
use serial::ArduinoCommunicationHandler;

/// Program main function
fn main() {
    println!("Hello, world!");

    let (tx_to_arduino, rx_to_arduino) = mpsc::channel();
    let (tx_to_simconnect, rx_to_simconnect) = mpsc::channel();

    let tx_to_arduino_from_cli = tx_to_arduino.clone();
    let tx_to_simconnect_from_cli = tx_to_simconnect.clone();
    // Start thread to handle communication with arduino modules
    let _arduino_thread_handle = thread::spawn(|| {
        let mut arduino_handler = ArduinoCommunicationHandler::new(rx_to_arduino, tx_to_simconnect);
        arduino_handler.run();
    });

    // Start thread to handle communication with MSFS via simconnect
    let _simconnect_thread_handle = thread::spawn(|| {
        simconnect::run(rx_to_simconnect, tx_to_arduino);
    });

    // Start CLI
    cli::cli(tx_to_arduino_from_cli, tx_to_simconnect_from_cli);
}
