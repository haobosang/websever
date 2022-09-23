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
#include"InetAddress.h"
#include"Socket.h"
#define MAXLISTEN 128
#define MAX_EVENTS 128
using namespace std;
void setfcntl(int fd){
    int oldsocketflag = fcntl(fd,F_GETFL,0);
    int newsocketflag = oldsocketflag | O_NONBLOCK;
    fcntl(fd,F_SETFL,newsocketflag);
}
int main(){
    Socket *sever_sock = new Socket();
    InetAddress *severaddr = new InetAddress("127.0.0.1",7777);
    sever_sock->bind(severaddr);
    sever_sock->listen();
    sever_sock->setnoblock();
    int epfd = epoll_create1(0);
    struct epoll_event events[MAX_EVENTS],ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd=sever_sock->getfd();
    epoll_ctl(epfd,EPOLL_CTL_ADD,sever_sock->getfd(),&ev);
    while(true)
    {
        int nfds = epoll_wait(epfd,events,MAX_EVENTS,-1);
        errif(nfds==-1,"nfd error"); 
        for(int i=0;i<nfds;i++)
        {
            if(events[i].data.fd == sever_sock->getfd())
            {
                InetAddress *cliaddr = new InetAddress();
                Socket *cli_sock = new Socket(sever_sock->accept(cliaddr));
                cli_sock->setnoblock();
                ev.data.fd = cli_sock->getfd();
                ev.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd,EPOLL_CTL_ADD,cli_sock->getfd(),&ev);

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
    return 0;
}
