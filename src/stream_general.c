#include "stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


void *stream(void *New)
{
	printf("Created New Thread");
	printf("====================");
	
	struct stream_type *N = (struct stream_type*) New;
	
	
	if(N->s_t.end_type==0 && N->s_t.domain==1 && N->s_t.transfer_type==1)
	{
    init_datagram_client(N);
	read_datagram(N);
    }
	
	if(N->s_t.end_type==1 && N->s_t.domain==1 && N->s_t.transfer_type==1)
	{
	init_datagram_server(N);
	write_datagram(N);
	}
	
	if(N->s_t.end_type==0 && N->s_t.domain==1 && N->s_t.transfer_type==0)
	{
    init_stream_client(N);
	read_stream(N);
    }
	
	if(N->s_t.end_type==1 && N->s_t.domain==1 && N->s_t.transfer_type==0)
	{
	init_stream_server(N);
	write_stream(N);
	}
		
	close_socket(N);
	return 0;
}


int main(int argc,char *argv[])
{
	int ret;

	int i=0,offset=0,instances,temp;
	pthread_t *thread;
	struct stream_type *N;

	if(argc>1)
	{
	instances=atoi(argv[1]);
	//printf("argv[1]=%d",instances);
    
	i=(instances*7)+2;
	//printf("\n%d,  %d\n",argc,i);
	}
	if(argc < i || argc==1)
	{
		
		
		
		printf("\nInvalid arguments passed, Please refer 'Instructions' to run this project\n");
		printf("\n===============================================================================================================\n");
		printf("\nInstruction to type command:\n===========================\n\n./stream <number_of_insance> <end_type> <domain> <Protocol> <port_number> <buffer_size> <file_name> <host>\n");
		printf("\nArguments details :\n================= \n");	
		printf("\n1. Selct End Type Streamer or reciever (0/1)");
		printf("\n2. Selct Domain AF_UNIX or AF_INET (0/1)");
		printf("\n3. Selct Protocol Tcp or Datagram (0/1)\n");
		printf("4. Define Port Number \n");
		printf("5. Define Packet size\n");
		printf("6. Select file_name which you want to stream on network \n");
		printf("7. Define 'host' as your IP address on which you server is going to run\n");
		printf("\n===============================================================================================================\n\n");
		
		exit(1);
	}
	printf("\n creating thread for loop\n");
	thread=(pthread_t *)malloc(sizeof(pthread_t)*instances);
	N=(struct stream_type *)malloc(sizeof(struct stream_type)*instances);
	
	
	printf("\nEntering into Process loop\n");
	printf("\n-----------------------------\n");
	
	
	for(i=0;i<instances;i++)
	{	
	

	
		printf("\nEnterd into process %d times\n",i);
			
		offset=(i*7)+2;
		printf("\noffset %d\n",offset);
		
		temp=atoi(argv[offset]);
		//printf("\ntemp %d\n",temp);
		
		N[i].s_t.end_type=temp;
		//printf("\ntemp %d\n",N[i].s_t.end_type);
		
		temp=atoi(argv[offset+1]);
		//printf("\ntemp %d\n",temp);
		N[i].s_t.domain=temp;
		
		temp=atoi(argv[offset+2]);
		//printf("\ntemp %d\n",temp);
		N[i].s_t.transfer_type=temp;
		
		temp=atoi(argv[offset+3]);
		//printf("\ntemp %d\n",temp);
		N[i].add.myport=temp;
		
		temp=atoi(argv[offset+4]);
		//printf("\ntemp %d\n",temp);
		N[i].buflen=temp;
		
	
		N[i].f_i.file=argv[offset+5];
		puts(N[i].f_i.file);
		
		N[i].add.host=argv[offset+6];
		puts(N[i].add.host);
		
		ret = pthread_create(&thread[i], NULL, stream, &N[i]);

    
		if(ret != 0)
		{
	        printf ("Creation of pthread error!\n");
	        exit (1);
		}
	}
	

	pthread_join( thread[0], NULL);
	pthread_join( thread[1], NULL);

	return 0;
}
