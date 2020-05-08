#ifndef __VT_LCD_H_
#define __VT_LCD_H_

typedef struct _LCD_INIT_CONFIG{			
	uint16_t id;				
	uint8_t  dir;
    uint8_t  touch_type;
    uint32_t numbyte;
    uint16_t block_size;
}LCD_INIT_CONFIG,*PLCD_INIT_CONFIG;

/* Private functions ---------------------------------------------------------*/

extern int32_t VT_LCD_Init(int32_t DevType, int32_t DevIndex,PLCD_INIT_CONFIG pInitConfig);

#endif
