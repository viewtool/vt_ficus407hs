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
/*
   A demo program for LED FLASH GPIO control with:
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
/*
WINAPI: Ficus board is hardware compatible with Ginkgo3 Ficus board, by enable WINAPI, could compile this software on PC
and run this code on PC (being a USB to GPIO adapter), more detail please look at website Ginkgo3 Ficus or contact: fae@viewtool.com

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

#define USING_MS_DELAY     1

int main(int argc, char* argv[])
{
	// Get GPIO_4 and GPIO_5 status 
    int ret;
//	  char *vt_bootloader_version = vt_get_bootloader_version();
//	  char *vt_dll_version = vt_get_dll_version();
//	  printf("%s\r\n", vt_bootloader_version);   // HS: High Speed (480M)
//	  printf("%s\r\n", vt_dll_version); 
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
				Sleep(500);
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
				Sleep(500);
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


