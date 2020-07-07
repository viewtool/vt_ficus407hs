  /*
  ******************************************************************************
  * @file     : Ficus_PWM_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_PWM_Test demo
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
   A demo program for 8 channel PWM control with:
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
   (1)J15_P7_PWM_CH2	
   (2)J15_P9_PWM_CH3	
   (3)J2_P1_PWM_CH0		
   (4)J2_P3_PWM_CH3		
   (5)J2_P5_PWM_CH1		
   (6)J2_P11_PWM_CH6	
   (7)J2_P18_PWM_CH5	
   (8)J6_P1_PWM_CH2		
   (9)J6_P2_PWM_CH3		
   (10)J1_P1_PWM_CH6	
   (11)J1_P2_PWM_CH7	
   (12)J8_P2_PWM_CH5	
   (13)J8_P4_PWM_CH6	
   (14)J18_P8_PWM_CH1	
   (15)J18_P10_PWM_CH0	
   (16)J18_P9_PWM_CH4	


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
#include "ControlPWM.h"
#else
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_pwm.h"
#include "func_map.h"
#endif

int main(int argc, char* argv[])
{
    int ret;
	VPI_INIT_CONFIG PWM_Config;
    // Scan connected device 
    ret = VPI_ScanDevice(1);
    if (ret <= 0)
    {
        printf("No device connect!\n");
        return ret;
    }
    // Open device
    ret = VPI_OpenDevice(VPI_USBPWM, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\n");
        return ret;
    }
    // Initialize PWM_CH0 channel
    PWM_Config.PWM_ChannelMask = VPI_PWM_CH0;
    PWM_Config.PWM_Frequency = 10000;
    PWM_Config.PWM_Mode = 0;
    PWM_Config.PWM_Polarity = 0;
    PWM_Config.PWM_Pulse = 50;
    ret = VPI_InitPWM(VPI_USBPWM,0,&PWM_Config);
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize device error!\n");
        return ret;
    }
    // Star PWM_CH0 channel
    ret = VPI_StartPWM(VPI_USBPWM,0,VPI_PWM_CH0);
    if (ret != ERR_SUCCESS)
    {
        printf("Start pwm error!\n");
        return ret;
    }
    // Run 1S
    Sleep(1000);
    // Stop PWM_CH0 channel
    ret = VPI_StopPWM(VPI_USBPWM, 0, VPI_PWM_CH0);
    if (ret != ERR_SUCCESS)
    {
        printf("Stop pwm error!\n");
        return ret;
    }
    // Initialize all of channel
    PWM_Config.PWM_ChannelMask = VPI_PWM_ALL;
    PWM_Config.PWM_Frequency = 100000;
    PWM_Config.PWM_Mode = 0;
    PWM_Config.PWM_Polarity = 0;
    PWM_Config.PWM_Pulse = 50;
    ret = VPI_InitPWM(VPI_USBPWM, 0, &PWM_Config);
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize device error!\n");
        return ret;
    }
    // Star PWM_CH0, PWM_CH2 channel
    ret = VPI_StartPWM(VPI_USBPWM, 0, VPI_PWM_CH0 | VPI_PWM_CH2);
    if (ret != ERR_SUCCESS)
    {
        printf("Start pwm error!\n");
        return ret;
    }
    // Run 1S
    Sleep(1000);
    // Adjust PWM_CH0 clock frequency
	uint32_t Frequency[8] = {0};
    Frequency[0] = 50000;
    ret = VPI_SetPWMPeriod(VPI_USBPWM, 0, VPI_PWM_CH0, Frequency);
    if (ret != ERR_SUCCESS)
    {
        printf("Set frequency error!\n");
        return ret;
    }
    // Adjust PWM_CH2 duty ratio
	uint8_t Pulse[8] = {0};
    Pulse[2] = 80;
    ret = VPI_SetPWMPulse(VPI_USBPWM, 0, VPI_PWM_CH2, Pulse);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pulse error!\n");
        return ret;
    }
    // Run 1s
    Sleep(1000);
    // Adjust PWM_CH0 and PWM_CH2 duty ratio
    Pulse[0] = 20;
    Pulse[2] = 80;
    ret = VPI_SetPWMPulse(VPI_USBPWM, 0, VPI_PWM_CH0|VPI_PWM_CH2, Pulse);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pulse error!\n");
        return ret;
    }
    // Run 1s
    Sleep(1000);
    // Attention: PWM_CH(2n) and PWM_CH(2n+1) cannot separate set
    // Each channel duty ratio can separate set
    // Close  device
    ret = VPI_CloseDevice(VPI_USBPWM, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Close device error!\n");
        return ret;
    }
	return 0;
}

