#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct list{
	char id[100],name[100];
	int price , quant;
};

void main(int argc, char ** argv){
int i,count;
int ssock,csock;
unsigned int len;       // creating server and clinet socket discriptor
char ans[100];
struct list items[100],item;
count= 10;
struct sockaddr_in server,client;   // creating server & client socket object

if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socket: is not created");
	exit(-1);
}

server.sin_family=AF_INET;
server.sin_port=htons(10000);       // initializing server socket parameters..
server.sin_addr.s_addr=inet_addr("127.0.0.1");
bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);

if((bind(ssock,(struct sockaddr *)&server,len))==-1){  // binding port & IP  
	perror("bind: ");
	exit(-1);
}

if((listen(ssock,5))==-1){     // listening for client
	perror("listen: ");                     
	exit(-1);
}


if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){  // accepting connectn
	perror("accept: ");                         
	exit(-1);
}


	recv(csock,&item,sizeof(item),0);
	FILE *file = fopen ( "items.txt", "r+" );
	if ( file != NULL )
	{
		char line [ 128 ]; /* or other suitable maximum line size */
		while ( fgets ( line, sizeof(line), file ) != NULL ) /* read a line */
		{
			char this_name[30],this_id[30];
			int this_price, this_quant;
			sscanf(line, "%s %s %d %d",this_id, this_name, &this_price, & this_quant);
			// printf("The item is %s and its price is %d",item,price);
	        if(strcmp(item.id,this_id)==0)
			{	if((this_quant-item.quant)>0)
				{
					sprintf(ans,"Order placed successfully:\n Order summary - \n %d pieces of %s bought for Rs. %d",item.quant,this_name,(this_price*item.quant));
					//strcpy(ans,set[i].a);
					send(csock,ans,sizeof(ans),0);
					break;
				}
				else
				{
					sprintf(ans,"Item not available");
					//strcpy(ans,set[i].a);
					send(csock,ans,sizeof(ans),0);
					break;
				}
			}

	  	}
	  	if(fgets(line, sizeof(line), file) == NULL)
		{
			sprintf(ans,"Item not available");
			send(csock,ans,sizeof(ans),0);
		}
		fclose ( file );
	}
	else
	{
	  perror ( "items.txt" ); /* why didn't the file open? */
	}

close(ssock);









}

