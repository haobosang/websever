/*************************************************************************
	> File Name: channel.h
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Sep 2022 04:25:42 PM CST
 ************************************************************************/

#ifndef _CHANNEL_H
#define _CHANNEL_H
#include"epoll.h"
class Epoll;
class Channel{
private:
    Epoll *ep;
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;
public:
    Channel();
    ~Channel();
    Channel(Epoll *_ep,int sockfd);
    void enableReading();
    int getfd();
    uint32_t getevents();
    uint32_t getrevents();
    bool getInepoll();
    void setInepoll();
    void setRevents(uint32_t);
};
#endif
