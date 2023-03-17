/*
 * rtc.c
 *
 *  Created on: Mar 12, 2023
 *      Author: baram
 */


#include "rtc.h"
#include "cli.h"



static void rtcCli(uint8_t argc, const char **argv);

extern RTC_HandleTypeDef hrtc;





bool rtcInit(void)
{
  cliAdd("rtc", rtcCli);
  return true;
}

bool rtcGetInfo(rtc_info_t *rtc_info)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  rtc_info->time.hours = sTime.Hours;
  rtc_info->time.minutes = sTime.Minutes;
  rtc_info->time.seconds = sTime.Seconds;

  rtc_info->date.year = sDate.Year;
  rtc_info->date.month = sDate.Month;
  rtc_info->date.day = sDate.Date;

  return true;
}

bool rtcGetTime(rtc_time_t *rtc_time)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  rtc_time->hours = sTime.Hours;
  rtc_time->minutes = sTime.Minutes;
  rtc_time->seconds = sTime.Seconds;

  return true;
}

bool rtcGetDate(rtc_date_t *rtc_date)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  rtc_date->year = sDate.Year;
  rtc_date->month = sDate.Month;
  rtc_date->day = sDate.Date;

  return true;
}

bool rtcSetTime(rtc_time_t *rtc_time)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  sTime.Hours = rtc_time->hours;
  sTime.Minutes = rtc_time->minutes;
  sTime.Seconds = rtc_time->seconds;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  return true;
}

bool rtcSetDate(rtc_date_t *rtc_date)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};


  if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  sDate.Year = rtc_date->year;
  sDate.Month = rtc_date->month;
  sDate.Date = rtc_date->day;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    return false;

  return true;
}

void rtcCli(uint8_t argc, const char **argv)
{
  bool ret = false;


  if (argc == 2 && cliIsStr(argv[0], "get") && cliIsStr(argv[1], "info"))
  {
    rtc_info_t rtc_info;

    while(cliKeepLoop())
    {
      rtcGetInfo(&rtc_info);

      cliPrintf("Y:%02d M:%02d D:%02d, H:%02d M:%02d S:%02d\n",
                rtc_info.date.year,
                rtc_info.date.month,
                rtc_info.date.day,
                rtc_info.time.hours,
                rtc_info.time.minutes,
                rtc_info.time.seconds);
      delay(1000);
    }
    ret = true;
  }

  if (argc == 5 && cliIsStr(argv[0], "set") && cliIsStr(argv[1], "time"))
  {
    rtc_time_t rtc_time;

    rtc_time.hours = cliGetData(argv[2]);
    rtc_time.minutes = cliGetData(argv[3]);
    rtc_time.seconds = cliGetData(argv[4]);

    rtcSetTime(&rtc_time);
    cliPrintf("H:%02d M:%02d S:%02d\n",
              rtc_time.hours,
              rtc_time.minutes,
              rtc_time.seconds);
    ret = true;
  }

  if (argc == 5 && cliIsStr(argv[0], "set") && cliIsStr(argv[1], "date"))
  {
    rtc_date_t rtc_date;

    rtc_date.year = cliGetData(argv[2]);
    rtc_date.month = cliGetData(argv[3]);
    rtc_date.day = cliGetData(argv[4]);

    rtcSetDate(&rtc_date);
    cliPrintf("Y:%02d M:%02d D:%02d\n",
              rtc_date.year,
              rtc_date.month,
              rtc_date.day);
    ret = true;
  }


  if (ret == false)
  {
    cliPrintf("rtc get info\n");
    cliPrintf("rtc set time [h] [m] [s]\n");
    cliPrintf("rtc set date [y] [m] [d]\n");
  }
}
