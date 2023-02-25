/*
 * pwm.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "pwm.h"



extern TIM_HandleTypeDef htim1;





bool pwmInit(void)
{
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  return true;
}

void pwmWrite(uint8_t ch, uint16_t duty)
{
  switch(ch)
  {
    case _DEF_CH1:
      htim1.Instance->CCR1 = duty;
      break;
  }
}

uint16_t pwmRead(uint8_t ch)
{
  uint16_t pwm_data = 0;


  switch(ch)
  {
    case _DEF_CH1:
      pwm_data = htim1.Instance->CCR1;
      break;
  }

  return pwm_data;
}
