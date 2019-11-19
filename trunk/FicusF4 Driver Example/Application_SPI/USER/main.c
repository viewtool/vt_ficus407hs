  /*
  ******************************************************************************
  * @file     : Ficus_SPI_W25Q32.cpp
  * @Copyright: ViewTool 
  * @Revision : Ver 1.0
  * @Date     : 2019/10/23 
  * @brief    : Ficus_SPI_W25Q32 Demo
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
#include "ControlSPI.h"
#else 
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "vt_spi.h"
#endif


int main(int argc, char* argv[])
{
	int ret,i;
	VSI_INIT_CONFIG	SPI_Init;
	uint8_t	WriteDataTemp[512]={0};
	uint8_t	ReadDataTemp[512]={0};
    int8_t SPI_Index = 1;
	// Check the device number of connections
	ret = VSI_ScanDevice(1);
	if(ret>0){
		printf("The connected device number is:%d\r\n",ret);
	}else{
		printf("No device to connect!\r\n");
		return 0;
	}
	// Open Device
	ret = VSI_OpenDevice(VSI_USBSPI,0,0);
	if(ret != ERR_SUCCESS){
		printf("Open device error :%d\r\n",ret);
		return ret;
	}else{
		printf("Open device success!\r\n");
	}
	// Device initialization
	SPI_Init.ClockSpeed = 1125000;
	SPI_Init.ControlMode = 0;
	SPI_Init.CPHA = 0;
	SPI_Init.CPOL = 0;
	SPI_Init.LSBFirst = 0;
	SPI_Init.MasterMode = 1;
	SPI_Init.SelPolarity = 0;
	SPI_Init.TranBits = 8;
	ret = VSI_InitSPI(VSI_USBSPI,0,SPI_Index,&SPI_Init);
	if(ret != ERR_SUCCESS){
		printf("Initialization device error :%d\r\n",ret);
		return ret;
	}else{
		printf("Initialization device success!\r\n");
	}
	// JEDEC ID
	WriteDataTemp[0] = 0x9F;
	ret = VSI_WriteReadBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,1,ReadDataTemp,3);
	if(ret != ERR_SUCCESS){
		printf("Read flash ID error :%d\r\n",ret);
		return ret;
	}else{
		printf("Flash ID = 0x%06X\r\n",(ReadDataTemp[0]<<16)|(ReadDataTemp[1]<<8)|(ReadDataTemp[2]));
	}
	// Write Enable
	WriteDataTemp[0] = 0x06;
	ret = VSI_WriteBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,1);
	if(ret != ERR_SUCCESS){
		printf("Flash write enable error :%d\r\n",ret);
		return ret;
	}else{
		printf("Write enable success!\r\n");
	}
	// Sector Erase (4KB)
	WriteDataTemp[0] = 0x20;
	WriteDataTemp[1] = 0x00;
	WriteDataTemp[2] = 0x00;
	WriteDataTemp[3] = 0x00;
	ret = VSI_WriteBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,4);
	if(ret != ERR_SUCCESS){
		printf("Sector Erase start error :%d\r\n",ret);
		return ret;
	}else{
		printf("Sector erase start success!\r\n");
	}
	// Check the operation to complete
	do{
		WriteDataTemp[0] = 0x05;// Read Status Register-1
		ret = VSI_WriteReadBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,1,ReadDataTemp,1);

	}while((ReadDataTemp[0]&0x01)&&(ret == ERR_SUCCESS));
	if(ret != ERR_SUCCESS){
		printf("Sector Erase error :%d\r\n",ret);
		return ret;
	}else{
		printf("Sector erase success!\r\n");
	}
	// Write Enable
	WriteDataTemp[0] = 0x06;
	ret = VSI_WriteBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,1);
	if(ret != ERR_SUCCESS){
		printf("Flash write enable error :%d\r\n",ret);
		return ret;
	}else{
		printf("Write enable success!\r\n");
	}
	// Page Program
	WriteDataTemp[0] = 0x02;// Page Program command
	WriteDataTemp[1] = 0x00;// Address
	WriteDataTemp[2] = 0x00;
	WriteDataTemp[3] = 0x00;
	for(i=4;i<(256+4);i++){
		WriteDataTemp[i] = i-4;
	}
	ret = VSI_WriteBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,256+4);
	if(ret != ERR_SUCCESS){
		printf("Page program start error :%d\r\n",ret);
		return ret;
	}else{
		printf("Page program start success!\r\n");
	}
	// Check the operation to complete
	do{
		WriteDataTemp[0] = 0x05;// Read Status Register-1
		ret = VSI_WriteReadBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,1,ReadDataTemp,1);

	}while((ReadDataTemp[0]&0x01)&&(ret == ERR_SUCCESS));
	if(ret != ERR_SUCCESS){
		printf("Page program error :%d\r\n",ret);
		return ret;
	}else{
		printf("Page program success!\r\n");
	}
	// Read Data
	WriteDataTemp[0] = 0x03;//Read Data command
	WriteDataTemp[1] = 0x00;//address
	WriteDataTemp[2] = 0x00;
	WriteDataTemp[3] = 0x00;
	ret = VSI_WriteReadBytes(VSI_USBSPI,0,SPI_Index,WriteDataTemp,4,ReadDataTemp,256);
	if(ret != ERR_SUCCESS){
		printf("Read Data error :%d\r\n",ret);
		return ret;
	}else{
		printf("Read Data success\r\n");
	}
	for(i=0;i<256;i++){
		if((i%26)==0){
			printf("\r\n");
		}
		printf("%02X ",ReadDataTemp[i]);
	}
	printf("\r\n\r\n");
	return 0;
}




