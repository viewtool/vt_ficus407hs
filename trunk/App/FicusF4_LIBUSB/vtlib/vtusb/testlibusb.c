/*
* Test suite program based of libusb-0.1-compat testlibusb
* Copyright (c) 2013 Nathan Hjelm <hjelmn@mac.ccom>
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include "libusb.h"
#include "vtusb.h"
#define  USB_VID  0x0483
#define  USB_PID  0x0666

static int8_t usb_init_flag = 0;
#if 0
#define	USB_EP_SIZE				512
#define	USB_SEND_BUFFER_SIZE	10240

#define EP1_IN  0x81
#define EP1_OUT 0x01
#define USB_TIMEOUT  500

int verbose = 0;
#define VT_DEV_MAX    5
int vt_dev_index[VT_DEV_MAX];
int vt_dev_num;
libusb_device **devs;
libusb_device_handle *device_handle = NULL;
unsigned char tx_buffer[4096];
unsigned char rx_buffer[4096];


static libusb_context *ctx = NULL;
static libusb_device_handle *handle;

static uint8_t receiveBuf[64];
uint8_t transferBuf[64];
#endif
#if 0
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define snprintf _snprintf
#endif

//消息传输状态
typedef enum
{
     MSG_NO_STATE=0,//保留
	 MSG_INIT_STATE,//消息初始化状态

	 MSG_MSG_DATA_TRAN_OK=2,//数据正确传输
	 MSG_MSG_DATA_TRAN_ERROR,//消息数据传输错误
	 MSG_MSG_DATA_TRAN_CRC_ERROR,//数据CRC错误
	 MSG_MSG_DATA_TRAN_SRL_ERROR,//数据包序号错误
	 MSG_MSG_EXECUT_OK,//消息执行成功
	 MSG_MSG_EXECUT_ERROR,//消息执行失败

	 MSG_GPIO_NINT_OK,//GPIO初始化成功
	 MSG_GPIO_NINT_ERROR,//GPIO初始化错误
	 MSG_GPIO_WRITE_DATA_OK,//GPIO写数据正确
	 MSG_GPIO_WRITE_DATA_ERROR,//GPIO写数据出错
	 MSG_GPIO_READ_DATA_OK,//GPIO读数据正确
	 MSG_GPIO_READ_DATA_ERROR,//GPIO读数据错误
	 MSG_GPIO_GET_LOG_OK,
	 MSG_GPIO_GET_LOG_ERROR,
}MSG_STATE;

typedef struct
{
    uint8_t x;
    uint8_t y;
}S_POINT;

typedef struct
{
    int32_t message;
    int32_t size;//指lParam所指数据长度
    MSG_STATE status;
	uint8_t PackNum;
    void *lParam;
}S_MSG;

typedef enum
{
    MSG_VT_EMPTY = 0,

    MSG_VT_REQUEST_USB_CONNECTION=0x00000100,
    MSG_VT_REQUEST_USB_CONNECTION_FB,

    MSG_VT_REQUEST_SIGNAL_GENERATION,
    MSG_VT_REQUEST_TESTING,

   // function message
    MSG_VT_REQUEST_PRODUCT_INFO,
    MSG_VT_REQUEST_PRODUCT_INFO_FB,

    //USB连接命令
    MSG_VT_REQUEST_STOP_CMD,//请求停止命令
    MSG_VT_REQUEST_STOP_CMD_FB,
    //Write/Read User Data
    MSG_VT_WRITE_USER_DATA,
    MSG_VT_READ_USER_DATA,

	MSG_VT_REQUEST_WRITE_READ,
	MSG_VT_REQUEST_WRITE_READ_FB,

	MSG_VT_EVENT_READ,
	MSG_VT_EVENT_READ_FB,
	MSG_VT_EVENT_WRITE,
	MSG_VT_EVENT_WRITE_FB,
	MSG_VT_EVENT_CLEAR,
	MSG_VT_EVENT_CLEAR_FB,
// GINKGO_GPIO
	MSG_VT_REQUEST_GPIO_INIT=0x00000600, 
	MSG_VT_REQUEST_GPIO_INIT_FB,
    MSG_VT_REQUEST_GPIO_WRITE_DATA,
    MSG_VT_REQUEST_GPIO_WRITE_DATA_FB,
    MSG_VT_REQUEST_GPIO_READ_DATA,
    MSG_VT_REQUEST_GPIO_READ_DATA_FB,
	MSG_VT_REQUEST_GPIO_READ_DATA_EX,
	MSG_VT_REQUEST_GPIO_READ_DATA_EX_FB,
	MSG_VT_REQUEST_GPIO_READ_DATA_WITH_SIZE,
	MSG_VT_REQUEST_GPIO_READ_DATA_WITH_SIZE_FB,
    MSG_VT_REQUEST_DEVICE_ID,
    MSG_VT_REQUEST_DEVICE_ID_FB,

// CUSTOMER GH GPIO
	MSG_GH_REQUEST_GPIO_INIT=0x00000700, 
	MSG_GH_REQUEST_GPIO_INIT_FB,
    MSG_GH_REQUEST_GPIO_WRITE_DATA,
    MSG_GH_REQUEST_GPIO_WRITE_DATA_FB,
    MSG_GH_REQUEST_GPIO_READ_DATA,
    MSG_GH_REQUEST_GPIO_READ_DATA_FB,
	MSG_GH_REQUEST_GPIO_READ_DATA_EX,
	MSG_GH_REQUEST_GPIO_READ_DATA_EX_FB,
	MSG_GH_REQUEST_GPIO_READ_DATA_WITH_SIZE,
	MSG_GH_REQUEST_GPIO_READ_DATA_WITH_SIZE_FB,
	MSG_GH_REQUEST_DEVICE_STATUS_WITH_SIZE,
	MSG_GH_REQUEST_DEVICE_STATUS_WITH_SIZE_FB,
    MSG_GH_REQUEST_DEVICE_HEART_PULSE_WITH_SIZE_FB,
    MSG_GH_REQUEST_DEVICE_SET_HEART_PULSE_ENABLE,
    MSG_GH_REQUEST_DEVICE_SET_HEART_PULSE_ENABLE_FB,
	MSG_GH_REQUEST_DEVICE_RESET_WITH_SIZE,
	MSG_GH_REQUEST_DEVICE_RESET_WITH_SIZE_FB,
}S_MSG_ENUM;



uint16_t counter=0;
#define USB_TIMEOUT  500



static void print_endpoint_comp(const struct libusb_ss_endpoint_companion_descriptor *ep_comp)
{
	printf("      USB 3.0 Endpoint Companion:\n");
	printf("        bMaxBurst:        %d\n", ep_comp->bMaxBurst);
	printf("        bmAttributes:     0x%02x\n", ep_comp->bmAttributes);
	printf("        wBytesPerInterval: %d\n", ep_comp->wBytesPerInterval);
}

static void print_endpoint(const struct libusb_endpoint_descriptor *endpoint)
{
	int i, ret;

	printf("      Endpoint:\n");
	printf("        bEndpointAddress: %02xh\n", endpoint->bEndpointAddress);
	printf("        bmAttributes:     %02xh\n", endpoint->bmAttributes);
	printf("        wMaxPacketSize:   %d\n", endpoint->wMaxPacketSize);
	printf("        bInterval:        %d\n", endpoint->bInterval);
	printf("        bRefresh:         %d\n", endpoint->bRefresh);
	printf("        bSynchAddress:    %d\n", endpoint->bSynchAddress);

	for (i = 0; i < endpoint->extra_length;) {
		if (LIBUSB_DT_SS_ENDPOINT_COMPANION == endpoint->extra[i + 1]) {
			struct libusb_ss_endpoint_companion_descriptor *ep_comp;

			ret = libusb_get_ss_endpoint_companion_descriptor(NULL, endpoint, &ep_comp);
			if (LIBUSB_SUCCESS != ret) {
				continue;
			}

			print_endpoint_comp(ep_comp);

			libusb_free_ss_endpoint_companion_descriptor(ep_comp);
		}

		i += endpoint->extra[i];
	}
}

static void print_altsetting(const struct libusb_interface_descriptor *interface)
{
	uint8_t i;

	printf("    Interface:\n");
	printf("      bInterfaceNumber:   %d\n", interface->bInterfaceNumber);
	printf("      bAlternateSetting:  %d\n", interface->bAlternateSetting);
	printf("      bNumEndpoints:      %d\n", interface->bNumEndpoints);
	printf("      bInterfaceClass:    %d\n", interface->bInterfaceClass);
	printf("      bInterfaceSubClass: %d\n", interface->bInterfaceSubClass);
	printf("      bInterfaceProtocol: %d\n", interface->bInterfaceProtocol);
	printf("      iInterface:         %d\n", interface->iInterface);

	for (i = 0; i < interface->bNumEndpoints; i++)
		print_endpoint(&interface->endpoint[i]);
}

static void print_2_0_ext_cap(struct libusb_usb_2_0_extension_descriptor *usb_2_0_ext_cap)
{
	printf("    USB 2.0 Extension Capabilities:\n");
	printf("      bDevCapabilityType: %d\n", usb_2_0_ext_cap->bDevCapabilityType);
	printf("      bmAttributes:       0x%x\n", usb_2_0_ext_cap->bmAttributes);
}

static void print_ss_usb_cap(struct libusb_ss_usb_device_capability_descriptor *ss_usb_cap)
{
	printf("    USB 3.0 Capabilities:\n");
	printf("      bDevCapabilityType: %d\n", ss_usb_cap->bDevCapabilityType);
	printf("      bmAttributes:       0x%x\n", ss_usb_cap->bmAttributes);
	printf("      wSpeedSupported:    0x%x\n", ss_usb_cap->wSpeedSupported);
	printf("      bFunctionalitySupport: %d\n", ss_usb_cap->bFunctionalitySupport);
	printf("      bU1devExitLat:      %d\n", ss_usb_cap->bU1DevExitLat);
	printf("      bU2devExitLat:      %d\n", ss_usb_cap->bU2DevExitLat);
}

static void print_bos(libusb_device_handle *handle)
{
	struct libusb_bos_descriptor *bos;
	int ret;

	ret = libusb_get_bos_descriptor(handle, &bos);
	if (0 > ret) {
		return;
	}

	printf("  Binary Object Store (BOS):\n");
	printf("    wTotalLength:       %d\n", bos->wTotalLength);
	printf("    bNumDeviceCaps:     %d\n", bos->bNumDeviceCaps);

	if(bos->dev_capability[0]->bDevCapabilityType == LIBUSB_BT_USB_2_0_EXTENSION) {

		struct libusb_usb_2_0_extension_descriptor *usb_2_0_extension;
	        ret =  libusb_get_usb_2_0_extension_descriptor(NULL, bos->dev_capability[0],&usb_2_0_extension);
	        if (0 > ret) {
		        return;
	        }

                print_2_0_ext_cap(usb_2_0_extension);
                libusb_free_usb_2_0_extension_descriptor(usb_2_0_extension);
        }

	if(bos->dev_capability[0]->bDevCapabilityType == LIBUSB_BT_SS_USB_DEVICE_CAPABILITY) {

	        struct libusb_ss_usb_device_capability_descriptor *dev_cap;
		ret = libusb_get_ss_usb_device_capability_descriptor(NULL, bos->dev_capability[0],&dev_cap);
	        if (0 > ret) {
		        return;
	        }

	        print_ss_usb_cap(dev_cap);
	        libusb_free_ss_usb_device_capability_descriptor(dev_cap);
        }

	libusb_free_bos_descriptor(bos);
}

static void print_interface(const struct libusb_interface *interface)
{
	int i;

	for (i = 0; i < interface->num_altsetting; i++)
		print_altsetting(&interface->altsetting[i]);
}

static void print_configuration(struct libusb_config_descriptor *config)
{
	uint8_t i;

	printf("  Configuration:\n");
	printf("    wTotalLength:         %d\n", config->wTotalLength);
	printf("    bNumInterfaces:       %d\n", config->bNumInterfaces);
	printf("    bConfigurationValue:  %d\n", config->bConfigurationValue);
	printf("    iConfiguration:       %d\n", config->iConfiguration);
	printf("    bmAttributes:         %02xh\n", config->bmAttributes);
	printf("    MaxPower:             %d\n", config->MaxPower);

	for (i = 0; i < config->bNumInterfaces; i++)
		print_interface(&config->interface[i]);
}

static int print_device(libusb_device *dev, int level)
{
	struct libusb_device_descriptor desc;
	libusb_device_handle *handle = NULL;
	char description[256];
	char string[256];
	int ret;
	uint8_t i;

	ret = libusb_get_device_descriptor(dev, &desc);
	if (ret < 0) {
		fprintf(stderr, "failed to get device descriptor");
		return -1;
	}

	ret = libusb_open(dev, &handle);
	if (LIBUSB_SUCCESS == ret) {
		if (desc.iManufacturer) {
			ret = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, string, sizeof(string));
			if (ret > 0)
				snprintf(description, sizeof(description), "%s - ", string);
			else
				snprintf(description, sizeof(description), "%04X - ",
				desc.idVendor);
		}
		else
			snprintf(description, sizeof(description), "%04X - ",
			desc.idVendor);

		if (desc.iProduct) {
			ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
			if (ret > 0)
				snprintf(description + strlen(description), sizeof(description) -
				strlen(description), "%s", string);
			else
				snprintf(description + strlen(description), sizeof(description) -
				strlen(description), "%04X", desc.idProduct);
		}
		else
			snprintf(description + strlen(description), sizeof(description) -
			strlen(description), "%04X", desc.idProduct);
	}
	else {
		snprintf(description, sizeof(description), "%04X - %04X",
			desc.idVendor, desc.idProduct);
	}

	printf("%.*sDev (bus %d, device %d): %s\n", level * 2, "                    ",
		libusb_get_bus_number(dev), libusb_get_device_address(dev), description);

	if (handle && verbose) {
		if (desc.iSerialNumber) {
			ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
			if (ret > 0)
				printf("%.*s  - Serial Number: %s\n", level * 2,
				"                    ", string);
		}
	}

	if (verbose) {
		for (i = 0; i < desc.bNumConfigurations; i++) {
			struct libusb_config_descriptor *config;
			ret = libusb_get_config_descriptor(dev, i, &config);
			if (LIBUSB_SUCCESS != ret) {
				printf("  Couldn't retrieve descriptors\n");
				continue;
			}

			print_configuration(config);

			libusb_free_config_descriptor(config);
		}

		if (handle && desc.bcdUSB >= 0x0201) {
			print_bos(handle);
		}
	}

	if (handle)
		libusb_close(handle);

	return 0;
}
#endif
#if 0
bool USBBulkWriteData(int DevIndex,int pipenum,unsigned char *sendbuffer,int len,int waittime)
{
	int ret=0;
//	printf("Enter: USBBulkWriteData, dev index: %d\n", DevIndex);
#if 1 // m.z
	// usb_list->handle[i]
	//pGinkgoBoardHandle = (libusb_device_handle *)usb_list_post_by_dev_index(DevIndex)->handle[0];
#endif

/*	if(pGinkgoBoardHandle == NULL){
		return false;
	}
	*/
