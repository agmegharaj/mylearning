/* include the header files as necessary*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <android/log.h>
#include <pthread.h>

/* defining macro's goes here*/
#define LOGTAG "UsbModemNative"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOGTAG, __VA_ARGS__))
#define CONFIG_PATH "/sdcard/pppWidget/"
#define DEBUG 1

/* declaration of global variables goes here*/
int connection_state;

/* to make sure after modswitch connection stays untill device is removed */
void stay_connected()
{
	int status=0;
	if(DEBUG) LOGI("%s the connection_state is %d \n",__func__, connection_state);
	while(connection_state == 1) {
			sleep(60); /* checks the connection every minute, if broken reconnects*/
			status=system("ifconfig ppp0");
			if(status != 0) {
				if(DEBUG) LOGI("Connection has been terminated due to some reason will re-connect\n");
				system("/system/bin/pppd call gprs &");		
			}
	}
	return NULL;
}

/* usb modswitch will be performed and connection will be performed */
int perform_modswitch(int *vendor_id, int *product_id)
{
	pthread_t thread;
	char command[100];
	sprintf(command,"/system/bin/usb_modeswitch -W -v %x -p %x -c %s%x.%x", (int) *vendor_id, (int) *product_id, CONFIG_PATH, (int) *vendor_id, (int) *product_id );
	if(DEBUG) LOGI("the command given is %s\n",command);
	if(DEBUG) LOGI("the required device found usb_modswitch will be performed\n");
 	system(command);
	connection_state=1;
	sleep(10);
	if(DEBUG) LOGI("Modswitch is performed establishing the connection\n");
	system("/system/bin/pppd call gprs &");
	sleep(15);
	pthread_create(&thread, NULL, stay_connected, NULL);
	return 0;
}
		
/* checks for the new added devices and performs action according to that*/
static int mdevice_added(const char *dev, void *client_data)
{
	struct usb_device *usbdevice = NULL;
	char filename[50],*dev_name;
	int vendor_id=0,product_id=0,i=0;
	dev_name=dev;
	connection_state=0;
	if(DEBUG) LOGI("%s: DEVICE %s \n", __func__,dev_name);
	usbdevice = usb_device_open(dev_name);
	vendor_id = usb_device_get_vendor_id(usbdevice);
	product_id = usb_device_get_product_id(usbdevice);
	if(DEBUG) LOGI("vendor_id: %x product_id: %x\n",(int) vendor_id, (int) product_id);
	/* now to check wheather the file exist or not */
	sprintf(filename,"%s%x.%x",CONFIG_PATH, (int) vendor_id, (int) product_id);
	if( access( filename, F_OK ) != -1 ) {
		perform_modswitch(&vendor_id,&product_id);	
	} 
	else {
		if(DEBUG) LOGI("the configuration for this product and vendor id is not supported yet contact the manufacturer\n");
	}	
	return 0;
}

/* checks if the attached device is removed*/
static int mdevice_removed(const char *dev, void *client_data)
{
	if(DEBUG) LOGI("%s: DEVICE %s \n", __func__,dev);
	return 0;
}

/* notifies the discovery of new device*/
static int mdiscovery_done(void *client_data)
{
	if(DEBUG) LOGI("%s: DEVICE\n", __func__);
	return 0;
}

/* this is the main function*/
int main()
{
	struct usb_host_context *ctx;
	ctx = usb_host_init();
	if (!ctx) {
		LOGI("%s:USB host init error\n",__func__);
		return 1;
	}
	while(1) {
		usb_host_run(ctx,mdevice_added,mdevice_removed,mdiscovery_done,NULL);
	}
	return 0;
}
