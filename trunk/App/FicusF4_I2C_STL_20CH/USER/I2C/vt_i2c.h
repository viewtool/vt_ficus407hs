


#ifndef __VT_I2C_H__
#define __VT_I2C_H__

#include <stdio.h>

//General Error Code
#define	ERR_SUCCESS					(0)		// no Error
#define	ERR_PARAMETER_NULL			(-1)	// void pointer 
#define	ERR_INPUT_DATA_TOO_MUCH		(-2)	// too many parameters
#define	ERR_INPUT_DATA_TOO_LESS		(-3)	// too few parameters
#define	ERR_INPUT_DATA_ILLEGALITY	(-4)	// illegal parameter
#define	ERR_USB_WRITE_DATA			(-5)	// USB write data error
#define	ERR_USB_READ_DATA			(-6)	// USB read data error
#define	ERR_READ_NO_DATA			(-7)	// no data return when request data
#define	ERR_OPEN_DEVICE				(-8)	// failed to open device
#define	ERR_CLOSE_DEVICE			(-9)	// failed to close device
#define	ERR_EXECUTE_CMD				(-10)	// the command failed to execute
#define ERR_SELECT_DEVICE			(-11)	// failed to select device
#define	ERR_DEVICE_OPENED			(-12)	// device has open
#define	ERR_DEVICE_NOTOPEN			(-13)	// device not open
#define	ERR_BUFFER_OVERFLOW			(-14)	// buffer overflow
#define	ERR_DEVICE_NOTEXIST			(-15)	// device not exist
#define	ERR_LOAD_KERNELDLL			(-16)	// failed to load KernelDLL
#define ERR_CMD_FAILED				(-17)	// failed to execute command
#define	ERR_BUFFER_CREATE			(-18)	// out of memory

#define I2C_ERROR_BUSY                0x04

#define I2C_ERROR_NACK				  0x0C		///< NACK error

#define MASTER_MODE_SELECT_FAILED                         (1)
#define MASTER_TRANSMITTER_MODE_SELECTED_FAILED           (2)    
#define MASTER_RECEIVER_MODE_SELECTED_FAILED              (3)
#define MASTER_BYTE_RECEIVED_FAILED                       (4)
#define MASTER_BYTE_TRANSMITTING_FAILED                   (5)
#define MASTER_BYTE_TRANSMITTED_FAILED                    (6)
#define MASTER_MODE_ADDRESS10_FAILED                      (7)
#define MASTER_GET_I2C_FLAG_BUSY_FAILED					   				(8)

#define SLAVE_WRITE	(1)
#define SLAVE_READ	(2)

#define VII_EVENT_PULLUP_FALLING			0x000C
#define VII_EVENT_PULLUP_RISING				0x0008
#define VII_EVENT_PULLUP_RISING_FALLING		0x0010
#define VII_EVENT_FLOAT_FALLING				0x030C
#define VII_EVENT_FLOAT_RISING				0x0308
#define VII_EVENT_FLOAT_RISING_FALLING		0x0310

//The adapter type definition
#define VII_USBI2C			(1)		//Adapter Type
//The adapter data initialization definition
#define VII_ADDR_7BIT		(7)		//7-bit address mode
#define VII_ADDR_10BIT		(10)	//10-bit address mode
#define VII_HCTL_SLAVE_MODE	(0)		//Standard slave mode
#define VII_HCTL_MODE		(1)		//Standard mode
#define VII_SCTL_MODE		(2)		//GPIO mode
#define VII_MASTER			(1)		//Master
#define VII_SLAVE			(0)		//Slave
#define VII_SUB_ADDR_NONE	(0)		//No sub-address
#define VII_SUB_ADDR_1BYTE	(1)		//1Byte sub-address
#define VII_SUB_ADDR_2BYTE	(2)		//2Byte sub-address
#define VII_SUB_ADDR_3BYTE	(3)		//3Byte sub-address
#define VII_SUB_ADDR_4BYTE	(4)		//4Byte sub-address


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
  
_sys_exit(int x) 
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
typedef struct
{
	uint32_t  speed;        ///<I2C��д�ٶ�
	uint8_t 	controlMode;  ///<I2C���Ʒ�ʽ
	uint8_t 	subAddrWidth; ///<�ӵ�ַ�ֽ���
	uint8_t 	slaveAddrMode; ///<�豸��ַģʽ
	uint8_t		MasterMode;		//����ģʽ���ߴӻ�ģʽ
}I2C_INIT_INFO;
//I2C���ݴ���ṹ��
//I2C�߼��������ݽṹ��
typedef struct
{
    //��������
    unsigned char MST_TRX_S;
    unsigned char MST_TRX_S_R;
    unsigned char MST_TRX_SLAW_ACK;
    unsigned char MST_TRX_SLAW_NACK;
    unsigned char MST_TRX_Data_ACK;
    unsigned char MST_TRX_Data_NACK;
    unsigned char MST_TRX_ALI;
    //��������
    unsigned char MST_REC_S;
    unsigned char MST_REC_S_R;
    unsigned char MST_REC_NACK_ALI;
    unsigned char MST_REC_SLAR_ACK;
    unsigned char MST_REC_SLAR_NACK;
    unsigned char MST_REC_Data_ACK;
    unsigned char MST_REC_Data_NACK;
}I2C_ADV_SET;
typedef struct
{
	unsigned int    subAddr;        //�����ݶ�Ӧ���ӵ�ַ
	unsigned char   SerialNumber;   //�����ݰ����
	unsigned char   *p_dataBuff;    //���ݻ�������ַ
	unsigned short  dataLenght;     //��������ݳ���
	unsigned char   leaveDataPack;  //��Ҫ�����ʣ�����ݰ���
	int             deviceNumber;   //��I2C�豸��
}I2C_DATA;


