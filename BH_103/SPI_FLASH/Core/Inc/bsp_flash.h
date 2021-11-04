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

/* W25Q64��ָ�� */
extern uint8_t w25x_read_id;				// ��ID
extern uint8_t m_addr[3];					// ���Ե�ַ0x000000
extern uint8_t check_addr;					// �����·�Ƿ�æ
extern uint8_t enable_write;				// ʹ���˲��ܸı�оƬ����
extern uint8_t erase_addr;					// ��������
extern uint8_t write_addr;					// д��������
extern uint8_t read_addr;					// ����������

extern uint8_t temp_ID[5];					// ���ջ���
extern uint8_t temp_wdata[5];		        // ��Ҫд�������
extern uint8_t temp_rdata[5];				// �������ݱ����buff

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
