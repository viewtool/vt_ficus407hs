  /*
  ******************************************************************************
  * @file     : Ficus_SPI_SlaveWriteRead.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_SPI_SlaveWriteRead Demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2019-2020, ViewTool
  * http://www.viewtool.com/
  * All Rights Reserved
  * 
  ******************************************************************************
  */
/*
   A demo program for SlaveWriteRead SPI control with:
   HW: FicusF4HS (STM32F407VET on board)
   FW: >= 
               Product name : FicusF4
               Firmware version : 1.0.2
               Hardware version : 2.1.0
   IDE: Keilv5 (or above)

   Ficus:
   http://www.viewtool.com/index.php/en/36-2016-09-26-03-58-56/271-ficus-stm32f407hs-high-speed-development-board
   
   Pin layout and definition:
   http://www.viewtool.com/demo/STM32/Ficus_document_html/index.html

   Ficus lead out 100% chip's resource for usage, for GPIO, it's more channel could be used. The demo shows defined pin number's usage
   It could be used with I2C, GPIO, CAN (driver module required) simultaneously.

   PIN definition rule and one example: 
   J8_P2_SPI0_MISO J8_P4_SPI0_MOSI J18_P3_SPI0_CLK 
   (1)J8_P2_P4_P6_P8_SPI0_NSS0    
   (9)J8_P1_P3_P5_P7_SPI1_NSS8    	

   1. socket definition: 
   J8 definition example (see above link for detail): 
   GND          1  2     P1  GPIOE_5    <--------------------- socket pin name for J15_P1_GPIO
   GND          3  4     P2  GPIOE_6  
   GND          5  6     P3  GPIOC_13  
   GPIOE_2  P4  7  8     P5  GPIOC_0  
   GPIOC_1  P6  9  10    P7  GPIOA_2  
   GPIOC_2  P8  11  12   P9  GPIOA_3  
   GND  13      14  P10      GPIOE_3  
   GND  15      16  P11      GPIOE_4 


   2. GPIO pin macro definitoin used in all of ficus board related programs:
   J15_P1_GPIO:  --------> GPIO pin macro defintion
   |   |   |____ usage: GPIO, fixed 
   |   |________ pinout index (at this socket), P1: index = 1, it's GPIOE_5 @ socket num 2 position
   |____________ FICUS board socket number (see above pin layout for more detail), J15: 2x8 pinout socket

   GPIOE_5: socket pinout name, equal to STM32FXXX standard GPIO pin definition: port = GPIOE, pin = GPIO_PIN_5
       | |____ pin index: 5  = GPIO_PIN_5
	   |______ port index: E = GPIOE

   3. check pin macro defition in func_map.h:
   #define J15_P1_GPIO  (VGI_GPIO_PORTE|VGI_GPIO_PIN5)
                                      |             |_____ GPIO_PIN_5
									  |___________________ GPIOE
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
    SPI_Config.ClockSpeed = 1;
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

