
#define HMC5883L    1
#define GMC5883     0

#if HMC5883L
#define HMC5883L_SLAVE_ADDR	0x3C   //7bit¦Ì??¡¤+1bit?¨¢D¡ä??¡ê??¨¢D¡ä??¨¦¨¨???a0
#define STATUS_REG       0x09
#define DATA_START_REG   0x03
//#define HMC5883L_SLAVE_ADDR	0x0d//7bit¦Ì??¡¤+1bit?¨¢D¡ä??¡ê??¨¢D¡ä??¨¦¨¨???a0
//#define HMC5883L_SLAVE_ADDR	0x1e  //7bit¦Ì??¡¤+1bit?¨¢D¡ä??¡ê??¨¢D¡ä??¨¦¨¨???a0
#define CHIP_ID          0x0a    // should read out 'H'
#define CHIP_ID2          0x0b    // should read out '4'
#define CHIP_ID3          0x0c    // should read out '3'

#endif 
#if GMC5883
#define HMC5883L_SLAVE_ADDR	0x1a   //7bit¦Ì??¡¤+1bit?¨¢D¡ä??¡ê??¨¢D¡ä??¨¦¨¨???a0
#define STATUS_REG       0x06
#define DATA_START_REG   0x00
#define CHIP_ID          0x0d
#endif 
/* Includes ------------------------------------------------------------------*/
#ifdef WINAPI
#include "ControlI2C.h"
#include "HMC5883L.h"
#else
#include "stm32f4xx_conf.h"
#include "vt_i2c.h"
#include "HMC5883L.h"
#endif



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

enum Status HMC5883L_Init(void)
{
	int ret;
	VII_INIT_CONFIG I2C_Config;
	//Scan device
	ret = VII_ScanDevice(1);
	if(ret <= 0){
		return FAILED;
	}
    //Open device
    ret = VII_OpenDevice(VII_USBI2C, 0, 0);
    if (ret != ERR_SUCCESS){
        return FAILED;
    }
    //Initializes the device
    I2C_Config.AddrType = VII_ADDR_7BIT;
    I2C_Config.ClockSpeed = 400000;
    I2C_Config.ControlMode = VII_HCTL_MODE;
    I2C_Config.MasterMode = VII_MASTER;
    I2C_Config.SubAddrWidth = VII_SUB_ADDR_1BYTE;
    ret = VII_InitI2C(VII_USBI2C, 0, 0, &I2C_Config);
    if (ret != ERR_SUCCESS){
        return FAILED;
    }
	return SUCCESS_S;
}
/**
  * @brief  ????HMC5883L1¡è¡Á¡Â?¡ê¨º?¦Ì¨¨
  * @param  None
  * @retval SUCCESS_S-????3¨¦1|¡ê?FAILED-????¨º¡ì¡ã¨¹
  */
enum Status HMC5883L_Config(void)
{
	int ret;
	uint8_t read_buffer[6]={0};
#if GMC5883
	uint8_t write_buffer[3]={0x41,0x01, 0x01};
	//Put the HMC5883 IC into the correct operating mode
    ret = VII_WriteBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, 0x9, &write_buffer[0], 1);
    ret = VII_WriteBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, 0xa, &write_buffer[1], 1);
    ret = VII_WriteBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, 0xb, &write_buffer[2], 1);
#else 
	uint8_t write_buffer[2]={0};
	//Put the HMC5883 IC into the correct operating mode
	write_buffer[0] = 0x00;
    ret = VII_WriteBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, 0x0, write_buffer, 2);
#endif 
    if (ret != ERR_SUCCESS){
        return FAILED;
    }
#if GMC5883
	ret = VII_ReadBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, CHIP_ID, read_buffer, 1);
#endif 
#if HMC5883L
	ret = VII_ReadBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, CHIP_ID, read_buffer, 3);
#endif 
	if (ret != ERR_SUCCESS){
		return FAILED;
	}
	else
	{
#if HMC5883L
		// should be "H4C"
		printf("%c%c%c\n" , read_buffer[0],read_buffer[1],read_buffer[2]);
#else
		printf("CHIP_ID= %x\n" , read_buffer[0]);
#endif 
        Sleep(100);  
	}
	return SUCCESS_S;
}
/**
  * @brief  ?¨¢¨¨?HMC5883L?¨´2a¡ä?3??¦Ì
  * @param  pXMagnetic X?¨¢¡ä?3??¦Ì????
  * @param  pYMagnetic Y?¨¢¡ä?3??¦Ì????
  * @param  pZMagnetic Z?¨¢¡ä?3??¦Ì????
  * @retval SUCCESS_S-?¨¢¨¨?¨ºy?Y3¨¦1|¡ê?FAILED-?¨¢¨¨?¨ºy?Y¨º¡ì¡ã¨¹
  */
enum Status HMC5883L_ReadMagnetic(int16_t *pXMagnetic,int16_t *pYMagnetic,int16_t *pZMagnetic)
{
	int ret,i;
	uint8_t write_buffer[2]={0};
	uint8_t read_buffer[6]={0};
	while(1){
		//Read status
		ret = VII_ReadBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, STATUS_REG, read_buffer, 1);
		if (ret != ERR_SUCCESS){
			return FAILED;
		}
		//Data ready?
//		if(read_buffer[0]&0x01){
		if(1){
			//Tell the HMC5883 where to begin reading data
			ret = VII_ReadBytes(VII_USBI2C, 0, 0, HMC5883L_SLAVE_ADDR, DATA_START_REG, read_buffer, 6);
			if (ret != ERR_SUCCESS){
				return FAILED;
			}
			*pXMagnetic = (read_buffer[0] << 8)|read_buffer[1];
			*pYMagnetic = (read_buffer[2] << 8)|read_buffer[3];
			*pZMagnetic = (read_buffer[4] << 8)|read_buffer[5];
			return SUCCESS_S;
		}
	}
}