#ifdef TEST_SET_CONFIGURATION
    if (usb_set_configuration(pGinkgoBoardHandle[nBoardID], MY_CONFIG) < 0)
    {
        usb_close(pGinkgoBoardHandle[nBoardID]);
        return SEVERITY_ERROR;
    }
#endif

#ifdef TEST_CLAIM_INTERFACE 
    //if (usb_claim_interface(pGinkgoBoardHandle, 0) < 0)
	if (libusb_claim_interface(pGinkgoBoardHandle, 0) < 0)
    {
        libusb_close(pGinkgoBoardHandle);
        return false;
    }
#endif

#if TEST_ASYNC
    // Running an async write test
    ret = transfer_bulk_async(dev, pipenum, sendbuffer, len, waittime);
#else
	
	// ret = usb_bulk_write(pGinkgoBoardHandle, pipenum, sendbuffer, len, waittime);
	int actual_length;
	ret = libusb_bulk_transfer(device_handle, pipenum, sendbuffer, len, &actual_length, waittime);
	if((len%64) == 0){
		libusb_bulk_transfer(device_handle, pipenum, sendbuffer, 0, &actual_length, waittime);
	}
#endif
#ifdef TEST_CLAIM_INTERFACE
    libusb_release_interface(pGinkgoBoardHandle, 0);
