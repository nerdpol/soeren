# Radio Protocol

The binary protocol used between SOEREN and ground station(s).
The link layer is based on the HC12 radio module operated in the 70cm amateur band by the HC12 UART/Radio modules.
The HC12 includes medium access control and modulation.
Packets begin with a type identifier (one character) that determines their content format and length, and ends with a checksum byte (simple XOR over all bytes BUT the checksum)

## protocol.yaml (JSON representation)

```yaml

accel:
  char: "A"
  fields:
  - {type: "int16_t", name: "accel", length: 3}
battery:
  char: "B"
  fields:
  - {type: "int16_t", name: "t_inside", unit: "1/100 °C"}
  - {type: "int16_t", name: "t_outside", unit: "1/100 °C"}

``` 

example pakets:

{"_type": "accel", "accel0": accel0, "accel1": accel1, "accel2": accel2}

{"_type": "battery", "t_inside": t_inside, "t_outside": t_outside}


## Packet Types (from / to SOEREN, binary encoded)
 
### Telemetry
 - 'A' <ax in (m/s/s) as int16_t> <ay in (m/s/s) as int16_t> <az in (m/s/s) as int16_t>: Accelerometer (linear acceleration)
 - 'B' <t_bat_in in (°C/100) as int16_t> <t_bat_out in (°C/100) as int16_t>: Battery temperature
 - 'F' <switch_state as uint16_t>: Flags
 - 'G' <lat in (°) as float> <lon in (°) as float> <alt in (m) as uint16_t> <links as uint8_t> <yaw in as> <velocity in as>: GPS
 - 'M' <x in as `uint16_t`> <y in as `uint16_t`> <z in as `uint16_t`>: Magnetometer
 - 'P' <v_bat in (mV) as uint16_t> <v_solar in (mV) as uint16_t> <i_system in (mA) as uint16_t>: Power
 - 'Q' <x as float> <y as float> <z as float> <w as float>: Orientation (as quaternion)
 - 'S' <state as uint8_t> <switches as uint16_t>: Status
 - 'T' <t_atm in (°C/100) as int16_t> <p in (Pa) as uint16_t>: Atmosphere
 - 'Y' <d_yaw in (°/s) as int16_t> <d_pitch in (°/s) as int16_t> <d_roll in (°/s) as int16_t>: Gyroscope (angular acceleration)

### Control
 - 'f' <switches_change_mask as uint16_t> <switches_change_value as uint16_t>: Internal switch control
 	`switches_new = (switches_old & ~switches_change_mask) | (switches_change_value & switches_change_mask)`
 	Flags:
 	- `0x0001`: Servos
 	- `0x0002`: Heating
 	- `0x0004`: Camera
 	- `0x0008`: Solar Panels
 - 'r' <baud as uint8_t> <channel as uint8_t> <power as uint8_t>: Radio
 	baud:
 	- `0`: Unchanged
 	- `1`: 2400 Bd
 	- `2`: 9600 Bd
 	- `3`: 34800 Bd
 	- `4`: 115200 Bd
 - 's' <aileron_l as uint8_t> <aileron_r as uint8_t> <rudder as uint8_t> <elevator as uint8_t>: Servos
 	values: 0 to 255 min to max servo positions
 - 't' <telemtry_force as uint16_t> <telemetry_mask as uint16_t> <telemetry_next as uint16_t>: Telemetry flags
 	every telemetry tick: `telemetry_send = telementry_changed & telemetry_mask | telemetry_force | telemetry_next; telemetry_next = 0;` ("mask": never send, "force": always send, "next": send once on next tick, otherwise: send only what changed since last time)
 	- `0x0001`: Accelerometer
 	- `0x0002`: Battery temperature
 	- `0x0004`: Flags
 	- `0x0008`: GPS
 	- `0x0010`: Magnetimeter
 	- `0x0020`: Power
 	- `0x0040`: Orientation
 	- `0x0080`: Status
 	- `0x0100`: Atmosphere
 	- `0x0200`: Gyroscope

### Heartbeat
 - 'H' <callsign as char[12]> <own_id as uint8_t (0 to 7)> <heard_ids as uint8_t>: Heartbeat

### Other
 - 'D' <data as char[16] with terminating nulls>: Debug

# JSON Protocol

The JSON Protocol is used 
{"mag": <[<x:float>,<y:float>,<z:float>]>}
{"gyro": <[<?:float (°/s)>, <?:float (°/s)>, <?:float (°/s)>]}
{"orientation": <quaternion: [<x: float>,<y:float>,<z:float>,<w:float>]>}
{"voltage_bat": <float (V)>}
{"current": <float (A)>}
{"temp_bat_inside": <float (°C)>}
{"temp_bat_out": <float (°C)>}
{"temp_board": <float (°C)>}
{"pressure": <float (Pa)}
{"pressure_front": <float (Pa)>}
{"gps_pos" [<lat: float (rad)>, <lon: float (rad)>, <alt: float (m)>], "gps_links": <int>, "gps_heading": <float (rad)>, "gps_vel": [<vx: float (m/s), <vy: float (m/s)>]}
{"servo_elevator": <float [-1:1]>, "servo_aileron_l": <float [-1:1]>, "servo_aileron_r": <float [-1,1]>, "servo_rudder": <float [-1:1]>}
{"debug": <str>}
{"control": <>}
