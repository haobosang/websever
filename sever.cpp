/*************************************************************************
    > File Name: sever.cpp
    > Author: 
    > Mail: 
    > Created Time: Tue 20 Sep 2022 09:03:51 PM CST
 ************************************************************************/
#include<iostream>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<sys/types.h>
#include<unistd.h>
#define MAXCONN 128
#define EXIT_FAIL 1
void errif(bool flag,const char * msg){
    if(flag)
    {
        perror(msg);
        exit(EXIT_FAIL);
    
    }
    return ;
}
int main(){
    char buf[1024];
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    errif(socketfd==-1,"socket create error"); 
    
    struct sockaddr_in sever_addr,cli_addr;
    bzero(&sever_addr,sizeof(sever_addr));
    sever_addr.sin_family = AF_INET;
    sever_addr.sin_port = htons(7777);
    sever_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(socketfd,(sockaddr *)&sever_addr,sizeof(sever_addr));
    
    listen(socketfd,MAXCONN);
    bzero(&cli_addr,sizeof(cli_addr));
    socklen_t cli_addr_len = sizeof(cli_addr);
    int connectfd=accept(socketfd,(sockaddr *)&cli_addr,&cli_addr_len);
    errif(connectfd==-1,"accept error\n");
    while(1)
    {
        bzero(&buf,sizeof(buf));
        int n=read(connectfd,buf,1024);
        if(n>0)
        {
            printf("msg send by client: %s",buf);
            for(int i=0;i<n;i++){
                buf[i]=toupper(buf[i]);
            }
            write(connectfd,buf,n);
        }else if(n==0)
        {
            printf("read disconnect\n");
            close(connectfd);
        }else{
            close(connectfd);
            errif(true,"socket read error\n");
        }
    }
    close(connectfd);


    return 0;
}
