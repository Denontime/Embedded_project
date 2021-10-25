/**
  ******************************************************************************
  * @file    eeprom.c
  * @brief   This file provides code for the configuration
  *          of the eeprom_r instances.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "eeprom.h"

/* USER CODE BEGIN 0 */

uint8_t HALIIC_WriteByteToSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t data)
{
  uint8_t  *pData;
  pData = &data;
  return HAL_I2C_Mem_Write(&hi2c1, I2C_Addr, reg, I2C_MEMADD_SIZE_8BIT, pData, 1, 100);
}

uint8_t HALIIC_ReadByteFromSlave(uint8_t I2C_Addr,uint8_t reg,uint8_t *buf)
{
  return HAL_I2C_Mem_Read(&hi2c1, I2C_Addr, reg, I2C_MEMADD_SIZE_8BIT, buf, 1, 100);
}
 
uint8_t HALIIC_ReadMultByteFromSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data)
{
  return HAL_I2C_Mem_Read(&hi2c1, dev, reg, I2C_MEMADD_SIZE_8BIT, data, length, 200);
}

uint8_t HALIIC_WriteMultByteToSlave(uint8_t dev, uint8_t reg, uint8_t length, uint8_t* data)
{
  return HAL_I2C_Mem_Write(&hi2c1, dev, reg, I2C_MEMADD_SIZE_8BIT, data, length, 200);
}


/* USER CODE END 0 */



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
