/**
  ******************************************************************************
  * @file    bsp_flash.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_flash.h"

/*FLASH 常用命令*/
uint8_t W25X_WriteEnable       = 0x06;       // 使能了才能改变芯片数据
uint8_t W25X_WriteDisable      = 0x04;       // 失能芯片写数据
uint8_t W25X_ReadStatusReg     = 0x05;       // 检查线路是否繁忙
uint8_t W25X_WriteStatusReg    = 0x01;       // 写入状态
uint8_t W25X_ReadData          = 0x03;       // 读数据命令
uint8_t W25X_FastReadData      = 0x0B;       // 快速读数据
uint8_t W25X_FastReadDual      = 0x3B;       // 快速读取双输出
uint8_t W25X_PageProgram       = 0x02;       // 写数据命令
uint8_t W25X_BlockErase        = 0xD8;       // 块擦除（64k）
uint8_t W25X_SectorErase       = 0x20;       // 指定擦除命令
uint8_t W25X_ChipErase         = 0xC7;       // 芯片擦除
uint8_t W25X_PowerDown         = 0xB9;       // 下电
uint8_t W25X_ReleasePowerDown  = 0xAB;       // 移除掉电
uint8_t W25X_DeviceID          = 0xAB;       // 设备ID
uint8_t W25X_ManufactDeviceID  = 0x90;       // 制造商/设备ID
uint8_t W25X_JedecDeviceID     = 0x9F;       // 读ID
uint8_t Dummy_Byte             = 0xFF;

/* 读ID */
uint32_t w25x_ReadFlashID(void)
{
    uint32_t Device_id = 0;
    uint8_t w25x_ID[3] = {0, 0, 0};                         // 接收缓存

    FLASH_SPI_CS_ENABLE();                                                      // 使能CS
    HAL_SPI_Transmit(&MY_HSPI, &W25X_JedecDeviceID, 1, SPI_FLASH_TIMEOUT);      // 读ID发送指令
    HAL_SPI_Receive(&MY_HSPI, w25x_ID, 3, SPI_FLASH_TIMEOUT);                   // 读取ID
    FLASH_SPI_CS_DISABLE();                                                     // 失能CS

    Device_id = (w25x_ID[0] << 16) | (w25x_ID[1] << 8) | w25x_ID[2];
    return Device_id;
}

/**
 * @brief  读取FLASH Device ID
 * @param 	无
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

/* 检查是否繁忙 */
void w25x_CheckBusy(void)
{
    uint8_t FLASH_Status = 1;
    uint32_t timeCount = 0;

    FLASH_SPI_CS_ENABLE();                                      // 使能CS

    do
    {
        timeCount++;
        if(timeCount > 0xEFFFFFFF) //等待超时
        {
            return ;
        }
        HAL_SPI_Transmit(&MY_HSPI, &W25X_ReadStatusReg, 1, SPI_FLASH_TIMEOUT);          // 发送指令
        HAL_SPI_Receive(&MY_HSPI, &FLASH_Status, 1, SPI_FLASH_TIMEOUT);                 // 读取
    }
    while((FLASH_Status & WIP_Flag) == WIP_Flag);

    FLASH_SPI_CS_DISABLE();                                     // 失能CS
}

/**
* @brief 向 FLASH 发送 写使能 命令
* @param none
* @retval none
*/
void w25x_WriteEnable(void)
{
    /* 写使能 */
    FLASH_SPI_CS_ENABLE();                                                      // 使能CS
    HAL_SPI_Transmit(&MY_HSPI, &W25X_WriteEnable, 1, SPI_FLASH_TIMEOUT);        // 发送指令
    FLASH_SPI_CS_DISABLE();                                                     // 失能CS
}

/**
 * @brief  擦除FLASH扇区
 * @param  SectorAddr：要擦除的扇区地址
 * @retval 无
 */
void w25x_SectorErase(uint32_t SectorAddr)
{
    w25x_WriteEnable();
    w25x_CheckBusy();

    uint8_t m_addr[3]  = {0, 0, 0};
    m_addr[0] = (SectorAddr & 0xFF0000) >> 16;
    m_addr[1] = (SectorAddr & 0xFF00) >> 8;
    m_addr[2] = SectorAddr & 0xFF;

    /* 擦除 */
    FLASH_SPI_CS_ENABLE();                                                      // 使能CS
    HAL_SPI_Transmit(&MY_HSPI, &W25X_SectorErase, 1, SPI_FLASH_TIMEOUT);        // 发送指令
    HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, SPI_FLASH_TIMEOUT);                   // 发送地址
    FLASH_SPI_CS_DISABLE();                                                     // 失能CS

    w25x_CheckBusy();
}

/**
 * @brief  擦除FLASH扇区，整片擦除
 * @param  无
 * @retval 无
 */
void w25x_BulkErase(void)
{
    /* 发送FLASH写使能命令 */
    w25x_WriteEnable();

    /* 选择FLASH: CS低电平 */
    FLASH_SPI_CS_ENABLE();
    /* 发送整块擦除指令*/
    HAL_SPI_Transmit(&MY_HSPI, &W25X_ChipErase, 1, SPI_FLASH_TIMEOUT);
    /* 停止信号 FLASH: CS 高电平 */
    FLASH_SPI_CS_DISABLE();

    /* 等待擦除完毕*/
    w25x_CheckBusy();
}

/**
 * @brief  对FLASH按页写入数据，调用本函数写入数据前需要先擦除扇区
 * @param   pBuffer，要写入数据的指针
 * @param WriteAddr，写入地址
 * @param  NumByteToWrite，写入数据长度，必须小于等于SPI_FLASH_PerWritePageSize
 * @retval 无
 */
