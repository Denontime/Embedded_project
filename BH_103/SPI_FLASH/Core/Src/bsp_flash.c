/**
  ******************************************************************************
  * @file    bsp_flash.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_flash.h"

/* W25Q64的指令 */
uint8_t w25x_read_id = 0x90;					// 读ID
uint8_t m_addr[3]    = {0,0,0};					// 测试地址0x000000
uint8_t check_addr   = 0x05;					// 检查线路是否繁忙
uint8_t enable_write = 0x06;					// 使能了才能改变芯片数据
uint8_t erase_addr   = 0x20;					// 擦除命令
uint8_t write_addr   = 0x02;					// 写数据命令
uint8_t read_addr    = 0x03;					// 读数据命令

uint8_t temp_ID[5] = {0,0,0,0,0};						// 接收缓存
uint8_t temp_wdata[5] = {0x99,0x88,0x77,0x66,0x55};		// 需要写入的数据
uint8_t temp_rdata[5] = {0,0,0,0,0};					// 读出数据保存的buff

/* 读ID */
void ReadID(void)
{
	SPI_NSS_DISABLE();	                                    // 使能CS
	HAL_SPI_Transmit(&MY_HSPI, &w25x_read_id, 1, 100);		// 读ID发送指令
	HAL_SPI_Receive(&MY_HSPI, temp_ID, 5, 100);				// 读取ID
	SPI_NSS_ENABLE();	                                    // 失能CS
}

/* 检查是否繁忙 */
void CheckBusy(void)
{
	uint8_t status=1;
	uint32_t timeCount=0;
	do
	{
		timeCount++;
		if(timeCount > 0xEFFFFFFF) //等待超时
		{
			return ;
		}
		
		SPI_NSS_DISABLE();	                                        // 使能CS	
		HAL_SPI_Transmit(&MY_HSPI, &check_addr, 1, 100);			// 发送指令
		HAL_SPI_Receive(&MY_HSPI, &status, 1, 100);				    // 读取
		SPI_NSS_ENABLE();                                           // 失能CS
	}while((status&0x01)==0x01);
}


/* 写入数据 */
void WriteData(void)
{
	/* 检查是否繁忙 */
	CheckBusy();
	
	/* 写使能 */
	SPI_NSS_DISABLE();	                                    // 使能CS
	HAL_SPI_Transmit(&MY_HSPI, &enable_write, 1, 100);		// 发送指令
	SPI_NSS_ENABLE(); 	                                    // 失能CS
	
	/* 擦除 */
	SPI_NSS_DISABLE();	                                    // 使能CS
	HAL_SPI_Transmit(&MY_HSPI, &erase_addr, 1, 100);		// 发送指令
	HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, 100);				// 发送地址
	SPI_NSS_ENABLE(); 	                                    // 失能CS
	
	/* 再次检查是否繁忙 */
	CheckBusy();
	
	/* 写使能 */
	SPI_NSS_DISABLE();	                                    // 使能CS
	HAL_SPI_Transmit(&MY_HSPI, &enable_write, 1, 100);		// 发送指令
	SPI_NSS_ENABLE(); 	                                    // 失能CS

	/* 写数据 */
	SPI_NSS_DISABLE();	                                    // 使能CS
	HAL_SPI_Transmit(&MY_HSPI, &write_addr, 1, 100);		// 发送指令
	HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, 100);				// 地址
	HAL_SPI_Transmit(&MY_HSPI, temp_wdata, 5, 100);			// 写入数据
	SPI_NSS_ENABLE(); 	                                    // 失能CS
}

/* 读取数据 */
void ReadData(void)
{
	/* 检查是否繁忙 */
	CheckBusy();	
	
	/* 开始读数据 */
	SPI_NSS_DISABLE();	                                    // 使能CS
	HAL_SPI_Transmit(&MY_HSPI, &read_addr, 1, 100);			// 读发送指令
	HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, 100);				// 地址
	HAL_SPI_Receive(&MY_HSPI,  temp_rdata, 5, 100);			// 拿到数据
	SPI_NSS_ENABLE(); 	                                    // 失能CS
}


