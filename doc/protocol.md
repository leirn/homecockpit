# Exchange protocol between arduino modules, PC middleware and SimConnect

## Serial exchange procotol

Exchange is mode of 2-byte messages

0baaaabbbbbbbbcccc:
- aaaa : event category
- bbbbbbbb : component
- cccc : action

A *Event* message goes from Arduino to the PC, a *Status* message goes the other way around.

## List of categories

| Value  | Category          |
|--------|-------------------|
| 0b0001 | Electrical events |
| 0b0010 | Engine events     |
| 0b0011 | Autopilot events  |
| 0b0100 | G1000 PFD events  |
| 0b0101 | G1000 MFD events  |
| 0b0110 | Misc events       |
| 0b0111 | Radio/Nav events  |


## List of Electrical events

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description            | SimConnect         |
|--------|--------|------------|--------|------------------------|--------------------|
| Event  | 0x1011 | 0b00000001 | 0b0001 | BCN Light set to On    | BEACON_LIGHTS_ON   |
| Status | 0x1013 | 0b00000001 | 0b0011 | BCN Light is On        | LIGHT BEACON       |
| Event  | 0x1010 | 0b00000001 | 0b0000 | BCN Light set to Off   | BEACON_LIGHTS_OFF  |
| Status | 0x1012 | 0b00000001 | 0b0010 | BCN Light is Off       | LIGHT BEACON       |
| Event  | 0x1021 | 0b00000010 | 0b0001 | LAND Light set to On   | LANDING_LIGHTS_ON  |
| Status | 0x1023 | 0b00000010 | 0b0011 | LAND Light is On       | LIGHT LANDING      |
| Event  | 0x1020 | 0b00000010 | 0b0000 | LAND Light set to Off  | LANDING_LIGHTS_OFF |
| Status | 0x1022 | 0b00000010 | 0b0010 | LAND Light is Off      | LIGHT LANDING      |
| Event  | 0x1031 | 0b00000011 | 0b0001 | TAXI Light set to On   | TAXI_LIGHTS_ON     |
| Status | 0x1033 | 0b00000011 | 0b0011 | TAXI Light is On       | LIGHT TAXI         |
| Event  | 0x1030 | 0b00000011 | 0b0000 | TAXI Light set to Off  | TAXI_LIGHTS_OFF    |
| Status | 0x1032 | 0b00000011 | 0b0010 | TAXI Light is Off      | LIGHT TAXI         |
| Event  | 0x1041 | 0b00000100 | 0b0001 | NAV Light set to On    | NAV_LIGHTS_ON      |
| Status | 0x1043 | 0b00000100 | 0b0011 | NAV Light is On        | LIGHT NAV          |
| Event  | 0x1040 | 0b00000100 | 0b0000 | NAV Light set to Off   | NAV_LIGHTS_OFF     |
| Status | 0x1042 | 0b00000100 | 0b0010 | NAV Light is Off       | LIGHT NAV          |
| Event  | 0x1051 | 0b00000101 | 0b0001 | STRB Light set to On   | STROBES_ON         |
| Status | 0x1053 | 0b00000101 | 0b0011 | STRB Light is On       | LIGHT STROBE       |
| Event  | 0x1050 | 0b00000101 | 0b0000 | STRB Light set to Off  | STROBES_OFF        |
| Status | 0x1052 | 0b00000101 | 0b0010 | STRB Light is Off      | LIGHT STROBE       |


