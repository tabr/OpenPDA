#pragma once
uint8_t pgm_read_byte(uint8_t* data)
  {
  return *data;
  }
uint8_t pgm_read_byte(const uint8_t* data)
  {
  return *data;
  }
//#define pgm_read_byte_near
//#define pgm_read_byte_near(x) (uint8_t)(x)
uint8_t pgm_read_byte_near(const char* data)
  {
  return *data;
  }
#define PROGMEM
#define memcpy_P memcpy