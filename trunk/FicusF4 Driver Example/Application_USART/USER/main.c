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
#endif

#define UART_CHANNEL_INDEX 0

int main(int argc, char* argv[])
{
	uint16_t Len = 0;
	uint8_t ReadBuffer[64]={0};
	uint32_t AllDataNum = 0;
	int ret,i=0;
	UART_INIT_CONFIG InitConfig;
	uint8_t WriteBuffer[64]={0};
	ret = UART_ScanDevice(1);
	if(ret <= 0){
		printf("No device connected!\r\n");
		return 0;
	}
	ret = UART_OpenDevice(UART_USBUART,0,0);
	if(ret != ERR_SUCCESS){
		printf("Open device error!\r\n");
		return 0;
	}
	InitConfig.BaudRate = 115200;
	InitConfig.Parity = 0;
	InitConfig.RS485Mode = 485;
	InitConfig.StopBits = 0;
	InitConfig.WordLength = 8;
	ret = UART_InitDevice(UART_USBUART,0,UART_CHANNEL_INDEX,&InitConfig);
	if(ret != ERR_SUCCESS){
		printf("Initialize device error!\r\n");
		return 0;
	}
	for(i=0;i<sizeof(WriteBuffer);i++){
		WriteBuffer[i] = i;
	}
	ret = UART_WriteBytes(UART_USBUART,0,UART_CHANNEL_INDEX,WriteBuffer,64);
	if(ret != ERR_SUCCESS){
		printf("Write data error!\r\n");
		return 0;
	}

	while(1){
		ret = UART_ReadBytes(UART_USBUART,0,UART_CHANNEL_INDEX,ReadBuffer,&Len);
		if(ret == ERR_READ_NO_DATA){
//			Sleep(50);
			continue;
		}else if(ret == ERR_SUCCESS){
			if(Len > 0){
				AllDataNum += Len;
				for(i=0;i<Len;i++){
					printf("%02X ",ReadBuffer[i]);
				}
                if((AllDataNum % 8) == 0)
                {
                    printf("\r\n");  
                }
				
				Len = 0;
                if(AllDataNum == 64)
                {
                    AllDataNum = 0;
                    printf("\r\n");
                    printf("\r\n");
                }
                
				//break;
			}
//			Sleep(50);
		
		}else{
			printf("Read data error!\r\n");
			//return 0;
		}
	}
	return 0;
}

