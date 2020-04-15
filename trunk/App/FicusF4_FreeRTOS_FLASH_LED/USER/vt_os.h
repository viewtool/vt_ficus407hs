
#ifndef __VT_OS_H
#define __VT_OS_H

typedef void (*VTFunction_t)( void * );

typedef struct _OS_INIT_CONFIG{
	uint32_t   HeepSize;
    uint8_t   *rtHeap;
}VOS_INIT_CONFIG,*PVOS_INIT_CONFIG;

extern int32_t VOS_Init(PVOS_INIT_CONFIG pInitConfig);
extern int32_t VOS_Start(void);
extern int32_t VOS_Enter_Critical(void);
extern int32_t VOS_Exit_Critical(void);
extern int32_t VOS_Create_Task(VTFunction_t pxTaskCode,
							const char * const pcName,		/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
							const uint16_t usStackDepth,
							void * const pvParameters,
							uint32_t uxPriority,
							void** const pxCreatedTask );
extern int32_t VOS_Delete_Task(void * pxDeleteTask);
#endif



