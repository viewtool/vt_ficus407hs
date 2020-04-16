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
