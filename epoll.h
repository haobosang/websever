/*************************************************************************
	> File Name: epoll.h
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Sep 2022 08:02:52 PM CST
 ************************************************************************/

#ifndef _EPOLL_H
#define _EPOLL_H
class Epoll{
private:
    int epfd;
    struct epoll_events *events;
public:
    Epoll();
    ~Epoll();
    void addFd(int fd,uint32_t op);
};

#endif
