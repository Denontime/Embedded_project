/**
  ******************************************************************************
  * @file    bsp_flash.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_flash.h"

/*FLASH ��������*/
uint8_t W25X_WriteEnable       = 0x06;       // ʹ���˲��ܸı�оƬ����
uint8_t W25X_WriteDisable      = 0x04;       // ʧ��оƬд����
uint8_t W25X_ReadStatusReg     = 0x05;       // �����·�Ƿ�æ
uint8_t W25X_WriteStatusReg    = 0x01;       // д��״̬
uint8_t W25X_ReadData          = 0x03;       // ����������
uint8_t W25X_FastReadData      = 0x0B;       // ���ٶ�����
uint8_t W25X_FastReadDual      = 0x3B;       // ���ٶ�ȡ˫���
uint8_t W25X_PageProgram       = 0x02;       // д��������
uint8_t W25X_BlockErase        = 0xD8;       // �������64k��
uint8_t W25X_SectorErase       = 0x20;       // ָ����������
uint8_t W25X_ChipErase         = 0xC7;       // оƬ����
uint8_t W25X_PowerDown         = 0xB9;       // �µ�
uint8_t W25X_ReleasePowerDown  = 0xAB;       // �Ƴ�����
uint8_t W25X_DeviceID          = 0xAB;       // �豸ID
uint8_t W25X_ManufactDeviceID  = 0x90;       // ������/�豸ID
uint8_t W25X_JedecDeviceID     = 0x9F;       // ��ID
uint8_t Dummy_Byte             = 0xFF;

/* ��ID */
uint32_t w25x_ReadFlashID(void)
{
    uint32_t Device_id = 0;
    uint8_t w25x_ID[3] = {0, 0, 0};                         // ���ջ���

    FLASH_SPI_CS_ENABLE();                                                      // ʹ��CS
    HAL_SPI_Transmit(&MY_HSPI, &W25X_JedecDeviceID, 1, SPI_FLASH_TIMEOUT);      // ��ID����ָ��
    HAL_SPI_Receive(&MY_HSPI, w25x_ID, 3, SPI_FLASH_TIMEOUT);                   // ��ȡID
    FLASH_SPI_CS_DISABLE();                                                     // ʧ��CS

    Device_id = (w25x_ID[0] << 16) | (w25x_ID[1] << 8) | w25x_ID[2];
    return Device_id;
}

/**
 * @brief  ��ȡFLASH Device ID
 * @param 	��
 * @retval FLASH Device ID
 */
uint32_t w25x_ReadDeviceID(void)
{
    uint8_t Temp = 0;

    /* Select the FLASH: Chip Select low */
    FLASH_SPI_CS_ENABLE();

    /* Send "RDID " instruction */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_DeviceID, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, &Dummy_Byte, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, &Dummy_Byte, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, &Dummy_Byte, 1, SPI_FLASH_TIMEOUT);

    /* Read a byte from the FLASH */
    HAL_SPI_Receive(&MY_HSPI, &Temp, 3, SPI_FLASH_TIMEOUT);

    /* Deselect the FLASH: Chip Select high */
    FLASH_SPI_CS_DISABLE();

    return (uint32_t)Temp;
}

/* ����Ƿ�æ */
void w25x_CheckBusy(void)
{
    uint8_t FLASH_Status = 1;
    uint32_t timeCount = 0;

    FLASH_SPI_CS_ENABLE();                                      // ʹ��CS

    do
    {
        timeCount++;
        if(timeCount > 0xEFFFFFFF) //�ȴ���ʱ
        {
            return ;
        }
        HAL_SPI_Transmit(&MY_HSPI, &W25X_ReadStatusReg, 1, SPI_FLASH_TIMEOUT);          // ����ָ��
        HAL_SPI_Receive(&MY_HSPI, &FLASH_Status, 1, SPI_FLASH_TIMEOUT);                 // ��ȡ
    }
    while((FLASH_Status & WIP_Flag) == WIP_Flag);

    FLASH_SPI_CS_DISABLE();                                     // ʧ��CS
}

