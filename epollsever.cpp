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
#include"epoll.h"
#define MAXLISTEN 128
#define MAX_EVENTS 128
using namespace std;
int main(){
    Socket *sever_sock = new Socket();
    InetAddress *severaddr = new InetAddress("127.0.0.1",7777);
    sever_sock->bind(severaddr);
    sever_sock->listen();
    sever_sock->setnoblock();
    Epoll *ep = new Epoll();
    ep->addFd(sever_sock->getfd(),EPOLLIN | EPOLLET);
    while(true)
    {
        std::vector<epoll_event> events = ep->poll();
        int nfds = events.size();
        for(int i=0;i<nfds;i++)
        {
            cout<<events[i].data.fd<<endl;
            if(events[i].data.fd == sever_sock->getfd())
            {
                InetAddress *cliaddr = new InetAddress();
                Socket *cli_sock = new Socket(sever_sock->accept(cliaddr));
                cli_sock->setnoblock();
                printf("new client fd %d! IP: %s Port: %d\n", cli_sock->getfd(), inet_ntoa(cliaddr->addr.sin_addr), ntohs(cliaddr->addr.sin_port));
                ep->addFd(cli_sock->getfd(),EPOLLIN|EPOLLET);
                
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
