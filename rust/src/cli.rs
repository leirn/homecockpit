//! CLI to interact with application

use std::io::stdin;
use std::process;

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
pub fn cli() {
    loop {
        let mut command = String::new();
        println!("Enter command :");
        stdin().read_line(&mut line).unwrap();
        match line {
            Commands::Start => start(),
            Commands::Stop => stop(),
            Commands::SetPort => {
                println!("What serial port do you want to use ?");
                let mut port = String::new();
                stdin().read_line(&mut port).unwrap();
                set_port(port.trim());
            },
            Commands::SendMessage => {
                println!("Enter the message you want to send in hexadecimal format : 0xabcd");
                let mut msg_code = String::new();
                stdin().read_line(&mut msg_code).unwrap();
                trimmed = msg_code.trim();
                match <T>::from_str_radix(trimmed.strip_prefix("0x").unwrap(), 16).ok() {
                    Ok(i) => send_message(i),
                    Err(..) => println!("The format wasn't respected: {}", trimmed),
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

/// Start listening to serial port
fn start() {
    //! To be implemented
}

/// Start listening to serial port
fn stop() {
    //! To be implemented
}

/// Start listening to serial port
fn set_port(&str _port) {
    //! To be implemented
}

/// Start listening to serial port
fn send_message(u16 message) {
    //! To be implemented
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