

#include <stdio.h>
#include "stm32f4xx_conf.h"
#define SWD_Debug   1

#if SWD_Debug

#pragma import(__use_no_semihosting_swi)  
  
struct __FILE { int handle; /* Add whatever you need here */ };  
    FILE __stdout;  
    FILE __stdin;  
      
int fputc(int ch, FILE *f)   
{  
    return ITM_SendChar(ch);  
}  
  
volatile int32_t ITM_RxBuffer;  
int fgetc(FILE *f)  
{  
  while (ITM_CheckChar() != 1) __NOP();  
  return (ITM_ReceiveChar());  
}  
  
int ferror(FILE *f)  
{  
    /* Your implementation of ferror */  
    return EOF;  
}  
  
void _ttywrch(int c)  
{  
    fputc(c, 0);  
}  
  
int __backspace()  
{  
    return 0;  
}  
void _sys_exit(int return_code)  
{  
label:  
    goto label;  /* endless loop */  
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