//! Homecockpit server entry file

use serialport::*;
use std::fmt;
use std::thread;

mod protocol;
use crate::protocol::*;
mod serial;
use crate::serial::arduino_communication_handler;

/// Program main function
fn main() {
    println!("Hello, world!");

    // Start thread to handle communication with arduino modules
    let _arduino_thread_handle = thread::spawn(|| arduino_communication_handler());

    // Start CLI
    cli::cli();
}
