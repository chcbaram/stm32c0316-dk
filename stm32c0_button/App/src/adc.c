/*
 * adc.c
 *
 *  Created on: Feb 23, 2023
 *      Author: baram
 */


#include "adc.h"


extern ADC_HandleTypeDef hadc1;

uint16_t adc_data[3];




bool adcInit(void)
{

  HAL_ADCEx_Calibration_Start(&hadc1);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_data, 3);

  return true;
}

uint16_t adcRead(uint8_t ch)
{
  uint16_t ret = 0;

  ret = adc_data[ch];

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