/**
* @brief �� FLASH ���� дʹ�� ����
* @param none
* @retval none
*/
void w25x_WriteEnable(void)
{
    /* дʹ�� */
    FLASH_SPI_CS_ENABLE();                                                      // ʹ��CS
    HAL_SPI_Transmit(&MY_HSPI, &W25X_WriteEnable, 1, SPI_FLASH_TIMEOUT);        // ����ָ��
    FLASH_SPI_CS_DISABLE();                                                     // ʧ��CS
}

/**
 * @brief  ����FLASH����
 * @param  SectorAddr��Ҫ������������ַ
 * @retval ��
 */
void w25x_SectorErase(uint32_t SectorAddr)
{
    w25x_WriteEnable();
    w25x_CheckBusy();

    uint8_t m_addr[3]  = {0, 0, 0};
    m_addr[0] = (SectorAddr & 0xFF0000) >> 16;
    m_addr[1] = (SectorAddr & 0xFF00) >> 8;
    m_addr[2] = SectorAddr & 0xFF;

    /* ���� */
    FLASH_SPI_CS_ENABLE();                                                      // ʹ��CS
    HAL_SPI_Transmit(&MY_HSPI, &W25X_SectorErase, 1, SPI_FLASH_TIMEOUT);        // ����ָ��
    HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, SPI_FLASH_TIMEOUT);                   // ���͵�ַ
    FLASH_SPI_CS_DISABLE();                                                     // ʧ��CS

    w25x_CheckBusy();
}

/**
 * @brief  ����FLASH��������Ƭ����
 * @param  ��
 * @retval ��
 */
void w25x_BulkErase(void)
{
    /* ����FLASHдʹ������ */
    w25x_WriteEnable();

    /* ѡ��FLASH: CS�͵�ƽ */
    FLASH_SPI_CS_ENABLE();
    /* �����������ָ��*/
    HAL_SPI_Transmit(&MY_HSPI, &W25X_ChipErase, 1, SPI_FLASH_TIMEOUT);
    /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
    FLASH_SPI_CS_DISABLE();

    /* �ȴ��������*/
    w25x_CheckBusy();
}

/**
 * @brief  ��FLASH��ҳд�����ݣ����ñ�����д������ǰ��Ҫ�Ȳ�������
 * @param   pBuffer��Ҫд�����ݵ�ָ��
 * @param WriteAddr��д���ַ
 * @param  NumByteToWrite��д�����ݳ��ȣ�����С�ڵ���SPI_FLASH_PerWritePageSize
 * @retval ��
 */
void w25x_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t m_addr[3]  = {0, 0, 0};
    m_addr[0] = (WriteAddr & 0xFF0000) >> 16;
    m_addr[1] = (WriteAddr & 0xFF00) >> 8;
    m_addr[2] = WriteAddr & 0xFF;

    /* ����FLASHдʹ������ */
    w25x_WriteEnable();

    /* ѡ��FLASH: CS�͵�ƽ */
    FLASH_SPI_CS_ENABLE();
    /* дҳдָ��*/
    HAL_SPI_Transmit(&MY_HSPI, &W25X_PageProgram, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, SPI_FLASH_TIMEOUT);               // ���͵�ַ

    if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
        FLASH_ERROR("w25x_PageWrite too large!");
    }

    /* д������*/
    HAL_SPI_Transmit(&MY_HSPI, pBuffer, NumByteToWrite, SPI_FLASH_TIMEOUT);             // ���͵�ַ

    /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
    FLASH_SPI_CS_DISABLE();

    /* �ȴ�д�����*/
    w25x_CheckBusy();
}

