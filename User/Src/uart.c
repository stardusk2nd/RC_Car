/*
 * uart.c
 *
 *  Created on: Aug 2, 2024
 *      Author: Stardust
 */

#include "uart.h"

uint8_t uart_rx_buffer[7];
uint8_t uart_rx_index = 0;
uint16_t adcValue[2];
uint8_t power_on = false;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if (huart->Instance == USART1)
    {
        // 패킷 시작 바이트를 찾음
        if (uart_rx_index == 0 && uart_rx_buffer[0] != 0xEE){
            HAL_UART_Receive_IT(&huart1, uart_rx_buffer, 1);
            return;
        }

        // 패킷 데이터 수신
        uart_rx_index++;
        if (uart_rx_index >= 7){
            if (uart_rx_buffer[6] == 0xFF){
            	power_on = uart_rx_buffer[1];
                adcValue[0] = (uart_rx_buffer[2] << 8) | uart_rx_buffer[3];
                adcValue[1] = (uart_rx_buffer[4] << 8) | uart_rx_buffer[5];
            }
            uart_rx_index = 0;
        }

        HAL_UART_Receive_IT(&huart1, uart_rx_buffer + uart_rx_index, 1);
    }
}
