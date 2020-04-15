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
  * Copyright 2009-2014, ViewTool
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
#endif
int main(int argc, char* argv[])
{
	// Get GPIO_4 and GPIO_5 status 
    int ret;
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
        Sleep(1000);
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
        Sleep(1000);
    }
    ret = VGI_CloseDevice(VGI_USBGPIO, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Close device error!\r\n");
        return ret;
    }
	return 0;
}


