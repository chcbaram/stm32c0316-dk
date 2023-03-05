/*
 * ap.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "ap.h"





float adc_vol = 0;
float adc_vol_vref = 0;

bool button_data[BUTTON_MAX_CH];



void apInit(void)
{
  ledInit();
  pwmInit();
  adcInit();
  buttonInit();
  uartInit();
}

void apMain(void)
{
  uint32_t pre_time;


  ledSetDuty(_DEF_CH1, 100);

  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();

      ledToggle(_DEF_CH1);
    }


    adc_vol      = (float)adcReadVoltage(_DEF_CH1) / 100.f;
    adc_vol_vref = (float)adcReadVoltage(_DEF_CH3) / 100.f;


    button_data[_BUTTON_CH_SEL  ] = buttonGetPressed(_BUTTON_CH_SEL);
    button_data[_BUTTON_CH_UP   ] = buttonGetPressed(_BUTTON_CH_UP);
    button_data[_BUTTON_CH_DOWN ] = buttonGetPressed(_BUTTON_CH_DOWN);
    button_data[_BUTTON_CH_LEFT ] = buttonGetPressed(_BUTTON_CH_LEFT);
    button_data[_BUTTON_CH_RIGHT] = buttonGetPressed(_BUTTON_CH_RIGHT);

    if (uartAvailable(_DEF_CH1) > 0)
    {
      uint8_t rx_data;


      rx_data = uartRead(_DEF_CH1);
      uartPrintf(_DEF_CH1, "rx data : 0x%02X (%c)\n", rx_data, rx_data);
    }
  }
}
