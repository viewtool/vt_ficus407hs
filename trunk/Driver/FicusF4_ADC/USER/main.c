  /*
  ******************************************************************************
  * @file     : Ficus_ADC_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23
  * @brief    : Ficus_ADC_Test demo
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
   A demo program for 8 channel ADC control with:
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

   Ficus lead out 100% chip's resource for usage, for GPIO, it's more  channel could be used. The demo shows defined pin number's usage
   It could be used with I2C, GPIO, CAN (driver module required) simultaneously.

   PIN definition rule and one example: 
   (1)J15_P7_ADC_CH2	
   (2)J15_P9_ADC_CH3	
   (3)J2_P1_ADC_CH0		
   (4)J2_P3_ADC_CH3		
   (5)J2_P5_ADC_CH1		
   (6)J2_P14_ADC_CH2	
   (7)J2_P18_ADC_CH7	
   (8)J6_P1_ADC_CH2		
   (9)J6_P2_ADC_CH3		
   (10)J18_P1_ADC_CH7	
   (11)J18_P3_ADC_CH2	
   (12)J18_P5_ADC_CH3	
   (13)J18_P8_ADC_CH1	
   (14)J18_P10_ADC_CH0	

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
#include <stdio.h>
#ifdef WINAPI
#include "stdafx.h"
#include "ControlADC.h"
#else
#include "stm32f4xx_conf.h"
#include "vt_adc.h"
#include "func_map.h"
#endif

int main(int argc, char* argv[])
 {
    int ret;
	VAI_BOARD_INFO pInfo;
	uint8_t SamplingCnt = 0;
    //Scan connected device
    ret = VAI_ScanDevice(1);
    if (ret <= 0)
    {
        printf("No device connect!\n");
        return ret;
    }
    // Open device
    ret = VAI_OpenDevice(VAI_USBADC, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\n");
        return ret;
    }
	//VAI_ReadBoardInfo(VAI_USBADC, 0, &pInfo);
    // Initialize ADC_CH0 channel
    ret = VAI_InitADC(VAI_USBADC, 0, VAI_ADC_CH0,0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize ADC error!\n");
        return ret;
    }
    // Get voltage values of ADC_CH0 
	uint16_t adc_datas[4096] = {0};
    ret = VAI_ReadDatas(VAI_USBADC, 0, 1, adc_datas);
    if (ret != ERR_SUCCESS)
    {
        printf("Read ADC data error!\n");
        return ret;
    }
    else
    {
        printf("ADC_CH0 = %.3f\n" ,((adc_datas[0]*3.3)/4095));
        printf("\n");
    }
    // Initialize ADC_CH0 & ADC_CH1
    ret = VAI_InitADC(VAI_USBADC, 0, VAI_ADC_CH0 | VAI_ADC_CH1, 0);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize ADC error!\n");
        return ret;
    }
    // Get voltage values of ADC_CH0 & ADC_CH1(each channel transfer a byte of data at a time.)
    ret = VAI_ReadDatas(VAI_USBADC, 0, 1, adc_datas);
    if (ret != ERR_SUCCESS)
    {
        printf("Read ADC data error!\n");
        return ret;
    }
    else
    {
        printf("ADC_CH0 = %.3f\n" , ((adc_datas[0] * 3.3) / 4095));
        printf("ADC_CH1 = %.3f\n" , ((adc_datas[1] * 3.3) / 4095));
		printf("\n");
    }
	// Initialize ADC_CH0 & ADC_CH1, each channel sampling interval is set to 1000us
    ret = VAI_InitADC(VAI_USBADC, 0, VAI_ADC_CH0 | VAI_ADC_CH1, 1000);// Cycle can be set to 0 if each channel transfer a byte of data at a time.
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize ADC error!\n");
        return ret;
    }
	// Get voltage values of ADC_CH0 & ADC_CH1
    ret = VAI_ReadDatas(VAI_USBADC, 0, 10, adc_datas);//Get 10 values each channel, return a total of 20 values
    if (ret != ERR_SUCCESS)
    {
        printf("Read ADC data error!\n");
        return ret;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            printf("ADC_CH0[%d] = %.3f\n" ,i, ((adc_datas[i*2] * 3.3) / 4095));
        }
        printf("\n");
        for (int i = 0; i < 10; i++)
        {
            printf("ADC_CH1[%d] = %.3f\n" ,i, ((adc_datas[i*2+1] * 3.3) / 4095));
        }
    }


	printf("=====================================================================\n");


	while(1)
	{
		// Get voltage values of ADC_CH0 & ADC_CH1
		ret = VAI_ReadDatas(VAI_USBADC, 0, 10, adc_datas);//Get 10 values each channel, return a total of 10 values,1ms*10=10ms
		if (ret != ERR_SUCCESS)
		{
			printf("Read ADC data error!\n");
			return ret; // exit if error ocurred
		}

		// 10ms * 100 =1s in theory,but there is other time-consuming in practice,I choose 50
		if( 50 == ++SamplingCnt ) //
		{
			SamplingCnt = 0;
			printf("ADC_CH0 = %.3f\n" , ((adc_datas[0] * 3.3) / 4095));
		}
	}


    // close device
    ret = VAI_CloseDevice(VAI_USBADC, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Close device error!\n");
        return ret;
    }
	return 0;
}
