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
                let port = &command[9..].trim(); // TODO : rework probably necessary
                set_port(port);
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
    println!("    quit : quit application");
}

/// Exit application
fn quit_app() {
    process::exit(process::ExitCode::SUCCESS);
}