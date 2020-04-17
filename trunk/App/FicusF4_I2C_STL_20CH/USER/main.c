  /*
  ******************************************************************************
  * @file     : Ficus_I2C_AT24C02_SCTL.cpp
  * @Copyright: ViewTool 
  * @Revision : Vers 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_I2C_AT24C02_SC19 demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2019-2020, ViewTool
  * http://www.viewtool.com/
  * All Rights Reserved
  * 
  ******************************************************************************
  */
#ifdef WINAPI
#include "stdafx.h"
#include "ControlI2C.h"
#else
#include "stm32f4xx_conf.h"
#include "vt_i2c.h"
#include "func_map.h"
#endif
int main(int argc, char* argv[])
{
	int ret = 0,i,j;
	VII_INIT_CONFIG I2C_Config;
	VII_TIME_CONFIG I2C_TimeConfig;
	uint8_t write_buffer[8]={0};
	uint8_t	read_buffer[8]={0};
	//Scan device
	ret = VII_ScanDevice(1);
	if(ret <= 0)
	{
		printf("No device connect!\r\n");
		return ret;
	}
    //Open device
    ret = VII_OpenDevice(VII_USBI2C, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\r\n");
        return ret;
    }
    I2C_Config.AddrType = VII_ADDR_7BIT;
    I2C_Config.ClockSpeed = 400000;
    I2C_Config.ControlMode = VII_SCTL_MODE;
    I2C_Config.MasterMode = VII_MASTER;
    I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
    ret = VII_InitI2C(VII_USBI2C, 0,J18_P2_P4_I2C_STL_CH0, &I2C_Config);
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize device error!\r\n");
        return ret;
    }
    //Config timing,Unit of time for microseconds
    I2C_TimeConfig.tSU_STA = 5;
    I2C_TimeConfig.tHD_STA = 4;
    I2C_TimeConfig.tLOW = 5; 
    I2C_TimeConfig.tHIGH = 5;
    I2C_TimeConfig.tSU_DAT = 1;
    I2C_TimeConfig.tSU_STO = 4;
    I2C_TimeConfig.tBuf = 5;  
    ret = VII_TimeConfig(VII_USBI2C, 0, J18_P2_P4_I2C_STL_CH0, &I2C_TimeConfig);
    if (ret != ERR_SUCCESS)
    {
        printf("Set time error!\r\n");
        return ret;
    }
    //Write 8 byte data to 0x00
    for (i = 0; i < 8; i++)
    {
        write_buffer[i] = i;
    }
    ret = VII_WriteBytes(VII_USBI2C, 0, J18_P2_P4_I2C_STL_CH0, 0xA0, 0x00, write_buffer, 8);
    if (ret != ERR_SUCCESS)
    {
        printf("Write data error!\r\n");
        return ret;
    }
    //Delay
    Sleep(10);
    //Read 8 byte data from 0x00
    ret = VII_ReadBytes(VII_USBI2C, 0, J18_P2_P4_I2C_STL_CH0, 0xA0, 0x00, read_buffer, 8);
    if (ret != ERR_SUCCESS)
    {
        printf("Read data error!\r\n");
        return ret;
    }
    else
    {
        printf("Read Data:\r\n");
        for(i=0;i<8;i++)
        {
            printf("%02X ",read_buffer[i]);
        }	
        printf("\r\n");
//		Sleep(1);
    }
    //Initializes the device
    for(j=1;j<20;j++)
    {
        I2C_Config.AddrType = VII_ADDR_7BIT;
        I2C_Config.ClockSpeed = 400000;
        I2C_Config.ControlMode = VII_SCTL_MODE;
        I2C_Config.MasterMode = VII_MASTER;
        I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
        ret = VII_InitI2C(VII_USBI2C, 0,j, &I2C_Config);
        if (ret != ERR_SUCCESS)
        {
            printf("Initialize device error!\r\n");
            return ret;
        }
        //Config timing,Unit of time for microseconds
        I2C_TimeConfig.tSU_STA = 5;
        I2C_TimeConfig.tHD_STA = 4;
        I2C_TimeConfig.tLOW = 5; 
        I2C_TimeConfig.tHIGH = 5;
        I2C_TimeConfig.tSU_DAT = 1;
        I2C_TimeConfig.tSU_STO = 4;
        I2C_TimeConfig.tBuf = 5;  
        ret = VII_TimeConfig(VII_USBI2C, 0, j, &I2C_TimeConfig);
        if (ret != ERR_SUCCESS)
        {
            printf("Set time error!\r\n");
            return ret;
        }
        //Write 8 byte data to 0x00
        for (i = 0; i < 8; i++)
        {
            write_buffer[i] = i;
        }
        ret = VII_WriteBytes(VII_USBI2C, 0, j, 0xA0, 0x00, write_buffer, 8);
        if (ret != ERR_SUCCESS)
        {
            printf("Write data error!\r\n");
            return ret;
        }
        //Delay
        Sleep(10);
        //Read 8 byte data from 0x00
        ret = VII_ReadBytes(VII_USBI2C, 0, j, 0xA0, 0x00, read_buffer, 8);
        if (ret != ERR_SUCCESS)
        {
            printf("Read data error!\r\n");
            return ret;
        }
        else
        {
            printf("Read Data:\r\n");
            for(i=0;i<8;i++)
            {
                printf("%02X ",read_buffer[i]);
            }	
            printf("\r\n");
    //		Sleep(1);
        }   
    }

	return 0;
}

