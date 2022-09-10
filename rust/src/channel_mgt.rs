//! Inter thread protocol

pub struct ChannelMessage {
    pub message_type: ListOfMessageTypes,
    pub payload: String,
    pub payload_int: u32,
}

pub enum ListOfMessageTypes {
    SerialStart,
    SerialStop,
    SerialSend,
    SerialPort,
}