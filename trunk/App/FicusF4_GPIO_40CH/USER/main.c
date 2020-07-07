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
/*
   A demo program for 40 channel GPIO control with:
   HW: FicusF4HS (STM32F407VET on board)
   FW: >= 
               Product name : FicusF4
               Firmware version : 1.0.2
               Hardware version : 2.1.0
   IDE: Keilv5 (or above)

   FicusF4:
   http://www.viewtool.com/index.php/en/36-2016-09-26-03-58-56/271-ficus-stm32f407hs-high-speed-development-board
   
   Pin layout and definition:
   http://www.viewtool.com/demo/STM32/Ficus_document_html/index.html

   FicusF4 lead out 100% chip's resource for usage, for GPIO, it's more channel could be used. The demo shows defined pin number's usage
   It could be used with I2C, GPIO, CAN (driver module required) simultaneously.

   PIN definition rule and one example: 
   (1)  J15_P1_GPIO 
   (2)  J15_P2_GPIO
   (3)  J15_P3_GPIO
   (4)  J15_P4_GPIO
   (5)  J15_P5_GPIO
   (6)  J15_P6_GPIO 
   (7)  J15_P7_GPIO
   (8)  J15_P8_GPIO
   (9)  J15_P9_GPIO
   (10) J15_P10_GPIO
   (11) J15_P11_GPIO
   (12) J15_P12_GPIO

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


