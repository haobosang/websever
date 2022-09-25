/*************************************************************************
	> File Name: InetAddress.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 22 Sep 2022 10:49:15 AM CST
 ************************************************************************/

#include"InetAddress.h"
#include<cstring>
InetAddress::InetAddress():addr_len(sizeof(addr)){
    bzero(&addr,addr_len);
}
InetAddress::InetAddress(const char* ip,int port):addr_len(sizeof(addr)){
    bzero(&addr,addr_len);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
}