#endif
   
	return ret==len;
}

int USBBulkReadData(int DevIndex,unsigned char pipenum,unsigned char *readbuffer, int len, unsigned int waittime)
{
	int ret=0;
//	printf("Enter: USBBulkReadData, dev index: %d, pipenum: %d\n", DevIndex, pipenum);

#if 1 // m.z
	//pGinkgoBoardHandle = (libusb_device_handle *)usb_list_post_by_dev_index(DevIndex)->handle[0];
#endif

	//if(pGinkgoBoardHandle == NULL)
	{
	//	return 0;
	}
#ifdef TEST_SET_CONFIGURATION
    if (usb_set_configuration(pGinkgoBoardHandle[DevIndex], MY_CONFIG) < 0)
    {
        usb_close(pGinkgoBoardHandle[DevIndex]);
        return SEVERITY_ERROR;
    }
#endif

#ifdef TEST_CLAIM_INTERFACE
    if (libusb_claim_interface(pGinkgoBoardHandle, 0) < 0)
    {
        libusb_close(pGinkgoBoardHandle);
        return 0;
    }
#endif

#if TEST_ASYNC
    // Running an async read test
    ret = transfer_bulk_async(pGinkgoBoardHandle[DevIndex], pipenum, sendbuffer, len, waittime);
#else

	//read from device buffer to data1    
	// r = libusb_bulk_transfer(hDevice,0x82,data1,512,&len,0); 
	ret = libusb_bulk_transfer(device_handle, pipenum, readbuffer,len,&len,waittime);    
	// ret = usb_bulk_read(pGinkgoBoardHandle, pipenum, readbuffer, len, waittime);
//	printf("libusb_bulk_transfer - read = %d\n",ret);
#endif

#ifdef TEST_CLAIM_INTERFACE
    libusb_release_interface(pGinkgoBoardHandle, 0);
#endif

    return ret;
}
#endif 
#if 0
uint8_t USB_SendMsg(int32_t dev, S_MSG *msg)
{
    int32_t ret=0;
    int32_t i;
	int actual_length;
    uint8_t sBuf[USB_SEND_BUFFER_SIZE] = {0};
    register uint8_t *s = sBuf;
    uint8_t *x = (uint8_t *)msg->lParam;
    *s++ = msg->message >> 24;
    *s++ = msg->message >> 16;
    *s++ = msg->message >> 8;
    *s++ = msg->message >> 0;
	*s++ = msg->PackNum;
	*s++ = (msg->size>>8)&0xFF;
	*s++ = (msg->size>>0)&0xFF;
    if(msg->size)
    {
        for(i=0; (i<msg->size)&&(i<(sizeof(sBuf)-7)); i++)
        {
            *s++ = x[i];
        }
    }
//	ret = USBBulkWriteData(dev,EP1_OUT,(unsigned char *)sBuf,msg->size+7,5000);
	//if (ret != msg->size+7) // m.z
	if(!ret)  
	{
		return 1;
	}

	if(((msg->size+7)%64)==0){
		ret = libusb_bulk_transfer(device_handle, EP1_OUT, tx_buffer, 64, &actual_length, 500);
	}
    return 0;
}