## List of Engine events

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description            | SimConnect                 |
|--------|--------|------------|--------|------------------------|----------------------------|
| Event  | 0x2011 | 0b00000001 | 0b0001 | Left Pump set to On    | FUELSYSTEM_PUMP_ON         |
| Status | 0x2013 | 0b00000001 | 0b0011 | Left Pump is On        | GENERAL ENG FUEL PUMP ON:0 |
| Event  | 0x2010 | 0b00000001 | 0b0000 | Left Pump set to Off   | FUELSYSTEM_PUMP_OFF        |
| Status | 0x2012 | 0b00000001 | 0b0010 | Left Pump is Off       | GENERAL ENG FUEL PUMP ON:0 |
| Event  | 0x2021 | 0b00000010 | 0b0001 | Right Pump set to On   | FUELSYSTEM_PUMP_ON         |
| Status | 0x2023 | 0b00000010 | 0b0011 | Right Pump is On       | GENERAL ENG FUEL PUMP ON:1 |
| Event  | 0x2020 | 0b00000010 | 0b0000 | Right Pump set to Off  | FUELSYSTEM_PUMP_OFF        |
| Status | 0x2022 | 0b00000010 | 0b0010 | Right Pump is Off      | GENERAL ENG FUEL PUMP ON:1 |
| Event  | 0x2031 | 0b00000011 | 0b0001 | Anti Ice set to On     | ANTI_ICE_ON                |
| Status | 0x2033 | 0b00000011 | 0b0011 | Anti Ice is On         | PANEL ANTI ICE SWITCH      |
| Event  | 0x2030 | 0b00000011 | 0b0000 | Anti Ice set to Off    | ANTI_ICE_OFF               |
| Status | 0x2032 | 0b00000011 | 0b0010 | Anti Ice is Off        | PANEL ANTI ICE SWITCH      |


## List of Autopilot events

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description            | SimConnect             |
|--------|--------|------------|--------|------------------------|------------------------|
| Event  | 0x3011 | 0b00000001 | 0b0001 | Toggle AP Master       | AP_MASTER              |
| Event  | 0x3021 | 0b00000010 | 0b0001 | Toggle Flight Dir      | TOGGLE_FLIGHT_DIRECTOR |
| Event  | 0x3031 | 0b00000011 | 0b0001 | Toggle Yaw Dampler     | YAW_DAMPER_TOGGLE      |
| Event  | 0x3041 | 0b00000100 | 0b0001 | Toggle IAS             | AP_PANEL_SPEED_HOLD    |
| Event  | 0x3051 | 0b00000101 | 0b0001 | Toggle Heading         | AP_PANEL_HEADING_HOLD  |
| Event  | 0x3061 | 0b00000110 | 0b0001 | Toggle Altitude        | AP_PANEL_ALTITUDE_HOLD |
| Event  | 0x3071 | 0b00000111 | 0b0001 | Toggle Nav mode        | AP_NAV1_HOLD           |
| Event  | 0x3081 | 0b00001000 | 0b0001 | Toggle VNV mode        |                        |
| Event  | 0x3091 | 0b00001001 | 0b0001 | Toggle Approach        | AP_APR_HOLD            |
| Event  | 0x30a1 | 0b00001010 | 0b0001 | Toggle Back course     | AP_BC_HOLD             |
| Event  | 0x30b1 | 0b00001011 | 0b0001 | Toggle VS mode         | AP_PANEL_VS_HOLD       |
| Event  | 0x30c1 | 0b00001100 | 0b0001 | Toggle VS Up           | AP_VS_VAR_INC          |
| Event  | 0x30d1 | 0b00001101 | 0b0001 | Toggle VS Down         | AP_VS_VAR_DEC          |
| Event  | 0x311x | 0b00010001 | 0bxxxx | Decrease HDG bug by x     | HEADING_BUG_DEC        |
| Event  | 0x311x | 0b00010001 | 0bxxxx | Increase HDG bug by x     | HEADING_BUG_INC        |
| Event  | 0x311f | 0b00010001 | 0b1111 | Set HDG bug to cur. HDG   | HEADING_BUG_SET        |
| Event  | 0x312x | 0b00010010 | 0bxxxx | Decrease CRS bug by x     | VOR1_OBI_INC, VOR1_OBI_FAST_INC |
| Event  | 0x312x | 0b00010010 | 0bxxxx | Increase CRS bug by x     | VOR1_OBI_DEC, VOR1_OBI_FAST_DEC |
| Event  | 0x312f | 0b00010001 | 0b1111 | Set CRS bug to cur. HDG   | VOR1_OBI_SET           |
| Event  | 0x3131 | 0b00010011 | 0b0001 | Decrease ALT bug by 100   | AP_ALT_VAR_DEC         |
| Event  | 0x3135 | 0b00010011 | 0b0101 | Increase ALT bug by 100   | AP_ALT_VAR_INC         |
| Event  | 0x3132 | 0b00010011 | 0b0010 | Decrease ALT bug by 1000  | AP_ALT_VAR_DEC         |
| Event  | 0x3136 | 0b00010011 | 0b0110 | Increase ALT bug by 1000  | AP_ALT_VAR_INC         |


