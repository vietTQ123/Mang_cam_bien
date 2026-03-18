#ifndef delays_h
#define delays_h

#include "define.h"      

// Khoi tao Timer2 de su dung cho delay
void Timer2_Init(void);

// Tao delay 1 mili giay
void Delay1Ms(void);

// Tao delay voi so mili giay duoc chi dinh
void delay_ms(uint32_t u32DelayInMs);

#endif
