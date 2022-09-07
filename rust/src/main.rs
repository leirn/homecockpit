use serialport::*;

mod protocol;

struct Message {
    category: u8,
    component: u8,
    action: u8
}

impl message {
    pub fn null() -> Message {
        Message {
            category: 0,
            component: 0,
            action: 0
        }
    }
    
    pub fn new(received_bytes:u8[2]) -> Message {
        let message:u16 = received_bytes[0] as u16 << 8 + received_bytes[1] as u16;
        let category = ((message & MASK_CATEGORY ) >> 12) as u8;
        Message {
            category: category,
            component: component,
            action: action
        }
    }
    
    pub fn get_bytes_message(&self) -> u8[2] {
        let buffer = [0:u8; 2];
        let message = self.get_message();
        buffer[0] = ((message & 0xff00) >> 8) as u8;
        buffer[1] = (message & 0xff) as u8;
        buffer        
    }
    
    pub fn get_message(&self) -> u16 {
        self.category as u16 << 12 + self.component as u16 << 4 + self.action as u16
    }
}

impl fmt::Display for User {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
      write!(f, "{}", self.get_message())
    }
}

fn main() {
    println!("Hello, world!");
    
    let ports = available_ports().expect("Failed to list serial ports");
    
    for port in ports {
        println!("Port name : {}", port.port_name);
    }
    
    let port = serialport::new("COM3", 9600).open().expect("Failed to open port");
    
    while true {
        let mut buffer = [0:u8; 2];
        
        bytes_to_read = port.bytes_to_read()?;
        if (bytes_to_read > 1) {
            port.read_exact(&mut buffer)?;
            
            let message = Messgae::new(buffer);
            
            println!("Message received : {}", message);
            
            let reponse = match message.category {
                CATEGORY_ELECTRICAL_EVENTS => electrical_events_handler(message),
                CATEGORY_ENGINE_EVENTS  => engine_events_handler(message),
                CATEGORY_AUTOPILOT_EVENTS  => autopilot_events_handler(message),
                CATEGORY_G1000_PFD_EVENTS  => g1000_pfd_events_handler(message),
                CATEGORY_G1000_MFD_EVENTS  => g1000_mfd_events_handler(message),
                CATEGORY_MISC_EVENTS  => misc_events_handler(message),
                CATEGORY_RADIO_NAV_EVENTS  => radio_nav_events_handler(message),
                _ => {
                    println!("Unrecognized category for message {}", message);
                    0
                },
            }
            
            if (reponse.get_message() != 0) {
                port.write(reponse.get_bytes_message());
            }
        }
    }
}

fn electrical_events_handler(message: Message) -> Message {
    Message::null()
}

fn engine_events_handler(message: Message) -> Message {v
}

fn autopilot_events_handler(message: Message) -> Message {
    Message::null()
}

fn g1000_pfd_events_handler(message: Message) -> Message {
    Message::null()
}

fn g1000_mfd_events_handler(message: Message) -> Message {
    Message::null()
}

fn misc_events_handler(message: u16) -> u16 {
    Message::null()
}

fn radio_nav_events_handler(message: u16) -> u16 {
    Message::null()
}
