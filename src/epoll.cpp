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
#define MAX_EVENTS 1024
Epoll::Epoll():epfd(-1),events(nullptr){
    epfd = epoll_create1(0);
    errif(epfd == -1,"epoll create error");
    events = new epoll_event[MAX_EVENTS];
    bzero(events,sizeof(*events)*MAX_EVENTS);
}
Epoll::~Epoll(){
    close(epfd);
    delete [] events;
}
void Epoll::addFd(int fd,uint32_t op){
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.fd =fd;
    ev.events = op;
    errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1,"epoll error");
}
/*
std::vector<epoll_event> Epoll::poll(int timeout){

    std::vector<epoll_event> activepoll;
    int nfds = epoll_wait(epfd,events,MAX_EVENTS,timeout);
    errif(nfds==-1,"nfds error");
    for(int i=0;i<nfds;i++)
    {
        activepoll.push_back(events[i]);
    }
    return activepoll;
} */
std::vector<Channel*> Epoll::poll(int timeout){

    std::vector<Channel *> activechannel;
    int nfds = epoll_wait(epfd,events,MAX_EVENTS,timeout);
    errif(nfds==-1,"nfds error");
    for(int i=0;i<nfds;i++)
    {
        Channel *ch = (Channel *)events[i].data.ptr;
        ch->setRevents(events[i].events);
        activechannel.push_back(ch);
    }
    return activechannel;
}
void Epoll::updateChannel(Channel *channel){
    int fd = channel->getfd();
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.ptr = channel;
    ev.events = channel->getevents();
    if(!channel->getInepoll())
    {
        errif(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1,"epoll add error");
        channel->setInepoll();
    }else{
        errif(epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev)==-1,"epoll mod error");
    }
}

