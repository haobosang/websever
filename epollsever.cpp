/*************************************************************************
	> File Name: epollsever.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 21 Sep 2022 12:02:41 PM CST
 ************************************************************************/

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<sys/epoll.h>
#include<unistd.h>
#include<fcntl.h>
#include"util.h"
#define MAXLISTEN 128
#define MAX_EVENTS 128
using namespace std;
void setfcntl(int fd){
    int oldsocketflag = fcntl(fd,F_GETFL,0);
    int newsocketflag = oldsocketflag | O_NONBLOCK;
    fcntl(fd,F_SETFL,newsocketflag);
}
int main(){
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in severaddr,cliaddr;
    bzero(&severaddr,sizeof(severaddr));
    severaddr.sin_family = AF_INET;
    severaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    severaddr.sin_port = htons(7777);
    bind(socketfd,(sockaddr *)&severaddr,sizeof(severaddr));
    listen(socketfd,MAXLISTEN);

    int epfd = epoll_create1(0);
    struct epoll_event events[MAX_EVENTS],ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd=socketfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketfd,&ev);
    while(true)
    {
        int nfds = epoll_wait(epfd,events,MAX_EVENTS,-1);
        errif(nfds==-1,"nfd error"); 
        for(int i=0;i<nfds;i++)
        {
            if(events[i].data.fd == socketfd)
            {
                socklen_t cliaddr_len = sizeof(cliaddr);
                int clisocket = accept(socketfd,(sockaddr *)&cliaddr,&cliaddr_len);
                ev.data.fd = clisocket;
                ev.events = EPOLLIN | EPOLLET;
                setfcntl(clisocket);
                epoll_ctl(epfd,EPOLL_CTL_ADD,clisocket,&ev);

            }else if(events[i].events & EPOLLIN){
                char buf[1024];
                while(1)
                {
                    bzero(&buf,sizeof(buf));
                    int n = read(events[i].data.fd,buf,1024);
                    if(n>0)
                    {
                        for(int i=0;i<n;i++)
                        {
                            buf[i]=toupper(buf[i]);
                        }
                        write(events[i].data.fd,buf,n);
                                
                    }else if(n==0)
                    {
                        printf("disconnect \n");
                        close(events[i].data.fd);
                        break;
                    }
                }
            }else{
                printf("others thing\n");
            }
            
        }
    }
    close(socketfd);
    return 0;
}
