/*
 * uart.h
 *
 *  Created on: Sep 8, 2023
 *      Author: phamv
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "usart.h"
#include <stdio.h>
#include "utils.h"
extern uint8_t flag_esp;
void uart_init_rs232();

void uart_Rs232SendString(uint8_t* str);

void uart_Rs232SendBytes(uint8_t* bytes, uint16_t size);

void uart_Rs232SendNum(uint32_t num);

void uart_Rs232SendNumPercent(uint32_t num);
void uart_EspSendByte(uint8_t* bytes);

#endif /* INC_UART_H_ */
