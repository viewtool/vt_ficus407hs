#ifndef __VTUSB_H__
#define __VTUSB_H__

	// Device endpoint(s)
#define EP0     0x00
#define EP1_IN  0x81    //wMaxPacketSize:   64	Bulk
#define EP1_OUT 0x01    //wMaxPacketSize:   64	Bulk

extern int8_t VTUSB_ScanDevice(void);
extern int8_t VTUSB_OpenDevice(int DevIndex);
extern int8_t VTUSB_CloseDevice(int DevIndex);


#endif

