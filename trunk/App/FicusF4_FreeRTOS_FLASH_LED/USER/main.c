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
/*
   A demo program for FREERTOS LED FLASH GPIO control with:
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
#include "vt_os.h"
#include "func_map.h"
#endif


#define START_TASK_PRIO		1
#define START_STK_SIZE 		256  
void* StartTask_Handler;
void start_task(void *pvParameters);

#define LED_TASK_PRIO1		4
#define LED_STK_SIZE1 		128 
void* LEDTask_Handler1;
void led_task1(void *pvParameters);

#define LED_TASK_PRIO2		5
#define LED_STK_SIZE2 		128 
void* LEDTask_Handler2;
void led_task2(void *pvParameters);

#define heep_size 20*1024
uint8_t uheap[heep_size];
int main(void)
{
    VOS_INIT_CONFIG pInitConfig;
    pInitConfig.HeepSize = heep_size;
    pInitConfig.rtHeap = uheap;
    VOS_Init(&pInitConfig);
    VOS_Create_Task(start_task,"start",START_STK_SIZE,NULL,START_TASK_PRIO,&StartTask_Handler);
    VOS_Start();
}
void start_task(void *pvParameters)
{
    int ret = 0;
    VOS_Enter_Critical(); 
    VOS_Create_Task(led_task1,"led1",LED_STK_SIZE1,NULL,LED_TASK_PRIO1,&LEDTask_Handler1);
    VOS_Create_Task(led_task2,"led2",LED_STK_SIZE2,NULL,LED_TASK_PRIO2,&LEDTask_Handler2);
    ret = VGI_SetOutputEx(VGI_USBGPIO, 0, VGI_GPIO_PORTA| VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
    }
    ret = VGI_SetOutputEx(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
    }
    VOS_Delete_Task(StartTask_Handler);
    VOS_Exit_Critical();   
}
void led_task1(void *pvParameters)
{
    int ret = 0;
    while(1)
    {
        VOS_Enter_Critical();
        ret = VGI_SetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            VOS_Delete_Task(LEDTask_Handler1);
        }else{
            printf("Set pin high LED\r\n");
        }
        VOS_Exit_Critical(); 
        Sleep(1000);
        VOS_Enter_Critical();
        ret = VGI_ResetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
            VOS_Delete_Task(LEDTask_Handler1);
        }else{
            printf("Set pin low LED\r\n");
        }
        VOS_Exit_Critical(); 
        Sleep(1000);
    }
}
void led_task2(void *pvParameters)
{
    int ret = 0;
    while(1)
    {
        VOS_Enter_Critical();
        ret = VGI_SetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
            VOS_Delete_Task(LEDTask_Handler2);
        }else{
            printf("Set pin high LED\r\n");
        }     
        VOS_Exit_Critical(); 
        Sleep(1000);
        VOS_Enter_Critical();
        ret = VGI_ResetPinsEx(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
             VOS_Delete_Task(LEDTask_Handler2);
        }else{
            printf("Set pin low LED\r\n");
        }
        VOS_Exit_Critical(); 
        Sleep(1000);
    }
}