uint8_t USB_GetMsg(int32_t dev, S_MSG *msg)
{
    uint8_t rBuf[USB_EP_SIZE];
	uint8_t *getDataBuff;
    int32_t ret;
    register uint32_t i;
    uint8_t *x=(uint8_t *)msg->lParam;
    uint32_t len;

	getDataBuff = rBuf;
	memset(rBuf, 0, USB_EP_SIZE);
	//ret = USBBulkReadData(dev,EP1_IN,(unsigned char *)rBuf,USB_EP_SIZE,5000);	//Receive R01
	if (ret != USB_EP_SIZE){
		msg->message = MSG_VT_EMPTY;
		return 1;
	}

    // retrieve message
    msg->message = *(getDataBuff+0) << 24 | *(getDataBuff+1) << 16 | *(getDataBuff+2) << 8 | *(getDataBuff+3);
    msg->status = (MSG_STATE)(*(getDataBuff+4));
    msg->size = *(getDataBuff+5)<<8 |*(getDataBuff+6);
    len = msg->size;
    if(len)
    {
        for(i=0; (i<len)&&(i<USB_EP_SIZE); i++)
        { 
            *(x+i) = *(getDataBuff+7+i);
        }
    }

    return 0;
}

uint8_t USB_GetMsgWithSize(int32_t dev, S_MSG *msg)
{
    uint8_t rBuf[USB_EP_SIZE];
	uint8_t *getDataBuff;
    register uint32_t i;
    uint8_t *x=(uint8_t *)msg->lParam;
    uint32_t len;
    int32_t ret;

	getDataBuff = rBuf;
	memset(rBuf, 0, USB_EP_SIZE);
//	ret = USBBulkReadData(dev,EP1_IN,(unsigned char *)rBuf,msg->size + 7,1000);	//Receive R01
	if (ret != (msg->size + 7)){
		msg->message = MSG_VT_EMPTY;
		return 1;
	}

    // retrieve message
    msg->message = *(getDataBuff+0) << 24 | *(getDataBuff+1) << 16 | *(getDataBuff+2) << 8 | *(getDataBuff+3);
    msg->status = (MSG_STATE)(*(getDataBuff+4));
    msg->size = *(getDataBuff+5)<<8 |*(getDataBuff+6);
    len = msg->size;
    if(len)
    {
        for(i=0; (i<len)&&(i<USB_EP_SIZE); i++)
        {
            *(x+i) = *(getDataBuff+7+i);
        }
    }
    return 0;
}


