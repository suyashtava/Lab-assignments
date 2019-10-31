#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int lcm(int arr[], int n)
{
    int ans = arr[0];
    int i;    
    for (i = 1; i < n; i++)
	        ans = (((arr[i] * ans)) /
	                (gcd(arr[i], ans)));
  
    return ans;
}
int Sqrt(int x)
{
    if (x == 0 || x == 1)
    return x;
    int i = 1, result = 1;
    while (result <= x)
    {
      i++;
      result = i * i;
    }
    return i - 1;
} 
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
int main()
{
	int server_socket;
	server_socket  = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(8271);
	server_address.sin_addr.s_addr=INADDR_ANY;
	bind(server_socket,(struct sockaddr *)&server_address,sizeof(struct sockaddr_in));
	listen(server_socket,10);
	int csock;
	csock=accept(server_socket,NULL,NULL);
	int choice;
	int n,i;
	recv(csock,&n,sizeof(n),0);
	int arr[n];
	for(i=0;i<n;i++)
	{
		int x;
		recv(csock,&x,sizeof(x),0);
		arr[i]=x;
	}
	//for(i=0;i<n;i++)
	//	printf("%d\n",arr[i]);
	while(1)
	{
		recv(csock,&choice,sizeof(choice),0);
		if(choice==1)
		{
			int ans=arr[0];			
			for(i=1;i<n;i++)
			{
				ans = gcd(ans,arr[i]);
			}
			send(csock,&ans,sizeof(ans),0);
		}
		else if(choice==2)
		{
			int ans=lcm(arr,n);
			send(csock,&ans,sizeof(ans),0);
		}
		else if(choice==3)
		{
			int sum=0;
			for(i=0;i<n;i++)
				sum+=arr[i];
			int ans = sum/n;
			send(csock,&ans,sizeof(ans),0);
		}
		else if(choice ==4)
		{
			int tmp[n];
			for(i=0;i<n;i++)
				tmp[i]=arr[i];
			qsort (tmp, sizeof(tmp)/sizeof(*tmp), sizeof(*tmp),comp);
			int ans = tmp[n/2];
			send(csock,&ans,sizeof(ans),0);
		}
		else if(choice == 5)
		{	
			int freq[1000]={0};
			int m=arr[0],f=0;
			for(i=0;i<n;i++)
			{
				freq[arr[i]]++;
				f = f>freq[i] ? f:freq[i];
				m = m>arr[i] ? m:arr[i];
			}
			for(i=0;i<m;i++)
			{
				if(f==freq[i])
				{
					int ans=i;
					send(csock,&ans,sizeof(ans),0);
					break;
				}
			}
		}
		else if(choice == 6)
		{
			int sum=0;
			for(i=0;i<n;i++)
				sum+=arr[i];
			int mean = sum/n;
			int ans=0;
			for(i=0;i<n;i++)
			{
				ans = ans+((arr[i]-mean)*(arr[i]-mean));
			}
			ans = ans/n;
			send(csock,&ans,sizeof(ans),0);
		}
		else if(choice == 7)
		{
			int sum=0;
			for(i=0;i<n;i++)
				sum+=arr[i];
			int mean = sum/n;
			int ans=0;
			for(i=0;i<n;i++)
			{
				ans = ans+((arr[i]-mean)*(arr[i]-mean));
			}
			ans = ans/n;
			ans = Sqrt(ans);
			send(csock,&ans,sizeof(ans),0);			
		}
		else
		{
			int ans=-1;
			send(csock,&ans,sizeof(ans),0);
		}
	}
	close(server_socket);
	return 0;
}
	/*FILE *fp;
	fp = fopen("file.txt","r");
	fscanf(fp,"%d\n",&n);
	int arr[n];
	int x,i=0;
	while(fscanf(fp,"%d\n",&x)!=EOF)
	{
		arr[i]=x;
		i++;
	}*/