/**
 * @brief  ��FLASHд�����ݣ����ñ�����д������ǰ��Ҫ�Ȳ�������
 * @param   pBuffer��Ҫд�����ݵ�ָ��
 * @param  WriteAddr��д���ַ
 * @param  NumByteToWrite��д�����ݳ���
 * @retval ��
 */
void w25x_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    /*mod�������࣬��writeAddr��SPI_FLASH_PageSize��������������AddrֵΪ0*/
    Addr = WriteAddr % SPI_FLASH_PageSize;

    /*��count������ֵ���պÿ��Զ��뵽ҳ��ַ*/
    count = SPI_FLASH_PageSize - Addr;
    /*�����Ҫд��������ҳ*/
    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
    /*mod�������࣬�����ʣ�಻��һҳ���ֽ���*/
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    /* Addr=0,��WriteAddr �պð�ҳ���� aligned  */
    if (Addr == 0)
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            w25x_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*�Ȱ�����ҳ��д��*/
            while (NumOfPage--)
            {
                w25x_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            /*���ж���Ĳ���һҳ�����ݣ�����д��*/
            w25x_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    /* ����ַ�� SPI_FLASH_PageSize ������  */
    else
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            /*��ǰҳʣ���count��λ�ñ�NumOfSingleС��һҳд����*/
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                /*��д����ǰҳ*/
                w25x_PageWrite(pBuffer, WriteAddr, count);

                WriteAddr +=  count;
                pBuffer += count;
                /*��дʣ�������*/
                w25x_PageWrite(pBuffer, WriteAddr, temp);
            }
            else /*��ǰҳʣ���count��λ����д��NumOfSingle������*/
            {
                w25x_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*��ַ����������count�ֿ������������������*/
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            /* ��д��count�����ݣ�Ϊ��������һ��Ҫд�ĵ�ַ���� */
            w25x_PageWrite(pBuffer, WriteAddr, count);

            /* ���������ظ���ַ�������� */
            WriteAddr +=  count;
            pBuffer += count;
            /*������ҳ��д��*/
            while (NumOfPage--)
            {
                w25x_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            /*���ж���Ĳ���һҳ�����ݣ�����д��*/
            if (NumOfSingle != 0)
            {
                w25x_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
 * @brief  ��ȡFLASH����
 * @param   pBuffer���洢�������ݵ�ָ��
 * @param   ReadAddr����ȡ��ַ
 * @param   NumByteToRead����ȡ���ݳ���
 * @retval ��
 */
void w25x_ReadData(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t m_addr[3]  = {0, 0, 0};
    m_addr[0] = (ReadAddr & 0xFF0000) >> 16;
    m_addr[1] = (ReadAddr & 0xFF00) >> 8;
    m_addr[2] = ReadAddr & 0xFF;

    /* ѡ��FLASH: CS�͵�ƽ */
    FLASH_SPI_CS_ENABLE();

    /* ���� �� ָ�� */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_ReadData, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, SPI_FLASH_TIMEOUT);               // ���͵�ַ

    /* ��ȡ���� */
    HAL_SPI_Receive(&MY_HSPI, pBuffer, NumByteToRead, SPI_FLASH_TIMEOUT);                   // ��ȡID

    /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
    FLASH_SPI_CS_DISABLE();
}


//�������ģʽ
void w25x_PowerDown(void)
{
    /* ͨѶ��ʼ��CS�� */
    FLASH_SPI_CS_ENABLE();

    /* ���� ���� ���� */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_PowerDown, 1, SPI_FLASH_TIMEOUT);

    /*ͨѶ������CS�� */
    FLASH_SPI_CS_DISABLE();
}

//����
void w25x_WAKEUP(void)
{
    /*ѡ�� FLASH: CS �� */
    FLASH_SPI_CS_ENABLE();

    /* ���� �ϵ� ���� */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_ReleasePowerDown, 1, SPI_FLASH_TIMEOUT);

    /* ֹͣ�ź� FLASH: CS �� */
    FLASH_SPI_CS_DISABLE();
}
