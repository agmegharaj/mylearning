#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */
#include <stdlib.h>
#include<assert.h>
#include <pthread.h>
#include "SDL.h" 




FILE *myfilenew;
#define PACKET_SIZE_IN_BYTES 30732
#define RTP_HEADER_SIZE 12
#define FRAME_SIZE 614400
#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240
#define FRAME_PITCH 2
#define PACKET_COUNT 5

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
SDL_Overlay *overlay;
SDL_Surface *screen, *srcbmp; 
SDL_Event sdlevent; 
SDL_Rect rect;
SDL_Event event;

typedef struct
{	
	unsigned short first_field;		//8bit
	unsigned short sequence_number;  		//16bit
	unsigned int timestamp; 		//32bit
	int ssrc;				//32 bit
	//int csrc; 				//32 bit //Ignored
}header;


struct sockaddr_in server;
struct sockaddr_in from;
int sock, length;
socklen_t fromlen;
char *framebuff;
char *packetbuff;

/*void create_rtp_receiver()
{
	//printf("\n********** create RTP receiver **********\n");
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		error("Opening socket");
	}
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));
	if (bind(sock,(struct sockaddr *)&server,length)<0)
	{
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);

	//printf("\n********** succesfully created RTP receiver **********\n");

}*/


void *rtp_receive_packets()
{
	int ret=0;
	header rtp;
#ifdef DEBUG_TOF_RECEIVER
	static int packetrcvCounter=0;
#endif
	//printf("\n********** Call recvfrom **********\n");
	while(1)
	{
		//printf("\n Received %d bytes of data from Socket\n",ret);
		/* Get an empty buffer, fill the data in it and pass to process module */
		/* rcv tof packets sent from ipnc;blocking call	*/
		ret = recvfrom(sock,packetbuff,PACKET_SIZE_IN_BYTES,0,(struct sockaddr *)&from,&fromlen);
		if (ret < 0)
		{
			error("recvfrom");
			exit(0);
		}	
		//memcpy(&rtp,packetbuff,RTP_HEADER_SIZE);
		//printf("tsms=%d\n",rtp.timestamp);

		pthread_mutex_lock( &count_mutex );
		pthread_cond_signal( &condition_var );
		pthread_mutex_unlock( &count_mutex );

		/*update the received packet size*/
		//BufIn->packetSize=ret;
	//printf("\n Received %d bytes of data from Socket \n",ret);
	}

}

