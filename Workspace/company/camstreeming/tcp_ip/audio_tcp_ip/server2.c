/*
    C socket server running on raspberry pi
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#define CHECK_STRING_IP "inet addr:"
#define VALID_STRING "00:24:1d:5b."
#define COMPARELIMIT 11

void get_server_ip(char *server_ip)
{
	FILE *fp,*output;
	char *start=NULL; 
	char line[100]; int i;
	printf("program to self querry the ip address\n");	
	fp = popen("ifconfig eth0", "r");
	fgets(line, 100, fp);
	fgets(line, 100, fp);
	start=strstr(line, CHECK_STRING_IP);
	start = start + 10;
	for(i=0;i<13;i++) {
		server_ip[i] = *start;
		start++;
	}
	server_ip[13] = '\0';
	pclose(fp);
	printf("the local ip needed to set up server is %s \n",server_ip);

}


void streem_audio()
{
	int status=0;
	status = system("ffmpeg -f alsa -i plughw:0 -ar 44100 -f mpegts udp://10.203.100.85:7006");
	//status = system("top");
	//return NULL;
}

 
int main(int argc , char *argv[])
{
	FILE *fp;
	char line[10],server_ip[14];
	int pid = 0, i;
	char command[100];
	int socket_desc , client_sock , c , read_size, status = 0;
	struct sockaddr_in server , client;
	char client_message[10];
     
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");
	for (i = 0; i <14;i++)
		server_ip[i] = '\0';
     	get_server_ip(server_ip);
	printf("the local ip needed to set up server is %s \n",server_ip);
	fflush(stdout);
     
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_port = htons( 5006 );
     
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)	{
	//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
     
	//Listen
	listen(socket_desc , 3);
     
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
     
	//accept connection from an incoming client
	while(1) {
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0) {
        		perror("accept failed");
        		return 1;
		}
		puts("Connection accepted");
		int i = 0;
		for(i=0; i<10;i++)
     		client_message[i] = '\0';
		//Receive a message from client
		while( (read_size = recv(client_sock , client_message , 10 , 0)) > 0 )
		{
			printf("in loop message received %s\n",client_message);
			pthread_t thread;
			if(strcmp(client_message,"2-on") == 0) {
				printf("start audio streeaming\n");
				pthread_create(&thread, NULL, streem_audio, NULL);
			
			}

			else if (strcmp(client_message,"2-off") == 0) {
				printf("start audio streeaming will be turned of\n");
				fp = popen("pidof ffmpeg", "r");
				fgets(line, 100, fp);
				pid = atoi(line);
				printf("pid = %d\n",pid);
				sprintf(command,"kill %d",pid);
				status = system(command);
				pclose(fp);
			}
		
    		}
		close(client_sock);
     	}
     
	return 0;
}
