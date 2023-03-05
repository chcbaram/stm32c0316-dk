/*
 * led.c
 *
 *  Created on: Feb 14, 2023
 *      Author: baram
 */


#include "led.h"
#include "pwm.h"



static uint16_t led_duty[1] = {100};




bool ledInit(void)
{
  return true;
}

void ledOn(uint8_t ch)
{
  switch(ch)
  {
    case _DEF_CH1:
      pwmWrite(_DEF_CH1, 100 - led_duty[_DEF_CH1]);
      break;
  }
}

void ledOff(uint8_t ch)
{
  switch(ch)
  {
    case _DEF_CH1:
      pwmWrite(_DEF_CH1, 100);
      break;
  }
}

void ledToggle(uint8_t ch)
{
  switch(ch)
  {
    case _DEF_CH1:
      if (pwmRead(_DEF_CH1) == 100)
        ledOn(_DEF_CH1);
      else
        ledOff(_DEF_CH1);
      break;
  }
}

void ledSetDuty(uint8_t ch, uint16_t duty_data)
{
  switch(ch)
  {
    case _DEF_CH1:
      led_duty[ch] = duty_data;
      break;
  }
}
