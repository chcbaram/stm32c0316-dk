/*
 * ap.c
 *
 *  Created on: Feb 16, 2023
 *      Author: baram
 */


#include "ap.h"
#include "string.h"
#include "stdlib.h"



float adc_vol = 0;
float adc_vol_vref = 0;

bool button_data[BUTTON_MAX_CH];


char     cli_buf[128];
uint16_t cli_buf_index = 0;

uint16_t cli_argc = 0;
char    *cli_argv[8];



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

      if (rx_data == '\r')
      {
        cli_buf[cli_buf_index] = 0;
        cli_buf_index = 0;

        uartPrintf(_DEF_CH1, "\r\n");

        // RUN CMD
        char *tok;
        char *str_ptr = cli_buf;

        cli_argc = 0;
        while((tok = strtok_r(str_ptr, " ", &str_ptr)) != NULL)
        {
          cli_argv[cli_argc] = tok;
          cli_argc++;
        }

        if (cli_argc == 2 && strcmp(cli_argv[0], "test") == 0)
        {
          int32_t test_data;

          test_data = (int32_t)strtoul(cli_argv[1], (char **)NULL, 0);
          uartPrintf(_DEF_CH1, "test data : %d\n", test_data);
        }

        uartPrintf(_DEF_CH1, "cli# ");
      }
      else if (cli_buf_index < (128 - 1))
      {
        cli_buf[cli_buf_index] = rx_data;
        cli_buf_index++;

        uartWrite(_DEF_CH1, &rx_data, 1);
      }
    }
  }
}
