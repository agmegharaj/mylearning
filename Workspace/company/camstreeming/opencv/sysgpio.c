#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include <pthread.h>
#include<fcntl.h>

#define FILE_NEEDED "/sys/class/gpio/gpio2/value"

void check_gpio_interface()
{
	if( access(FILE_NEEDED, F_OK ) != -1 ) {
		printf("interface is present,will open and read the file\n");
	}
	else {
		printf("GPIO interface no created login as root and creat the interface and then try\n");
		exit(0);
	}
}

void streem_video()
{
	system("ffmpeg -v verbose -f video4linux2 -s 320x240 -r 25 -i /dev/video0 -f mpegts udp://10.203.100.83:5004 &");
}

int main()
{
	int fd,pid,status;
	char read_value,line[10],command[100];
	FILE *fp;
	pthread_t thread;
	check_gpio_interface();
	
	if(fd = open(FILE_NEEDED,O_RDONLY) < 0) {
		printf("error opening the file\n");
		exit(0);
	}
	else 
		printf("file has been opened successfully\n");

	while(1) {
		if(!read(fd,&read_value,1))
			printf("Failed to read the file\n");
		if(read_value == '0') {
			printf("Activity has been detected, will streem the video\n");
			pthread_create(&thread, NULL, streem_video, NULL);
		}
		else if(read_value == '1') {
			printf("No activity video streeming will be closed\n");
			fp = popen("pidof ffmpeg", "r");
			fgets(line, 100, fp);
			pid = atoi(line);
			printf("pid = %d\n",pid);
			sprintf(command,"kill %d",pid);
			status = system(command);
			pclose(fp);
		}
	}
	close(fd);
}
