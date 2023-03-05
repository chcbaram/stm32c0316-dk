/*
 * uart.h
 *
 *  Created on: Mar 5, 2023
 *      Author: baram
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_


#include "def.h"


#define UART_MAX_CH           1



bool     uartInit(void);
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
uint32_t uartAvailable(uint8_t ch);
uint8_t  uartRead(uint8_t ch);
uint32_t uartPrintf(uint8_t ch, const char *fmt, ...);


#endif /* INCLUDE_UART_H_ */
