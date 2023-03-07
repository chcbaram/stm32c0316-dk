/*
 * utils.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "utils.h"





void delay(uint32_t time_ms)
{
  HAL_Delay(time_ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}
