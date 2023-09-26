/*
 * uart.c
 *
 *  Created on: Sep 8, 2023
 *      Author: phamv
 */

#include "uart.h"

uint8_t receive_buffer1 = 0,receive_buffer2 = 0, receive_buffer3 = 0;
uint8_t msg[100];
uint8_t flag_esp = 0;

void uart_init_rs232(){
	HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
}

void uart_init_Esp(){
	HAL_UART_Receive_IT(&huart2, &receive_buffer2, 1);
}

void uart_init_rs485(){
	HAL_UART_Receive_IT(&huart3, &receive_buffer3, 1);
}

void uart_Rs232SendString(uint8_t* str){
	HAL_UART_Transmit(&huart1, (void*)msg, sprintf((void*)msg,"%s",str), 10);
}

void uart_EspSendString(uint8_t* str){
	HAL_UART_Transmit(&huart2, (void*)msg, sprintf((void*)msg,"%s",str), 10);
}

void uart_Rs485SendString(uint8_t* str){
	HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, 1);
	HAL_UART_Transmit(&huart3, (void*)msg, sprintf((void*)msg,"%s",str), 10);
	HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, 0);
}

//uint8_t uart_Rs232ReceiveString(){
//	 HAL_UART_Receive(&huart1, (uint8_t*)msg_rx, 100, 10);
//	 return msg_rx;
//}

void uart_Rs232SendBytes(uint8_t* bytes, uint16_t size){
	HAL_UART_Transmit(&huart1, bytes, size, 10);
}

void uart_EspSendByte(uint8_t* bytes){
	HAL_UART_Transmit(&huart2, bytes, 1,10);
}

void uart_Rs232SendNum(uint32_t num){
    uint8_t num_flag = 0;
    int i;
	if(num < 0) uart_Rs232SendString("-");
    for(i = 10; i > 0; i--)
    {
        if((num / mypow(10, i-1)) != 0)
        {
            num_flag = 1;
            sprintf((void*)msg,"%d",num/mypow(10, i-1));
            uart_Rs232SendString(msg);
        }
        else
        {
            if(num_flag != 0)
            	uart_Rs232SendString("0");
        }
        num %= mypow(10, i-1);
    }
}

void uart_Rs232SendNumPercent(uint32_t num)
{
	sprintf((void*)msg,"%ld",num/100);
    uart_Rs232SendString(msg);
    uart_Rs232SendString(".");
    sprintf((void*)msg,"%ld",num%100);
    uart_Rs232SendString(msg);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		HAL_UART_Transmit(&huart1, &receive_buffer1, 1, 10);
		HAL_UART_Receive_IT(&huart1, &receive_buffer1, 1);
	}
	if(huart->Instance == USART2){

		if(receive_buffer2 == 'B') flag_esp = 1;
		HAL_UART_Receive_IT(&huart2, &receive_buffer2, 1);
	}
	if(huart->Instance == USART3){
		HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, 1);
		HAL_UART_Transmit(&huart3, &receive_buffer3, 1, 10);
		HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, 0);
		HAL_UART_Receive_IT(&huart3, &receive_buffer3, 1);
	}
}
