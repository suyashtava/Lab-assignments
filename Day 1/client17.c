#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct list
{
	char id[100],name[100];
	int price,quant;
};

void main(int argc, char ** argv){
int sock;      // client socket discriptor
char ans[100],que[100];
unsigned int len;
char ch[3]="no";
char ch1[3];
int i;
struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
perror("socket: ");
exit(-1);
}

client.sin_family=AF_INET;
client.sin_port=htons(atoi(argv[2]));        // initializing  socket  parameters 
client.sin_addr.s_addr=inet_addr(argv[1]);
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}

struct list item;
strcpy(item.id,argv[3]);
item.quant = atoi(argv[4]);
//printf("%s %d",item.id,item.quant);
send(sock,&item,sizeof(item),0);       // sending data back to client...

recv(sock,ans,sizeof(ans),0);

printf("%s\n\n",ans);
                           // receiving data from client


close(sock);
}