## List of G1000 PFD events

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description            | SimConnect             |
|--------|--------|------------|--------|------------------------|------------------------|
| Event  | 0x4011 | 0b00000001 | 0b0001 | softkey 1              | G1000_PFD_SOFTKEY1     |
| Event  | 0x4021 | 0b00000010 | 0b0001 | softkey 2              | G1000_PFD_SOFTKEY2     |
| Event  | 0x4031 | 0b00000011 | 0b0001 | softkey 3              | G1000_PFD_SOFTKEY3     |
| Event  | 0x4041 | 0b00000100 | 0b0001 | softkey 4              | G1000_PFD_SOFTKEY4     |
| Event  | 0x4051 | 0b00000101 | 0b0001 | softkey 5              | G1000_PFD_SOFTKEY5     |
| Event  | 0x4061 | 0b00000110 | 0b0001 | softkey 6              | G1000_PFD_SOFTKEY6     |
| Event  | 0x4071 | 0b00000111 | 0b0001 | softkey 7              | G1000_PFD_SOFTKEY7     |
| Event  | 0x4081 | 0b00001000 | 0b0001 | softkey 8              | G1000_PFD_SOFTKEY8     |
| Event  | 0x4091 | 0b00001001 | 0b0001 | softkey 9              | G1000_PFD_SOFTKEY9     |
| Event  | 0x40a1 | 0b00001010 | 0b0001 | softkey 10             | G1000_PFD_SOFTKEY10    |
| Event  | 0x40b1 | 0b00001011 | 0b0001 | softkey 11             | G1000_PFD_SOFTKEY11    |
| Event  | 0x40c1 | 0b00001100 | 0b0001 | softkey 12             | G1000_PFD_SOFTKEY12    |
| Event  | 0x4111 | 0b00010001 | 0b0001 | Clear button           | G1000_PFD_CLEAR_BUTTON      |
| Event  | 0x4121 | 0b00010010 | 0b0001 | ?                      | G1000_PFD_CURSOR_BUTTON     |
| Event  | 0x4131 | 0b00010011 | 0b0001 | Directo To button      | G1000_PFD_DIRECTTO_BUTTON   |
| Event  | 0x4141 | 0b00010100 | 0b0001 | Enter button           | G1000_PFD_ENTER_BUTTON      |
| Event  | 0x4151 | 0b00010101 | 0b0001 | FPL Button             | G1000_PFD_FLIGHTPLAN_BUTTON |
| Event  | 0x4161 | 0b00010110 | 0b0001 | Group knob dec         | G1000_PFD_GROUP_KNOB_DEC    |
| Event  | 0x4171 | 0b00010111 | 0b0001 | Group knob inc         | G1000_PFD_GROUP_KNOB_INC    |
| Event  | 0x4181 | 0b00011000 | 0b0001 | Menu button            | G1000_PFD_MENU_BUTTON       |
| Event  | 0x4191 | 0b00011001 | 0b0001 | Page knob dec          | G1000_PFD_PAGE_KNOB_DEC     |
| Event  | 0x41a1 | 0b00011010 | 0b0001 | Page knob inc          | G1000_PFD_PAGE_KNOB_INC     |
| Event  | 0x41b1 | 0b00011011 | 0b0001 | PROC button            | G1000_PFD_PROCEDURE_BUTTON  |
| Event  | 0x41c1 | 0b00011100 | 0b0001 | Zoom in                | G1000_PFD_ZOOMIN_BUTTON     |
| Event  | 0x41d1 | 0b00011101 | 0b0001 | Zoom out               | G1000_PFD_ZOOMOUT_BUTTON    |


