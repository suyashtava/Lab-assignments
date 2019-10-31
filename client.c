#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
	int netsock;
	netsock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(8271);
	server_address.sin_addr.s_addr=INADDR_ANY;
	int status=connect(netsock,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	if(status==-1)
	{
	printf("\n connection error.....");
	}
	FILE* fp;
	int n;
	fp = fopen("file.txt","r");
	fscanf(fp,"%d\n",&n);
	send(netsock,&n,sizeof(n),0);
	int x;		
	while(fscanf(fp,"%d\n",&x)!=EOF)
	{
		send(netsock,&x,sizeof(x),0);
	}
	fclose(fp);
	char ch1[3],ch[3]="no";
	while(1)
	{
		printf("enter your choice\n");
		int choice;
		scanf("%d",&choice);
		send(netsock,&choice,sizeof(choice),0);
		int ans;
		recv(netsock,&ans,sizeof(ans),0);
		if(ans==-1)
			printf("Enter a valid choice \n");
		else
			printf("The required value is %d",ans);
		printf("\nTo exit...press 'no'\n");
		scanf("%s",ch1);
		if(strcmp(ch,ch1)==0)
		{
			close(netsock);
			exit(0);
		}
	}
	//close(netsock);	
	return 0;
}









