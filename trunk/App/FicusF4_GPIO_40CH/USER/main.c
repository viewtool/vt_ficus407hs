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
#include "func_map.h"
#endif
uint32_t num[40]={
J15_P1_GPIO,J15_P2_GPIO,J15_P3_GPIO,J15_P4_GPIO,
J15_P5_GPIO,J15_P6_GPIO,J15_P7_GPIO,J15_P8_GPIO,    
J15_P9_GPIO,J15_P10_GPIO,J15_P11_GPIO,
J2_P1_GPIO,J2_P2_GPIO,J2_P3_GPIO,J2_P4_GPIO,
J2_P5_GPIO,J2_P6_GPIO,J2_P7_GPIO,J2_P8_GPIO, 
J2_P9_GPIO,J2_P10_GPIO,J2_P11_GPIO,J2_P12_GPIO, 
J2_P13_GPIO,J2_P14_GPIO,J2_P15_GPIO,J2_P16_GPIO, 
J2_P17_GPIO,J2_P18_GPIO,J2_P19_GPIO,J2_P20_GPIO,   
J50_P1_GPIO,J50_P3_GPIO,J50_P4_GPIO,J50_P5_GPIO,
J50_P6_GPIO,J50_P7_GPIO,J50_P8_GPIO,J50_P9_GPIO,
J50_P10_GPIO
};
int main(int argc, char* argv[])
{
    uint16_t pin_value = 0, j = 0;
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
    for(j=0;j<40;j++)
    {
        // Set GPIOA_0 and GPIOA_1 to output 
        ret = VGI_SetOutputEx(VGI_USBGPIO, 0, num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin output error!\r\n");
            return ret;
        }
        // Set GPIOA_0 and GPIOA_1 
        ret = VGI_SetPinsEx(VGI_USBGPIO, 0,  num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            return ret;
        }
        // Reset GPIOA_0 and GPIOA_1 
        ret = VGI_ResetPinsEx(VGI_USBGPIO, 0, num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
            return ret;
        }
        // Set GPIOA_4 and GPIOA_5 to input 
        ret = VGI_SetInputEx(VGI_USBGPIO, 0, num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin input error!\r\n");
            return ret;
        }
        // Read GPIOA_4 and GPIOA_5 Data 
        ret = VGI_ReadDatasEx(VGI_USBGPIO, 0,num[j], &pin_value);
        if (ret != ERR_SUCCESS)
        {
            printf("Get pin data error!\r\n");
            return ret;
        }
        else
        {
            if ((pin_value & num[j]) != 0)
            {
                printf("GPIO is high-level!\r\n");
            }
            else
            {
                printf("GPIO is low-level!\r\n");
            }
            if ((pin_value & num[j]) != 0)
            {
                printf("GPIO is high-level!\r\n");
            }
            else
            {
                printf("GPIO is low-level!\r\n");
            }
        }
        ret = VGI_SetOpenDrainEx(VGI_USBGPIO, 0, num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin open drain error!\r\n");
            return ret;
        }
        
        ret = VGI_SetPinsEx(VGI_USBGPIO, 0,num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            return ret;
        }
        ret = VGI_ResetPinsEx(VGI_USBGPIO, 0, num[j]);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            return ret;
        }
        ret = VGI_ReadDatasEx(VGI_USBGPIO, 0,num[j], &pin_value);
        if (ret != ERR_SUCCESS)
        {
            printf("Get pin data error!\r\n");
            return ret;
        }
        else
        {
            if ((pin_value & num[j]) != 0)
            {
                printf("GPIOA is high-level!\r\n");
            }
            else
            {
                printf("GPIOA is low-level!\r\n");
            }
            if ((pin_value & num[j]) != 0)
            {
                printf("GPIOA is high-level!\r\n");
            }
            else
            {
                printf("GPIOA is low-level!\r\n");
            }
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


