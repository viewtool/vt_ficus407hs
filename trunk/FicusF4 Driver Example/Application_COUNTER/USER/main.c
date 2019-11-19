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
#ifdef WINAPI
#include "stdafx.h"
#include "ControlCNT.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_counter.h"
#endif

int main(int argc, char* argv[])
{
	int ret;
	//Config device
	CNT_INIT_CONFIG CNTConfig;
	//Clear counter
	uint32_t CounterValue[4]={0,0,0,0};	
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
	CNTConfig.CounterBitWide = 32;
	CNTConfig.CounterMode = 0;
	CNTConfig.CounterPolarity = 0;
	ret = CNT_InitCounter(CNT_USBCNT,0,CNT_CH0,&CNTConfig);
	if(ret != ERR_SUCCESS){
		printf("Config device error!\n");
		return ret;
	}
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
    //Get counter value
    ret = CNT_GetCounter(CNT_USBCNT,0,CNT_CH0,CounterValue);
    if(ret != ERR_SUCCESS){
        printf("Get counter value error!\n");
    }else{
        printf("Counter Value :%d\n",CounterValue[0]);
    }  
	while(1)
	{
		//Get counter value
		ret = CNT_GetCounter(CNT_USBCNT,0,CNT_CH0,CounterValue);
		if(ret != ERR_SUCCESS){
			printf("Get counter value error!\n");
		}else{
			printf("Counter Value :%d\n",CounterValue[0]);
		}   
		Sleep(100);
	}
	//Stop counter
	ret = CNT_StopCounter(CNT_USBCNT,0,CNT_CH0);
	if(ret != ERR_SUCCESS){
		printf("Stop counter error!\n");
		return ret;
	}
	return 0;
}

