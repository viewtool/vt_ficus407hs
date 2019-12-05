#include <stdint.h>
/* Private typedef -----------------------------------------------------------*/
enum Status{
	FAILED = 0,
	SUCCESS_S,
};
enum Status;
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
#ifndef __HMC5883L_H
#define __HMC5883L_H

enum Status HMC5883L_Init(void);
enum Status HMC5883L_Config(void);
enum Status HMC5883L_ReadMagnetic(int16_t *pXMagnetic,int16_t *pYMagnetic,int16_t *pZMagnetic);

#endif
