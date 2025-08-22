#ifndef __PRINTF_H
#define __PRINTF_H

#include "stm32f4xx_hal.h"

void Sguan_SendByte(uint8_t Byte);
void Sguan_SendString(char *myStr);
void UART_SendFloats(float *data, uint8_t count, uint8_t decimal_places);


#endif // 

