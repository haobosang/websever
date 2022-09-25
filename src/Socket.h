/*************************************************************************
	> File Name: Socket.h
	> Author: 
	> Mail: 
	> Created Time: Thu 22 Sep 2022 10:24:41 AM CST
 ************************************************************************/

#ifndef _SOCKET_H
#define _SOCKET_H
class InetAddress;
class Socket{
private:
   int fd; 
public:
    Socket();
    ~Socket();
    Socket(int _fd);
    void listen();
    void bind(InetAddress *addr);
    void setnoblock();
    int accept(InetAddress *addr);
    int getfd();
};
#endif
