#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


void main(){
int sock;      // client socket discriptor
int a,b,i;
float arr[4];
unsigned int len;
char ch[3]="no";
char ch1[3];

struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
perror("socket: ");
exit(-1);
}

client.sin_family=AF_INET;
client.sin_port=htons(10000);        // initializing  socket  parameters 
client.sin_addr.s_addr=INADDR_ANY;
//inet_addr("127.0.0.1");
bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
perror("connect: ");
exit(-1);
}
while(1){
printf("enter 2 numbers:\n");
scanf("%d%d",&a,&b);
while(b==0)
{
printf("A number cannot be divided by zero. Re-enter 2nd number:");
scanf("%d",&b);
}
send(sock,&a,sizeof(a),0);
send(sock,&b,sizeof(b),0);     // sending data back to client...


recv(sock,arr,sizeof(arr),0);

printf("a = m + n = %0.0f\n",arr[0]);
printf("b = m - n = %0.0f\n",arr[1]);
printf("c = m * n = %0.0f\n",arr[2]);
printf("d = m / n = %f\n",arr[3]);
                           // receiving data from client
printf("\nTo exit press 'no'\n");


scanf("%s",ch1);

if(i=(strcmp(ch,ch1))==0){
close(sock);
exit(0);
}

}

}
