  /*
  ******************************************************************************
  * @file     : Ficus_UART_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23
  * @brief    : Ficus_UART_Test demo
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
   A demo program for 2 channel USART control with:
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
   (1)J5_P2_P3_UART_CH0		
   (2)J6_P1_P2_UART_CH1		

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
#include "ControlUART.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_usart.h"
#include "func_map.h"
#endif

int main(int argc, char* argv[])
{
	int ret;
	ret = UART_ScanDevice(1);
	if(ret <= 0){
		printf("No device connected!\n");
		return 0;
	}
	ret = UART_OpenDevice(UART_USBUART,0,0);
	if(ret != ERR_SUCCESS){
		printf("Open device error!\n");
		return 0;
	}
	UART_INIT_CONFIG InitConfig;
	InitConfig.BaudRate = 115200;
	InitConfig.Parity = 0;
	InitConfig.RS485Mode = 485;
	InitConfig.StopBits = 0;
	InitConfig.WordLength = 8;
	ret = UART_InitDevice(UART_USBUART,0,0,&InitConfig);
	if(ret != ERR_SUCCESS){
		printf("Initialize device error!\n");
		return 0;
	}
	uint8_t WriteBuffer[64]={0};
	for(int i=0;i<sizeof(WriteBuffer);i++){
		WriteBuffer[i] = i;
	}
	ret = UART_WriteBytes(UART_USBUART,0,0,WriteBuffer,64);
	if(ret != ERR_SUCCESS){
		printf("Write data error!\n");
		return 0;
	}
	uint16_t Len = 0;
	uint8_t ReadBuffer[64]={0};
	uint32_t AllDataNum = 0;
    Sleep(1000);
	while(1){
		ret = UART_ReadBytes(UART_USBUART,0,0,ReadBuffer,&Len);
		if(ret == ERR_READ_NO_DATA){
			Sleep(50);
			continue;
		}else if(ret == ERR_SUCCESS){
			if(Len > 0){
				AllDataNum += Len;
				for(int i=0;i<Len;i++){
					printf("%02X ",ReadBuffer[i]);
					if(((i+1)%16)==0){
						printf("\n");
					}
				}
				printf("\n");
				printf("AllDataNum = %d\n",AllDataNum);
				Len = 0;
			}
			Sleep(50);
		}else{
			printf("Read data error!\n");
			return 0;
		}
	}
	return 0;
}
