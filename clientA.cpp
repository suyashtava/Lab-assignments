//client   
 #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <errno.h>
    #include <string.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include<bits/stdc++.h>
    using namespace std;
    int main(){
    int sock; // client socket discriptor
    int a,b,c,i, ent, f;
    int cl, el;
int ans;
    int tcl = 10, tel = 30;
    unsigned int len;
    char leaveType[10];
    char ch[3]="no", password[13], word[20], greetings[10], ser[10], rep[3], real[20];
    char ch1[3];
    char meaning[20];
     
    struct sockaddr_in client;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){ // client created..
    perror("socket: ");
    exit(-1);
    }
     
    client.sin_family=AF_INET;
    client.sin_port=htons(10000); // initializing parameters
    client.sin_addr.s_addr=INADDR_ANY;
    bzero(&client.sin_zero,0); //appending
     
     
    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1){ //conneting client
    perror("connect: ");
    exit(-1);
    }
    int choice;
    while(1){
    cout << "Enter any number to operate : \n";
    cout << "1. GCD or \t";
    cout << "2. LCM or \t";
    cout << "3. Mean or \t";
    cout << "4. Meadian or \t";
    cout << "5. Mode or \t";
    cout << "6. Variance or \t";
    cout << "7. Standard-Division \t";
     
    scanf("%d", &ent);
    send(sock, &ent, sizeof(ent), 0);
    recv(sock, &ans, sizeof(ans), 0);
    cout<<"Your ans is "<<ans<<endl;
     
    cout<<"if to enter choice again ? 0/1";
    cin>>choice;
	//reenter choice
    send(sock, &choice, sizeof(choice), 0);
    if(choice==0) break;
    }
     
     
    close(sock);
    return 0;
    }
     

