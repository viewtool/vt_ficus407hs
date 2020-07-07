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
  * Pinout:http://www.viewtool.com/demo/STM32/Ficus_document_html/d5/db5/ficuspinout.html
  * All Rights Reserved
  * 
  ******************************************************************************
  */
/*
   A demo program for LCD control with:
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

   Ficus lead out 100% chip's resource for usage, for GPIO, it's more than 16 channel could be used. The demo shows defined pin number's usage
   It could be used with I2C, GPIO, CAN (driver module required) simultaneously.

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
#include "GUI.h"
#include "vt_lcd.h"
#include "GUIDemo.h"

#endif
int main(int argc, char* argv[])
{
    GUI_PID_STATE TouchState; 
    LCD_INIT_CONFIG LCD_Inits;
    LCD_INIT_CONFIG init_config;
    int32_t xPhys;  
    int32_t yPhys; 
    init_config.dir = 0;
    init_config.id = 0x8999;
    init_config.touch_type = 0;
    init_config.block_size = 0x20;
    init_config.numbyte = 50*1024;
    VT_LCD_Init(0,0,&init_config);
    GUI_Init(); 
    GUI_SetFont(&GUI_Font16_ASCII); 
    GUI_SetBkColor(GUI_YELLOW);
    GUI_SetColor(GUI_RED);  
    GUI_Clear(); 
    GUI_DispString("Measurement of \nA/D converter values\n");       
    while(1)
    {
        GUI_TOUCH_GetState(&TouchState); 
        xPhys = GUI_TOUCH_GetxPhys();     // Get the A/D mesurement result in x   
        yPhys = GUI_TOUCH_GetyPhys();     // Get the A/D mesurement result in y 
        GUI_SetColor(GUI_BLUE); 
        GUI_DispStringAt("Analog input:\n", 0, 40); 
        GUI_GotoY(GUI_GetDispPosY() + 2); 
        GUI_DispString("x:"); 
        GUI_DispDec(xPhys, 4); 
        GUI_DispString(", y:"); 
        GUI_DispDec(yPhys, 4); 
        GUI_SetColor(GUI_RED); 
        GUI_GotoY(GUI_GetDispPosY() + 4); 
        GUI_DispString("\nPosition:\n"); 
        GUI_GotoY(GUI_GetDispPosY() + 2); 
        GUI_DispString("x:"); 
        GUI_DispDec(TouchState.x,4); 
        GUI_DispString(", y:"); 
        GUI_DispDec(TouchState.y,4); 
        Sleep(50);
        GUI_TOUCH_Exec();
    }
}


