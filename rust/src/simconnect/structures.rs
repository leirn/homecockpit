use crate::enumerations::SIMCONNECT_SIMOBJECT_TYPE;

/// The SIMCONNECT_DATA_FACILITY_AIRPORT pub structure is used to return information
/// on a single airport in the facilities cache.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_FACILITY_AIRPORT {
    Icao: [u8; 9],  // char [9]
    Latitude: f64,  // double
    Longitude: f64, // double
    Altitude: f64,  // double
}

/// The SIMCONNECT_DATA_FACILITY_NDB pub structure is used to return information
/// on a single NDB station in the facilities cache.
/// Supposed to extend SIMCONNECT_DATA_FACILITY_WAYPOINT
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_FACILITY_NDB {
    Icao: [u8; 9],   // char [9]
    Latitude: f64,   // double
    Longitude: f64,  // double
    Altitude: f64,   // double
    fMagVar: f32,    // float
    fFrequency: u32, // DWORD
}

/// The SIMCONNECT_DATA_FACILITY_VOR pub structure is used to return information
///  on a single VOR station in the facilities cache.
/// Supposed to extend SIMCONNECT_DATA_FACILITY_NDB
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_FACILITY_VOR {
    Icao: [u8; 9],         // char [9]
    Latitude: f64,         // double
    Longitude: f64,        // double
    Altitude: f64,         // double
    fMagVar: f32,          // float
    fFrequency: u32,       // DWORD
    Flags: u32,            // DWORD
    fLocalizer: f32,       // float
    GlideLat: f64,         // double
    GlideLon: f64,         // double
    GlideAlt: f64,         // double
    fGlideSlopeAngle: f32, // float
}

/// The SIMCONNECT_DATA_FACILITY_WAYPOINT pub structure used to return information
///  on a single waypoint in the facilities cache.
/// Supposed to extend SIMCONNECT_DATA_FACILITY_AIRPORT
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_FACILITY_WAYPOINT {
    Icao: [u8; 9],  // char [9]
    Latitude: f64,  // double
    Longitude: f64, // double
    Altitude: f64,  // double
    fMagVar: f32,   // float
}

/// The SIMCONNECT_DATA_INITPOSITION pub structure is used to initialize the position
///  of the user aircraft, AI controlled aircraft, or other simulation object.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_INITPOSITION {
    Latitude: f64,  // double
    Longitude: f64, // double
    Altitude: f64,  // double
    Pitch: f64,     // double
    Bank: f64,      // double
    Heading: f64,   // double
    OnGround: u32,  // DWORD
    Airspeed: u32,  // DWORD
}

/// The SIMCONNECT_DATA_LATLONALT pub structure is used to hold a world position.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_LATLONALT {
    Latitude: f64,  // double
    Longitude: f64, // double
    Altitude: f64,  // double
}

/// The SIMCONNECT_DATA_MARKERSTATE pub structure is used to help graphically
/// link flight model data with the graphics model.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_MARKERSTATE {
    szMarkerName: [u8; 64], // char [64]
    dwMarkerState: u32,     // DWORD
}

/// The SIMCONNECT_DATA_MARKERSTATE pub structure is used to help graphically
/// link flight model data with the graphics model.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_WAYPOINT {
    Latitude: f64,        // double
    Longitude: f64,       // double
    Altitude: f64,        // double
    Flags: u64,           // unsigned long
    ktsSpeed: f64,        // double
    percentThrottle: f64, // double
}
/// The SIMCONNECT_DATA_XYZ pub structure is used to hold a 3D co-ordinate.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_DATA_XYZ {
    x: f64, // double
    y: f64, // double
    z: f64, // double
}

/// The SIMCONNECT_DATATYPE enumeration type is used with the
/// SimConnect_AddToDataDefinition call to specify the data type that the
/// server should use to return the specified data to the client.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV {
    dwSize: u32,    // DWORD
    dwVersion: u32, // DWORD
    dwID: u32,      // DWORD
}

/// The SIMCONNECT_RECV_AIRPORT_LIST pub structure is used to return a list
/// of SIMCONNECT_DATA_FACILITY_AIRPORT pub structures.
/// Supposed to extend SIMCONNECT_RECV_FACILITIES_LIST
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_AIRPORT_LIST {
    dwSize: u32,                                   // DWORD
    dwVersion: u32,                                // DWORD
    dwID: u32,                                     // DWORD
    dwRequestID: u32,                              // DWORD
    dwArraySize: u32,                              // DWORD
    dwREntry: u32,                                 // DWORD
    dwOutOf: u32,                                  // DWORD
    rgData: [SIMCONNECT_DATA_FACILITY_AIRPORT; 1], // SIMCONNECT_DATA_FACILITY_AIRPORT [1]
}

/// The SIMCONNECT_RECV_ASSIGNED_OBJECT_ID pub structure is used to return
/// an object ID that matches a request ID.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_ASSIGNED_OBJECT_ID {
    dwSize: u32,      // DWORD
    dwVersion: u32,   // DWORD
    dwID: u32,        // DWORD
    dwRequestID: u32, // DWORD
    dwObjectID: u32,  // DWORD
}

