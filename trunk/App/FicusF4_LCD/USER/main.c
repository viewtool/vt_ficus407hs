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


