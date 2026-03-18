#include "delays.h"

void Timer2_Init(void)
{
	// Kich hoat clock cho TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Cau hinh bo dem thoi gian (timer)
	TIM_TimeBaseInitTypeDef timerInit; 

	// Che do dem len
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;

	// Gia tri tran (Period) = 0xFFFF
	timerInit.TIM_Period = 0xFFFF;

	// He so chia (Prescaler) = 72 - 1 (de tao xung 1 MHz neu su dung clock 72 MHz)
	timerInit.TIM_Prescaler = 72 - 1;

	// Clock division (khong su dung)
	timerInit.TIM_ClockDivision = 0;

	// Khoi tao TIM2 voi cac thong so tren
	TIM_TimeBaseInit(TIM2, &timerInit);

	// Kich hoat TIM2
	TIM_Cmd(TIM2, ENABLE);
}

void Delay1Ms(void)
{
	// Dat gia tri dem cua TIM2 ve 0
	TIM_SetCounter(TIM2, 0);

	// Cho den khi bo dem dem du 1000 (ung voi 1 ms voi tan so 1 MHz)
	while (TIM_GetCounter(TIM2) < 1000) 
	{
	}
}

void delay_ms(uint32_t u32DelayInMs)
{
	// Lap lai Delay1Ms() voi so lan tuong ung voi u32DelayInMs
	while (u32DelayInMs) 
	{
		Delay1Ms();
		--u32DelayInMs;
	}
}
