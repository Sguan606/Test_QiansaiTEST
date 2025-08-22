/*
 * @Author: 星必尘Sguan
 * @Date: 2025-08-10 19:15:57
 * @LastEditors: 星必尘Sguan|3464647102@qq.com
 * @LastEditTime: 2025-08-10 20:39:28
 * @FilePath: \test_QiansaiTEST\Hardware\printf.c
 * @Description: uart发送
 * 
 * Copyright (c) 2025 by $JUST, All Rights Reserved. 
 */
#include "printf.h"

extern UART_HandleTypeDef huart1;
uint8_t Read_Buffer[10];

void Sguan_SendByte(uint8_t Byte){
    HAL_UART_Transmit(&huart1,&Byte,1,HAL_MAX_DELAY);
}


void Sguan_SendString(char *myStr){
    uint16_t i;
    for (i = 0; myStr[i] != '\0'; i++){
        Sguan_SendByte(myStr[i]);
    }
    
}


void UART_SendFloats(float *data, uint8_t count, uint8_t decimal_places) {
    char buffer[128];  // 缓冲区（根据数据量调整大小）
    char *ptr = buffer;  // 指针指向缓冲区起始位置
    // 遍历所有 float 数据
    for (uint8_t i = 0; i < count; i++) {
        // 格式化 float 到字符串（如 "1.23"）
        ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), 
                      "%.*f", decimal_places, data[i]);
        // 添加逗号分隔（最后一个数据不加）
        if (i < count - 1) {
            ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), ", ");
        }
    }
    ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), "\n");    // 添加换行符
    // 通过 HAL_UART_Transmit 发送
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, ptr - buffer, HAL_MAX_DELAY);
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART1) {
        for(uint16_t i = 0; i < sizeof(Read_Buffer); i++) {
            // 遇到结束符停止检查
            if(Read_Buffer[i] == '\0' || Read_Buffer[i] == '\r' || Read_Buffer[i] == '\n') {
                break;
            }
            // 检查是否是0xB0命令
            if(Read_Buffer[i] != '\0') {
                Sguan_SendString("ST is OK\n");
            }
        }
        // 重新启动接收，使用Ex函数，接收不定长数据
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, Read_Buffer, sizeof(Read_Buffer));
        // 关闭DMA传输过半中断（HAL库默认开启，但我们只需要接收完成中断）
        __HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
    }
}