uint8_t USB_GetMsgEx(int32_t dev, S_MSG *msg)
{
    uint8_t rBuf[USB_SEND_BUFFER_SIZE];
	uint8_t *getDataBuff;
    int32_t ret;
    memset(rBuf, 0, USB_SEND_BUFFER_SIZE);
//	ret = USBBulkReadData(dev,EP1_IN,(unsigned char *)rBuf,7,1000); 
	if (ret != 7){
		msg->message = MSG_VT_EMPTY;
		return 1;
	}else{
		getDataBuff = rBuf;
		// retrieve message
		msg->message = *(getDataBuff+0) << 24 | *(getDataBuff+1) << 16 | *(getDataBuff+2) << 8 | *(getDataBuff+3);
		msg->status = (MSG_STATE)(*(getDataBuff+4));
		msg->size = *(getDataBuff+5)<<8 |*(getDataBuff+6);
	}
	if(msg->size < 0){
		return 1;
	}
	if(msg->size == 0){
		return 0;
	}
//	ret = USBBulkReadData(dev,EP1_IN,(unsigned char *)rBuf,msg->size,1000);	//Receive R01
	if (ret != msg->size){
		msg->message = MSG_VT_EMPTY;
		return 1;
	}else{
		uint8_t *x=(uint8_t *)msg->lParam;
		register uint32_t i;
		uint32_t len = msg->size;
		if(len){
			for(i=0; i<len; i++){ 
				*(x+i) = *(rBuf+i);
			}
		}
		return 0;
	}
}