/// The SIMCONNECT_RECV_CLIENT_DATA pub structure will be received by the client
/// after a successful call to SimConnect_RequestClientData. It is an identical
/// pub structure to SIMCONNECT_RECV_SIMOBJECT_DATA.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_CLIENT_DATA {
    dwSize: u32,        // DWORD
    dwVersion: u32,     // DWORD
    dwID: u32,          // DWORD
    dwRequestID: u32,   // DWORD
    dwObjectID: u32,    // DWORD
    dwDefineID: u32,    // DWORD
    dwFlags: u32,       // DWORD
    dwentrynumber: u32, // DWORD
    dwoutof: u32,       // DWORD
    dwDefineCount: u32, // DWORD
    dwData: u32,        // DWORD
}

/// The SIMCONNECT_RECV_EVENT pub structure is used to return an event ID to the client.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_EVENT {
    dwSize: u32,    // DWORD
    dwVersion: u32, // DWORD
    dwID: u32,      // DWORD
    uGroupID: u32,  // DWORD
    uEventID: u32,  // DWORD
    dwData: u32,    // DWORD
}

/// The SIMCONNECT_RECV_EVENT_FILENAME pub structure is used to return a filename and
/// an event ID to the client.
/// Supposed to extend SIMCONNECT_RECV_EVENT
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_EVENT_FILENAME {
    dwSize: u32,           // DWORD
    dwVersion: u32,        // DWORD
    dwID: u32,             // DWORD
    uGroupID: u32,         // DWORD
    uEventID: u32,         // DWORD
    dwData: u32,           // DWORD
    szFileName: [u8; 256], // char [MAX_PATH]
    dwFlags: u32,          // DWORD
}

/// The SIMCONNECT_RECV_EVENT_FRAME pub structure is used with the
/// SimConnect_SubscribeToSystemEvent call to return the frame rate and simulation
/// speed to the client.
/// Supposed to extend SIMCONNECT_RECV_EVENT
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_EVENT_FRAME {
    dwSize: u32,     // DWORD
    dwVersion: u32,  // DWORD
    dwID: u32,       // DWORD
    uGroupID: u32,   // DWORD
    uEventID: u32,   // DWORD
    dwData: u32,     // DWORD
    fFrameRate: f32, // float
    fSimSpeed: f32,  // float
}

/// The SIMCONNECT_RECV_EVENT_OBJECT_ADDREMOVE pub structure is used to return the type
/// and ID of an AI object that has been added or removed from the simulation, by any client.
/// Supposed to extend SIMCONNECT_RECV_EVENT
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_EVENT_OBJECT_ADDREMOVE {
    dwSize: u32,                                              // DWORD
    dwVersion: u32,                                           // DWORD
    dwID: u32,                                                // DWORD
    uGroupID: u32,                                            // DWORD
    uEventID: u32,                                            // DWORD
    dwData: u32,                                              // DWORD
    eObjType: SIMCONNECT_SIMOBJECT_TYPE, // SIMCONNECT_SIMOBJECT_TYPE
}

/// The SIMCONNECT_RECV_EXCEPTION pub structure is used with the SIMCONNECT_EXCEPTION
/// enumeration type to return information on an error that has occurred.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_EXCEPTION {
    dwSize: u32,      // DWORD
    dwVersion: u32,   // DWORD
    dwID: u32,        // DWORD
    dwException: u32, // DWORD
    dwSendID: u32,    // DWORD
    dwIndex: u32,     // DWORD
}

/// The SIMCONNECT_RECV_FACILITIES_LIST pub structure is used to provide information on the number
/// of elements in a list of facilities returned to the client, and the number of packets
/// that were used to transmit the data.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_FACILITIES_LIST {
    dwSize: u32,      // DWORD
    dwVersion: u32,   // DWORD
    dwID: u32,        // DWORD
    dwRequestID: u32, // DWORD
    dwArraySize: u32, // DWORD
    dwREntry: u32,    // DWORD
    dwOutOf: u32,     // DWORD
}

/// The SIMCONNECT_RECV_NDB_LIST pub structure is used to return a list of SIMCONNECT_DATA_FACILITY_NDB
/// pub structures.
/// Supposed to extend SIMCONNECT_RECV_FACILITES_LIST
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_NDB_LIST {
    dwSize: u32,                               // DWORD
    dwVersion: u32,                            // DWORD
    dwID: u32,                                 // DWORD
    dwRequestID: u32,                          // DWORD
    dwArraySize: u32,                          // DWORD
    dwREntry: u32,                             // DWORD
    dwOutOf: u32,                              // DWORD
    rgData: [SIMCONNECT_DATA_FACILITY_NDB; 1], // SIMCONNECT_DATA_FACILITY_NDB[1]
}

