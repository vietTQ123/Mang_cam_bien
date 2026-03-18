#ifndef __DHT11__
#define __DHT11__

#include "define.h"

extern uint16_t arrTimeAll[40];
extern uint8_t  arrBitAll[40];

// Khoi tao cam bien DHT11 (thiet lap GPIO, che do ban dau)
void DHT11_Init(void);

// Doc du lieu tu cam bien DHT11
void DHT11_Read(void);

// Lay gia tri nhiet do tu DHT11 (don vi: do C)
uint8_t DHT11_Get_Temperature(void);

// Lay gia tri do am tu DHT11 (don vi: %)
uint8_t DHT11_Get_Humidity(void);


float DHT11_Get_Temperature_Decimal(void);

float DHT11_Get_Humidity_Decimal(void);

#endif
