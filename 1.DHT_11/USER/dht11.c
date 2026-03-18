#include "dht11.h"

// Bo dem luu du lieu tu DHT11
uint8_t u8Buff[5] = {0};

uint16_t arrTimeAll[40] = {0};  // Luu thoi gian 40 bit
uint8_t  arrBitAll[40]  = {0};  // Luu gia tri 40 bit
uint8_t  bitIndex = 0;

void DHT11_Init(void)
{
    GPIO_InitTypeDef gpioInit;

    // Cap xung clock cho cong GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Thiet lap chan PB12 lam OUTPUT (che do Open-Drain)
    gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
    gpioInit.GPIO_Pin = GPIO_Pin_12;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpioInit);

    // Keo cao chan PB12
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/**
 * @brief Doc 1 byte du lieu tu DHT11
 * @note Theo datasheet DHT11:
 * - Bit 0: muc cao trong 26-28us
 * - Bit 1: muc cao trong ~70us
 * 
 * @return uint8_t: byte du lieu tu DHT11
 */
static uint8_t DHT11_ReadByte(void)
{
    uint8_t byte = 0;
    uint8_t i;
    uint16_t u16Tim;

    for (i = 0; i < 8; i++) 
    {
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12));
        while (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12));
        TIM_SetCounter(TIM2, 0);
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) 
        {
            if (TIM_GetCounter(TIM2) > 100) break;
        }
        u16Tim = TIM_GetCounter(TIM2);

        // Chi luu, khong in
        arrTimeAll[bitIndex] = u16Tim;
        byte <<= 1;
        if (u16Tim > 40) 
        {
            byte |= 1;
            arrBitAll[bitIndex] = 1;
        }
        else
        {
            arrBitAll[bitIndex] = 0;
        }
        bitIndex++;
    }

    return byte;
}

/**
 * @brief Doc du lieu tu cam bien DHT11
 * @note DHT11 gui 5 byte:
 * - Byte 1: do am phan nguyen
 * - Byte 2: do am phan thap phan
 * - Byte 3: nhiet do phan nguyen
 * - Byte 4: nhiet do phan thap phan
 * - Byte 5: tong 4 byte tren (checksum)
 */
void DHT11_Read(void)
{
    uint8_t i;
    uint8_t u8CheckSum;
    uint16_t time_out = 0;
		bitIndex = 0;

    // Keo muc thap 20ms de bao hieu bat dau doc
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    delay_ms(20);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    // Cho DHT11 phan hoi keo xuong
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
    {
        time_out++;
        if (time_out > 1000) 
        {
            flag = 0; // Loi timeout
            return;
        }
    }

    // Cho DHT11 keo len
    time_out = 0;
    while (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)) 
    {
        time_out++;
        if (time_out > 1000) 
        {
            flag = 0;
            return;
        }
    }

    // Cho DHT11 keo xuong lan nua
    time_out = 0;
    while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
    {
        time_out++;
        if (time_out > 1000) 
        {
            flag = 0;
            return;
        }
    }

    // Doc 5 byte du lieu tu DHT11
    for (i = 0; i < 5; i++) 
    {
        u8Buff[i] = DHT11_ReadByte();
    }

    // Kiem tra checksum
    u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];
    if (u8CheckSum != u8Buff[4]) 
    {
        flag = 0; // Loi checksum
        return;
    }

    flag = 1; // Doc du lieu thanh cong
}

/**
 * @brief Lay nhiet do (phan nguyen) tu DHT11
 * 
 * @return uint8_t: nhiet do (do C)
 */
uint8_t DHT11_Get_Temperature(void)
{
    return u8Buff[2];
}

/**
 * @brief Lay do am (phan nguyen) tu DHT11
 * 
 * @return uint8_t: do am (%)
 */
uint8_t DHT11_Get_Humidity(void)
{
    return (uint8_t)u8Buff[0];
}

float DHT11_Get_Temperature_Decimal(void)
{
    return u8Buff[2] + u8Buff[3] * 0.1f;
}

float DHT11_Get_Humidity_Decimal(void)
{
    return u8Buff[0] + u8Buff[1] * 0.1f;
}
