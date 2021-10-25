/**
  ******************************************************************************
  * @file    time.c
  * @brief   This file provides code for the configuration
  *          of the time instances.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "time.h"

/* ÿ���µ����� */
const unsigned char g_day_per_mon[MONTH_PER_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* USER CODE BEGIN 0 */

static unsigned char applib_dt_is_leap_year(unsigned short year)
{

    if ((year % 400) == 0) {
        return 1;
    } else if ((year % 100) == 0) {
        return 0;
    } else if ((year % 4) == 0) {
        return 1;
    } else {
        return 0;
    }
}

static unsigned char applib_dt_last_day_of_mon(unsigned char month, unsigned short year)
{
    if ((month == 0) || (month > 12)) {
        return g_day_per_mon[1] + applib_dt_is_leap_year(year);
    }

    if (month != 2) {
        return g_day_per_mon[month - 1];
    } else {
        return g_day_per_mon[1] + applib_dt_is_leap_year(year);
    }
}

/* USER CODE END 0 */



/* USER CODE BEGIN 1 */

void Uinx2UTC(long ts)
{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;


    //��ʱ���ֵת����������ͨ���������ԱȽϷ��������ꡢ�¡��ա�
    int days = ts / SEC_PER_DAY;
    //���ʱ���ֵ���ꡣ
    int yearTmp = 0;
    int dayTmp = 0;
    //ʹ�üбƷ����� days ���а�����������
    for (yearTmp = UTC_BASE_YEAR; days > 0; yearTmp++) {
        dayTmp = (DAY_PER_YEAR + applib_dt_is_leap_year(yearTmp)); //��һ���ж����죿
        if (days >= dayTmp) //������������ yearTmp �������ʱ���ֵ�������������
        {
           days -= dayTmp;
        }
        else
        {
           break;
        }
    }
    year = yearTmp;

    //���ʱ���ֵ����
    int monthTmp = 0;
    for (monthTmp = 1; monthTmp < MONTH_PER_YEAR; monthTmp++) {
       dayTmp = applib_dt_last_day_of_mon(monthTmp, year);
       if (days >= dayTmp) {
           days -= dayTmp;
       }
       else
       {
           break;
       }
    }
    month = monthTmp;

    day = days + 1;

    //ת�����롣
    int secs = ts % SEC_PER_DAY;
    //���ʱ���ֵ��Сʱ����
    hour = secs / SEC_PER_HOUR;
    //���ʱ���ֵ�ķ�������
    secs %= SEC_PER_HOUR;
    minute = secs / SEC_PER_MIN;
    //���ʱ�������������
    second = secs % SEC_PER_MIN;

    printf("%d-%d-%d %d:%d:%d\n\n", year, month, day, hour, minute, second);
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
