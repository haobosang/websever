/*************************************************************************
	> File Name: util.h
	> Author: 
	> Mail: 
	> Created Time: Wed 21 Sep 2022 10:32:28 PM CST
 ************************************************************************/

#ifndef _UTIL_H
#define _UTIL_H

#define EXIT_FAIL 1
void errif(bool flag,const char * msg){
    
    if(flag)
    {
        perror(msg);
        exit(EXIT_FAIL);
    
    }
    return ;
}

#endif
