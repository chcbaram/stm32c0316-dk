/*
 * ap.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "ap.h"





float adc_vol = 0;
float adc_vol_vref = 0;



void apInit(void)
{
  ledInit();
  pwmInit();
  adcInit();
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


    adc_vol      = (float)adcReadVoltage(_DEF_CH1) / 100.f;
    adc_vol_vref = (float)adcReadVoltage(_DEF_CH3) / 100.f;
  }
}
