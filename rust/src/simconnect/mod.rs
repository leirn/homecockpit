//! Functions to handle simconnect interactions

mod bindings;
pub mod enumerations;
pub mod events;
pub mod structures;

use std::ptr::null_mut;
use std::sync::mpsc::{Receiver, Sender};
use std::{thread, time};

use std::ffi::CString;

use crate::channel_mgt::{ChannelMessage, MessageTypes};
use bindings::*;

/// Main thread function
pub fn run(rx_to_simconnect: Receiver<ChannelMessage>, tx_to_arduino: Sender<ChannelMessage>) {
    let mut simconnect_handler = SimConnectHandler::new(tx_to_arduino.clone());

    loop {
        for msg in rx_to_simconnect.try_iter() {
            match msg.message_type {
                MessageTypes::SimStart => {
                    simconnect_handler.start();
                }
                MessageTypes::SimStop => {
                    simconnect_handler.stop();
                }
                MessageTypes::SimSendEvent => {
                    println!("Not connected yet");
                    simconnect_handler.event(msg);
                }
                _ => {}
            }
        }
        simconnect_handler.next();
        let one_sec = time::Duration::from_millis(1000);
        thread::sleep(one_sec);
    }
}

struct SimConnectHandler {
    _tx_to_arduino: Sender<ChannelMessage>,
    running: bool,
    sim_handle: Option<HANDLE>,
}

impl SimConnectHandler {
    /// Constructor
    fn new(tx_to_arduino: Sender<ChannelMessage>) -> SimConnectHandler {
        SimConnectHandler {
            _tx_to_arduino: tx_to_arduino,
            running: false,
            sim_handle: None,
        }
    }

    pub fn start(&mut self) {
        if self.running {
            println!("Already running");
            return;
        }
        let mut sim_connect_ptr: HANDLE = null_mut();
        let name = CString::new("test").unwrap();
        let name: LPCSTR = name.as_ptr();

        match unsafe { SimConnect_Open(&mut sim_connect_ptr, name, null_mut(), 0, null_mut(), 0) } {
            0 => {
                println!("Connection success");
                self.running = true;
            }
            hr => {
                println!("Connection failed due to error 0x{:08x}", hr);
                println!("Connection to sim not running");
                println!("Simulation may not be started");
                self.running = false;
                return;
            }
        }

        self.sim_handle = Some(sim_connect_ptr);

        self.add_event("BEACON_LIGHTS_ON", BEACON_LIGHTS_ON);
        self.add_event("BEACON_LIGHTS_OFF", BEACON_LIGHTS_OFF);

        match unsafe {
            SimConnect_AddClientEventToNotificationGroup(self.sim_handle.unwrap(), 0, 0, 0)
        } {
            0 => {
                println!("SimConnect_AddClientEventToNotificationGroup success");
                self.running = true;
            }
            hr => println!(
                "SimConnect_AddClientEventToNotificationGroup failed due to error 0x{:08x}",
                hr
            ),
        }

        match unsafe {
            SimConnect_SetNotificationGroupPriority(
                sim_connect_ptr,
                0,
                SIMCONNECT_GROUP_PRIORITY_HIGHEST,
            )
        } {
            0 => {
                println!("SimConnect_SetNotificationGroupPriority success");
                self.running = true;
            }
            hr => println!(
                "SimConnect_SetNotificationGroupPriority failed due to error 0x{:08x}",
                hr
            ),
        }

        // Request information to know if sim is running
        let name1 = CString::new("Sim").unwrap();
        let name: bindings::LPCSTR = name1.as_ptr();
        match unsafe { SimConnect_RequestSystemState(self.sim_handle.unwrap(), 0, name) } {
            0 => {
                println!("SimConnect_RequestSystemState success");
                self.running = true;
            }
            hr => println!(
                "SimConnect_RequestSystemState failed due to error 0x{:08x}",
                hr
            ),
        }
    }

    pub fn next(&mut self) {
        if self.running == false || self.sim_handle.is_none() {
            return;
        }

        let mut pp_data = null_mut();
        let mut pcb_data = 0_u32;

        match unsafe {
            SimConnect_GetNextDispatch(self.sim_handle.unwrap(), &mut pp_data, &mut pcb_data)
        } {
            0 => {
                unsafe {
                    let id = (*pp_data).dwID as i32;
                    match id {
                        SIMCONNECT_RECV_ID_SIMCONNECT_RECV_ID_OPEN => {
                            let open_data: &SIMCONNECT_RECV_OPEN = &*(pp_data.cast());
                            let v_major = open_data.dwApplicationVersionMajor;
                            let v_minor = open_data.dwApplicationVersionMinor;
                            println!("Open to version {} {}", v_major, v_minor,)
                        }
                        SIMCONNECT_RECV_ID_SIMCONNECT_RECV_ID_EVENT => {
                            let _evt: &SIMCONNECT_RECV_EVENT = &*(pp_data.cast());
                            // ...use evt
                        }
                        SIMCONNECT_RECV_ID_SIMCONNECT_RECV_ID_SYSTEM_STATE => {
                            let _system_state: &SIMCONNECT_RECV_SYSTEM_STATE = &*(pp_data.cast());
                            //
                        }
                        // ...
                        _ => println!("Unknown SIMCONNECT_RECV type {}", id),
                    }
                }
            }
            _ => {
                // Happens when no message available
                // println!(
                //     "Error while calling SimConnect_GetNextDispatch : 0x{:08x}",
                //     hr
                // );
                //self.running = false;
            }
        }
        thread::sleep(time::Duration::from_millis(10));
    }

    pub fn stop(&mut self) {
        println!("Deconnecting from sim");
        let hr = unsafe { bindings::SimConnect_Close(self.sim_handle.unwrap()) };
        match hr {
            0 => {
                println!("Deconnection success");
            }
            _ => println!("Deconnection failed, status undefined"),
        }
        self.running = false;
        self.sim_handle = None;
    }

    pub fn event(&mut self, _msg: ChannelMessage) {}

    fn add_event(&mut self, event_name: &str, event_id: u32) {
        let event = CString::new(event_name).unwrap();
        let event: LPCSTR = event.as_ptr();
        match unsafe {
            SimConnect_MapClientEventToSimEvent(self.sim_handle.unwrap(), event_id, event)
        } {
            0 => {
                println!("SimConnect_MapClientEventToSimEvent success");
                self.running = true;
            }
            hr => println!(
                "SimConnect_MapClientEventToSimEvent failed due to error 0x{:08x}",
                hr
            ),
        }
    }
}

const BEACON_LIGHTS_ON: u32 = 0;
const BEACON_LIGHTS_OFF: u32 = 1;
