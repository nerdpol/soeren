/* THIS FILE IS GENERATED, DO NOT EDIT BY HAND */

#include "protocol.h"

uint32_t radio_packet_size(uint8_t id) {
  switch(id) {
    case PKT_ACCEL: return sizeof(packet.accel);
    case PKT_BATTERY: return sizeof(packet.battery);
    case PKT_GPS: return sizeof(packet.gps);
    case PKT_MAG: return sizeof(packet.mag);
    case PKT_POWER: return sizeof(packet.power);
    case PKT_QUAT: return sizeof(packet.quat);
    case PKT_TELEMETRY_RADIO: return sizeof(packet.telemetry_radio);
    case PKT_STATUS: return sizeof(packet.status);
    case PKT_ATMOSPHERE: return sizeof(packet.atmosphere);
    case PKT_GYRO: return sizeof(packet.gyro);
    case PKT_HEARTBEAT: return sizeof(packet.heartbeat);
    case PKT_DEBUG: return sizeof(packet.debug);
    case PKT_CONTROL: return sizeof(packet.control);
    case PKT_LOCK: return sizeof(packet.lock);
    case PKT_PANIC: return sizeof(packet.panic);
    case PKT_CONTROL_RADIO: return sizeof(packet.control_radio);
    case PKT_SERVOS: return sizeof(packet.servos);
    case PKT_TELEMETRY: return sizeof(packet.telemetry);
    case PKT_UNLOCK: return sizeof(packet.unlock);
    case PKT_SWITCHES: return sizeof(packet.switches);
    default: return 0;
  }
}
