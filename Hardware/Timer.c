/*
 * @Author: 星必尘Sguan
 * @Date: 2025-05-08 19:26:48
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-08-10 20:55:10
 * @FilePath: \test_QiansaiTEST\Hardware\Timer.c
 * @Description: TIM定时中断统一管理函数;
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "Timer.h"

uint32_t mycount = 0;

/**
 * @description: TIM2中断回调函数，1ms的定时器定时中断;
 * @param {TIM_HandleTypeDef*} htim
 * @return {*}
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim1) {  // 1kHz中断
        Key_Tick();
        if (mycount != 30000)
        {
            mycount ++;
        }
        
        
    }
}



