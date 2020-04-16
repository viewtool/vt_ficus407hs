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
#include "func_map.h"
#endif
#define MLX90614_IIC_ADDR   00

#define MLX90614_TA 		0x06
#define MLX90614_TOBJ1 		0x07
uint16_t Get_Register(uint8_t reg)
{
    uint8_t result[2];
    VII_ReadBytes(VII_USBI2C,0,0,MLX90614_IIC_ADDR,reg,result,2);
    return result[0]|result[1]<<8;
}

float GetTemp(uint8_t Register)
{
  float temp;
  temp = Get_Register(Register)*0.02-273.15;//Temperature conversion
  return temp;    
}
double GetAmbientTemp_Celsius(void)
{
    return GetTemp(MLX90614_TA); 
}
double GetObjectTemp_Celsius(void)
{
    return GetTemp(MLX90614_TOBJ1);
}
double GetObjectTemp_Fahrenheit(void)
{
    return (GetTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}
double GetAmbientTemp_Fahrenheit(void)
{
    return (GetTemp(MLX90614_TA) * 9 / 5) + 32;
}
int main(int argc, char* argv[])
{
    int ret,i;
	VII_INIT_CONFIG I2C_Config;
	VII_BOARD_INFO BoardInfo;
    int8_t I2C_Index = 0;
	//Scan device
	ret = VII_ScanDevice(1);
	if(ret <= 0)
	{
		printf("No device connect!\r\n");
		return ret;
	}
    //Open device
    ret = VII_OpenDevice(VII_USBI2C, 0, 0);
    if (ret != ERR_SUCCESS)
    {
        printf("Open device error!\r\n");
        return ret;
    }
	//Get product information
	ret = VII_ReadBoardInfo(0,&BoardInfo);
    if (ret != ERR_SUCCESS){
        printf("Read board information error!\r\n");
        return ret;
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
    I2C_Config.ClockSpeed = 100000;
    I2C_Config.ControlMode = VII_HCTL_MODE;
    I2C_Config.MasterMode = VII_MASTER;
    I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
    ret = VII_InitI2C(VII_USBI2C, 0,I2C_Index, &I2C_Config);
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize device error!\r\n");
        return ret;
    }
	while(1)
	{
        printf("Ambient = %4.3f \r\n",GetAmbientTemp_Celsius());
        printf("Object  = %4.3f \r\n",GetObjectTemp_Celsius());
        printf("Ambient = %4.3f \r\n",GetAmbientTemp_Fahrenheit());
        printf("Object  = %4.3f \r\n",GetObjectTemp_Fahrenheit());
        printf("\r\n");
        Sleep(1000);
	}    

}

