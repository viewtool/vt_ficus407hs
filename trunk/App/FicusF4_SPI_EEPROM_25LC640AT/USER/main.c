  /*
  ******************************************************************************
  * @file     : Ficus_SPI_25LC640AT.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_SPI_25LC640AT demo
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
   A demo program for 25LC640AT SPI control with:
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
   (1)J8_P2_P4_P6_P8_SPI0_NSS0      
   (2)J8_P2_P4_P6_J50_P4_SPI0_NSS1  
   (3)J8_P2_P4_P6_J50_P6_SPI0_NSS2  
   (4)J8_P2_P4_P6_J50_P8_SPI0_NSS3  
   (5)J8_P2_P4_P6_J50_P10_SPI0_NSS4 
   (6)J8_P2_P4_P6_J50_P12_SPI0_NSS5 
   (7)J8_P2_P4_P6_J50_P14_SPI0_NSS6 
   (8)J8_P2_P4_P6_J50_P16_SPI`0_NSS7 
   (9)J8_P1_P3_P5_P7_SPI1_NSS8    	
   (10)J8_P1_P3_P5_J50_P7_SPI1_NSS9 
   (11)J8_P1_P3_P5_J50_P7_SPI1_NSS10
   (12)J8_P1_P3_P5_J50_P7_SPI1_NSS11
   (13)J8_P1_P3_P5_J50_P7_SPI1_NSS12
   (14)J8_P1_P3_P5_J50_P7_SPI1_NSS13
   (15)J8_P1_P3_P5_J50_P7_SPI1_NSS14
   (16)J8_P1_P3_P5_J50_P7_SPI1_NSS15

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
#include <string.h>
#include <stdlib.h>
#include "stm32f4xx_conf.h"
#include "vt_spi.h"
#include "func_map.h"
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


