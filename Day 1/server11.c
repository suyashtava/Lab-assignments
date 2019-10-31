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
	char q[100];
char a[100];
};

void main(){
int i,count;
int ssock,csock;       // creating server and clinet socket discriptor
char que[100],ans[100];
struct list set[100];
count= 10;
strcpy(set[0].q,"Zeal");
strcpy(set[0].a,"Enthusiasm");
strcpy(set[1].q, "Ubiquitous");
strcpy(set[1].a,"Omnipresent");
strcpy(set[2].q, "Obstinate");
strcpy(set[2].a, "Stubborn");
strcpy(set[3].q, "Insatiable");
strcpy(set[3].a, "Cannot be satisfied");
strcpy(set[4].q, "Word");
strcpy(set[4].a, "General meaning");
for(i=5;i<10;i++)
{
	strcpy(set[i].q,"Others");
	strcpy(set[i].a,"BLAH");
}

unsigned int len;

struct sockaddr_in server,client;   // creating server & client socket object

if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socket: is not created");
	exit(-1);
}

server.sin_family=AF_INET;
server.sin_port=htons(10000);       // initializing server socket parameters..
server.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
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
while(1){

	recv(csock,&que,sizeof(que),0);
	for(i=0;i<count;i++)
	{
		if(strcmp(que,set[i].q)==0)
		{strcpy(ans,set[i].a);send(csock,ans,sizeof(ans),0);break;}
	}
	
	if(i==count)
	{
		strcpy(set[i].q,que);
		printf("Word not found... Enter the meaning to add it to the dictionary:\n");
		scanf("%[^\n]s",set[i].a);
		count++;
		strcpy(ans,"Word added successfully");
		send(csock,ans,sizeof(ans),0);
	}
	
}


close(ssock);









}

