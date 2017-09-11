#ifndef SOEREN_RADIO_PACKET_H_
#define SOEREN_RADIO_PACKET_H_

#include <stdint.h>

enum {
  PKT_MAG = 'M',
  PKT_FLIGHT = 'F',
  PKT_POWER = 'P',
  PKT_ATMOSPHERE = 'T',
  PKT_GPS = 'G',
  PKT_DEBUG = 'D',
  PKT_CONTROL = 'c',
  PKT_REPORT = 'i',
};

union __attribute__((packed)) packet {
  uint8_t tag;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t mag[3];
  } mag;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t gyr[3];
    int16_t acc[3];
  } flight;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint16_t voltage;
    int16_t current;
  } power;
  struct __attribute__((packed)) {
    uint8_t tag;
    int16_t temperature;
    uint16_t pressure;
  } atmosphere;
  struct __attribute__((packed)) {
    uint8_t tag;
    uint8_t control[5];
  } control;
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
    char message[16];
  } debug;
  uint8_t bytes[0];
};

#endif
