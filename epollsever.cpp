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
#include"src/util.h"
#include"src/InetAddress.h"
#include"src/Socket.h"
#include"src/epoll.h"
#include"src/channel.h"
#define MAXLISTEN 128
#define MAX_EVENTS 128
using namespace std;
void ReadEvents(int socketfd);
int main(){
    Socket *sever_sock = new Socket();
    InetAddress *severaddr = new InetAddress("127.0.0.1",7777);
    sever_sock->bind(severaddr);
    sever_sock->listen();
    sever_sock->setnoblock();
    Epoll *ep = new Epoll();
    Channel *severchannel = new Channel(ep,sever_sock->getfd());
    severchannel->enableReading();
    while(true)
    {
        std::vector<Channel *> activeChannels = ep->poll();
        int nfds = activeChannels.size();
        for(int i=0;i<nfds;i++)
        {
            int chfd = activeChannels[i]->getfd();
            if(chfd == sever_sock->getfd())
            {
                InetAddress *cliaddr = new InetAddress();
                Socket *cli_sock = new Socket(sever_sock->accept(cliaddr));
                cli_sock->setnoblock();
                printf("new client fd %d! IP: %s Port: %d\n", cli_sock->getfd(), inet_ntoa(cliaddr->addr.sin_addr), ntohs(cliaddr->addr.sin_port));
                Channel *clich = new Channel(ep,cli_sock->getfd());
                clich->enableReading();
            }else if(activeChannels[i]->getevents() & EPOLLIN){
                ReadEvents(chfd);
            }else{
                printf("others thing\n");
            }
            
        }
    }
    return 0;
}
void ReadEvents(int socketfd){
    char buf[1024];
    while(true){
        bzero(&buf,sizeof(buf));
        int n = read(socketfd,buf,sizeof(buf));
        if(n==0) {
            close(socketfd);
            cout<<"disconnect"<<endl;
            break;
        }
        for(int i =0 ;i<n;i++)
        {
            buf[i]=toupper(buf[i]);
        }
        write(socketfd,buf,n);
    }
    close(socketfd);
    
}
