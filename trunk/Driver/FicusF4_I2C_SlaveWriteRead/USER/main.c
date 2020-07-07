  /*
  ******************************************************************************
  * @file     : Ficus_I2C_AT24C02.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2020/10/23
  * @brief    : Ficus_I2C_AT24C02 demo
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
   A demo program for 2 channel I2C control with:
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
   (1)J28_P2_P4_I2C		 
   (2)J28_P1_P3_I2C      

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
#include "ControlI2C.h"
#else
#include "stm32f4xx_conf.h"
#include "vt_i2c.h"
#include "func_map.h"
#endif

int main(int argc, char* argv[])
{
	int ret,i;
	VII_INIT_CONFIG I2C_Config;
	VII_BOARD_INFO BoardInfo;
	uint16_t SlaveReadLen;
	uint8_t write_buffer[512]={0};
	uint8_t	read_buffer[512]={0};
	//Scan device
	ret = VII_ScanDevice(1);
	if(ret <= 0){
		printf("No device connect!\n");
		return ret;
	}
    //Open device
    ret = VII_OpenDevice(VII_USBI2C, 0, 0);
    if (ret != ERR_SUCCESS){
        printf("Open device error!\n");
        return ret;
    }
	//Get product information
	ret = VII_ReadBoardInfo(0,&BoardInfo);
    if (ret != ERR_SUCCESS){
        printf("Read board information error!\n");
        return ret;
    }else{
		printf("Product Name:%s\n",BoardInfo.ProductName);
		printf("Firmware Version:V%d.%d.%d\n",BoardInfo.FirmwareVersion[1],BoardInfo.FirmwareVersion[2],BoardInfo.FirmwareVersion[3]);
		printf("Hardware Version:V%d.%d.%d\n",BoardInfo.HardwareVersion[1],BoardInfo.HardwareVersion[2],BoardInfo.HardwareVersion[3]);
		printf("Serial Number:");
		for(i=0;i<12;i++){
			printf("%02X",BoardInfo.SerialNumber[i]);
		}
		printf("\n");
	}
    //Initializes the device
    I2C_Config.AddrType = VII_ADDR_7BIT;
    I2C_Config.ClockSpeed = 400000;
    I2C_Config.ControlMode = VII_HCTL_SLAVE_MODE;
    I2C_Config.MasterMode = VII_SLAVE;
    I2C_Config.SubAddrWidth = VII_SUB_ADDR_NONE;
	I2C_Config.Addr = 0xA0;	//Must be set,very important
    ret = VII_InitI2C(VII_USBI2C, 0, 0, &I2C_Config);
    if (ret != ERR_SUCCESS){
        printf("Initialize device error!\n");
        return ret;
    }
	//Slave write data
	for (i = 0; i < 16; i++){
        write_buffer[i] = i;
    }
    ret = VII_SlaveWriteBytes(VII_USBI2C, 0, 0, write_buffer, 16);
    if (ret != ERR_SUCCESS){
        printf("Slave write data error!\n");
        return ret;
    }else{
		printf("Write Data:\n");
		for(i=0;i<16;i++){
			printf("%02X ",write_buffer[i]);
			if(((i+1)%16)==0){
				printf("\n");
			}
		}
	}
	//Slave read data
	while(1){
		Sleep(50);
		ret = VII_SlaveReadBytes(VII_USBI2C, 0, 0,read_buffer,&SlaveReadLen);
		if((ret == ERR_SUCCESS)&&(SlaveReadLen > 0)){
			printf("Read Data:\n");
			for(i=0;i<SlaveReadLen;i++){
				printf("%02X ",read_buffer[i]);
				if(((i+1)%16)==0){
					printf("\n");
				}
			}
			printf("\n");
			continue;
		}
		if(ret == ERR_READ_NO_DATA){
			continue;
		}else{
			printf("Slave read data error!\n");
			return ret;
		}
	}
	return 0;
}

