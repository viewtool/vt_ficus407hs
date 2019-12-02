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
#endif

#define COLOR_SENSOR_ADDR			0x49
#define REG_CONTROL					0x80	/* 0x00 */
#define REG_TIMING					0x81	/* 0x01 */
#define REG_INTRRUPT				0x82	/* 0x02 */
#define REG_INT_SOURCE				0x83	/* 0x03 */
#define REG_ID						0x84	/* 0x04 */
#define REG_GAIN					0x87	/* 0x07 */
#define REG_LOW_THRESH_LOW_BYTE		0x88	/* 0x08 */
#define REG_LOW_THRESH_HIGH_BYTE	0x89	/* 0x09 */
#define REG_HIGH_THRESH_LOW_BYTE	0x8A	/* 0x0A */
#define REG_HIGH_THRESH_HIGH_BYTE	0x8B	/* 0x0B */

#define REG_GREEN_LOW				0xD0	/* 0x10 */
#define REG_GREEN_HIGH				0xD1	/* 0x11 */
#define REG_RED_LOW					0xD2	/* 0x12 */
#define REG_RED_HIGH				0xD3	/* 0x13 */
#define REG_BLUE_LOW				0xD4	/* 0x14 */
#define REG_BLUE_HIGH				0xD5	/* 0x15 */
#define REG_CLEAR_LOW				0xD6	/* 0x16 */
#define REG_CLEAR_HIGH				0xD7	/* 0x17 */

#define CLR_INT						0xE0
#define CTL_DAT_INIITIATE			0x03

/* Timing Register */
#define SYNC_EDGE					0x40
#define INTEG_MODE_FREE				0x00
#define INTEG_MODE_MANUAL			0x10
#define INTEG_MODE_SYN_SINGLE		0x20
#define INTEG_MODE_SYN_MULTI		0x30

#define INTEG_PARAM_PULSE_COUNT1	0x00
#define INTEG_PARAM_PULSE_COUNT2	0x01
#define INTEG_PARAM_PULSE_COUNT4	0x02
#define INTEG_PARAM_PULSE_COUNT8	0x03

/* Interrupt Control Register */
#define INTR_STOP			40
#define INTR_DISABLE		0x00
#define INTR_LEVEL			0x10			/* 兼容SMB-Alert */
#define INTR_PERSIST_EVERY	0x00			/* 每个ADC都会产生中断 */
#define INTR_PERSIST_SINGLE 0x01

/* Interrupt Souce Register */
#define INT_SOURCE_GREEN	0x00
#define INT_SOURCE_RED		0x01
#define INT_SOURCE_BLUE		0x10
#define INT_SOURCE_CLEAR	0x03

/* Gain Register */
#define GAIN_1			0x00
#define GAIN_4			0x10
#define GAIN_16			0x20
#define GAIN_64			0x30
#define PRESCALER_1		0x00
#define PRESCALER_2		0x01
#define PRESCALER_4		0x02
#define PRESCALER_8		0x03
#define PRESCALER_16	0x04
#define PRESCALER_32	0x05
#define PRESCALER_64	0x06
typedef struct
{
	uint16_t	Red;
	uint16_t	Green;
	uint16_t	Blue;
	uint16_t	Clear;
} _RGB;
uint8_t				triggerMode_ = (INTEG_MODE_FREE | INTEG_PARAM_PULSE_COUNT1);
uint8_t				interruptSource_ = (INT_SOURCE_CLEAR);
uint8_t				interruptMode_ = (INTR_LEVEL | INTR_PERSIST_EVERY);
uint8_t				gainAndPrescaler_ = (GAIN_1 | PRESCALER_1);
uint8_t				sensorAddress_ = (COLOR_SENSOR_ADDR<<1);
void				TCS_Read_Block(uint8_t reg, uint8_t len, uint8_t *data);
uint8_t				TCS_Read_Byte(uint8_t reg);
uint8_t				TCS_Write_Byte(uint8_t reg, uint8_t data);

/*
 ===============================================================================
 ===============================================================================
 */
uint8_t readID(void)
{
	return TCS_Read_Byte(REG_ID);	/* TCS3414-->0X11 */
}

/*
 ===============================================================================
 ===============================================================================
 */
void setTimingReg(void)
{
	TCS_Write_Byte(REG_TIMING, triggerMode_);
	Sleep(10);
}

/*
 ===============================================================================
 ===============================================================================
 */
void setInterruptSourceReg(void)
{
	TCS_Write_Byte(REG_INT_SOURCE, interruptSource_);
	Sleep(10);
}

