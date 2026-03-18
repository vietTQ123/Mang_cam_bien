#include "define.h"

extern uint8_t u8Buff[5];  // Truy cap mang tu dht11.c

void Print_Bits(uint8_t byte)
{
    int8_t i;  
    for (i = 7; i >= 0; i--)
    {
        if (byte & (1 << i))
            Uart_SendChar('1');
        else
            Uart_SendChar('0');
    }
}

int main() {
    Uart_Gpio_TxRx_Init();
    DHT11_Init();
    Led_Debug();
    Timer2_Init();
    Uart_Init();
    off();
    
  /*  while(1){
        DHT11_Read();
        
        if(flag == 1)
        {
            Uart_SendStr("=== MANG DU LIEU DHT11 ===\n");
            
            Uart_SendStr("u8Buff[0] = ");
            Print_Bits(u8Buff[0]);
            Uart_SendStr(" = ");
            Uart_SendInt(u8Buff[0]);
            Uart_SendStr(" (Do am nguyen)\n");
            
            Uart_SendStr("u8Buff[1] = ");
            Print_Bits(u8Buff[1]);
            Uart_SendStr(" = ");
            Uart_SendInt(u8Buff[1]);
            Uart_SendStr(" (Do am thap phan)\n");
            
            Uart_SendStr("u8Buff[2] = ");
            Print_Bits(u8Buff[2]);
            Uart_SendStr(" = ");
            Uart_SendInt(u8Buff[2]);
            Uart_SendStr(" (Nhiet do nguyen)\n");
            
            Uart_SendStr("u8Buff[3] = ");
            Print_Bits(u8Buff[3]);
            Uart_SendStr(" = ");
            Uart_SendInt(u8Buff[3]);
            Uart_SendStr(" (Nhiet do thap phan)\n");
            
            Uart_SendStr("u8Buff[4] = ");
            Print_Bits(u8Buff[4]);
            Uart_SendStr(" = ");
            Uart_SendInt(u8Buff[4]);
            Uart_SendStr(" (Checksum)\n");
            
            Uart_SendStr("=========================\n");
            
            Uart_SendStr("Temperature: ");
            Uart_SendFloat(DHT11_Get_Temperature_Decimal());
            Uart_SendStr("C\n");
            
            Uart_SendStr("Humidity: ");
            Uart_SendInt(DHT11_Get_Humidity());
            Uart_SendStr("%\n\n");
        }
        else
        {
            Uart_SendStr("Loi doc DHT11!\n");
        }
        
        delay_ms(1000);
    }*/
	while(1)
	{
    DHT11_Read();

    if(flag == 1)
    {
        // In 40 bit chia thanh 5 byte
        uint8_t b, i;
        for (b = 0; b < 5; b++)
        {
            Uart_SendStr("=== Byte[");
            Uart_SendInt(b);
            Uart_SendStr("] ===\n");
            for (i = 0; i < 8; i++)
            {
                Uart_SendStr("Bit[");
                Uart_SendInt(7 - i);
                Uart_SendStr("] time=");
                Uart_SendInt(arrTimeAll[b*8 + i]);
                Uart_SendStr("us -> ");
                Uart_SendInt(arrBitAll[b*8 + i]);
                Uart_SendStr("\n");
            }
            Uart_SendStr("=> ");
            Uart_SendInt(u8Buff[b]);
            Uart_SendStr("\n\n");
        }
    }
   delay_ms(1000);
	}
}
