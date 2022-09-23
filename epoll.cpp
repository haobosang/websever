/*************************************************************************
	> File Name: epoll.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Sep 2022 08:02:47 PM CST
 ************************************************************************/

#include<iostream>
#include"epoll.h"
#include"util.h"
#include<sys/epoll.h>
#include<unistd.h>
#include<cstring>
Epoll::Epoll(){
    epfd = epoll_create1(0);
    errif(epfd == -1,"epoll create error");
}
Epoll::~Epoll(){
    close(epfd);
}
void Epoll::addFd(int fd,uint32_t op){
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.fd =fd;
    ev.events = op;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);
}
