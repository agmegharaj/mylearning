/*
    C socket server running on raspberry pi
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <stdlib.h>

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
 
int main(int argc , char *argv[])
{
	FILE *fp;
	char line[10],got_ip[32],server_ip[14];
	int pid = 0,i=0;
	char command[100];
	int socket_desc , client_sock , c , read_size, status = 0;
	struct sockaddr_in server , client;
	char client_message[32];
	char *client_replay;
	client_replay = (char *)malloc(5 * sizeof(char));
	client_replay = "SLEEP";
     
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
		for(i=0; i<32;i++)
     		client_message[i] = '\0';
		//Receive a message from client
		while( (read_size = recv(client_sock , client_message , 32 , 0)) > 0 )
		{
			//if(!strncmp(client_message, VALID_STRING, COMPARELIMIT)) {
				//strcpy(got_ip,client_message);
				printf("the received ip of client is %s valid\n",client_message);
			//}
			if( sendto(client_sock , client_replay , strlen(client_replay) , 0,(struct sockaddr *)&client,c) < 0) {
            			puts("Send failed");
			}
			printf("data sent is %s\n",client_replay);	
    		}
		
		close(client_sock);
     	}
	free(client_replay);
     
	return 0;
}
