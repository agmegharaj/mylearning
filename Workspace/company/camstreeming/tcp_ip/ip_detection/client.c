/*
    C ECHO client running on pandaboard
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>


#define CHECK_STRING_IP "inet addr:"
#define CHECK_STRING_MAC "HWaddr "

void get_my_ip(char *ip_mac_address)
{
	FILE *fp,*output;
	char *start=NULL; 
	char *end=NULL;
	char line[100];
	output=fopen("my_ip_address.txt", "w");
	if(output == NULL) {
		printf("error creating outputfile\n");
		return -1; 
	}

	printf("program to self querry the ip address\n");	
	fp = popen("ifconfig eth0", "r");
	fgets(line, 100, fp);
	start=strstr(line, CHECK_STRING_MAC);
	start = start + 7;
	fwrite(start, 1, 17, output); start = NULL;
	fgets(line, 100, fp);
	start=strstr(line, CHECK_STRING_IP);
	start = start + 10;
	fwrite(start, 1, 14, output);
	fclose(output);	
	pclose(fp);
	if( access("my_ip_address.txt", F_OK ) != -1 ) {
		printf("found file having ip address\n");
		output=fopen("my_ip_address.txt", "r");
		fgets(ip_mac_address, 32, output);
	}
	else
		printf("unabe to find file with ip address\n");
	fclose(output);
	printf("my ip and mac address adress is %s \n",ip_mac_address);
	
}

int connect_server(struct sockaddr_in server,char *read,int *decide)
{
	int sock,i,read_size = 0;
	char message[32];
	char *server_replay;
	server_replay = (char *)malloc(5 * sizeof(char));
	//Create socket
	strcpy(message,read);
	printf("ip to send is %s \n",message);
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");
	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        	perror("connect failed. Error");
		return 1;
	}
     
	puts("Connected\n");
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0) {
            	puts("Send failed");
	}
        if( read_size = recv(sock , server_replay , 5 , 0) < 0) {
            	puts("receive failed failed");
	}
	//printf("read size = %d",read_size);
	printf("data received from server is %s\n",server_replay);
	fflush(stdout);
	i = strcmp(server_replay,"SLEEP");
	printf(" i = %d\n",i);
	if ( i == 0)
		*decide = 100;
	close(sock);
	free(server_replay);
	return 0;
} 
 
int main(int argc , char *argv[])
{
	struct sockaddr_in server;
	int decide = 0;
	char send_ip_mac[32],*char_return;
	server.sin_addr.s_addr = inet_addr("10.203.100.84");
	server.sin_family = AF_INET;
	server.sin_port = htons( 5006 );

	get_my_ip(send_ip_mac);
	printf("my ip address is, i am at the main %s\n",send_ip_mac);
	//keep communicating with server
	while(1) {
		sleep(5);
		connect_server(server,send_ip_mac,&decide);
		printf("value of decide is %d\n",decide);
		if(decide == 100)
			break;
	}
	return 0;
}