/* Process  */
void *process_rtp_packets()
{
	int quit;
	header rtp;
	static unsigned short prevSeqNo=0;
	static unsigned int prevTimeStamp=0;
	static int PacketCount=0,isFirstFrame=1;
	
	//printf("\n********** Inside Process packet **********\n");
	//return NULL;
	while(1)
	{
		pthread_mutex_lock( &count_mutex );
		pthread_cond_wait( &condition_var, &count_mutex );
		pthread_mutex_unlock( &count_mutex );

		/* Copy Header to local struct */
		memcpy(&rtp,packetbuff,RTP_HEADER_SIZE);
		if(isFirstFrame==1)	
		{
			prevSeqNo=rtp.sequence_number;
			prevTimeStamp=rtp.timestamp;
			PacketCount=0;
			isFirstFrame=0;
		//printf("\n********** processing First(1st) packet of FirstFrame**********\n");
		}
		if(prevTimeStamp==rtp.timestamp && PacketCount<20)
		{
			if(PacketCount==0)
			{
				/*Get a Empty buffer from out Queue, call this only once in 3 packets (3 packet=1frame)*/
				//framebuff=(char *)malloc(FRAME_SIZE);
				//assert(framebuff!=NULL);
				memset(framebuff,0,FRAME_SIZE);
			}
			/* copy each packet to Out Buffer */
			memcpy(framebuff+(PacketCount*(PACKET_SIZE_IN_BYTES-RTP_HEADER_SIZE)),
								packetbuff+RTP_HEADER_SIZE,PACKET_SIZE_IN_BYTES-RTP_HEADER_SIZE);
			PacketCount++;
			prevTimeStamp=rtp.timestamp;
			if(PacketCount>(PACKET_COUNT -1))
			{
				//printf("\n***** processing Frames condition-1 tsms=%d*** PacketCount = %d\n",rtp.timestamp,PacketCount);
				PacketCount=0; //confirms only 20 packets per Frame	
				/*PUT a FULL Frame to out Queue, call this only once in 20 packets (20 packet=1frame)*/
				//fwrite
				//free(framebuff);
		                 rect.x = rect.y = 0;
             			 rect.w = 320;
             			 rect.h = 240;
				 overlay->pixels[0] = framebuff;
						//fread ( overlay->pixels[0], 1, 640*480*, fp ); 
              			SDL_UnlockYUVOverlay( overlay );
             			 SDL_DisplayYUVOverlay( overlay, &rect );
              				SDL_LockYUVOverlay(overlay);
					 SDL_Delay (50);
             			 while( SDL_PollEvent( &event ) )
              			{
                   		  if( event.type == SDL_QUIT )
                    			 {
                       		     printf( "quit\n" );
                      		    exit(0);
                    		 }
             			 }


				//fwrite(framebuff,640 *2,480,stdout);
				memset(framebuff,0,FRAME_SIZE);
				
			}
		//if(rtp.timestamp != 0)
		//printf("\n***** processing Frames condition-1 tsms=%d*** PacketCount = %d\n",rtp.timestamp,PacketCount);
	
		}
		else if(prevTimeStamp!=rtp.timestamp && PacketCount==0)
		{
			/* This Packet belongs to new Farame*/
			if(PacketCount==0)
			{
				/*Get a Empty buffer from out Queue, call this only once in 3 packets (3 packet=1frame)*/
				//framebuff=(char *)malloc(FRAME_SIZE);
				//assert(framebuff!=NULL);
				memset(framebuff,0,FRAME_SIZE);
			}
			/* copy each packet to Out Buffer */
			memcpy(framebuff+(PacketCount*(PACKET_SIZE_IN_BYTES-RTP_HEADER_SIZE)),
								packetbuff+RTP_HEADER_SIZE,PACKET_SIZE_IN_BYTES-RTP_HEADER_SIZE);
			PacketCount++;
			prevTimeStamp=rtp.timestamp;
	//#ifdef DEBUG_TOF_PROCESS_PACKET
		//printf("\n********** processing Frames condition-2 tsms=%d**********\n",rtp.timestamp);
	//#endif	
		}
		else if(prevTimeStamp!=rtp.timestamp && PacketCount>0)
		{
			/*We lost some packets & new Frame arrived here. Handle the case now*/
			/*release current OutFrame & get New OutFrame From Empty queue */
			
				//fwrite
				//free(framebuff);//put bug
				//framebuff=(char *)malloc(FRAME_SIZE);//get buff
				//assert(framebuff!=NULL);
				memset(framebuff,0,FRAME_SIZE);
				PacketCount=0;//force to 0; bcz its new Frame.
			/* copy each packet to Out Buffer */
			memcpy(framebuff+(PacketCount*(PACKET_SIZE_IN_BYTES-RTP_HEADER_SIZE)),
								packetbuff+RTP_HEADER_SIZE,PACKET_SIZE_IN_BYTES-RTP_HEADER_SIZE);
				PacketCount++;
				prevTimeStamp=rtp.timestamp;
	#ifdef DEBUG_TOF_PROCESS_PACKET
		printf("\n********** processing Frames condition-3 ********** tsms=%d\n",rtp.timestamp);
	#endif
		}
/* Put a Empty packet Buf back to In Queue */
	//fwrite
	//free(framebuff);//put bug
	}//end of while(1)	
}


int main(int argc, char *argv[])
{
	pthread_t receivethread,processthread;
	myfilenew = fopen("myfilenew.yuv", "w");
        if (myfilenew == NULL) {
                perror("Opening video device");
                return 1;
        }
	packetbuff=(char *)malloc(PACKET_SIZE_IN_BYTES);
	assert(packetbuff!=NULL);
	memset(packetbuff,0,PACKET_SIZE_IN_BYTES);

	framebuff=(char *)malloc(FRAME_SIZE);
	assert(framebuff!=NULL);
	memset(framebuff,0,FRAME_SIZE);
	while ( SDL_PollEvent(&sdlevent) ) ; 

	//initialize video system 
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError()); 
		exit(1); 
	} 
	//ensure SDL_Quit is called when the program exits 
	atexit(SDL_Quit); 
    
	//set video mode of 320 x 240 with 24-bit pixels 
	screen = SDL_SetVideoMode( 320, 240, 16, SDL_SWSURFACE); 
	if ( screen == NULL ) { 
		fprintf(stderr, "Unable to set 320x240 video: %s\n", SDL_GetError()); 
		exit(1); 
	} 

	overlay = SDL_CreateYUVOverlay(320,240,SDL_UYVY_OVERLAY,screen);
	if( overlay == NULL ){
        	fprintf( stderr, "Unable to create overlay: %s\n", SDL_GetError() );
        	exit( 1 );
        }
	framebuff = overlay->pixels[0];

	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		error("Opening socket");
	}
	length = sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));
	if (bind(sock,(struct sockaddr *)&server,length)<0)
	{
		error("binding");
	}
	fromlen = sizeof(struct sockaddr_in);

	
	//create_rtp_receiver();
	//rtp_receive_packets();
	//process_rtp_packets();
	pthread_create(&receivethread,NULL,rtp_receive_packets,NULL);//tof rtp receiver thread
	pthread_create(&processthread,NULL,process_rtp_packets,NULL);//tof packet process thread

	
	pthread_join(receivethread, NULL);
	pthread_join(processthread, NULL);

	return 0;
}
	

	
