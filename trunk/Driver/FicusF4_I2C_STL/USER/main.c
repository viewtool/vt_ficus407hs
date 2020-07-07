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
/*
   A demo program for AT24C02 I2C control with:
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
   (1)J28_P2_P4_I2C_STL_CH0       
   (2)J50_P6_P8_I2C_STL_CH1       
   (3)J50_P10_P12_I2C_STL_CH2     
   (4)J50_P14_P16_I2C_STL_CH3     
   (5)J50_P1_P3_I2C_STL_CH4       
   (6)J50_P5_P7_I2C_STL_CH5       
   (7)J50_P9_P10_I2C_STL_CH6      
   (8)J50_P13_P15_I2C_STL_CH7     
   (9)J18_P1_P5_I2C_STL_CH8       
   (10)J18_P4_P6_I2C_STL_CH9      
   (11)J2_P1_P5_I2C_STL_CH9       
   (12)J8_P1_P3_I2C_STL_CH10      
   (13)J8_P5_J50_P4_I2C_STL_CH11  
   (14)J8_P2_P4_I2C_STL_CH12      
   (15)J8_P6_P8_I2C_STL_CH13      
   (16)J1_P1_P2_I2C_STL_CH14      
   (17)J2_P7_P9_I2C_STL_CH15      
   (18)J2_P17_P19_I2C_STL_CH16    
   (19)J2_P8_P10_I2C_STL_CH17     
   (20)J2_P12_P14_I2C_STL_CH18    
   (21)J5_P1_P7_I2C_STL_CH19      

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
	int ret = 0,i;
    uint8_t I2C_Index = 0;
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
    //Initializes the device
    I2C_Config.AddrType = VII_ADDR_7BIT;
    I2C_Config.ClockSpeed = 400000;
    I2C_Config.ControlMode = VII_SCTL_MODE;
    I2C_Config.MasterMode = VII_MASTER;
    I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
    ret = VII_InitI2C(VII_USBI2C, 0,I2C_Index, &I2C_Config);
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
    ret = VII_TimeConfig(VII_USBI2C, 0, I2C_Index, &I2C_TimeConfig);
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
    ret = VII_WriteBytes(VII_USBI2C, 0, I2C_Index, 0xA0, 0x00, write_buffer, 8);
    if (ret != ERR_SUCCESS)
    {
        printf("Write data error!\r\n");
        return ret;
    }
    //Delay
    Sleep(10);
	//Read 8 byte data from 0x00
    ret = VII_ReadBytes(VII_USBI2C, 0, I2C_Index, 0xA0, 0x00, read_buffer, 8);
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
	return 0;
}

