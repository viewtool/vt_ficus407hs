
#ifndef VT_PWM_H
#define VT_PWM_H


// Define adapter type
#define VPI_USBPWM		(2)

// Define PWM channel
#define	VPI_PWM_CH0		(1<<0)	//PWM_CH0
#define	VPI_PWM_CH1		(1<<1)	//PWM_CH1
#define	VPI_PWM_CH2		(1<<2)	//PWM_CH2
#define	VPI_PWM_CH3		(1<<3)	//PWM_CH3
#define	VPI_PWM_CH4		(1<<4)	//PWM_CH4
#define	VPI_PWM_CH5		(1<<5)	//PWM_CH5
#define	VPI_PWM_CH6		(1<<6)	//PWM_CH6
#define	VPI_PWM_CH7		(1<<7)	//PWM_CH7
#define	VPI_PWM_ALL		(0XFF)	//PWM_ALL

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
typedef struct _VPI_INIT_CONFIG{
	uint8_t		PWM_ChannelMask;		//PWM索引号
	uint8_t   	PWM_Mode;		//PWM模式
	uint8_t		PWM_Pulse;		//PWM占空比
	uint8_t		PWM_Polarity;	//PWM输出极性
	uint32_t 	PWM_Frequency;	//PWM频率
}VPI_INIT_CONFIG,*PVPI_INIT_CONFIG;

extern int32_t VPI_ScanDevice(uint8_t NeedInit);
extern int32_t VPI_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
extern int32_t VPI_CloseDevice(int32_t DevType,int32_t DevIndex);
extern int32_t VPI_InitPWM(int32_t DevType, int32_t DevIndex, PVPI_INIT_CONFIG pInitConfig);
extern int32_t VPI_StartPWM(int32_t DevType, int32_t DevIndex, uint8_t ChannelMask);
extern int32_t VPI_StopPWM(int32_t DevType, int32_t DevIndex, uint8_t ChannelMask);
extern int32_t VPI_SetPWMPulse(int32_t DevType, int32_t DevIndex, uint8_t ChannelMask,uint8_t *pPulse);
extern int32_t VPI_SetPWMPeriod(int32_t DevType, int32_t DevIndex, uint8_t ChannelMask,uint32_t *pFrequency);


#endif

