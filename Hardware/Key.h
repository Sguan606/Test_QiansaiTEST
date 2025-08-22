#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx_hal.h"

uint8_t Key_GetState(void);
uint8_t Key_GetNum(void);
void Key_Tick(void);

void LED1_ON(void);
void LED1_OFF(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED3_ON(void);
void LED3_OFF(void);
void LED4_ON(void);
void LED4_OFF(void);


#endif //Key_H