/*
 ===============================================================================
 ===============================================================================
 */
void setInterruptControlReg(void)
{
	TCS_Write_Byte(REG_INTRRUPT, interruptMode_);
	Sleep(10);
}

/*
 ===============================================================================
 ===============================================================================
 */
void setGain(void)
{
	TCS_Write_Byte(REG_GAIN, gainAndPrescaler_);
	Sleep(10);
}

/*
 ===============================================================================
 ===============================================================================
 */
void setEnableADC(void)
{
	TCS_Write_Byte(REG_CONTROL, CTL_DAT_INIITIATE);
	Sleep(10);
}

/*
 ===============================================================================
 ===============================================================================
 */
uint8_t clearInterrupt(void)
{
    uint8_t ret = 0,data = CLR_INT;
    ret = VII_WriteBytes(VII_USBI2C, 0,0, sensorAddress_, 0x00, &data, 1);
	/*
	 * mraa_i2c_stop(i2c);
	 */
	return 0;
}


uint8_t TCS_Write_Byte(uint8_t reg, uint8_t data)
{
    uint8_t ret = 0;
    ret = VII_WriteBytes(VII_USBI2C, 0,0, sensorAddress_, reg, &data, 1);
	return 0;
}

uint8_t TCS_Read_Byte(uint8_t reg)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
	uint8_t I2cRecvTemp = 0x00, ret = 0x00;
	/*~~~~~~~~~~~~~~~~~~~~~~~*/
    ret = VII_ReadBytes(VII_USBI2C, 0,0,sensorAddress_,reg,&I2cRecvTemp,1);
    
	return I2cRecvTemp;
}

/*
 ===============================================================================
    IIC读一块区域 ;
    data:存放数据的地址地址 ;
    len:读的次数
 ===============================================================================
 */
void TCS_Read_Block(uint8_t reg, uint8_t len, uint8_t *data)
{
	/*~~~~~~~~*/
    uint8_t ret = 0;
	int num = 0;
	/*~~~~~~~~*/
    ret = VII_ReadBytes(VII_USBI2C, 0,0,COLOR_SENSOR_ADDR<<1,reg,data,len);
	printf("RecevNum:%d   ", num);
}

/*
 ===============================================================================
 ===============================================================================
 */
void TCS3414_Init(void)
{
	Sleep(10);
	setTimingReg();
	setInterruptSourceReg();
	setInterruptControlReg();
	setGain();
	setEnableADC();
	Sleep(10);
}
int green,red,blue;
void readRGB_Block(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint8_t color[8] = { 0x00 },
	i = 0;
	int		Green, Red, Blue, Clear;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < 8; i++) color[i] = 0;
	TCS_Read_Block(REG_GREEN_LOW, 8, color);
	Green = green = (color[1] << 8) | color[0];
	Red   = red   = (color[3] << 8) | color[2];
	Blue  = blue  = (color[5] << 8) | color[4];
	Clear = (color[7] << 8) | color[6];

	printf("Green:%d Red :%d Blue:%d Clear:%d\n", Green, Red, Blue, Clear);
}
void calculateCoordinate(void)
{
    double X,Y,Z,x,y,z;
    X=(-0.14282)*red+(1.54924)*green+(-0.95641)*blue;
    Y=(-0.32466)*red+(1.57837)*green+(-0.73191)*blue;
    Z=(-0.68202)*red+(0.77073)*green+(0.56332)*blue;
    x=X/(X+Y+Z);
    y=Y/(X+Y+Z);
    if((X>0)&&(Y>0)&&(Z>0))
    {
        printf("The x,y value is");
        printf("(%02f , %02f)\r\n",x,y);
    }
}
int main(int argc, char* argv[])
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
    I2C_Config.ClockSpeed = 400000;
    I2C_Config.ControlMode = VII_HCTL_MODE;
    I2C_Config.MasterMode = VII_MASTER;
    I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
    ret = VII_InitI2C(VII_USBI2C, 0,I2C_Index, &I2C_Config);
    if (ret != ERR_SUCCESS)
    {
        printf("Initialize device error!\r\n");
        return ret;
    }
    TCS3414_Init();
    uint8_t TCS3414_ID = 0x00;
    TCS3414_ID = readID();
    printf("ID:0x%02x\r\n", TCS3414_ID);
	while(1)
	{
		readRGB_Block();
        calculateCoordinate();
		Sleep(1000);
        clearInterrupt();
	}    
	return 0;
}

