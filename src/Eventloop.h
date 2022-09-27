/*************************************************************************
	> File Name: Eventloop.h
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Sep 2022 05:35:09 PM CST
 ************************************************************************/

#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include"epoll.h"
#include"channel.h"
class Epoll;
class Channel;
class EventLoop{
private:
    Epoll *ep;
    bool quit;
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel *);
};

#endif
