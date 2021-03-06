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
uint8_t len = 0;
uint8_t AT24C02_Write_nBytes(uint8_t addr, uint8_t *data, uint8_t length)
{
    while(len < length-I2C_PAGE_SIZE_8BIT) {
        if (HAL_I2C_Mem_Write( &hi2c1, AT24C02_ADDR, (addr+len), I2C_MEMADD_SIZE_8BIT, &data[len], I2C_PAGE_SIZE_8BIT, 1000 ) == HAL_OK)
        {
            printf("\r\n Byte %02d to Byte %02d Write OK",len,len+8);
            HAL_Delay(5);//写完以后需要延时5ms，这个不能少
        }
        len = len + 8;
    }
    HAL_I2C_Mem_Write( &hi2c1, AT24C02_ADDR, (addr+len), I2C_MEMADD_SIZE_8BIT, &data[len], length-len, 1000 );
    HAL_Delay(5);
    return (1);
}

uint8_t AT24C02_Read_nBytes(uint8_t addr, uint8_t *data, uint8_t length)
{
    if( HAL_I2C_Mem_Read( &hi2c1, AT24C02_ADDR, addr * BYTE_SIZE, I2C_MEMADD_SIZE_8BIT, data, length, 1000 ) == HAL_OK )
        return 1;
    else
        return 0;
}

/* USER CODE END 0 */



/* USER CODE BEGIN 1 */


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
