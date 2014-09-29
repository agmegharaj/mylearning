/*
    C ECHO client running on pandaboard
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr

#define NOFS1
#define NOFS2
#define NOFS3
#define NOFS4

void connect_server(struct sockaddr_in server,char *read)
{
	int sock,i;
	char message[10];
	//Create socket
	strcpy(message,read);
	printf("message %s received\n",message);
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
	printf("message %s sent succesfully\n",message);
	close(sock);
} 
 
int main(int argc , char *argv[])
{
	struct sockaddr_in server1,server2,server3,server4;
	char message[10];
#ifdef NOFS1
	server1.sin_addr.s_addr = inet_addr("10.203.100.93");
	server1.sin_family = AF_INET;
	server1.sin_port = htons( 5005 );
#endif
#ifdef NOFS2
	server2.sin_addr.s_addr = inet_addr("10.203.100.93");
	server2.sin_family = AF_INET;
	server2.sin_port = htons( 5006 );
#endif
#ifdef NOFS3
	server3.sin_addr.s_addr = inet_addr("10.203.100.93");
	server3.sin_family = AF_INET;
	server3.sin_port = htons( 5007 );
#endif
#ifdef NOFS4
	server4.sin_addr.s_addr = inet_addr("10.203.100.93");
	server4.sin_family = AF_INET;
	server4.sin_port = htons( 5008 );
#endif

	//keep communicating with server
	while(1) {
		printf("Enter message : ");
        	scanf("%s" , message);
#ifdef NOFS1         	
		if((strcmp(message,"1-on") == 0) || (strcmp(message,"1-off") == 0))  {
		connect_server(server1,message);
		}
#endif
#ifdef NOFS2 
		if((strcmp(message,"2-on") == 0) || (strcmp(message,"2-off") == 0))  {
		connect_server(server2,message);
		}
#endif
#ifdef NOFS3 
		if((strcmp(message,"3-on") == 0) || (strcmp(message,"3-off") == 0))  {
		connect_server(server3,message);
		}
#endif
#ifdef NOFS4
		if((strcmp(message,"4-on") == 0) || (strcmp(message,"4-off") == 0))  {
		connect_server(server4,message);
		}
#endif
	}
	return 0;
}
