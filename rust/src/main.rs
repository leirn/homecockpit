use serialport::*;

fn main() {
    println!("Hello, world!");
    
    let ports = available_ports().expect("Failed to list serial ports");
    
    for port in ports {
        println!("Port name : {}", port.port_name);
    }
    
    let port = serialport::new("COM3", 9600).open().expect("Failed to open port");
    
    while true {
        let mut buffer = [0; 2];
        
        bytes_to_read = port.bytes_to_read()?;
        if (bytes_to_read > 1) {
            port.read_exact(&mut buffer)?;
            
            let message:u16 = buffer[0] as u16 << 8 + buffer[1] as u16;
            
            
        }
    }
}
