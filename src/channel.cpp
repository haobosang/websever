/*************************************************************************
	> File Name: channel.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Sep 2022 04:37:19 PM CST
 ************************************************************************/
#include<iostream>
#include"channel.h"
#include"epoll.h"
#include"Eventloop.h"
#include<sys/epoll.h>
Channel::Channel(EventLoop *_loop,int sockfd):loop(_loop),fd(sockfd),events(0),revents(0),inEpoll(false){
}
Channel::~Channel(){
}
void Channel::handleEvent(){
    callback();
}
void Channel::enableReading(){
    events = EPOLLIN | EPOLLET;
    loop->updateChannel(this);
}
int Channel::getfd(){
    return fd;
}
uint32_t Channel::getevents(){
    return events;
}
uint32_t Channel::getrevents(){
    return revents;
}
bool Channel::getInepoll(){
    return inEpoll;

}
void Channel::setInepoll(){
    inEpoll = true;
}
void Channel::setRevents(uint32_t _ev){
    revents = _ev;

}
void Channel::setcallback(std::function<void()> _cb){
    callback = _cb;
}
