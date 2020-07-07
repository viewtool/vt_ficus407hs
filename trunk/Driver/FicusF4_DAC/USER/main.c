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
/*
   A demo program for 1 channel DAC control with:
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
   (1)  J18_P1_DAC_CH0 

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
