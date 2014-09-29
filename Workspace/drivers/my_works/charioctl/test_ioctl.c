#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */
#include"cioctl.h"
#define DEVICE "/dev/megharajchard"

int main()
{
	int file_desc, ret_val;
	char *message;// = "My name is megharaj i am the owner of this device\n";
	char *answer;
	file_desc = open(DEVICE, O_RDWR);
	if(file_desc < 0)
		printf("failed to open the device \n");
	
	/*ret_val = ioctl(file_desc, IOCTL_WRITE, message);
	if(ret_val < 0)
		printf("failed to write the device \n");*/
	ret_val = ioctl(file_desc, IOCTL_READ,message);
	if(ret_val < 0)
		printf("failed to read the device \n");
		printf("message read is %s  \n",message);
	ret_val = ioctl(file_desc, IOCTL_HELLO); /* only this command works*/
	close(file_desc);
	return 0;
}
		
