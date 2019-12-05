


#ifndef VT_COUNTER_H
#define VT_COUNTER_H



#define CNT_USBCNT	1
#define	ERR_SUCCESS					(0)		// no Error
// Define Counter channel
#define	CNT_CH0		(1<<0)	//CNT_CH0	
#define	CNT_CH1		(1<<1)	//CNT_CH1	
#define	CNT_CH2		(1<<2)	//CNT_CH2	
#define	CNT_CH3		(1<<3)	//CNT_CH3	
#define	CNT_ALL		(0x0F)	//CNT_CH_ALL	

typedef struct _CNT_INIT_CONFIG{
	uint8_t 	CounterMode;		//Counter Mode: 0-Up,1-Down
	uint8_t		CounterPolarity;	//Counter Polarity:0-Rising,1-Falling,2-BothEdge
	uint8_t		CounterBitWide;		//Counter Bit Wide:16-16bit,32-32bit
}CNT_INIT_CONFIG,*PCNT_INIT_CONFIG;

extern int32_t  CNT_ScanDevice(uint8_t NeedInit);
extern int32_t  CNT_OpenDevice(int32_t DevType,int32_t DevIndex,int32_t Reserved);
extern int32_t  CNT_CloseDevice(int32_t DevType,int32_t DevIndex);
extern int32_t  CNT_InitCounter(int32_t DevType, int32_t DevIndex, uint8_t Channel, PCNT_INIT_CONFIG pInitConfig);
extern int32_t  CNT_SetCounter(int32_t DevType, int32_t DevIndex, uint8_t Channel, uint32_t *pCounterValue);
extern int32_t  CNT_GetCounter(int32_t DevType, int32_t DevIndex, uint8_t Channel, uint32_t *pCounterValue);
extern int32_t  CNT_StartCounter(int32_t DevType, int32_t DevIndex, uint8_t Channel);
extern int32_t  CNT_StopCounter(int32_t DevType, int32_t DevIndex, uint8_t Channel);



#endif

