/*************************************************************************
	> File Name: util.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Sep 2022 05:08:42 PM CST
 ************************************************************************/

#include<stdlib.h>
#include<iostream>
#define EXIT_FAIL 1
void errif(bool flag,const char * msg){
    
    if(flag)
    {
        perror(msg);
        exit(EXIT_FAIL);
    
    }
    return ;
}