void w25x_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t m_addr[3]  = {0, 0, 0};
    m_addr[0] = (WriteAddr & 0xFF0000) >> 16;
    m_addr[1] = (WriteAddr & 0xFF00) >> 8;
    m_addr[2] = WriteAddr & 0xFF;

    /* 发送FLASH写使能命令 */
    w25x_WriteEnable();

    /* 选择FLASH: CS低电平 */
    FLASH_SPI_CS_ENABLE();
    /* 写页写指令*/
    HAL_SPI_Transmit(&MY_HSPI, &W25X_PageProgram, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, SPI_FLASH_TIMEOUT);               // 发送地址

    if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
    {
        NumByteToWrite = SPI_FLASH_PerWritePageSize;
        FLASH_ERROR("w25x_PageWrite too large!");
    }

    /* 写入数据*/
    HAL_SPI_Transmit(&MY_HSPI, pBuffer, NumByteToWrite, SPI_FLASH_TIMEOUT);             // 发送地址

    /* 停止信号 FLASH: CS 高电平 */
    FLASH_SPI_CS_DISABLE();

    /* 等待写入完毕*/
    w25x_CheckBusy();
}

/**
 * @brief  对FLASH写入数据，调用本函数写入数据前需要先擦除扇区
 * @param   pBuffer，要写入数据的指针
 * @param  WriteAddr，写入地址
 * @param  NumByteToWrite，写入数据长度
 * @retval 无
 */
void w25x_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    /*mod运算求余，若writeAddr是SPI_FLASH_PageSize整数倍，运算结果Addr值为0*/
    Addr = WriteAddr % SPI_FLASH_PageSize;

    /*差count个数据值，刚好可以对齐到页地址*/
    count = SPI_FLASH_PageSize - Addr;
    /*计算出要写多少整数页*/
    NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
    /*mod运算求余，计算出剩余不满一页的字节数*/
    NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

    /* Addr=0,则WriteAddr 刚好按页对齐 aligned  */
    if (Addr == 0)
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            w25x_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*先把整数页都写了*/
            while (NumOfPage--)
            {
                w25x_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            /*若有多余的不满一页的数据，把它写完*/
            w25x_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    /* 若地址与 SPI_FLASH_PageSize 不对齐  */
    else
    {
        /* NumByteToWrite < SPI_FLASH_PageSize */
        if (NumOfPage == 0)
        {
            /*当前页剩余的count个位置比NumOfSingle小，一页写不完*/
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;
                /*先写满当前页*/
                w25x_PageWrite(pBuffer, WriteAddr, count);

                WriteAddr +=  count;
                pBuffer += count;
                /*再写剩余的数据*/
                w25x_PageWrite(pBuffer, WriteAddr, temp);
            }
            else /*当前页剩余的count个位置能写完NumOfSingle个数据*/
            {
                w25x_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /* NumByteToWrite > SPI_FLASH_PageSize */
        {
            /*地址不对齐多出的count分开处理，不加入这个运算*/
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
            NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

            /* 先写完count个数据，为的是让下一次要写的地址对齐 */
            w25x_PageWrite(pBuffer, WriteAddr, count);

            /* 接下来就重复地址对齐的情况 */
            WriteAddr +=  count;
            pBuffer += count;
            /*把整数页都写了*/
            while (NumOfPage--)
            {
                w25x_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
                WriteAddr +=  SPI_FLASH_PageSize;
                pBuffer += SPI_FLASH_PageSize;
            }
            /*若有多余的不满一页的数据，把它写完*/
            if (NumOfSingle != 0)
            {
                w25x_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
 * @brief  读取FLASH数据
 * @param   pBuffer，存储读出数据的指针
 * @param   ReadAddr，读取地址
 * @param   NumByteToRead，读取数据长度
 * @retval 无
 */
void w25x_ReadData(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint8_t m_addr[3]  = {0, 0, 0};
    m_addr[0] = (ReadAddr & 0xFF0000) >> 16;
    m_addr[1] = (ReadAddr & 0xFF00) >> 8;
    m_addr[2] = ReadAddr & 0xFF;

    /* 选择FLASH: CS低电平 */
    FLASH_SPI_CS_ENABLE();

    /* 发送 读 指令 */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_ReadData, 1, SPI_FLASH_TIMEOUT);
    HAL_SPI_Transmit(&MY_HSPI, m_addr, 3, SPI_FLASH_TIMEOUT);               // 发送地址

    /* 读取数据 */
    HAL_SPI_Receive(&MY_HSPI, pBuffer, NumByteToRead, SPI_FLASH_TIMEOUT);                   // 读取ID

    /* 停止信号 FLASH: CS 高电平 */
    FLASH_SPI_CS_DISABLE();
}


//进入掉电模式
void w25x_PowerDown(void)
{
    /* 通讯开始：CS低 */
    FLASH_SPI_CS_ENABLE();

    /* 发送 掉电 命令 */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_PowerDown, 1, SPI_FLASH_TIMEOUT);

    /*通讯结束：CS高 */
    FLASH_SPI_CS_DISABLE();
}

//唤醒
void w25x_WAKEUP(void)
{
    /*选择 FLASH: CS 低 */
    FLASH_SPI_CS_ENABLE();

    /* 发送 上电 命令 */
    HAL_SPI_Transmit(&MY_HSPI, &W25X_ReleasePowerDown, 1, SPI_FLASH_TIMEOUT);

    /* 停止信号 FLASH: CS 高 */
    FLASH_SPI_CS_DISABLE();
}
