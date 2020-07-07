  /*
  ******************************************************************************
  * @file     : Ficus_CNT_Counter.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_CNT_Counter demo
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
   A demo program for 4 channel CNT control with:
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

   Ficus lead out 100% chip's resource for usage, for GPIO, it's more than 16 channel could be used. The demo shows defined pin number's usage
   It could be used with I2C, GPIO, CAN (driver module required) simultaneously.

   PIN definition rule and one example: 
   (1)J2_P1_CNT_CH0 
   (2)J2_P5_CNT_CH1	
   (3)J18_P5_CNT_CH2
   (4)J18_P10_CNT_CH0 
   (5)J18_P8_CNT_CH1
   (6)J28_P4_CNT_CH3


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
#include "ControlCNT.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_counter.h"
#include "func_map.h"
#endif

int main(int argc, char* argv[])
{
	int ret;
	//Scan device
	ret = CNT_ScanDevice(1);
	if(ret <= 0){
		printf("No device connected!\n");
		return ret;
	}
	//Open device
	ret = CNT_OpenDevice(CNT_USBCNT,0,0);
	if(ret != ERR_SUCCESS){
		printf("Open device error!\n");
		return ret;
	}
	//Config device
	CNT_INIT_CONFIG CNTConfig;
	CNTConfig.CounterBitWide = 32;
	CNTConfig.CounterMode = 0;
	CNTConfig.CounterPolarity = 0;
	ret = CNT_InitCounter(CNT_USBCNT,0,CNT_CH0,&CNTConfig);
	if(ret != ERR_SUCCESS){
		printf("Config device error!\n");
		return ret;
	}
	//Clear counter
	uint32_t CounterValue[4]={0,0,0,0};
	ret = CNT_SetCounter(CNT_USBCNT,0,CNT_CH0,CounterValue);
	if(ret != ERR_SUCCESS){ 
		printf("Set counter value error!\n");
		return ret;
	}
	//Start counter
	ret = CNT_StartCounter(CNT_USBCNT,0,CNT_CH0);
	if(ret != ERR_SUCCESS){
		printf("Start counter error!\n");
		return ret;
	}
	while(1)
	{
		//Get counter value
		ret = CNT_GetCounter(CNT_USBCNT,0,CNT_CH0,CounterValue);
		if(ret != ERR_SUCCESS){
			printf("Get counter value error!\n");
			//break;
		}else{
			printf("Counter Value :%d\n",CounterValue[0]);
		}
		Sleep(1000);
	}
	//Stop counter
	ret = CNT_StopCounter(CNT_USBCNT,0,CNT_CH0);
	if(ret != ERR_SUCCESS){
		printf("Stop counter error!\n");
		return ret;
	}
	return 0;
}

