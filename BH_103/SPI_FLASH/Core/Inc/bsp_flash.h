/**
  ******************************************************************************
  * @file    bsp_flash.h
  * @brief   This file contains all the function prototypes for
  *          the bsp_flash.c file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_FLASH_H
#define _BSP_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */

#define FLASH_SPI_CS_DISABLE();    HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_SET);
#define FLASH_SPI_CS_ENABLE();   HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_RESET);
#define MY_HSPI          hspi1

#define  sFLASH_ID              0XEF4017    //W25Q64

/* WIP(busy)标志，FLASH内部正在写入 */
#define WIP_Flag                  0x01

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256
#define SPI_FLASH_TIMEOUT               100

#define FLASH_ERROR(fmt,arg...)          printf("<<-FLASH-ERROR->> "fmt"\n",##arg)

/* 获取缓冲区的长度 */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define BufferSize      (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */

uint32_t w25x_ReadFlashID(void);
uint32_t w25x_ReadDeviceID(void);
void w25x_CheckBusy(void);
void w25x_WriteEnable(void);
void w25x_BulkErase(void);
void w25x_SectorErase(uint32_t SectorAddr);
void w25x_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void w25x_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void w25x_ReadData(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void w25x_PowerDown(void);
void w25x_WAKEUP(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
