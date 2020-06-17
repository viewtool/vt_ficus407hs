  /*
  ******************************************************************************
  * @file     : Ficus_DAC_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_DAC_Test demo
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
#include "ControlADC.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_dac.h"
#include "func_map.h"

#endif
int main(int argc, char* argv[])
{
    int ret;
    //Scan connected device
    ret = VAO_ScanDevice(1);
    if (ret <= 0)
    {
        printf("No device connect!\r\n");
        return ret;
    }
    // Open device
    ret = VAO_OpenDevice(VAO_USBDAC, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\r\n");
        return ret;
    }
    // Initialize DAC_CH0 channel
    ret = VAO_InitDAC(VAO_USBDAC, 0, VAO_DAC_CH0,0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize DAC Channel 0 error!\r\n");
        return ret;
    }else{
        printf("Initialize DAC Channel 0 success!\r\n");
    }
    // Set voltage values of DAC_CH0 
	ret = VAO_Start(VAO_USBDAC, 0,VAO_DAC_CH0,400,256);
    if (ret != ERR_SUCCESS)
    {
        printf("Start DAC error!\r\n");
        return ret;
    }else{
        printf("DAC Channel 0 Start Output 400MV");
        printf("\r\n");
    }
	Sleep(100);
	ret = VAO_Stop(VAO_USBDAC, 0,VAO_DAC_CH0);
    if (ret != ERR_SUCCESS)
    {
        printf("Stop DAC error!\r\n");
        return ret;
    }else{
        printf("DAC Channel 0 Stop Output");
        printf("\r\n");
    }	
    while(1);
    // Initialize ADC_CH1
    ret = VAO_InitDAC(VAO_USBDAC, 0, VAO_DAC_CH1 , 0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize DAC Channel 1 error!\r\n");
        return ret;
    }else{
        printf("Initialize DAC Channel 1 success!\r\n");
    }
    // Get voltage values of ADC_CH0 & ADC_CH1(each channel transfer a byte of data at a time.)
	ret = VAO_Start(VAO_USBDAC, 0, VAO_DAC_CH1,400,256);
    if (ret != ERR_SUCCESS)
    {
        printf("Start DAC data error!\r\n");
        return ret;
    }
    else
    {
        printf("DAC Channel 1 Start Output 400MV");
		printf("\r\n");
    }
	ret = VAO_Stop(VAO_USBDAC, 0,VAO_DAC_CH1);
    if (ret != ERR_SUCCESS)
    {
        printf("Stop DAC data error!\r\n");
        return ret;
    }
    else
    {
        printf("DAC Channel 1 Stop Output");
		printf("\r\n");
    }	
	// Initialize DAC_CH0 & ADC_CH1, each channel sampling interval is set to 1000us
    ret = VAO_InitDAC(VAO_USBDAC, 0, VAO_DAC_CH0 , 0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
	if (ret != ERR_SUCCESS)
    {
        printf("Initialize DAC error!\r\n");
        return ret;
    }else{
        printf("Initialize DAC Channel 0 and 1 success!\r\n");
    }
	ret = VAO_Start(VAO_USBDAC, 0,VAO_DAC_CH0,3000,256);
    if (ret != ERR_SUCCESS)
    {
        printf("Start DAC data error!\r\n");
        return ret;
    }else
    {
        printf("DAC Channel 0 and 1 Start Output 3000MV\r\n");
    }
	ret = VAO_Stop(VAO_USBDAC, 0,VAO_DAC_CH0);
    if (ret != ERR_SUCCESS)
    {
        printf("Stop DAC data error!\r\n");
        return ret;
    }else{
        printf("DAC Channel 0 and 1 Stop Output\r\n");
    }	
	printf("=====================================================================\r\n");
	while(1)
	{
		ret = VAO_Start(VAO_USBDAC, 0,VAO_DAC_CH0 | VAO_DAC_CH1,2500,256);
		if (ret != ERR_SUCCESS)
		{
			printf("Start DAC data error!\r\n");
			return ret;
		}else{
            printf("DAC Channel 0 and 1 Start Output 2500MV\r\n");
        } 
        Sleep(1000);
		ret = VAO_Stop(VAO_USBDAC, 0,VAO_DAC_CH0 | VAO_DAC_CH1);
		if (ret != ERR_SUCCESS)
		{
			printf("Stop DAC data error!\r\n");
			return ret;
		}else{
            printf("DAC Channel 0 and 1 Stop Output\r\n");
        }
	}
    // close device
    ret = VAO_CloseDevice(VAO_USBDAC, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Close device error!\r\n");
        return ret;
    }
	return 0;
}
