//===========================================================================================================//
//													     //
// File    :  stream.h                                                                                       //
// Purpose :  Stream file over TCP as well as UDP. Support iterative clients		                     //
// 													     //
// Date    :  16th May 2014 									             //
// 								     					     //
//===========================================================================================================//



#ifndef MULTI_STREAM_H
#define MULTI_STREAM_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>


struct socket_type
{
	int end_type;              //0-client   1-server
	int domain;                //0-AF_UNIX  1-AF_INET
	int transfer_type;         //0-stream   1-Datagram
	int sockfd;
	int sockfd1;
};


struct file_info     // struct for file information 
{
	char *file;                
	FILE *f_r,*f_w;
};

struct address    // strcut to define address
{
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	char *host;
	struct hostent *he;
	int myport;              
	
};

struct stream_type  //struct to define type of the stream
{

	struct socket_type  s_t;
	struct file_info f_i;
	struct address add;
		
	int buflen;             
	
	int i;
	socklen_t len,addr_len;
	int numbytes;
	char buf[1000000]; //buffer length set
	
};


//===============Datagram server Initialization=======================//
//							              //
//		Creates sockets and attach them to address            //
//								      //
//====================================================================//

void init_datagram_server(struct stream_type *N)   
{	
	if((N->s_t.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		
		perror("Server-socket() sockfd error !");
		exit(1);
		
	}
	
	else
	
		printf("Server-socket() sockfd is OK...\n");
	
	
	
	
	N->add.my_addr.sin_family = AF_INET;
	N->add.my_addr.sin_port = htons(N->add.myport);
	N->add.my_addr.sin_addr.s_addr = INADDR_ANY;

	memset(&(N->add.my_addr.sin_zero), '\0', 8);
	

	if(bind(N->s_t.sockfd, (struct sockaddr *)&N->add.my_addr, sizeof(struct sockaddr)) == -1)
	{
	
		perror("Datagram-Server-bind() error !");
		exit(1);
		
	}
	
	else
	
		printf("Datagram-Server-bind() is OK...\n");
	
	
	
	N->addr_len = sizeof(struct sockaddr);
}

//======================Datagram server Write=========================//
//								      //
//      Reads data from the client and write to the respective file   //
//								      //
//====================================================================//

void write_datagram(struct stream_type *N)   
{
		
		char ip_lookup[20][20],number;
		char file_name[20][20];
		int D_c=1,flag=0,i=0;
		size_t written=0;
	

	while(1)
	{
		if((N->numbytes = recvfrom(N->s_t.sockfd, N->buf, N->buflen, 0, (struct sockaddr *)&N->add.their_addr, &N->addr_len)) == -1)
		{
			
			perror("Dtgram-Server-recvfrom() error !");
		
			exit(1);
			
		}
		
		else
		{
			printf("Datagram-Server-Waiting and listening...\n");
		
			printf("DatgramServer-recvfrom() is OK...\n");
		
		}
	

		printf("Datagram-Server got packet from %s    size:%d  %s\n", inet_ntoa(N->add.their_addr.sin_addr),N->numbytes,N->buf);
		
		flag=0;
		for(i=0;i<D_c;i++)
		{	
			printf("\nEntered into process %d\n",i);
	
			if(!strcmp(ip_lookup[i],inet_ntoa(N->add.their_addr.sin_addr)))
			{
				printf("\nMatch found at %d\n",i);
				flag=1;
				break;
			}
				printf("\nMatch not found at %d\n",i);
		}	
			if(flag==0)
			{
				printf("\nFile name:%s          %s\n",file_name[D_c-1],N->f_i.file);
					

				strncpy(file_name[D_c-1],N->f_i.file,15);
				printf("\nFile name:%s\n",file_name[D_c-1]);
				
			    sprintf(&number, "%d", D_c);
			
				printf("\n%c\n",number);
				strcat(file_name[D_c-1],&number);
				printf("\nFile name:%s\n",file_name[D_c-1]);
				
				strcat(file_name[D_c-1],".txt");
				
				printf("\nFile name:%s\n",file_name[D_c-1]);
				
				strcpy(ip_lookup[D_c-1],inet_ntoa(N->add.their_addr.sin_addr));
				printf("\nip:%s\n",ip_lookup[D_c-1]);
				i=D_c-1;
				D_c++;
				
				
			}
							
		printf("\nFile name:%s\n",file_name[i]);
		
	
		N->f_i.f_w=fopen(file_name[i],"ab");
		
		if (N->f_i.f_w==NULL)
			printf("file is not working or currputed");
		
		printf("\nOpening File");
				
		int written=fwrite(N->buf,1, N->numbytes,N->f_i.f_w);	
			printf("\nFile written         %d",written);
		fclose(N->f_i.f_w);
			printf("\nFile transmission closed\n");
	
	}

}
//===========================CLoseSocket==============================//
//								      //
//		            Closessocket                              //
//								      //
//====================================================================//

void close_socket(struct stream_type *N)
{
	if(close(N->s_t.sockfd) != 0)
	
		printf("sockfd closing failed!:%d\n",N->s_t.transfer_type);
	
	else
	
		printf("sockfd successfully closed!:%d\n",N->s_t.transfer_type);
	
}



//===============Datagram client Initialization=======================//
//								      //
//	    Creates sockets and attaches them to address              //
//								      //
//====================================================================//

void init_datagram_client(struct stream_type *N)           
{

	if ((N->add.he = gethostbyname(N->add.host)) == NULL)
	{
		
		perror("Datgram-Client-gethostbyname() error !");
		
		exit(1);
		
	}
	
	else
	
		printf("Datgram-Client-gethostname() is OK...\n");
	
	 
	
	if((N->s_t.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		
		perror("Datgram-Client-socket() error !");
		
		exit(1);
		
	}
	
	else
	
	printf("Datgram-Client-socket() sockfd is OK...\n");
	
	N->add.their_addr.sin_family = AF_INET;
	N->add.their_addr.sin_port = htons(N->add.myport);
	N->add.their_addr.sin_addr = *((struct in_addr *)N->add.he->h_addr);

	memset(&(N->add.their_addr.sin_zero), '\0', 8);
	
}

//=====================Datagram client read===========================//
//								      //
//         Reads data from file and writes it to the socket           //
//								      //
//====================================================================//


void read_datagram(struct stream_type *N)         
{
	
	N->f_i.f_r =  fopen(N->f_i.file,"rb");
	while(!feof(N->f_i.f_r))
	{	
			
		 N->i = fread(N->buf, 1, N->buflen, N->f_i.f_r);
		
		
		if((N->numbytes = sendto(N->s_t.sockfd,N->buf,N->buflen, 0, (struct sockaddr *)&N->add.their_addr, sizeof(struct sockaddr))) == -1)
		{
			
			perror("Datgram-Client-sendto() error !");
			exit(1);
			
		}
		
		else
			//usleep(2000);
			printf("\n====================== Sending next chunks =====================\n\n");
			printf("Datgram-Client-sendto() is OK...\n");
			printf("Datgram-sent %d bytes to %s   %s\n", N->numbytes, inet_ntoa(N->add.their_addr.sin_addr),N->buf);
			printf("\n================== Sent chunks Successfully!!====================\n");
			usleep(14900);
	
	} 
		
}


//====================TCP Server Initialization=======================//
//								      //
//          Creates sockets and attaches them to address              //
//								      //
//====================================================================//


void init_stream_server(struct stream_type *N)      
{
	N->s_t.sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (N->s_t.sockfd < 0) 
        printf("ERROR opening socket");
     
     bzero((char *) &N->add.my_addr, sizeof(N->add.my_addr));
     
     
     
    N->add.my_addr.sin_family = AF_INET;
    N->add.my_addr.sin_addr.s_addr = INADDR_ANY;
    N->add.my_addr.sin_port = htons(N->add.myport);
     
    if (bind(N->s_t.sockfd, (struct sockaddr *) &N->add.my_addr,sizeof(N->add.my_addr)) < 0) 
        printf("tcp-ERROR on binding");
     
    listen(N->s_t.sockfd,5);
 
    signal(SIGCHLD, SIG_IGN);

   

}

//====================TCP Client Initialization=======================//
//								      //
//	    Creates sockets and attaches them to address              //
//								      //
//====================================================================//

void init_stream_client(struct stream_type *N)   
{

	N->s_t.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (N->s_t.sockfd < 0) 
        printf("tcp-ERROR opening socket");
   
    N->add.he= gethostbyname(N->add.host);
    if (N->add.he == NULL) {
        fprintf(stderr,"tcp-ERROR, no such host\n");
        exit(0);
    }
   
    bzero((char *) &N->add.my_addr, sizeof(N->add.my_addr));
   
    N->add.my_addr.sin_family = AF_INET;
   
    bcopy((char *)N->add.he->h_addr,(char *)&N->add.my_addr.sin_addr.s_addr,N->add.he->h_length);
    N->add.my_addr.sin_port = htons(N->add.myport);
   
    if (connect(N->s_t.sockfd,(struct sockaddr *) &N->add.my_addr,sizeof(N->add.my_addr)) < 0) 
       printf("tcp-ERROR connecting");
}

//==========================TCP server Write==========================//
//								      //
//      Reads data from the client and write to the respective file   //
//								      //
//====================================================================//

void write_stream(struct stream_type *N)             
{
	char file_count[7]={'_','0','.','t','x','t','\0'};


	while(1)
	{
		N->len = sizeof(N->add.their_addr);
	    N->s_t.sockfd1 = accept(N->s_t.sockfd,(struct sockaddr *) &N->add.their_addr,&N->len);
	     
	    if (N->s_t.sockfd1 < 0) 
	        printf("tcp-ERROR on accept");
			
		printf("\n%d \n",N->s_t.sockfd1);
		file_count[1]++;
		if(fork()==0)
		{
			
			
			strcat(N->f_i.file,file_count);
			printf("\nfile name:%s",N->f_i.file);
			N->f_i.f_w=fopen(N->f_i.file,"wb");
			
			while(1) 
			{
		
			
				N->i=read(N->s_t.sockfd1,N->buf, N->buflen);
				if(N->i<=0)
				break;
				printf("tcp-Server-Got packet from %s    size:%d  %s\n", inet_ntoa(N->add.their_addr.sin_addr),N->i,N->buf);
				
			
				fwrite(N->buf, 1, N->i, N->f_i.f_w);
			}
			fclose(N->f_i.f_w);
		}	
	}
}

//=========================TCP client read============================//
//								      //
//         Reads data from file and writes it to the socket           //
//								      //
//====================================================================//

void read_stream(struct stream_type *N)     
{

	N->f_i.f_r =  fopen(N->f_i.file,"rb");
	while(!feof(N->f_i.f_r))
	{
		N->i = fread(N->buf, 1, N->buflen, N->f_i.f_r);
		
		printf("\nTCP is reading %s \n",N->buf);
		write(N->s_t.sockfd,N->buf,N->buflen);
		//usleep(10400);
	}
	
}

#endif

