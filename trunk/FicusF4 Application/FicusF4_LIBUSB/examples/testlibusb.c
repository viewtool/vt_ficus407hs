#include <stdio.h>
#include <string.h>
#include "libusb.h"

#define  USB_VID  0x0483
#define  USB_PID  0x0666

#define	USB_EP_SIZE				512
#define	USB_SEND_BUFFER_SIZE	10240

#define EP1_IN  0x81
#define EP1_OUT 0x01
#define USB_TIMEOUT  500
#define VT_DEV_MAX    5

static int verbose = 0;

static int vt_dev_index[VT_DEV_MAX];
static int vt_dev_num;
static libusb_device **devs;
static libusb_device_handle *device_handle = NULL;
static uint8_t tx_buffer[4096];
static uint8_t rx_buffer[4096];
static uint16_t counter = 0;

static libusb_context *ctx = NULL;
static libusb_device_handle *handle;

static uint8_t receiveBuf[64];
static uint8_t transferBuf[64];

static int ficus_usb_read(struct libusb_device_handle *dev_handle,
	unsigned char endpoint, unsigned char *data, int length, int *transferred,
	unsigned int timeout)
{
	int nread = 0, ret;
	ret = libusb_bulk_transfer(dev_handle, endpoint, data, length,
			transferred, timeout);
	if (ret){
		printf("ERROR in bulk read: %d\n", ret);
		return -1;
    }
}
static int ficus_usb_write(struct libusb_device_handle *dev_handle,
	unsigned char endpoint, unsigned char *data, int length, int *transferred,
	unsigned int timeout)
{
	int n, ret;
    //count up
    //write transfer
    //probably unsafe to use n twice...
	ret = libusb_bulk_transfer(dev_handle, EP1_OUT, data, length,
			transferred, timeout);
    //Error handling
    switch(ret){
        case 0:
            printf("send %d bytes to device\n", length);
        default:
            break;
    }
    return -1;
}
int ficus_usb_init(void)
{
	int r = 1;
	libusb_init(&ctx);
	handle = libusb_open_device_with_vid_pid(ctx,
		USB_VID, USB_PID);
	if (!handle) {
		perror("device not found");
		return 1;
	}
	r = libusb_claim_interface(handle, 0);
	if (r < 0) {
		fprintf(stderr, "usb_claim_interface error %d\n", r);
		return 2;
	}
	return 0;
}
int main(int argc, char*argv[])
{
	int i;
	int n;
	int ret;
	int actual_length;
	int count = 0;
	int PacketSize =64 * 1024;
	char *pReadDataBuffer = (char *)malloc(PacketSize);
	char WriteDataBuffer[4];
	int DataNum = 5000;
	int DataNumIndex = DataNum;
	ret = ficus_usb_init();
	if (ret != 0)
	{
		printf("ficus libusb init error\n");
	}
	else {
		printf("ficus libusb init success\n");
	}
	WriteDataBuffer[0] = DataNum >> 24;
	WriteDataBuffer[1] = DataNum >> 16;
	WriteDataBuffer[2] = DataNum >> 8;
	WriteDataBuffer[3] = DataNum >> 0;
	ret = ficus_usb_write(handle, EP1_OUT, WriteDataBuffer,4,&actual_length, 0);
	if (ret) {
		printf("Write Data Success\n");
	}
	else {
		printf("Write Data Fail\n");
	}
	LARGE_INTEGER litmp;
	LONGLONG StartTime, EndTime;
	double dfFreq;
	QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
	dfFreq = (double)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
	StartTime = litmp.QuadPart;
	do {
		ret = ficus_usb_read(handle, EP1_IN, pReadDataBuffer, PacketSize, &actual_length,1000);
		if (ret == PacketSize) {
			//break;
		}
		else {
			DataNumIndex--;
		}
	} while (DataNumIndex > 0);
	if (DataNumIndex > 0) {
		printf("Read Data Fail\n");
	}
	else {
		printf("Read Data Success\n");
	}
	QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
	EndTime = litmp.QuadPart; // Stop time
	printf("-----------------------[url=http://www.viewtool.com]www.viewtool.com[/url]-----------------------\n");
	printf("Read Data Byte Num: %d MBytes\n", (DataNum - DataNumIndex)*PacketSize / (1024 * 1024));
	printf("Read Data waste time: %f s\n", (EndTime - StartTime) / dfFreq);
	printf("Read Data Speed: %.3f MByte/s\n", (DataNum - DataNumIndex)*PacketSize / ((EndTime - StartTime) / dfFreq) / (1024 * 1024));
	printf("-----------------------[url=http://www.viewtool.com]www.viewtool.com[/url]-----------------------\n");
	//释放动态分配的内存空间
	free(pReadDataBuffer);
	//while (1)
	//{
	//	count++;	
	//	ret = ficus_usb_read(handle, EP1_IN, receiveBuf, 8, &actual_length, 0);
	//	Sleep(100);
	//	ret = ficus_usb_write(handle, EP1_OUT, &receiveBuf[1], 8, &actual_length, 0);
	//	Sleep(100);
 //   }
    //never reached
	libusb_close(handle);
	libusb_exit(NULL);

	return 0;
}