## List of G1000 MFD events

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description            | SimConnect             |
|--------|--------|------------|--------|------------------------|------------------------|
| Event  | 0x5011 | 0b00000001 | 0b0001 | Softkey 1              | G1000_MFD_SOFTKEY1     |
| Event  | 0x5021 | 0b00000010 | 0b0001 | Softkey 2              | G1000_MFD_SOFTKEY2     |
| Event  | 0x5031 | 0b00000011 | 0b0001 | Softkey 3              | G1000_MFD_SOFTKEY3     |
| Event  | 0x5041 | 0b00000100 | 0b0001 | Softkey 4              | G1000_MFD_SOFTKEY4     |
| Event  | 0x5051 | 0b00000101 | 0b0001 | Softkey 5              | G1000_MFD_SOFTKEY5     |
| Event  | 0x5061 | 0b00000110 | 0b0001 | Softkey 6              | G1000_MFD_SOFTKEY6     |
| Event  | 0x5071 | 0b00000111 | 0b0001 | Softkey 7              | G1000_MFD_SOFTKEY7     |
| Event  | 0x5081 | 0b00001000 | 0b0001 | Softkey 8              | G1000_MFD_SOFTKEY8     |
| Event  | 0x5091 | 0b00001001 | 0b0001 | Softkey 9              | G1000_MFD_SOFTKEY9     |
| Event  | 0x50a1 | 0b00001010 | 0b0001 | Softkey 10             | G1000_MFD_SOFTKEY10    |
| Event  | 0x50b1 | 0b00001011 | 0b0001 | Softkey 11             | G1000_MFD_SOFTKEY11    |
| Event  | 0x50c1 | 0b00001100 | 0b0001 | Softkey 12             | G1000_MFD_SOFTKEY12    |
| Event  | 0x5111 | 0b00010001 | 0b0001 | Clear button           | G1000_MFD_CLEAR_BUTTON      |
| Event  | 0x5121 | 0b00010010 | 0b0001 | ?                      | G1000_MFD_CURSOR_BUTTON     |
| Event  | 0x5131 | 0b00010011 | 0b0001 | Directo To button      | G1000_MFD_DIRECTTO_BUTTON   |
| Event  | 0x5141 | 0b00010100 | 0b0001 | Enter button           | G1000_MFD_ENTER_BUTTON      |
| Event  | 0x5151 | 0b00010101 | 0b0001 | FPL Button             | G1000_MFD_FLIGHTPLAN_BUTTON |
| Event  | 0x5161 | 0b00010110 | 0b0001 | Group knob dec         | G1000_MFD_GROUP_KNOB_DEC    |
| Event  | 0x5171 | 0b00010111 | 0b0001 | Group knob inc         | G1000_MFD_GROUP_KNOB_INC    |
| Event  | 0x5181 | 0b00011000 | 0b0001 | Menu button            | G1000_MFD_MENU_BUTTON       |
| Event  | 0x5191 | 0b00011001 | 0b0001 | Page knob dec          | G1000_MFD_PAGE_KNOB_DEC     |
| Event  | 0x51a1 | 0b00011010 | 0b0001 | Page knob inc          | G1000_MFD_PAGE_KNOB_INC     |
| Event  | 0x51b1 | 0b00011011 | 0b0001 | PROC button            | G1000_MFD_PROCEDURE_BUTTON  |
| Event  | 0x51c1 | 0b00011100 | 0b0001 | Zoom in                | G1000_MFD_ZOOMIN_BUTTON     |
| Event  | 0x51d1 | 0b00011101 | 0b0001 | Zoom out               | G1000_MFD_ZOOMOUT_BUTTON    |


