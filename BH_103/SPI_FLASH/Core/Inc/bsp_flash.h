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

#define SPI_NSS_ENABLE();    HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_SET);
#define SPI_NSS_DISABLE();   HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_RESET);
#define MY_HSPI          hspi1

/* W25Q64的指令 */
extern uint8_t w25x_read_id;				// 读ID
extern uint8_t m_addr[3];					// 测试地址0x000000
extern uint8_t check_addr;					// 检查线路是否繁忙
extern uint8_t enable_write;				// 使能了才能改变芯片数据
extern uint8_t erase_addr;					// 擦除命令
extern uint8_t write_addr;					// 写数据命令
extern uint8_t read_addr;					// 读数据命令

extern uint8_t temp_ID[5];					// 接收缓存
extern uint8_t temp_wdata[5];		        // 需要写入的数据
extern uint8_t temp_rdata[5];				// 读出数据保存的buff

/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */

void ReadID(void);
void CheckBusy(void);
void WriteData(void);
void ReadData(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
