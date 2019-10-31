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
int i;
int ssock,csock;       // creating server and clinet socket discriptor
char que[100],ans[100];
struct list set[10];

strcpy(set[0].q,"Name");
strcpy(set[0].a,"Aadarsh");
strcpy(set[1].q, "Admission");
strcpy(set[1].a,"16JE002144");
strcpy(set[2].q, "Gender");
strcpy(set[2].a, "Male");
strcpy(set[3].q, "DOB");
strcpy(set[3].a, "19/11/1997");
strcpy(set[4].q,"Category");
strcpy(set[4].a, "General");
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
	
	FILE *file = fopen ( "Q_A.txt", "r" );
	if ( file != NULL )
	{
	  char line [ 128 ]; /* or other suitable maximum line size */
	  while ( fgets ( line, sizeof(line), file ) != NULL ) /* read a line */
	  {
	  	 char temp[100];
	  	 strcpy(temp,que);
	     if(strcmp(line, strcat(temp,"\n"))==0)
	     {
		  	printf("Successful - %s %s",line,que);
	     	fgets(line, sizeof(line),file);
	     	strcpy(ans,line);send(csock,ans,sizeof(ans),0);break;
	     }
	     else 
	     {	
	  		printf("Not - %s %s",line,que);
	     	fgets(line,sizeof(line),file);
	     }
	  }
	  
	  strcpy(ans,"Try again");
	  if(fgets(line,sizeof(line),file)==NULL)
	  {send(csock,ans,sizeof(ans),0);break;}

	  fclose ( file );
	}
	else
	{
	  perror ( "items.txt" ); /* why didn't the file open? */
	}

	// for(i=0;i<10;i++)
	// {
	// 	if(strcmp(que,set[i].q)==0)
	// 	{strcpy(ans,set[i].a);send(csock,ans,sizeof(ans),0);break;}
	// }
	

}


close(ssock);









}

