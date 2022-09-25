/*************************************************************************
	> File Name: InetAddress.h
	> Author: 
	> Mail: 
	> Created Time: Thu 22 Sep 2022 10:48:56 AM CST
 ************************************************************************/

#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include<arpa/inet.h>
class InetAddress{
private:
public:
    struct sockaddr_in addr;
    socklen_t addr_len;
    InetAddress();
    InetAddress(const char * ip,int port);
    ~InetAddress();
};
#endif