int main1(int argc, char *argv[])
{
	libusb_device *dev;
	int usb_dev_index; 
	ssize_t cnt;
	int r, i,j;
	int status;
	int ret;
	int actual_length;

	if (argc > 1 && !strcmp(argv[1], "-v"))
		verbose = 1;

	r = libusb_init(NULL);
	if (r < 0)
		return r;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int)cnt;

	usb_dev_index = 0;
	vt_dev_num = 0;
    while ((dev = devs[usb_dev_index]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if((desc.idVendor == USB_VID)&&(desc.idProduct == USB_PID)){
			vt_dev_index[vt_dev_num++] = usb_dev_index; 
		}
		usb_dev_index++;
	}
	for(i=0; i<vt_dev_num; i++)
	{
		status = libusb_open(devs[vt_dev_index[0]], &device_handle);
	}

	memset(tx_buffer, 0, 512);
	for(i=0; i<16; i++)
	{ 
		tx_buffer[i] = i; 
	}
	ret = libusb_bulk_transfer(device_handle, EP1_OUT, tx_buffer, 16, &actual_length, 500);

    ret = libusb_bulk_transfer(device_handle, (EP1_IN | LIBUSB_ENDPOINT_IN), rx_buffer, 64, &actual_length, 500);

	/*
    if (libusb_set_configuration(pGinkgoBoardHandle[DevIndex], MY_CONFIG) < 0)
    {
        libusb_close(pGinkgoBoardHandle[DevIndex]);
        return SEVERITY_ERROR;
    }
    if (libusb_claim_interface(pGinkgoBoardHandle, 0) < 0)
    {
        libusb_close(pGinkgoBoardHandle);
        return 0;
    }
	*/

	for (i = 0; devs[i]; ++i) {
		print_device(devs[i], 0);
	}

	libusb_free_device_list(devs, 1);

	libusb_exit(NULL);
	return 0;
}
#endif

/*
 * Read a packet
 */
