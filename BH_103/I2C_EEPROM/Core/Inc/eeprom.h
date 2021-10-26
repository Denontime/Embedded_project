/**
  ******************************************************************************
  * @file    eeprom.h
  * @brief   This file contains all the function prototypes for
  *          the eeprom.h file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H__
#define __EEPROM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



/* USER CODE BEGIN Private defines */

#define I2C_PAGE_SIZE_8BIT  8
#define BYTE_SIZE  8
#define I2Cx_EEPROM_ADDRESS 0xA0


/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

uint8_t AT24C02_Read_nBytes(uint8_t addr, uint8_t *data, uint8_t length);
uint8_t AT24C02_Write_nBytes(uint8_t addr, uint8_t *data, uint8_t length);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
