/*************************************************************************
	> File Name: Socket.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 22 Sep 2022 10:24:48 AM CST
 ************************************************************************/

#include"Socket.h"
#include"InetAddress.h"
#include"util.h"
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#define MAXCONN 128
Socket::Socket():fd(-1){
    fd = socket(AF_INET,SOCK_STREAM,0);
    errif(fd == -1,"socket create error");
}
Socket::Socket(int _fd):fd(_fd){
    errif(fd == -1,"socket create error");
}
Socket::~Socket(){
    if(fd!=-1) close(fd);
}
void Socket::bind(InetAddress *addr){
    ::bind(fd,(struct sockaddr *)&addr->addr,addr->addr_len);
    
}
void Socket::listen(){
    ::listen(fd,MAXCONN);
}
int Socket::accept(InetAddress *addr){
    int clifd = ::accept(fd,(struct sockaddr *)&addr->addr,&addr->addr_len);
    errif(clifd == -1,"accept error");
    return clifd;
}
void Socket::setnoblock(){
    int oldflag = fcntl(fd,F_GETFL,0);
    int newflag = oldflag | O_NONBLOCK;
    fcntl(fd,F_SETFL,newflag);
}
int Socket::getfd(){
    return fd;
}
