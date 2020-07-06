  /*
  ******************************************************************************
  * @file     : Ficus_SPI_W25Q32.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_SPI_W25Q32 Demo
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
#include "ControlSPI.h"
#else 
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_spi.h"
#include "func_map.h"
#endif
#include <stdlib.h>

#define	SLAVE_WRITE	    0
#define SLAVE_READ	    1
#define DEVICE_INDEX	0

int main(void)
{
    int ret;
	VSI_INIT_CONFIG SPI_Config;
	VSI_BOARD_INFO BoardInfo;
    // Scan device
    ret = VSI_ScanDevice(1);
    if (ret <= 0){
        printf("No device connect!\n");
        return ret;
    }
    // Open device
    ret = VSI_OpenDevice(VSI_USBSPI, DEVICE_INDEX, 0);
    if (ret != ERR_SUCCESS){
        printf("Open device error!\n");
        return ret;
    }
	// Get board information
	ret = VSI_ReadBoardInfo(DEVICE_INDEX,&BoardInfo);
    if (ret != ERR_SUCCESS){
        printf("Read board information error!\n");
        return ret;
    }else{
		printf("Product Name:%s\n",BoardInfo.ProductName);
		printf("Firmware Version:V%d.%d.%d\n",BoardInfo.FirmwareVersion[1],BoardInfo.FirmwareVersion[2],BoardInfo.FirmwareVersion[3]);
		printf("Hardware Version:V%d.%d.%d\n",BoardInfo.HardwareVersion[1],BoardInfo.HardwareVersion[2],BoardInfo.HardwareVersion[3]);
		printf("Serial Number:");
		for(int i=0;i<12;i++){
			printf("%02X",BoardInfo.SerialNumber[i]);
		}
		printf("\n");
	}
    // Initializes the device
    SPI_Config.ControlMode = 1;
    SPI_Config.MasterMode = 0;
    SPI_Config.ClockSpeed = 42000000;
    SPI_Config.CPHA = 0;
    SPI_Config.CPOL = 0;
    SPI_Config.LSBFirst = 0;
    SPI_Config.TranBits = 8;
	SPI_Config.SelPolarity = 0;
    ret = VSI_InitSPI(VSI_USBSPI, DEVICE_INDEX, &SPI_Config);
    if (ret != ERR_SUCCESS){
        printf("Initialize device error!\n");
        return ret;
    }
	uint8_t write_buffer[10240];
	uint8_t read_buffer[10240];
#if SLAVE_WRITE
    for(int i=0;i<64;i++){
        write_buffer[i] = i;
    }
    ret = VSI_SlaveWriteBytes(VSI_USBSPI,DEVICE_INDEX,write_buffer,64);
    if(ret != ERR_SUCCESS){
        printf("Slave write data error!\n");
        return ret;
    }
#endif
#if SLAVE_READ
	// Get data
	while(1)
	{
		int read_data_num = 0;
		ret = VSI_SlaveReadBytes(VSI_USBSPI, DEVICE_INDEX, read_buffer, &read_data_num,100);
		if (ret != ERR_SUCCESS){
			printf("Read data error!\n");
			return ret;
		}else{
			if (read_data_num > 0){
				printf("Read data(Hex):\n");
				for (int i = 0; i < read_data_num; i++){
					printf("%02X ",read_buffer[i]);
				}
				printf("\n");
			}
		}
		Sleep(100);
	}
#endif
	return 0;
}

