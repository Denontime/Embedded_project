/**
  ******************************************************************************
  * @file    bsp_flash.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_flash.h"

/* W25Q64��ָ�� */
uint8_t w25x_read_id = 0x90;					// ��ID
uint8_t m_addr[3]    = {0,0,0};					// ���Ե�ַ0x000000
uint8_t check_addr   = 0x05;					// �����·�Ƿ�æ
uint8_t enable_write = 0x06;					// ʹ���˲��ܸı�оƬ����
uint8_t erase_addr   = 0x20;					// ��������
uint8_t write_addr   = 0x02;					// д��������
uint8_t read_addr    = 0x03;					// ����������

uint8_t temp_ID[5] = {0,0,0,0,0};						// ���ջ���
uint8_t temp_wdata[5] = {0x99,0x88,0x77,0x66,0x55};		// ��Ҫд�������
uint8_t temp_rdata[5] = {0,0,0,0,0};					// �������ݱ����buff

/* ��ID */
void ReadID(void)
{
	SPI_NSS_DISABLE();	                                    // ʹ��CS
	HAL_SPI_Transmit(&MY_HSPI, &w25x_read_id, 1, 100);		// ��ID����ָ��
	HAL_SPI_Receive(&MY_HSPI, temp_ID, 5, 100);				// ��ȡID
	SPI_NSS_ENABLE();	                                    // ʧ��CS
}

/* ����Ƿ�æ */
void CheckBusy(void)
{
	uint8_t status=1;
	uint32_t timeCount=0;
	do
	{
		timeCount++;
		if(timeCount > 0xEFFFFFFF) //�ȴ���ʱ
		{
			return ;
		}
		
		SPI_NSS_DISABLE();	                                        // ʹ��CS	
		HAL_SPI_Transmit(&MY_HSPI, &check_addr, 1, 100);			// ����ָ��
		HAL_SPI_Receive(&MY_HSPI, &status, 1, 100);				    // ��ȡ
		SPI_NSS_ENABLE();                                           // ʧ��CS
	}while((status&0x01)==0x01);
}


/* д������ */
void WriteData(void)
{
	/* ����Ƿ�æ */
	CheckBusy();
	
	/* дʹ�� */
	SPI_NSS_DISABLE();	                                    // ʹ��CS
	HAL_SPI_Transmit(&MY_HSPI, &enable_write, 1, 100);		// ����ָ��
	SPI_NSS_ENABLE(); 	                                    // ʧ��CS
	
	/* ���� */
	SPI_NSS_DISABLE();	                                    // ʹ��CS
	HAL_SPI_Transmit(&MY_HSPI, &erase_addr, 1, 100);		// ����ָ��
	HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, 100);				// ���͵�ַ
	SPI_NSS_ENABLE(); 	                                    // ʧ��CS
	
	/* �ٴμ���Ƿ�æ */
	CheckBusy();
	
	/* дʹ�� */
	SPI_NSS_DISABLE();	                                    // ʹ��CS
	HAL_SPI_Transmit(&MY_HSPI, &enable_write, 1, 100);		// ����ָ��
	SPI_NSS_ENABLE(); 	                                    // ʧ��CS

	/* д���� */
	SPI_NSS_DISABLE();	                                    // ʹ��CS
	HAL_SPI_Transmit(&MY_HSPI, &write_addr, 1, 100);		// ����ָ��
	HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, 100);				// ��ַ
	HAL_SPI_Transmit(&MY_HSPI, temp_wdata, 5, 100);			// д������
	SPI_NSS_ENABLE(); 	                                    // ʧ��CS
}

/* ��ȡ���� */
void ReadData(void)
{
	/* ����Ƿ�æ */
	CheckBusy();	
	
	/* ��ʼ������ */
	SPI_NSS_DISABLE();	                                    // ʹ��CS
	HAL_SPI_Transmit(&MY_HSPI, &read_addr, 1, 100);			// ������ָ��
	HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, 100);				// ��ַ
	HAL_SPI_Receive(&MY_HSPI,  temp_rdata, 5, 100);			// �õ�����
	SPI_NSS_ENABLE(); 	                                    // ʧ��CS
}


