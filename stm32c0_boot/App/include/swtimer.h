/*
 * swtimer.h
 *
 *  Created on: Mar 12, 2023
 *      Author: baram
 */

#ifndef INCLUDE_SWTIMER_H_
#define INCLUDE_SWTIMER_H_


#include "def.h"


typedef enum
{
  SWTIMER_LOOP,
  SWTIMER_ONETIME,
} SwtimerMode_t;


bool swtimerInit(void);
bool swtimerGetCh(uint8_t *p_ch);
bool swtimerSet(uint8_t ch,
                void (*func)(void *arg),
                void *func_arg,
                SwtimerMode_t mode,
                uint32_t time_ms);
bool swtimerStart(uint8_t ch);
bool swtimerStop(uint8_t ch);


#endif /* INCLUDE_SWTIMER_H_ */
