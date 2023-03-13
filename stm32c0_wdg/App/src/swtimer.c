/*
 * swtimer.c
 *
 *  Created on: Mar 12, 2023
 *      Author: baram
 */


#include "swtimer.h"


#define SWTIMER_MAX_CH          8


typedef struct
{
  bool enable;
  SwtimerMode_t mode;
  uint32_t counter;
  uint32_t reload;
  void (*func)(void *arg);
  void *func_arg;
} swtimer_t;


static uint8_t swtimer_count = 0;
static swtimer_t swtimer_tbl[SWTIMER_MAX_CH];
extern TIM_HandleTypeDef htim14;





bool swtimerInit(void)
{
  for (int i=0; i<SWTIMER_MAX_CH; i++)
  {
    swtimer_tbl[i].enable = false;
    swtimer_tbl[i].counter = 0;
    swtimer_tbl[i].func = NULL;
    swtimer_tbl[i].func_arg = NULL;
  }

  HAL_TIM_Base_Start_IT(&htim14);
  return true;
}

bool swtimerGetCh(uint8_t *p_ch)
{
  if (swtimer_count >= SWTIMER_MAX_CH)
    return false;

  *p_ch = swtimer_count;

  swtimer_count++;

  return true;
}

bool swtimerSet(uint8_t ch,
                void (*func)(void *arg),
                void *func_arg,
                SwtimerMode_t mode,
                uint32_t time_ms)
{
  if (ch >= SWTIMER_MAX_CH)
    return false;

  swtimer_tbl[ch].func = func;
  swtimer_tbl[ch].func_arg = func_arg;
  swtimer_tbl[ch].mode = mode;
  swtimer_tbl[ch].counter = 0;
  swtimer_tbl[ch].reload = time_ms;
  swtimer_tbl[ch].enable = false;

  return true;
}

bool swtimerStart(uint8_t ch)
{
  if (ch >= SWTIMER_MAX_CH)
    return false;

  swtimer_tbl[ch].counter = 0;
  swtimer_tbl[ch].enable = true;

  return true;
}

bool swtimerStop(uint8_t ch)
{
  if (ch >= SWTIMER_MAX_CH)
    return false;

  swtimer_tbl[ch].enable = false;

  return true;
}

void swtimerISR(void)
{
  for (int i=0; i<swtimer_count; i++)
  {
    if (swtimer_tbl[i].enable == true)
    {
      swtimer_tbl[i].counter++;
      if (swtimer_tbl[i].counter >= swtimer_tbl[i].reload)
      {
        if (swtimer_tbl[i].func != NULL)
        {
          swtimer_tbl[i].func(swtimer_tbl[i].func_arg);
        }
        swtimer_tbl[i].counter = 0;
        if (swtimer_tbl[i].mode == SWTIMER_ONETIME)
        {
          swtimer_tbl[i].enable = false;
        }
      }
    }
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim14)
  {
    swtimerISR();
  }
}
