  /*
  ******************************************************************************
  * @file     : Ficus_USB_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_USB_Test demo
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
#include "vt_usb.h"
#include "func_map.h"
#endif

int main(int argc, char* argv[])
{
	int ret;
    static uint32_t SendDataNum = 0;
    static uint8_t SendDataBuff[64 *1024]={0x00};
	uint8_t	read_buffer[8]={0};
	//Scan device
	ret = VUI_ScanDevice(1);
	if(ret <= 0)
	{
        printf("No device connect!\r\n");
		return ret;
	}
    //Open device
    ret = VUI_OpenDevice(VUI_USB, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\r\n");
        return ret;
    }
    ret = VUI_InitUSB(VUI_USB,VT_USB_HS);
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize device error!\r\n");
        return ret;
    }
    while(1)
    {
        ret = VUI_ReadByte(VUI_USB, 0,read_buffer, 4 ,0);
        if (ret != ERR_SUCCESS)
        {
            printf("Read data error!\r\n");
            return ret;
        }
        SendDataNum = read_buffer[0]<<24 | read_buffer[1]<<16 | read_buffer[2]<<8 | read_buffer[3];
        printf("SendDataNum : %d\n",SendDataNum);
        do{
            ret = VUI_WriteByte(VUI_USB, 0,SendDataBuff, sizeof(SendDataBuff),0);
            if (ret != ERR_SUCCESS)
            {
                printf("Write data error!\r\n");
                return ret;
            }     
            SendDataNum--;            
        }while(SendDataNum>0);     
    } 
}

