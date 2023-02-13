/*
 * led.c
 *
 *  Created on: Feb 14, 2023
 *      Author: baram
 */


#include "led.h"




bool ledInit(void)
{
  return true;
}

void ledOn(uint8_t ch)
{
  switch(ch)
  {
    case _DEF_CH1:
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
      break;
  }
}

void ledOff(uint8_t ch)
{
  switch(ch)
  {
    case _DEF_CH1:
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
      break;
  }
}

void ledToggle(uint8_t ch)
{
  switch(ch)
  {
    case _DEF_CH1:
      HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      break;
  }
}
