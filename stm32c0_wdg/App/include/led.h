/*
 * led.h
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */

#ifndef INCLUDE_LED_H_
#define INCLUDE_LED_H_


#include "def.h"


bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);
void ledSetDuty(uint8_t ch, uint16_t duty_data);

#endif /* INCLUDE_LED_H_ */
