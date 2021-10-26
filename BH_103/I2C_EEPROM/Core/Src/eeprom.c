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

uint8_t AT24C02_Write_nBytes(uint8_t addr, uint8_t *data, uint8_t length)
{
    uint8_t len;
    for(len = 0; len < length; len = len + 8){
        HAL_I2C_Mem_Write( &hi2c1, I2Cx_EEPROM_ADDRESS, (addr+len) * BYTE_SIZE, I2C_MEMADD_SIZE_8BIT, &data[len], I2C_PAGE_SIZE_8BIT, 1000 );
        HAL_Delay(10);
    }
    HAL_I2C_Mem_Write( &hi2c1, I2Cx_EEPROM_ADDRESS, (addr+len) * BYTE_SIZE, I2C_MEMADD_SIZE_8BIT, &data[len], length-len, 1000 );
    HAL_Delay(10);
    return (1);
//    if( HAL_I2C_Mem_Write( &hi2c1, I2Cx_EEPROM_ADDRESS, addr * I2C_MEMADD_SIZE_8BIT, I2C_MEMADD_SIZE_8BIT, data, I2C_PAGE_SIZE_8BIT, 1000 ) == HAL_OK )
//        return 0;
//    else
//        return -1;
}
 
uint8_t AT24C02_Read_nBytes(uint8_t addr, uint8_t *data, uint8_t length)
{
    if( HAL_I2C_Mem_Read( &hi2c1, I2Cx_EEPROM_ADDRESS, addr * I2C_MEMADD_SIZE_8BIT, I2C_MEMADD_SIZE_8BIT, data, length, 1000 ) == HAL_OK )
        return 0;
    else
        return -1;
}

/* USER CODE END 0 */



/* USER CODE BEGIN 1 */


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
