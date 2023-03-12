/*
 * cli.c
 *
 *  Created on: 2023. 3. 10.
 *      Author: baram
 */


#include "cli.h"
#include "uart.h"


#define CLI_CMD_LIST_MAX          8


typedef struct
{
  char   cmd_str[8];
  void (*cmd_func)(uint8_t argc, const char **argv);
} cli_cmd_t;


static const uint8_t cli_ch = _DEF_CH1;

static char     cli_buf[128];
static uint16_t cli_buf_index = 0;

static uint16_t cli_argc = 0;
static char    *cli_argv[8];

static uint8_t   cli_cmd_count = 0;
static cli_cmd_t cli_cmd_func[CLI_CMD_LIST_MAX];


static void cliHelp(uint8_t argc, const char **argv);




bool cliInit(void)
{
  for (int i=0; i<CLI_CMD_LIST_MAX; i++)
  {
    cli_cmd_func[i].cmd_func = NULL;
  }

  cliAdd("help", cliHelp);
  return true;
}

bool cliAdd(const char *cmd_str, void (*cmd_func)(uint8_t argc, const char **argv))
{
  if (cli_cmd_count >= CLI_CMD_LIST_MAX)
    return false;

  strncpy(cli_cmd_func[cli_cmd_count].cmd_str, cmd_str, 8);
  cli_cmd_func[cli_cmd_count].cmd_func = cmd_func;
  cli_cmd_count++;

  return true;
}

void cliHelp(uint8_t argc, const char **argv)
{
  cliPrintf("-----------------------\n");

  for (int i=0; i<cli_cmd_count; i++)
  {
    cliPrintf("%s\n", cli_cmd_func[i].cmd_str);
  }

  cliPrintf("-----------------------\n");
}

void cliPrintf(const char *fmt, ...)
{
  va_list arg;

  va_start(arg, fmt);
  uartVPrintf(cli_ch, fmt, arg);
  va_end(arg);
}

bool cliIsStr(const char *p_arg, const char *p_str)
{
  if (strcmp(p_arg, p_str) == 0)
    return true;
  else
    return false;
}

int32_t cliGetData(const char *p_arg)
{
  int32_t ret;

  ret = (int32_t)strtoul(p_arg, (char **)NULL, 0);

  return ret;
}

bool cliKeepLoop(void)
{
  if (uartAvailable(cli_ch) == 0)
    return true;
  else
    return false;
}

bool cliMain(void)
{
  bool ret = false;


  if (uartAvailable(cli_ch) > 0)
  {
    uint8_t rx_data;

    rx_data = uartRead(cli_ch);

    if (rx_data == '\r')
    {
      cli_buf[cli_buf_index] = 0;
      cli_buf_index = 0;

      uartPrintf(cli_ch, "\r\n");

      // RUN CMD
      char *tok;
      char *str_ptr = cli_buf;

      cli_argc = 0;
      while((tok = strtok_r(str_ptr, " ", &str_ptr)) != NULL)
      {
        cli_argv[cli_argc] = tok;
        cli_argc++;
      }


      for (int i=0; i<cli_cmd_count; i++)
      {
        if (strcmp(cli_argv[0], cli_cmd_func[i].cmd_str) == 0)
        {
          if (cli_cmd_func[i].cmd_func != NULL)
          {
            cli_cmd_func[i].cmd_func(cli_argc - 1, (const char **)&cli_argv[1]);
            ret = true;
            break;
          }
        }
      }

      uartPrintf(cli_ch, "cli# ");
    }
    else if (cli_buf_index < (128 - 1))
    {
      cli_buf[cli_buf_index] = rx_data;
      cli_buf_index++;

      uartWrite(cli_ch, &rx_data, 1);
    }
  }

  return ret;
}



