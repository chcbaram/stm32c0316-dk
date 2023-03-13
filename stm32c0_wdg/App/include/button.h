/*
 * button.h
 *
 *  Created on: 2023. 2. 27.
 *      Author: hancheol
 */

#ifndef INCLUDE_BUTTON_H_
#define INCLUDE_BUTTON_H_


#include "def.h"


#define BUTTON_MAX_CH         5


bool buttonInit(void);
bool buttonGetPressed(uint8_t ch);
uint32_t buttonGetData(uint8_t ch);


#endif /* INCLUDE_BUTTON_H_ */
