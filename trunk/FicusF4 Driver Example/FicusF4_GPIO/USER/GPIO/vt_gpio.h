

#ifndef VT_GPIO_H_
#define VT_GPIO_H_


// The adapter type definition
#define VGI_USBGPIO			(1)	

// Define GPIO pin
#define	VGI_GPIO_PIN0		(1<<0)	//GPIO_0
#define	VGI_GPIO_PIN1		(1<<1)	//GPIO_1
#define	VGI_GPIO_PIN2		(1<<2)	//GPIO_2
#define	VGI_GPIO_PIN3		(1<<3)	//GPIO_3
#define	VGI_GPIO_PIN4		(1<<4)	//GPIO_4
#define	VGI_GPIO_PIN5		(1<<5)	//GPIO_5
#define	VGI_GPIO_PIN6		(1<<6)	//GPIO_6
#define	VGI_GPIO_PIN7		(1<<7)	//GPIO_7
#define	VGI_GPIO_PIN8		(1<<8)	//GPIO_8
#define	VGI_GPIO_PIN9		(1<<9)	//GPIO_9
#define	VGI_GPIO_PIN10		(1<<10)	//GPIO_10
#define	VGI_GPIO_PIN11		(1<<11)	//GPIO_11
#define	VGI_GPIO_PIN12		(1<<12)	//GPIO_12
#define	VGI_GPIO_PIN13		(1<<13)	//GPIO_13
#define	VGI_GPIO_PIN14		(1<<14)	//GPIO_14
#define	VGI_GPIO_PIN15		(1<<15)	//GPIO_15
#define	VGI_GPIO_PIN_ALL	(0xFFFF)//ALL PIN

#define VGI_GPIO_PORTA      (1<<16)
#define VGI_GPIO_PORTB      (1<<17)
#define VGI_GPIO_PORTC      (1<<18)
#define VGI_GPIO_PORTD      (1<<19)
#define VGI_GPIO_PORTE      (1<<20)
#define VGI_GPIO_PORT_ALL   (0xFFFF<<16)

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

extern int32_t  VGI_ScanDevice(uint8_t NeedInit);
extern int32_t  VGI_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
extern int32_t  VGI_CloseDevice(int32_t DevType,int32_t DevIndex);
extern int32_t  VGI_InitGPIO(int32_t DevType, int32_t DevIndex, uint32_t PinMask, uint32_t PinMode);
extern int32_t  VGI_WriteDatas(int32_t DevType,int32_t DevIndex, uint32_t PinMask,uint16_t Data);
extern int32_t  VGI_ReadDatas(int32_t DevType,int32_t DevIndex,uint32_t PinMask,uint16_t *pData);
extern int32_t	 VGI_SetPins(int32_t DevType,int32_t DevIndex,uint32_t PinMask);
extern int32_t	 VGI_ResetPins(int32_t DevType,int32_t DevIndex,uint32_t PinMask);
extern int32_t	 VGI_SetInput(int32_t DevType,int32_t DevIndex,uint32_t PinMask);
extern int32_t	 VGI_SetOutput(int32_t DevType,int32_t DevIndex,uint32_t PinMask);
extern int32_t	 VGI_SetOpenDrain(int32_t DevType,int32_t DevIndex,uint32_t PinMask);

#endif


