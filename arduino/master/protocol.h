/**
 * protocol.h
 * Contains all protocol messages
 */

// Engine and systems
// Left Pump
#define EVENT_LPUMP_ON 0x2011
#define EVENT_LPUMP_OFF 0x2010
// Right Pump
#define EVENT_RPUMP_ON 0x2021
#define EVENT_RPUMP_OFF 0x2020
// Carb. heat
#define EVENT_CARB_ON 0x2031
#define EVENT_CARB_OFF 0x2030
// Pitot heat
#define EVENT_PITOT_ON 0x6011
#define EVENT_PITOT_OFF 0x6010
// Anti-ice
#define EVENT_ANTI_ICE_ON 0xffff
#define EVENT_ANTI_ICE_OFF 0xffff

// Lights
// BCN
#define EVENT_BCN_OFF 0x1010
#define EVENT_BCN_ON 0x1011
#define STATUS_BCN_OFF 0x0012
#define STATUS_BCN_ON 0x0013
// LAND
#define EVENT_LAND_OFF 0x1020
#define EVENT_LAND_ON 0x1021
#define STATUS_LAND_OFF 0x0022
#define STATUS_LAND_ON 0x0023
// TAXI
#define EVENT_TAXI_OFF 0x1030
#define EVENT_TAXI_ON 0x1031
#define STATUS_TAXI_OFF 0x0032
#define STATUS_TAXI_ON 0x0033
// NAV
#define EVENT_NAV_OFF 0x1040
#define EVENT_NAV_ON 0x1041
#define STATUS_NAV_OFF 0x0042
#define STATUS_NAV_ON 0x0043
// Strobe
#define EVENT_STRB_OFF 0x1050
#define EVENT_STRB_ON 0x1051
#define STATUS_STRB_OFF 0x0052
#define STATUS_STRB_ON 0x0053

// Landing gear
#define EVENT_LDG_GEAR_UP 0x6020
#define EVENT_LDG_GEAR_DN 0x6021

// Flaps
#define EVENT_FLAPS_INC 0x6061
#define EVENT_FLAPS_DEC 0x6060
