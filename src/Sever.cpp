/*************************************************************************
	> File Name: Sever.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 26 Sep 2022 12:06:40 PM CST
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
#include"channel.h"
#include"Eventloop.h"
#include"Sever.h"
Sever::Sever(EventLoop *_loop):loop(_loop){
    InetAddress *severaddr = new InetAddress("127.0.0.1",7777);
    Socket *sever = new Socket();
    sever->bind(severaddr);
    sever->listen();
    sever->setnoblock();

    Channel *ch = new Channel(loop,sever->getfd());
    std::function<void()> cb = std::bind(&Sever::newConnection,this,sever);
    ch->setcallback(cb);
    ch->enableReading();
}
Sever::~Sever(){

}
void Sever::newConnection(Socket *sever_sock){
    InetAddress *cliaddr = new InetAddress();
    Socket *cli_sock = new Socket(sever_sock->accept(cliaddr));
    cli_sock->setnoblock();
    printf("new client fd %d! IP: %s Port: %d\n", cli_sock->getfd(), inet_ntoa(cliaddr->addr.sin_addr), ntohs(cliaddr->addr.sin_port));
    Channel *ch = new Channel(loop,cli_sock->getfd());
    std::function<void()> cb = std::bind(&Sever::handleEvent,this,cli_sock->getfd());
    ch->setcallback(cb);
    ch->enableReading();

}

void Sever::handleEvent(int socketfd){
    char buf[1024];
    while(true){
        bzero(&buf,sizeof(buf));
        int n = read(socketfd,buf,sizeof(buf));
        if(n==0) {
            close(socketfd);
            std::cout<<"disconnect"<<std::endl;
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

