#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <fcntl.h>

#define DEVICE "/dev/megharajchard"

int debug;

int main()
{
	int value = 0,ret = 0;
	char *data, *command;
	if(access(DEVICE, F_OK) == -1) {
		printf("module %s not loaded\n",DEVICE);
		return 0;
	}
	else
		printf("module %s loaded, will be used\n",DEVICE);
	data = (char *)malloc(1024 * sizeof(char));
	command = (char *)malloc(100 * sizeof(char));
	printf("please enter 1 to write and 2 to read\n");
	scanf("%d",&value);
	switch(value) {
	case 1 :printf("write option selected\n");
		printf("please enter the data to write into device\n");
		scanf(" %[^\n]",data); /* a space added after"so that it reads white space, %[^\n] is addeed so that it takes input until new line*/
		if(debug)printf("data : %s\n",data);
		sprintf(command,"echo %s > /dev/megharajchard",data);
		if(debug)printf("command : %s\n",command);
		if(debug)fflush(stdout);
		ret = system(command);
		if(ret == 0)
			printf("write succesful\n");
		break;
	case 2 :printf("read option selected\n"); 	
		command[0] = '\0';
		sprintf(command,"cat /dev/megharajchard");
		ret = system(command);
		if(ret == 0)
			printf("read succesful\n");	
		break;
	}
	return 0;
	free(data);
	free(command);
}
