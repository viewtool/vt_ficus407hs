  /*
  ******************************************************************************
  * @file     : Ficus_I2C_AT24C02.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2020/10/23
  * @brief    : Ficus_I2C_AT24C02 demo
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
#include "ControlI2C.h"
#else
#include "stm32f4xx_conf.h"
#include "vt_i2c.h"
#include "HMC5883L.h"
#include "func_map.h"
#endif

#define SWD_Debug   1

#if SWD_Debug
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
     while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
#else
/*
    *** USE Print()Function Need Init UART1 or UART2 or UART3 Driver
*/
#pragma import(__use_no_semihosting)             
              
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
  
int _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);
	USART1->DR = (u8) ch;      
	return ch;
}

#endif
int main(void)
{
	enum Status status;
	status = HMC5883L_Init();
	if(status != SUCCESS_S){
		printf("Initialize HMC5883L failed!\n");
		return 0;
	}
	// if config failed, please step into this function, give each function call a short delay time, it will work.
	status = HMC5883L_Config();
	if(status != SUCCESS_S){
		printf("Config HMC5883L failed!\n");
		return 0;
	}
    while (1)
    {
		int16_t XMagnetic, YMagnetic, ZMagnetic;
        //Get data
		status = HMC5883L_ReadMagnetic(&XMagnetic, &YMagnetic, &ZMagnetic);
		if(status != SUCCESS_S){
			printf("Get Magnetic failed!\n");
			return 0;
		}
        //Display data
      //  system("cls");
        printf("XMagnetic= %d\n" , XMagnetic);
        printf("YMagnetic= %d\n" , YMagnetic);
        printf("ZMagnetic= %d\n" , ZMagnetic);
        Sleep(100);
    }
	return 0;
}