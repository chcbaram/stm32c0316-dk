/*
 * button.c
 *
 *  Created on: 2023. 2. 27.
 *      Author: hancheol
 */


#include "button.h"
#include "adc.h"


typedef struct
{
  uint16_t adc_min;
  uint16_t adc_max;
} button_adc_t;


static const uint8_t adc_ch = _DEF_CH1;
static const button_adc_t button_adc[BUTTON_MAX_CH] =
    {
        {0,    20},
        {40,   87},
        {122, 152},
        {180, 220},
        {245, 285},
    };





bool buttonInit(void)
{
  return true;
}

bool buttonGetPressed(uint8_t ch)
{
  bool ret = false;
  uint32_t adc_voltage;


  if (ch >= BUTTON_MAX_CH)
    return false;

  adc_voltage = adcReadVoltage(adc_ch);


  if (adc_voltage >= button_adc[ch].adc_min && adc_voltage <= button_adc[ch].adc_max)
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
