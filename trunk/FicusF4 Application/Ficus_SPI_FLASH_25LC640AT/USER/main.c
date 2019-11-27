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
#include <string.h>
#include <stdlib.h>
#include "stm32f4xx_conf.h"
#include "vt_spi.h"
#endif
#define W_MAX 1000
#define R_MAX 1000

int main(int argc, char* argv[])
{
// Get GPIO_4 and GPIO_5 status 
    int ret,i;
    uint8_t *demo_w = NULL;
    uint8_t *demo_r = NULL;
    // Scan connected device
    VSI_FLASH_INIT_CONFIG FLASH_INIT_CONFIG;
    demo_w = malloc(W_MAX);
    demo_r = malloc(R_MAX);
    for(i = 0;i<W_MAX;i++)
    {
        demo_w[i]=i+2;
    }    
    FLASH_INIT_CONFIG.busy_bit = 0x01;
    FLASH_INIT_CONFIG.busy_mask = 0x01;
    FLASH_INIT_CONFIG.read_status[0] = 0x05;
    FLASH_INIT_CONFIG.write_enable[0] = 0x06;
    FLASH_INIT_CONFIG.read_data[0] = 0x03;
    FLASH_INIT_CONFIG.write_data[0] = 0x02;
    FLASH_INIT_CONFIG.chip_erase[0] = 0x20;
    FLASH_INIT_CONFIG.page_size = 0x100;
    FLASH_INIT_CONFIG.page_num = 0x4000;
    FLASH_INIT_CONFIG.addr_bytes = 0x03;
    FLASH_INIT_CONFIG.addr_shift = 0x08;
    ret = VSI_FlashInit(0,0,&FLASH_INIT_CONFIG);
    if (ret != ERR_SUCCESS)
    {
        printf("Init device error!\r\n");
        return ret;
    }
    ret = VSI_FlashWriteBytes(0,0,0,demo_w,W_MAX);
    if (ret != ERR_SUCCESS)
    {
        printf("Write data error!\r\n");
        return ret;
    }
    ret =  VSI_FlashReadBytes(0,0,0,demo_r,R_MAX);
    if (ret != ERR_SUCCESS)
    {
        printf("Read data error!\r\n");
        return ret;
    }
    for(i = 0;i<R_MAX;i++)
    {
        printf("%x ", demo_r[i]);
    }
    if(memcmp(demo_r,demo_w,R_MAX) == 0)
    {
        printf("Is OK\r\n");
    }
	return 0;
}


