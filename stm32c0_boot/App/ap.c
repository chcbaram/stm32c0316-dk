/*
 * ap.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "ap.h"




static void jumpToAddr(uint32_t addr);






void apInit(void)
{
  wdgInit();
  buttonInit();

  if (buttonGetPressed(_DEF_CH1))
  {
    wdgBegin(2000);
    jumpToAddr(0x1FFF0000); // Jump To System Bootloader
  }
  else
  {
    jumpToAddr(0x8000800); // Jump To Firmware
  }
}

void apMain(void)
{
  while(1)
  {

  }
}


void jumpToAddr(uint32_t addr)
{
  void (**jump_addr)(void) = (void (**)(void))(addr + 4);

  SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL  = 0;

  for (volatile int i=0; i<8; i++)
  {
    NVIC->ICER[i] = 0xFFFFFFFF;
    NVIC->ICPR[i] = 0xFFFFFFFF;
    __DSB();
    __ISB();
  }

  __set_MSP(*(uint32_t *)addr);
  (*jump_addr)();
}
