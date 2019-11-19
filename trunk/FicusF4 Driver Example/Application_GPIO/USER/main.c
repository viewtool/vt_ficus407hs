  /*
  ******************************************************************************
  * @file     : Ficus_GPIO_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_GPIO_Test demo
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
#include "ControlGPIO.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_gpio.h"
#endif
int main(int argc, char* argv[])
{
    uint16_t pin_value = 0;
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
    // Set GPIOA_0 and GPIOA_1 to output 
    ret = VGI_SetOutput(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN0 | VGI_GPIO_PIN1);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
        return ret;
    }
    // Set GPIOA_0 and GPIOA_1 
    ret = VGI_SetPins(VGI_USBGPIO, 0,  VGI_GPIO_PORTA | VGI_GPIO_PIN0 | VGI_GPIO_PIN1);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin high error!\r\n");
        return ret;
    }
    // Reset GPIOA_0 and GPIOA_1 
    ret = VGI_ResetPins(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN0 | VGI_GPIO_PIN1);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin low error!\r\n");
        return ret;
    }
    // Set GPIOA_4 and GPIOA_5 to input 
    ret = VGI_SetInput(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN4 | VGI_GPIO_PIN5);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin input error!\r\n");
        return ret;
    }
	// Read GPIOA_4 and GPIOA_5 Data 
    ret = VGI_ReadDatas(VGI_USBGPIO, 0,VGI_GPIO_PORTA | VGI_GPIO_PIN4 | VGI_GPIO_PIN5, &pin_value);
    if (ret != ERR_SUCCESS)
    {
        printf("Get pin data error!\r\n");
        return ret;
    }
    else
    {
        if ((pin_value & VGI_GPIO_PIN4) != 0)
        {
            printf("GPIOA_4 is high-level!\r\n");
        }
        else
        {
            printf("GPIOA_4 is low-level!\r\n");
        }
        if ((pin_value & VGI_GPIO_PIN5) != 0)
        {
            printf("GPIOA_5 is high-level!\r\n");
        }
        else
        {
            printf("GPIOA_5 is low-level!\r\n");
        }
    }
    ret = VGI_SetOpenDrain(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN4 | VGI_GPIO_PIN5);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin open drain error!\r\n");
        return ret;
    }
	
    ret = VGI_SetPins(VGI_USBGPIO, 0,VGI_GPIO_PORTA | VGI_GPIO_PIN4 | VGI_GPIO_PIN5);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin high error!\r\n");
        return ret;
    }
    ret = VGI_ResetPins(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN4 | VGI_GPIO_PIN5);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin high error!\r\n");
        return ret;
    }
    ret = VGI_ReadDatas(VGI_USBGPIO, 0,VGI_GPIO_PORTA | VGI_GPIO_PIN4 | VGI_GPIO_PIN5, &pin_value);
    if (ret != ERR_SUCCESS)
    {
        printf("Get pin data error!\r\n");
        return ret;
    }
    else
    {
        if ((pin_value & VGI_GPIO_PIN4) != 0)
        {
            printf("GPIOA_4 is high-level!\r\n");
        }
        else
        {
            printf("GPIOA_4 is low-level!\r\n");
        }
        if ((pin_value & VGI_GPIO_PIN5) != 0)
        {
            printf("GPIOA_5 is high-level!\r\n");
        }
        else
        {
            printf("GPIOA_5 is low-level!\r\n");
        }
    }
    //Close Device 
    ret = VGI_CloseDevice(VGI_USBGPIO, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Close device error!\r\n");
        return ret;
    }
	return 0;
}


