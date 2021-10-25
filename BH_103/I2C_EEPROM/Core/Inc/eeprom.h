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

#define EEP_FirstAddr     0x00
#define I2Cx_EEPROM_ADDRESS 0xA0

/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

uint8_t HALIIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t data);
uint8_t HALIIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf);
uint8_t HALIIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t HALIIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
