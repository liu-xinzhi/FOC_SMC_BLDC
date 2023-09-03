#ifndef MAGNETICSENSOR_LIB_H
#define MAGNETICSENSOR_LIB_H

#include "stm32f4xx.h"

/******************************************************************************/
uint16_t ReadAS5600(uint8_t x);
uint16_t ReadAS5047P(uint8_t x);
uint16_t ReadTLE5012B(uint8_t x);
uint16_t ReadMA730(uint8_t x);
uint16_t ReadMT6701(uint8_t x);
/******************************************************************************/
#endif
