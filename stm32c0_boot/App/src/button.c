/*
 * button.c
 *
 *  Created on: 2023. 2. 27.
 *      Author: hancheol
 */


#include "button.h"




bool buttonInit(void)
{
  return true;
}

bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;

  if (ch >= BUTTON_MAX_CH)
    return false;

  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_RESET)
  {
    ret = true;
  }

  return ret;
}

uint32_t buttonGetData(uint8_t ch)
{
  uint32_t ret = 0;


  for (int i=0; i<BUTTON_MAX_CH; i++)
  {
    ret |= (buttonGetPressed(i)<<i);
  }

  return ret;
}
