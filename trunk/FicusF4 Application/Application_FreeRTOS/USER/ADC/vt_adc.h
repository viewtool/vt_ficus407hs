

#ifndef __VT_ADC_H_
#define __VT_ADC_H_

#include <stdio.h>

#define VAI_USBADC		(1)

#define	VAI_ADC_CH0		(1<<0)	    
#define	VAI_ADC_CH1		(1<<1)	    
#define	VAI_ADC_CH2		(1<<2)	    
#define	VAI_ADC_CH3		(1<<3)	    
#define	VAI_ADC_CH4		(1<<4)	    
#define	VAI_ADC_CH5		(1<<5)	    
#define	VAI_ADC_CH6		(1<<6)	    
#define	VAI_ADC_CH7		(1<<7)	       
#define	VAI_ADC_ALL		(0xFF)	

#define	ERR_SUCCESS					(0)		
#define	ERR_PARAMETER_NULL			(-1)	
#define	ERR_INPUT_DATA_TOO_MUCH		(-2)	
#define	ERR_INPUT_DATA_TOO_LESS		(-3)	
#define	ERR_INPUT_DATA_ILLEGALITY	(-4)	
#define	ERR_USB_WRITE_DATA			(-5)	
#define	ERR_USB_READ_DATA			(-6)	
#define	ERR_READ_NO_DATA			(-7)	
#define	ERR_OPEN_DEVICE				(-8)	
#define	ERR_CLOSE_DEVICE			(-9)	
#define	ERR_EXECUTE_CMD				(-10)	
#define ERR_SELECT_DEVICE			(-11)	
#define	ERR_DEVICE_OPENED			(-12)	
#define	ERR_DEVICE_NOTOPEN			(-13)	
#define	ERR_BUFFER_OVERFLOW			(-14)	
#define	ERR_DEVICE_NOTEXIST			(-15)	
#define	ERR_LOAD_KERNELDLL			(-16)	
#define ERR_CMD_FAILED				(-17)	
#define	ERR_BUFFER_CREATE			(-18)	
 
typedef  struct  _VAI_BOARD_INFO{
	uint16_t	dr_Version;			
	uint16_t	in_Version;			
	uint8_t		adc_num;			
	char		str_hw_Name[100];	
	char		str_fw_Version[100];
	char		str_hw_Version[100];
	char		str_Serial_Num[100];
	uint16_t	Reserved[4];		
} VAI_BOARD_INFO,*PVAI_BOARD_INFO; 

extern int32_t VAI_ScanDevice(uint8_t NeedInit);
extern int32_t VAI_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
extern int32_t VAI_CloseDevice(int32_t DevType,int32_t DevIndex);
extern int32_t VAI_ReadBoardInfo(int32_t DevType,int32_t DevIndex,PVAI_BOARD_INFO pInfo);
extern int32_t VAI_InitADC(int32_t DevType, int32_t DevIndex, uint8_t Channel, uint16_t Period);
extern int32_t VAI_ReadDatas(int32_t DevType,int32_t DevIndex,uint16_t DataNum,uint16_t *pData);


#endif