## List of Misc events

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description            | SimConnect          |
|--------|--------|------------|--------|------------------------|---------------------|
| Event  | 0x6011 | 0b00000001 | 0b0001 | Pitot Heat set to On   | PITOT_HEAT_ON       |
| Status | 0x6013 | 0b00000001 | 0b0011 | Pitot Heat is On       | PITOT HEAT          |
| Event  | 0x6010 | 0b00000001 | 0b0000 | Pitot Heat set to Off  | PITOT_HEAT_OFF      |
| Status | 0x6012 | 0b00000001 | 0b0010 | Pitot Heat is Off      | PITOT HEAT          |
| Event  | 0x6021 | 0b00000010 | 0b0001 | Gear set to Down       | GEAR_DOWN           |
| Event  | 0x6020 | 0b00000010 | 0b0000 | Gear set to Up         | GEAR_UP             |
| Status | 0x6032 | 0b00000011 | 0b0010 | Center Gear is Down    | GEAR POSITION:index |
| Status | 0x6031 | 0b00000011 | 0b0001 | Center Gear is Up      | GEAR POSITION:index |
| Status | 0x6030 | 0b00000011 | 0b0011 | Center Gear is Unkw    | GEAR POSITION:index |
| Status | 0x6042 | 0b00000100 | 0b0010 | Left Gear is Down      | GEAR POSITION:index |
| Status | 0x6041 | 0b00000100 | 0b0001 | Left Gear is Up        | GEAR POSITION:index |
| Status | 0x6040 | 0b00000100 | 0b0000 | Left Gear is Unkw      | GEAR POSITION:index |
| Status | 0x6052 | 0b00000101 | 0b0010 | Right Gear is Down     | GEAR POSITION:index |
| Status | 0x6051 | 0b00000101 | 0b0001 | Right Gear is Up       | GEAR POSITION:index |
| Status | 0x6050 | 0b00000101 | 0b0000 | Right Gear is Unkw     | GEAR POSITION:index |
| Event  | 0x6061 | 0b00000110 | 0b0001 | Increment Flaps Pos.   | FLAPS_INCR          |
| Status | 0x606x | 0b00000110 | 0b1xxx | Flaps Handle Pos.      | FLAPS HANDLE INDEX  |
| Event  | 0x6060 | 0b00000110 | 0b0000 | Decrement Flaps Pos.   | FLAPS_DECR          |
| Event  | 0x6071 | 0b00000111 | 0b0001 | Increment alt set.     | KOHLSMAN_DEC        |
| Event  | 0x6072 | 0b00000111 | 0b0010 | Decrement alt set.     | KOHLSMAN_INC        |


## List of Nav/Radio events

Arduino will only knows what button is pressed without any knowledge of the COM/NAV component status.
As a consequence, the server component will need to define whether commands should be sent to COM1/COM2 or NAV1/NAV2

| Type   | Value  | 0bbbbbbbbb | 0bcccc | Description                  | SimConnect           |
|--------|--------|------------|--------|------------------------------|----------------------|
| Event  | 0x7011 | 0b00000001 | 0b0001 | Swap COM1/COM2               | COM_RADIO            |
| Event  | 0x7021 | 0b00000010 | 0b0001 | Swap active frequency        | COMX_RADIO_SWAP      |
| Event  | 0x7031 | 0b00000011 | 0b0001 | Increment active freq. 25kHz | COMX_RADIO_FRACT_DEC |
| Event  | 0x7032 | 0b00000011 | 0b0010 | Decrement active freq. 25kHz | COMX_RADIO_FRACT_INC |
| Event  | 0x7041 | 0b00000011 | 0b0001 | Increment active freq. 1MHz  | COMX_RADIO_WHOLE_DEC |
| Event  | 0x7042 | 0b00000011 | 0b0010 | Decrement active freq. 1MHz  | COMX_RADIO_WHOLE_INC |
| Event  | 0x7111 | 0b00010001 | 0b0001 | Swap NAV1/NAV2               | NAV_RADIO            |
| Event  | 0x7121 | 0b00010010 | 0b0001 | Swap active frequency        | NAVX_RADIO_SWAP      |
| Event  | 0x7131 | 0b00010011 | 0b0001 | Increment active freq. 25kHz | NAVX_RADIO_FRACT_DEC |
| Event  | 0x7132 | 0b00010011 | 0b0010 | Decrement active freq. 25kHz | NAVX_RADIO_FRACT_INC |
| Event  | 0x7141 | 0b00010011 | 0b0001 | Increment active freq. 1MHz  | NAVX_RADIO_WHOLE_DEC |
| Event  | 0x7142 | 0b00010011 | 0b0010 | Decrement active freq. 1MHz  | NAVX_RADIO_WHOLE_INC |

