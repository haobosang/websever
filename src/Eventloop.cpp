/*************************************************************************
	> File Name: Eventloop.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Sep 2022 05:35:17 PM CST
 ************************************************************************/
#include"Eventloop.h"
#include"channel.h"
#include"epoll.h"
EventLoop::EventLoop():ep(nullptr),quit(false){
    ep = new Epoll();
};
EventLoop::~EventLoop(){ delete ep; }
void EventLoop::loop(){
    while(!quit){
        std::vector<Channel *> ch;
        ch = ep->poll();
        for(auto it :ch){
            it->handleEvent();
        }
    }
}
void EventLoop::updateChannel(Channel *ch){
   ep->updateChannel(ch); 
}
