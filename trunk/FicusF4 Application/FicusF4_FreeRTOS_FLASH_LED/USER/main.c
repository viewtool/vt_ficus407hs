  /*
  ******************************************************************************
  * @file     : Ficus_Test.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_Test demo
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
#include "FreeRTOS.h"
#include "task.h"
#endif

#define START_TASK_PRIO		1
#define START_STK_SIZE 		256  
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);


#define I2C_TASK_PRIO		2
#define I2C_STK_SIZE 		128 
TaskHandle_t I2CTask_Handler;
void at24c02_task(void *pvParameters);


#define LED_TASK_PRIO		3
#define LED_STK_SIZE 		128 
TaskHandle_t LEDTask_Handler;
void led_task(void *pvParameters);


#define FLOAT_TASK_PRIO		4
#define FLOAT_STK_SIZE 		128
TaskHandle_t FLOATTask_Handler;
void float_task(void *pvParameters);

int main(int argc, char* argv[])
{
    xTaskCreate((TaskFunction_t )start_task,            
                (const char*    )"start_task",          
                (uint16_t       )START_STK_SIZE,       
                (void*          )NULL,                  
                (UBaseType_t    )START_TASK_PRIO,      
                (TaskHandle_t*  )&StartTask_Handler);               
    vTaskStartScheduler();         
}
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); 
    xTaskCreate((TaskFunction_t )at24c02_task,     	
                (const char*    )"at24c02_task",   	
                (uint16_t       )I2C_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )I2C_TASK_PRIO,	
                (TaskHandle_t*  )&I2CTask_Handler);
				
    xTaskCreate((TaskFunction_t )led_task,     
                (const char*    )"led_task",   
                (uint16_t       )LED_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED_TASK_PRIO,
                (TaskHandle_t*  )&LEDTask_Handler);  

    xTaskCreate((TaskFunction_t )float_task,     
                (const char*    )"float_task",   
                (uint16_t       )FLOAT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )FLOAT_TASK_PRIO,
                (TaskHandle_t*  )&FLOATTask_Handler);
				
	vTaskDelete(StartTask_Handler);		
	taskEXIT_CRITICAL();			
}

void at24c02_task(void *pvParameters)
{
	while(1)
	{
		int ret,i;
		VII_INIT_CONFIG I2C_Config;
		VII_BOARD_INFO BoardInfo;
		uint8_t write_buffer[8]={0};
		uint8_t	read_buffer[8]={0};
		int8_t I2C_Index = 0;
		//Scan device
		ret = VII_ScanDevice(1);
		if(ret <= 0)
		{
			printf("No device connect!\r\n");
			break;
		}
		//Open devices
		ret = VII_OpenDevice(VII_USBI2C, 0, 0);
		if (ret != ERR_SUCCESS)
		{
			printf("Open device error!\r\n");
			break;
		}
		//Get product information
		ret = VII_ReadBoardInfo(0,&BoardInfo);
		if (ret != ERR_SUCCESS){
			printf("Read board information error!\r\n");
		}else{
			printf("Product Name:%s\r\n",BoardInfo.ProductName);
			printf("Firmware Version:V%d.%d.%d\r\n",BoardInfo.FirmwareVersion[1],BoardInfo.FirmwareVersion[2],BoardInfo.FirmwareVersion[3]);
			printf("Hardware Version:V%d.%d.%d\r\n",BoardInfo.HardwareVersion[1],BoardInfo.HardwareVersion[2],BoardInfo.HardwareVersion[3]);
			printf("Serial Number:");
			for(i=0;i<12;i++){
				printf("%02X",BoardInfo.SerialNumber[i]);
			}
			printf("\r\n");
		}
		//Initializes the device
		I2C_Config.AddrType = VII_ADDR_7BIT;
		I2C_Config.ClockSpeed = 400000;
		I2C_Config.ControlMode = VII_HCTL_MODE;
		I2C_Config.MasterMode = VII_MASTER;
		I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
		ret = VII_InitI2C(VII_USBI2C, 0,I2C_Index, &I2C_Config);
		if (ret != ERR_SUCCESS)
		{
			printf("Initialize device error!\r\n");
			break;
		}
		//Write 8 byte data to 0x00
		for (i = 0; i < 8; i++)
		{
			write_buffer[i] = i;
		}
		ret = VII_WriteBytes(VII_USBI2C, 0,I2C_Index, 0xA0, 0x00, write_buffer, 8);
		if (ret != ERR_SUCCESS)
		{
			printf("Write data error!\r\n");
			break;
		}
		vTaskDelay(100);
		//Read 8 byte data from 0x00
		ret = VII_ReadBytes(VII_USBI2C, 0, I2C_Index, 0xA0, 0x00, read_buffer, 8);
		if (ret != ERR_SUCCESS)
		{
			printf("Read data error!\r\n");
			break;
		}
		else
		{
			printf("Read Data:\r\n");
			for(i=0;i<8;i++)
			{
				printf("%02X ",read_buffer[i]);
			}
			printf("\r\n");
		}
		vTaskDelay(100);
	}
	vTaskDelete(I2CTask_Handler);	
}
void led_task(void *pvParameters)
{
	int ret = 0;
    ret = VGI_SetOutput(VGI_USBGPIO, 0, VGI_GPIO_PORTA| VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
		return ;
    }
    ret = VGI_SetOutput(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
    if (ret != ERR_SUCCESS)
    {
        printf("Set pin output error!\r\n");
		return ;
    }
	while(1)
	{
        ret = VGI_SetPins(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
        }else{
            printf("Set pin high LED\r\n");
        }
        ret = VGI_SetPins(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin high error!\r\n");
        }else{
            printf("Set pin high LED\r\n");
        }        
        vTaskDelay(1000);
        // Reset GPIO_7 and GPIO_8 
        ret = VGI_ResetPins(VGI_USBGPIO, 0, VGI_GPIO_PORTA | VGI_GPIO_PIN6 | VGI_GPIO_PIN7);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
        }else{
            printf("Set pin low LED\r\n");
        }
        ret = VGI_ResetPins(VGI_USBGPIO, 0, VGI_GPIO_PORTB | VGI_GPIO_PIN12 | VGI_GPIO_PIN13);
        if (ret != ERR_SUCCESS)
        {
            printf("Set pin low error!\r\n");
        }else{
            printf("Set pin low LED\r\n");
        }
		vTaskDelay(1000);	
	}
}

void float_task(void *pvParameters)
{
	static float float_num=0.00;
	while(1)
	{
		float_num+=0.01f;
		printf("float_num Value: %.4f\r\n",float_num);
        vTaskDelay(10);
	}
}
