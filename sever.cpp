/*************************************************************************
	> File Name: sever.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 26 Sep 2022 01:26:36 PM CST
 ************************************************************************/

#include<iostream>
#include"src/Eventloop.h"
#include"src/Sever.h"
#include"src/channel.h"
int main(){
    EventLoop *loop = new EventLoop();
    Sever *sever = new Sever(loop);
    loop->loop();
    return 0;
}
