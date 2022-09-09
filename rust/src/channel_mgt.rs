//! Inter thread protocol

pub struct ChannelMessage {
    message_type: ListOfMessageTypes,
    payload: <T>,
}


pub enum ListOfMessageTypes {
    SerialStart,
    SerialStop,
    SerialSend,
    SerialPort,
}