  /*
  ******************************************************************************
  * @file     : Ficus_LED_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_LED_Test demo
  ******************************************************************************
  * @attention
  *
  * Copyright 2009-2020, ViewTool
  * http://www.viewtool.com/
  * All Rights Reserved
  * 
  ******************************************************************************
  */
#ifdef WINAPI
#include "stdafx.h"
#include "ControlGPIO.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_gpio.h"
#include "func_map.h"
#endif
#include "vt_driver.h"

/*
WINAPI: Ficus board is hardware compatible with Ginkgo3 Ficus board, by enable WINAPI, could compile this software on PC
and run this code on PC (being a USB to GPIO adapter), more detail please look at website Ginkgo3 Ficus or contact: fae@viewtool.com

*/
#define WINAPI     0
	
#define USING_MS_DELAY     1

int main(int argc, char* argv[])
{
	// Get GPIO_4 and GPIO_5 status 
    int ret;
	  char *vt_bootloader_version = vt_get_bootloader_version();
	  char *vt_dll_version = vt_get_dll_version();
	  printf("%s\r\n", vt_bootloader_version);   // HS: High Speed (480M)
	  printf("%s\r\n", vt_dll_version); 
#if WINAPI
	// Scan connected device
    ret = VGI_ScanDevice(1);
    if (ret <= 0)
    {
        printf("No device connect!\r\n");
        return ret;
    }
    // Open device 
    ret = VGI_OpenDevice(VGI_USBGPIO, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\r\n");
        return ret;
    } 
#endif 	
    ret = VGI_SetOutputEx(VGI_USBGPIO, 0, VGI_GPIO_PORTA| VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
        return ret;
    }
    ret = VGI_SetOutputEx(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
        return ret;
    }
    while(1)
    {
        // Set GPIO_7 and GPIO_8 
        ret = VGI_SetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            return ret;
        }else{
            printf("Set pin high LED\r\n");
        }
        ret = VGI_SetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            return ret;
        }else{
            printf("Set pin high LED\r\n");
        }        
#if USING_MS_DELAY				
				vt_delay_ms(500);
#else 				
				vt_delay_us(500*1000);
#endif 				
        // Reset GPIO_7 and GPIO_8 
        ret = VGI_ResetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
            return ret;
        }else{
            printf("Set pin low LED\r\n");
        }
        ret = VGI_ResetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
            return ret;
        }else{
            printf("Set pin low LED\r\n");
        }
#if USING_MS_DELAY				
				vt_delay_ms(500);
#else 				
				vt_delay_us(500*1000);
#endif 
    }
#ifdef WINAPI
    ret = VGI_CloseDevice(VGI_USBGPIO, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Close device error!\r\n");
        return ret;
    }
#endif 
	return 0;
}