/// The SIMCONNECT_RECV_OPEN pub structure is used to return information to the client, after a
/// successful call to SimConnect_Open.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_OPEN {
    dwSize: u32,                    // DWORD
    dwVersion: u32,                 // DWORD
    dwID: u32,                      // DWORD
    szApplicationName: [u8; 256],   // char [256]
    dwApplicationVersionMajor: u32, // DWORD
    dwApplicationVersionMinor: u32, // DWORD
    dwApplicationBuildMajor: u32,   // DWORD
    dwApplicationBuildMinor: u32,   // DWORD
    dwSimConnectVersionMajor: u32,  // DWORD
    dwSimConnectVersionMinor: u32,  // DWORD
    dwSimConnectBuildMajor: u32,    // DWORD
    dwSimConnectBuildMinor: u32,    // DWORD
    dwReserved1: u32,               // DWORD
    dwReserved2: u32,               // DWORD
}

/// The SIMCONNECT_RECV_QUIT is an identical pub structure to the SIMCONNECT_RECV pub structure.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_QUIT {
    dwSize: u32,    // DWORD
    dwVersion: u32, // DWORD
    dwID: u32,      // DWORD
}

/// The SIMCONNECT_RECV_RESERVED_KEY pub structure is used with the
/// SimConnect_RequestReservedKey function to return the reserved key combination.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_RESERVED_KEY {
    dwSize: u32,                // DWORD
    dwVersion: u32,             // DWORD
    dwID: u32,                  // DWORD
    szChoiceReserved: [u8; 30], // char [30]
    szReservedKey: [u8; 50],    // char [50]
}

/// The SIMCONNECT_RECV_SIMOBJECT_DATA pub structure will be received by the client
/// after a successful call to SimConnect_RequestDataOnSimObject or
/// SimConnect_RequestDataOnSimObjectType.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_SIMOBJECT_DATA {
    dwSize: u32,        // DWORD
    dwVersion: u32,     // DWORD
    dwID: u32,          // DWORD
    dwRequestID: u32,   // DWORD
    dwObjectID: u32,    // DWORD
    dwDefineID: u32,    // DWORD
    dwFlags: u32,       // DWORD
    dwentrynumber: u32, // DWORD
    dwoutof: u32,       // DWORD
    dwDefineCount: u32, // DWORD
    dwData: u32,        // DWORD
}

/// The SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE pub structure will be received by the
/// client after a successful call to SimConnect_RequestDataOnSimObjectType. It
/// is an identical pub structure to SIMCONNECT_RECV_SIMOBJECT_DATA.
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE {
    dwSize: u32,        // DWORD
    dwVersion: u32,     // DWORD
    dwID: u32,          // DWORD
    dwRequestID: u32,   // DWORD
    dwObjectID: u32,    // DWORD
    dwDefineID: u32,    // DWORD
    dwFlags: u32,       // DWORD
    dwentrynumber: u32, // DWORD
    dwoutof: u32,       // DWORD
    dwDefineCount: u32, // DWORD
    dwData: u32,        // DWORD
}

/// The SIMCONNECT_RECV_SYSTEM_STATE pub structure is used with the
/// SimConnect_RequestSystemState function to retrieve specific Microsoft Flight
/// Simulator systems states and information.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_SYSTEM_STATE {
    dwSize: u32,         // DWORD
    dwVersion: u32,      // DWORD
    dwID: u32,           // DWORD
    dwRequestID: u32,    // DWORD
    dwInteger: u32,      // DWORD
    fFloat: f32,         // float
    szString: [u8; 256], // char [MAX_PATH]
}

/// The SIMCONNECT_RECV_VOR_LIST pub structure is used to return a list of
/// SIMCONNECT_DATA_FACILITY_VOR pub structures.
/// Supposed to extend SIMCONNECT_RECV
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_VOR_LIST {
    dwSize: u32,         // DWORD
    dwVersion: u32,      // DWORD
    dwID: u32,           // DWORD
    dwRequestID: u32,    // DWORD
    dwInteger: u32,      // DWORD
    fFloat: f32,         // float
    szString: [u8; 256], // char [MAX_PATH]
}

/// The SIMCONNECT_RECV_WAYPOINT_LIST pub structure is used to return a list of
/// SIMCONNECT_DATA_FACILITY_WAYPOINT pub structures.
/// Supposed to extend SIMCONNECT_RECV_FACILITIES_LIST
#[repr(C)]
#[allow(non_snake_case)]
pub struct SIMCONNECT_RECV_WAYPOINT_LIST {
    dwSize: u32,                                    // DWORD
    dwVersion: u32,                                 // DWORD
    dwID: u32,                                      // DWORD
    dwRequestID: u32,                               // DWORD
    dwArraySize: u32,                               // DWORD
    dwREntry: u32,                                  // DWORD
    dwOutOf: u32,                                   // DWORD
    rgData: [SIMCONNECT_DATA_FACILITY_WAYPOINT; 1], //SIMCONNECT_DATA_FACILITY_WAYPOINT [1]
}
