
#ifndef __VT_USB_H_
#define __VT_USB_H_


#define VUI_USB			            (0)		//USB Type

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

#define VT_USB_HS                   (0)
#define VT_USB_FS                   (1)


extern int32_t VUI_ScanDevice(uint8_t NeedInit);
extern int32_t VUI_OpenDevice(int32_t DeviceType,int32_t DeviceIndex,int32_t Reserved);
extern int32_t  VUI_CloseDevice(int32_t DeviceType,int32_t DeviceIndex);
extern int32_t  VUI_InitUSB(int32_t DeviceType, int32_t UsbMode);
extern int32_t  VUI_WriteByte(int32_t DeviceType, int32_t DeviceIndex,uint8_t *p_WriteData,uint32_t Lenth,uint16_t waittime);
extern int32_t  VUI_ReadByte(int32_t DeviceType, int32_t DeviceIndex,uint8_t *p_ReadData,uint32_t Lenth,uint16_t waittime);


#endif