typedef struct IIC_TIME
{
    unsigned short tHD_STA;///<��ʼ�źű���ʱ��
    unsigned short tSU_STA;///<��ʼ�źŽ���ʱ��
    unsigned short tLOW;///<ʱ�ӵ͵�ƽʱ��
    unsigned short tHIGH;///<ʱ�Ӹߵ�ƽʱ��
    unsigned short tSU_DAT;///<�������뽨��ʱ��
    unsigned short tSU_STO;///<ֹͣ�źŽ���ʱ��
    unsigned short tDH;///<�����������ʱ��
    unsigned short tDH_DAT;///<�������뱣��ʱ��
    unsigned short tAA;///<SCL�����SDA���������Ӧ���ź�
    unsigned short tR;///<SDA��SCL����ʱ��
    unsigned short tF;///<SDA��SCL�½�ʱ��
	unsigned short tBuf;	///<�µķ��Ϳ�ʼǰ���߿���ʱ��		
	unsigned char tACK[4];	
	unsigned short tStart;	
	unsigned short tStop;							
}IICTime;
//1.Data types of Ginkgo series adapter information.
typedef  struct  _VII_BOARD_INFO{
	uint8_t		ProductName[32];	//Product name
	uint8_t		FirmwareVersion[4];	//Firmware version
	uint8_t		HardwareVersion[4];	//Hardware version
	uint8_t		SerialNumber[12];	//The adapter serial number
} VII_BOARD_INFO,*PVII_BOARD_INFO; 


//2.I2C data types initialization Define
typedef struct _VII_INIT_CONFIG{
	uint8_t		MasterMode;		//Master-slave choice: 0-slave, 1-master
	uint8_t		ControlMode;	//Control mode: 0-Standard slave mode, 1-Standard mode, 2-GPIO mode
	uint8_t		AddrType;		//7-7bit mode, 10-10bit mode
	uint8_t		SubAddrWidth;	//Sub-Address width: value of 0~4, 0 means no Sub-Address mode
	uint16_t	Addr;			//Device address in salve mode
	uint32_t	ClockSpeed;		//Clock frequency(HZ)
}VII_INIT_CONFIG,*PVII_INIT_CONFIG;

//3.I2C time parameter definition in GPIO mode(ms)
typedef struct _VII_TIME_CONFIG
{
    uint16_t tHD_STA;   //Timing for start signal Keeping
    uint16_t tSU_STA;   //Timing for start signal be established
    uint16_t tLOW;      //Timing for clock low level
    uint16_t tHIGH;     //Timing for clock high level
    uint16_t tSU_DAT;   //Timing for data input be established
    uint16_t tSU_STO;   //Timing for stop signal be established
    uint16_t tDH;       //Timing for data output Keeping
    uint16_t tDH_DAT;   //Timing for data input Keeping
    uint16_t tAA;       //SCL lower to SDA output and response signal
    uint16_t tR;        //Timing for SDA and SCL rising
    uint16_t tF;        //Timing for SDA and SCL going down
    uint16_t tBuf;      //Free timing of the bus until the new mission
    uint8_t tACK[4];
    uint16_t tStart;
    uint16_t tStop;
}VII_TIME_CONFIG,*PVII_TIME_CONFIG;

extern I2C_INIT_INFO I2C_Info[];	///<I2C�����������Ϣ
extern IICTime 		swi2c_time;

extern int32_t VII_ScanDevice(uint8_t NeedInit);
extern int32_t VII_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
extern int32_t VII_CloseDevice(int32_t DevType,int32_t DevIndex);
extern int32_t VII_ReadBoardInfo(int32_t DevIndex,PVII_BOARD_INFO pInfo);
extern int32_t VII_TimeConfig(int32_t DevType, int32_t DevIndex, int32_t I2CIndex, PVII_TIME_CONFIG pTimeConfig);
extern int32_t VII_InitI2C(int32_t DevType, int32_t DevIndex, int32_t I2CIndex, PVII_INIT_CONFIG pInitConfig);
extern int32_t VII_WriteBytes(int32_t DevType,int32_t DevIndex,int32_t I2CIndex,uint16_t SlaveAddr,uint32_t SubAddr,uint8_t *pWriteData,uint16_t Len);
extern int32_t VII_ReadBytes(int32_t DevType,int32_t DevIndex,int32_t I2CIndex,uint16_t SlaveAddr,uint32_t SubAddr,uint8_t *pReadData,uint16_t Len);
extern int32_t VII_SetUserKey(int32_t DevType,int32_t DevIndex,uint8_t* pUserKey);
extern int32_t VII_CheckUserKey(int32_t DevType,int32_t DevIndex,uint8_t* pUserKey);
extern int32_t VII_SlaveReadBytes(int32_t DevType,int32_t DevIndex,int32_t I2CIndex,uint8_t* pReadData,uint16_t *pLen);
extern int32_t VII_SlaveWriteBytes(int32_t DevType,int32_t DevIndex,int32_t I2CIndex,uint8_t* pWriteData,uint16_t Len);
extern int32_t VII_SlaveWriteRemain(int32_t DevType,int32_t DevIndex,int32_t I2CIndex,uint16_t* pRemainBytes);

#endif
