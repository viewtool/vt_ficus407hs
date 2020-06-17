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
