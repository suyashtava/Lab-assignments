//server    
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
    #include<string>
    using namespace std;
     
    int main(){
     
    int ssock,csock;
    int a,b,c, id, eid;
    int cl, el;
    char passeid[13], meaning[20], ser[10], rep[3], real[20];
    unsigned int len;
     
    struct sockaddr_in server,client;
     
    if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
    perror("socket: ");
    exit(-1);
    }
     
    server.sin_family=AF_INET;
    server.sin_port=htons(10000);
     
    // initializing server parameters..
    server.sin_addr.s_addr=INADDR_ANY;

    bzero(&server.sin_zero,0);
    len=sizeof(struct sockaddr_in);
     
    if((bind(ssock,(struct sockaddr *)&server,len))==-1){
    // binding port & IP
    perror("bind error: ");
    exit(-1);
    }
     
    if((listen(ssock,5))==-1){
    // listening for client
    perror("listen error: ");
    exit(-1);
    }
     
     
    if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){
    // accepting connectn
    perror("accept error: ");
    exit(-1);
    }
     
     
    ifstream infile;
    infile.open("abc.txt");
    if(!infile.is_open()){
    cout<<"File is Not Opening";
    exit(-1);
    }
    string line;
    int x;
    vector<int> dt;
    while(getline(infile, line))
    {
    sscanf(line.c_str(), "%d", &x);
    cout<<x<<endl;
    dt.push_back(x);
    }
    infile.close();
    ofstream ofs;
    ofs.open("upload.txt", ofstream::out);
    for(int k=0;k<dt.size();k++){
    ofs<<dt[k]<<endl;
    }
    ofs.close();
    int choice,ans=0,temp;
    while(1) {
    recv(csock, &eid, sizeof(eid), 0);
     //choice starts here eid= entered id
    if(eid == 1){
    ans = dt[0];
    for(int k=1;k<dt.size();k++) ans=__gcd(ans,dt[k]);
    } else if (eid == 2) {
    temp = dt[0];
    for(int k=1;k<dt.size();k++) { temp*=dt[k]; ans=__gcd(ans,dt[k]);}
    ans = temp/ans;
    } else if(eid == 3) {
    ans = dt[0];
    for(int k=1;k<dt.size();k++) { ans+=dt[k];}
    ans = ans/dt.size();
    } else if(eid == 4) {
    sort(dt.begin(),dt.end());
    ans = dt[dt.size()/2];
    } else if(eid == 5) {
    int tmax=1,mmax=1,value=-1,posit=0;
    sort(dt.begin(),dt.end());
    for(int k=1;k<dt.size();k++) {
    if(dt[k] == dt[posit]) tmax++;
    else { if(tmax>mmax) value=dt[posit]; mmax = max(tmax,mmax); }
    }
    ans = value;
    } else if(eid == 6) {
    ans = dt[0];
    for(int k=1;k<dt.size();k++)
 	{ ans+=dt[k];}
    int mean = ans/dt.size();
     
    for(int k=0;k<dt.size();k++) 
	{ ans+=(dt[k]-mean)*(dt[k]-mean);}
    ans = ans/dt.size();
    } else {
    ans = data[0];
    for(int k=1;k<dt.size();k++) 
	{ ans+=dt[k];}
    int mean = ans/data.size();
     
    for(int k=0;k<dt.size();k++) 
	{ ans+=(dt[k]-mean)*(dt[k]-mean);}
	    ans = ans/dt.size();
    ans = sqrt(ans);
    }
     
     
     
    send(csock, &ans, sizeof(ans), 0);
    cout<<"Answer is send to client,will print on scren\n";
    recv(csock, &choice, sizeof(choice), 0);
    if(choice==0) break;
    }
     
     
     
    close(ssock);
    return 0;
    }
     
     
     
     
     
     
     
     
     
     
   
