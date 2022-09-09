//! CLI to interact with application

use std::io::stdin;
use std::process;

use crate::channel_mgt::*;

/// List of available commands
enum Commands {
    Quit: String::from("quit"),
    Start: String::from("start"),
    Stop: String::from("stop"),
    ListPorts: String::from("list_serial_ports"),
    SetPort: String::from("set_port"),
    SendMessage: String::from("send_message"),
    Help: String::from("help"),
}

/// Main CLI function
pub fn cli(Sender<T> tx_to_arduino) {
    loop {
        let mut command = String::new();
        println!("Enter command :");
        stdin().read_line(&mut line).unwrap();
        match line {
            Commands::Start => tx_to_arduino.send(ChannelMessage{
                message_type: ListOfMessageTypes::SerialStart,
                payload: 1,
            }),
            Commands::Stop => tx_to_arduino.send(ChannelMessage{
                message_type: ListOfMessageTypes::SerialStop,
                payload: 1,
            }),
            Commands::SetPort => {
                println!("What serial port do you want to use ?");
                let mut port = String::new();
                stdin().read_line(&mut port).unwrap();
                tx_to_arduino.send(ChannelMessage{
                    message_type: ListOfMessageTypes::SerialPort,
                    payload: port.trim(),
                })
            },
            Commands::SendMessage => {
                println!("Enter the message you want to send in hexadecimal format : 0xabcd");
                let mut msg_code = String::new();
                stdin().read_line(&mut msg_code).unwrap();
                trimmed = msg_code.trim();
                let re = Regex::new(r"^\0x[0-9a-fA-F]{4}$").unwrap();
                if re.is_match(trimmed) {
                    match <T>::from_str_radix(trimmed.strip_prefix("0x").unwrap(), 16).ok() {
                        Ok(i) => {
                            let mut buffer: [u8;2];
                            buffer[0] = (i >> 8) as u8;
                            buffer[1] = (i & 0xff) as u8;
                            tx_to_arduino.send(ChannelMessage{
                                message_type: ListOfMessageTypes::SerialSend,
                                payload: buffer,
                            });
                        }
                        Err(..) => println!("The format wasn't respected: {}", trimmed),
                    }
                };
            },
            Commands::ListPorts => list_serial_ports(),
            Commands::Help => print_help(),
            Commands::Quit("quit") => quit_app(),
            _ => {
                println!("Unknow command {}", command);
                print_help();
            },
        }
    }
}

/// List serial port
fn list_serial_ports() {
    let ports = available_ports().expect("Failed to list serial ports");

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
    process::exit(process::ExitCode::SUCCESS);
}