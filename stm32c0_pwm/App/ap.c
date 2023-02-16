/*
 * ap.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "ap.h"





void apInit(void)
{
  ledInit();
  pwmInit();
}

void apMain(void)
{
  uint32_t pre_time;


  ledSetDuty(_DEF_CH1, 100);

  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();

      ledToggle(_DEF_CH1);
    }
  }
}