static int usb_read(struct libusb_device_handle *dev_handle,
	unsigned char endpoint, unsigned char *data, int length, int *transferred,
	unsigned int timeout)
{
	int nread=0,ret=0;
	ret = libusb_bulk_transfer(dev_handle, endpoint, data, length,
			transferred, timeout);
	if (ret){
		printf("ERROR in bulk read: %d\n", ret);
		return -1;
    }
	else{
		//printf("%d receive %d bytes from device: %s\n", ++counter, nread, receiveBuf);
//		printf("%s", 0);  //Use this for benchmarking purposes
		return 0;
    }
}


/*
 * write a few bytes to the device
 *
 */
uint16_t count=0;
static int usb_write(struct libusb_device_handle *dev_handle,
	unsigned char endpoint, unsigned char *data, int length, int *transferred,
	unsigned int timeout)
{
	int n = 0, ret = 0;
    //count up
    //write transfer
    //probably unsafe to use n twice...
	ret = libusb_bulk_transfer(dev_handle, EP1_OUT, data, length,
			transferred, timeout);
    //Error handling
#if 0
    switch(ret){
        case 0:
            printf("send %d bytes to device\n", n);
        case LIBUSB_ERROR_TIMEOUT:
            printf("ERROR in bulk write: %d Timeout\n", ret);
            break;
        case LIBUSB_ERROR_PIPE:
            printf("ERROR in bulk write: %d Pipe\n", ret);
            break;
        case LIBUSB_ERROR_OVERFLOW:
            printf("ERROR in bulk write: %d Overflow\n", ret);
            break;
        case LIBUSB_ERROR_NO_DEVICE:
            printf("ERROR in bulk write: %d No Device\n", ret);
            break;
        default:
            printf("ERROR in bulk write: %d\n", ret);
            break;

    }
#endif
    return -1;

}
#if 0
/*
 * on SIGINT: close USB interface
 * This still leads to a segfault on my system...
 */
static void sighandler(int signum)
{
    printf( "\nInterrupt signal received\n" );
	if (handle){
        libusb_release_interface (handle, 0);
        printf( "\nInterrupt signal received1\n" );
        libusb_close(handle);
        printf( "\nInterrupt signal received2\n" );
	}
	printf( "\nInterrupt signal received3\n" );
	libusb_exit(NULL);
	printf( "\nInterrupt signal received4\n" );

	exit(0);
}
#endif 
#if 0
int main(int argc, char*argv[])
{
    //Pass Interrupt Signal to our handler
//	signal(SIGINT, sighandler);
	int i = 0;
	int n = 0;
	int r = 1;
	int ret = 0;
	int actual_length = 0;
	int nread = 0;
	int count = 0;

	libusb_init(&ctx);

    //Open Device with VendorID and ProductID
	handle = libusb_open_device_with_vid_pid(ctx,
				USB_VID, USB_PID);
	if (!handle) {
		perror("device not found");
		return 1;
	}

	//Claim Interface 0 from the device
    r = libusb_claim_interface(handle, 0);
	if (r < 0) {
		fprintf(stderr, "usb_claim_interface error %d\n", r);
		return 2;
	}

	printf("Interface claimed\n");
	while (1)
	{
		count++;	
		if (count % 10 == 0)
		{
			ret = usb_read(handle, EP1_IN, receiveBuf, n, &nread, USB_TIMEOUT);
		}	
		Sleep(1);
		if(count % 1 == 0)
		{
			ret = usb_write(handle, EP1_OUT, tx_buffer, n, &actual_length, 500); 
		}
	//	printf("received: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, ", receiveBuf[0], receiveBuf[1], receiveBuf[2], receiveBuf[3], receiveBuf[4], receiveBuf[5], receiveBuf[6] );
    }
    //never reached
	libusb_close(handle);
	libusb_exit(NULL);

	return 0;
}
#endif
static libusb_context *ctx = NULL;
static libusb_device_handle *hanSdle;
libusb_device **devs;
int8_t VTUSB_ScanDevice(void)
{
	if (usb_init_flag) {
		libusb_get_device_list(ctx,&devs);
		usb_init_flag = 0;
	}
	return 0;
}

int8_t VTUSB_OpenDevice(int DevIndex)
{
	return 0;
}
int8_t VTUSB_CloseDevice(int DevIndex)
{
	return 0;
}
