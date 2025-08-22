#include "Key.h"

#define Key_Dissipate_Time 20
uint8_t Key_Num;

//GPIO引脚的宏定义，方便代码管理
#define Key1_GPIO_Port GPIOA
#define Key1_Pin GPIO_PIN_0
#define Key2_GPIO_Port GPIOA
#define Key2_Pin GPIO_PIN_1
#define Key3_GPIO_Port GPIOA
#define Key3_Pin GPIO_PIN_2
#define Key4_GPIO_Port GPIOA
#define Key4_Pin GPIO_PIN_3


/**
 * @description: 读取GPIO_Input的不同引脚的数值;
 * @return {*}
 */
uint8_t Key_GetState(void)
{
    if (HAL_GPIO_ReadPin(Key1_GPIO_Port,Key1_Pin) == 1){
        return 1;
    }
    if (HAL_GPIO_ReadPin(Key2_GPIO_Port,Key2_Pin) == 1){
        return 2;
    }
    if (HAL_GPIO_ReadPin(Key3_GPIO_Port,Key3_Pin) == 1){
        return 3;
    }
    if (HAL_GPIO_ReadPin(Key4_GPIO_Port,Key4_Pin) == 1){
        return 4;
    }
    return 0;
}

/**
 * @description: 更新Key_Num的数值
 * @return {*}
 */
uint8_t Key_GetNum(void)
{
    uint8_t Temp;
    if (Key_Num)
    {
        Temp = Key_Num;
        Key_Num = 0;
        return Temp;
    }
    return 0;
}

/**
 * @description: TIM定时中断的写入函数（可设1ms中断）
 * @return {*}
 */
void Key_Tick(void)
{
    static uint8_t Key_Count;
    static uint8_t CurrState, PrevState;
    Key_Count++;
    if (Key_Count >= Key_Dissipate_Time)
    {
        Key_Count = 0;

        PrevState = CurrState;
        CurrState = Key_GetState();
        if (CurrState == 0 && PrevState != 0)
        {
            Key_Num = PrevState;
        }
    }
}

/**
 * @description: TIM2中断回调函数，1ms的定时器定时中断
 * @param {TIM_HandleTypeDef*} htim
 * @return {*}
 */
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//     if (htim == &htim2) {  // 1kHz中断
//         Key_Tick();
//     }
// }



void LED1_ON(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
}

void LED1_OFF(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
}

void LED2_ON(void)
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
}

void LED2_OFF(void)
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
}

void LED3_ON(void)
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_SET);
}

void LED3_OFF(void)
{
    HAL_GPIO_WritePin(GPIOG,GPIO_PIN_8,GPIO_PIN_RESET);
}

void LED4_ON(void)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);
}

void LED4_OFF(void)
{
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);
}



