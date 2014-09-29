/*
    C socket server running on raspberry pi
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

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
	char line[10];
	int pid = 0;
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
     
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("10.203.100.85");
	server.sin_port = htons( 5005 );
     
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
			if(strcmp(client_message,"1-on") == 0) {
				printf("start audio streeaming\n");
				pthread_create(&thread, NULL, streem_audio, NULL);
			
			}

			else if (strcmp(client_message,"1-off") == 0) {
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
