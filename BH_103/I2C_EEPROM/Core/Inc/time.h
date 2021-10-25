/**
  ******************************************************************************
  * @file    time.h
  * @brief   This file contains all the function prototypes for
  *          the time.h file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIME_H__
#define __TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */

#define UTC_BASE_YEAR   1970
#define MONTH_PER_YEAR  12
#define DAY_PER_YEAR    365
#define SEC_PER_DAY     86400
#define SEC_PER_HOUR    3600
#define SEC_PER_MIN     60

/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

void Uinx2UTC(long ts);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
