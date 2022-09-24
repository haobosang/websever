/*************************************************************************
	> File Name: epoll.h
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Sep 2022 08:02:52 PM CST
 ************************************************************************/

#ifndef _EPOLL_H
#define _EPOLL_H
#include<vector>
class Epoll{
private:
    int epfd;
    struct epoll_event *events;
public:
    Epoll();
    ~Epoll();
    void addFd(int fd,uint32_t op);
    std::vector<epoll_event> poll(int timeout=-1);
};

#endif
