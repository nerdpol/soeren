/* THIS FILE IS GENERATED, DO NOT EDIT BY HAND */

#ifndef SOEREN_RADIO_PACKET_H_
#define SOEREN_RADIO_PACKET_H_

#include <stdint.h>

enum {
  PKT_ACCEL = 'A',
  PKT_BATTERY = 'B',
  PKT_GPS = 'G',
  PKT_MAG = 'M',
  PKT_POWER = 'P',
  PKT_QUAT = 'Q',
  PKT_TELEMETRY_RADIO = 'R',
  PKT_STATUS = 'S',
  PKT_ATMOSPHERE = 'T',
  PKT_GYRO = 'Y',
  PKT_HEARTBEAT = 'H',
  PKT_DEBUG = 'D',
  PKT_CONTROL = 'c',
  PKT_LOCK = 'l',
  PKT_PANIC = 'p',
  PKT_CONTROL_RADIO = 'r',
  PKT_SERVOS = 's',
  PKT_TELEMETRY = 't',
  PKT_UNLOCK = 'u',
  PKT_SWITCHES = 'w',
};

union __attribute__((packed)) packet {
  uint8_t tag;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t accel[3];
  } accel;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t t_inside;
    int16_t t_outside;
  } battery;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint32_t latitude;
    uint32_t longitude;
    uint16_t altitude;
    uint8_t links;
    uint16_t yaw;
    uint16_t velocity;
  } gps;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t mag[3];
  } mag;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint16_t voltage;
    int16_t current;
  } power;
  struct __attribute__((packed)) {
    uint8_t tag;
    float quat[4];
  } quat;
  struct __attribute__((packed)) {
    uint8_t tag;
  } telemetry_radio;
  struct __attribute__((packed)) {
    uint8_t tag;
  } status;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t temperature;
    uint16_t pressure;
  } atmosphere;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t gyro[3];
  } gyro;
  struct __attribute__((packed)) {
    uint8_t tag;
    char callsign[12];
    uint8_t id;
    uint8_t hear;
  } heartbeat;
  struct __attribute__((packed)) {
    uint8_t tag;
    char message[16];
  } debug;
  struct __attribute__((packed)) {
    uint8_t tag;
  } control;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint32_t lock;
  } lock;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint8_t payload_ignored;
  } panic;
  struct __attribute__((packed)) {
    uint8_t tag;
  } control_radio;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint8_t servos[8];
  } servos;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint32_t next;
    uint32_t always;
    uint32_t never;
  } telemetry;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint32_t unlock;
  } unlock;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint8_t change_mask;
    uint8_t change_value;
  } switches;
  uint8_t bytes[0];
};

uint32_t radio_packet_size(uint8_t id);

#endif

