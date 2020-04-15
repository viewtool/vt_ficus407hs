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
    VOS_Enter_Critical(); 
    VOS_Create_Task(led_task1,"led1",LED_STK_SIZE1,NULL,LED_TASK_PRIO1,&LEDTask_Handler1);
    VOS_Create_Task(led_task2,"led2",LED_STK_SIZE2,NULL,LED_TASK_PRIO2,&LEDTask_Handler2);
    VOS_Delete_Task(StartTask_Handler);
    VOS_Exit_Critical();   
}
void led_task1(void *pvParameters)
{
    int i = 0;
    while(1)
    {
        i++;
        VOS_Enter_Critical();
        if(i == 5)
        {
            VOS_Delete_Task(LEDTask_Handler2);
        }
        VOS_Exit_Critical(); 
        Sleep(100);
    }
}
void led_task2(void *pvParameters)
{
    while(1)
    {
        Sleep(100);         
    }
}
