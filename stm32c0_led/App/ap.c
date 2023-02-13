/*
 * ap.c
 *
 *  Created on: Feb 12, 2023
 *      Author: baram
 */


#include "ap.h"





void apInit(void)
{
  ledInit();
}

void apMain(void)
{
  uint32_t pre_time;


  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();

      ledToggle(_DEF_CH1);
    }
  }
}
