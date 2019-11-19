
#ifndef __VT_USART_H__
#define __VT_USART_H__


#ifndef USART
#define USART
#endif
#define UART_USBUART		(2)

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
typedef  struct  _UART_BOARD_INFO{
	uint8_t		ProductName[32];	
	uint8_t		FirmwareVersion[4];
	uint8_t		HardwareVersion[4];	
	uint8_t		SerialNumber[12];	
} UART_BOARD_INFO,*PUART_BOARD_INFO; 



typedef struct _UART_INIT_CONFIG{
	uint8_t		StopBits;		
	uint8_t		WordLength;		
	uint8_t		Parity;			
	uint16_t	RS485Mode;		
	uint32_t	BaudRate;		
}UART_INIT_CONFIG,*PUART_INIT_CONFIG;

extern int32_t  UART_ScanDevice(uint8_t NeedInit);
extern int32_t  UART_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
extern int32_t  UART_InitDevice(int32_t DevType,int32_t DevIndex,int32_t UARTIndex, PUART_INIT_CONFIG pInitConfig);
extern int32_t  UART_WriteBytes(int32_t DevType,int32_t DevIndex,int32_t UARTIndex,uint8_t* pWriteData,uint16_t Len);
extern int32_t  UART_ReadBytes(int32_t DevType,int32_t DevIndex,int32_t UARTIndex,uint8_t *pReadData,uint16_t *pLen);

#endif


