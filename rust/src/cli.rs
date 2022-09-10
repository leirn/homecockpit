//! CLI to interact with application

use std::io::stdin;
use std::process;

use crate::channel_mgt::*;
use regex::Regex;
use std::sync::mpsc::Sender;

/// List of available commands
const COMMAND_QUIT: &str = "quit";
const COMMAND_START: &str = "start";
const COMMAND_STOP: &str = "stop";
const COMMAND_LIST_SERIAL_PORTS: &str = "list_serial_ports";
const COMMAND_SET_PORT: &str = "set_port";
const COMMAND_SEND_MESSAGE: &str = "send_message";
const COMMAND_HELP: &str = "help";

/// Main CLI function
pub fn cli(tx_to_arduino: Sender<ChannelMessage>) {
    loop {
        let mut raw_command = String::new();
        println!("Enter command :");
        stdin().read_line(&mut raw_command).unwrap();
        let command = raw_command.trim();
        if command.eq(COMMAND_START) {
            tx_to_arduino
                .send(ChannelMessage {
                    message_type: ListOfMessageTypes::SerialStart,
                    payload: String::new(),
                    payload_int: 1,
                })
                .unwrap();
        } else if command.eq(COMMAND_STOP) {
            tx_to_arduino
                .send(ChannelMessage {
                    message_type: ListOfMessageTypes::SerialStop,
                    payload: String::new(),
                    payload_int: 1,
                })
                .unwrap();
        } else if command.eq(COMMAND_SET_PORT) {
            println!("What serial port do you want to use ?");
            let mut port = String::new();
            stdin().read_line(&mut port).unwrap();
            tx_to_arduino
                .send(ChannelMessage {
                    message_type: ListOfMessageTypes::SerialPort,
                    payload: String::from(port.trim()),
                    payload_int: 0,
                })
                .unwrap();
        } else if command.eq(COMMAND_SEND_MESSAGE) {
            println!("Enter the message you want to send in hexadecimal format : 0xabcd");
            let mut msg_code = String::new();
            stdin().read_line(&mut msg_code).unwrap();
            let trimmed = msg_code.trim();
            let re = Regex::new(r"^\0x[0-9a-fA-F]{4}$").unwrap();
            if re.is_match(trimmed) {
                match <u32>::from_str_radix(trimmed.strip_prefix("0x").unwrap(), 16) {
                    Ok(i) => {
                        let mut buffer: [u8; 2] = [0, 0];
                        buffer[0] = (i >> 8) as u8;
                        buffer[1] = (i & 0xff) as u8;
                        tx_to_arduino
                            .send(ChannelMessage {
                                message_type: ListOfMessageTypes::SerialSend,
                                payload: String::new(),
                                payload_int: i,
                            })
                            .unwrap();
                    }
                    Err(..) => println!("The format wasn't respected: {}", trimmed),
                }
            };
        } else if command.eq(COMMAND_LIST_SERIAL_PORTS) {
            list_serial_ports();
        } else if command.eq(COMMAND_HELP) {
            print_help();
        } else if command.eq(COMMAND_QUIT) {
            quit_app();
        } else {
            println!("Unknow command {}", command);
            print_help();
        }
    }
}

/// List serial port
fn list_serial_ports() {
    println!("Listing serial port on computer");
    let ports = serialport::available_ports().expect("Failed to list serial ports");

    for port in ports {
        println!("Port name : {}", port.port_name);
    }
}

/// Display CLI help
fn print_help() {
    println!("Available commands:");
    println!("    help : print this help text");
    println!("    start : start listening to serial port");
    println!("    stop : stop listening to serial port");
    println!("    list_serial_ports : display a list of serial ports on this computer");
    println!("    set_port : ask for the serial port to use");
    println!("    send_message : ask for a specific command to send. For debugging only");
    println!("    quit : quit application");
}

/// Exit application
fn quit_app() {
    println!("Bye bye");
    process::exit(0);
}
