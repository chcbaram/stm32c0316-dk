/*
 * adc.c
 *
 *  Created on: Feb 23, 2023
 *      Author: baram
 */


#include "adc.h"


extern ADC_HandleTypeDef hadc1;





bool adcInit(void)
{
  return true;
}

uint16_t adcRead(uint8_t ch)
{
  uint16_t ret = 0;


  switch(ch)
  {
    case _DEF_CH1:
      HAL_ADC_Start(&hadc1);
      HAL_ADC_PollForConversion(&hadc1, 10);
      ret = HAL_ADC_GetValue(&hadc1);
      break;
  }

  return ret;
}

uint32_t adcReadVoltage(uint8_t ch)
{
  uint32_t ret;
  uint32_t adc_data;


  adc_data = adcRead(ch);

  ret = (330 * adc_data) / 4096;

  return ret;
}
