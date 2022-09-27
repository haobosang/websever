/*************************************************************************
	> File Name: Sever.h
	> Author: 
	> Mail: 
	> Created Time: Mon 26 Sep 2022 12:06:30 PM CST
 ************************************************************************/

#ifndef _SEVER_H
#define _SEVER_H
class EventLoop;
class Socket;
class Sever{
private:
    EventLoop *loop;
public:
    Sever(EventLoop *);
    ~Sever();
    void handleEvent(int);
    void newConnection(Socket *sever_sock);

};

#endif
