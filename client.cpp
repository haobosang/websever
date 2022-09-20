/*************************************************************************
	> File Name: client.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 20 Sep 2022 09:51:02 PM CST
 ************************************************************************/
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<sys/types.h>
#include<unistd.h>
#define MAXCONN 128
int main(){
    char buf[20];
    int sockefd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in cli_addr;
    bzero(&cli_addr,sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(7777);
    cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int confd=connect(sockefd,(sockaddr *)&cli_addr,sizeof(cli_addr));
    write(confd,"hello\n",6);
    close(confd);
    return 0;
}
