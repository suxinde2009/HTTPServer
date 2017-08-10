//
//  SOCKET.cpp
//  HTTPServer
//
//  Created by suxinde on 2017/8/10.
//  Copyright © 2017年 com.su. All rights reserved.
//

#include "SOCKET.hpp"

namespace TCP {
    Socket::Socket() {
    }
    Socket::~Socket() {
    }
    int Socket::server_socket() {
        listenfd= socket(AF_INET,SOCK_STREAM,0);
        if(listenfd !=-1){
            std::cout<<"server_socket() ...succeed"<<std::endl;
        }else{
            std::cout<<"server_socket() ...failed"<<std::endl;
        }
        return listenfd;
    }
    
    int Socket::server_listen() {
        int ret = listen(listenfd,100);
        if(ret ==0){
            std::cout<<"server_listen() ...succeed"<<std::endl;
        }else{
            std::cout<<"server_listen() ...failed"<<std::endl;
        }
        return ret;
    }
    void Socket::server_close(int confd) {
        close(confd);
    }
    int Socket::server_accept() {
        socklen_t clientlen = sizeof(struct sockaddr_in);
        struct sockaddr clientaddr;
        
        int fd = accept(listenfd,(struct sockaddr *)&clientaddr,&clientlen);
        if(fd !=-1){
            std::cout<<"server_accept() ...succeed"<<std::endl;
        }else{
            std::cout<<"server_accept() ...failed"<<std::endl;
        }
        return fd;
    }
    int Socket::server_bind() {
        int ret =bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
        if(ret ==0){
            std::cout<<"server_bind() ...succeed"<<std::endl;
        }else{
            std::cout<<"server_bind() ...failed"<<std::endl;
        }
        return ret;
    }
    void  Socket::server_init() {
        bzero(&serveraddr,sizeof(serveraddr));
        serveraddr.sin_family=AF_INET;
        serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
        serveraddr.sin_port=htons(PORT);
        
    }
    ssize_t Socket::server_read(int fd,char*recvBuf,ssize_t maxlen) {
        long  long havedreadCount=0;
        ssize_t readCount=0;
        while(1){
            readCount = __readline(fd,recvBuf+havedreadCount,maxlen);
            havedreadCount+=readCount;
            //std::cout<<"readCount:"<<readCount<<std::endl;
            if(readCount==0)//当一行是\r\n时，空行，表示这一次读完。
                break;
        }
        return 0;
        
    }
    ssize_t Socket::server_write(int fd,char*sendBuf,ssize_t maxlen){
        return __writen(fd,sendBuf,maxlen);
    }

    ssize_t Socket::__writen(int fd,char*sendBuf,ssize_t maxlen){
        size_t nleft;
        ssize_t nwritten;
        const char *ptr;
        ptr=sendBuf;
        nleft=maxlen;
        //int count=0;
        
        while(nleft>0){
            if((nwritten=write(fd,ptr,nleft))<=0){
                if(nwritten<0&& errno==EINTR)
                    nwritten=0;
                else{
                    return -1;
                }
            }
            nleft-=nwritten;
            ptr+=nwritten;
        }
        return maxlen;
    }
    ssize_t Socket::__readline(int fd,char*recvBuf,ssize_t maxlen) {
        ssize_t n,rc;
        char c,*ptr;
        ptr=recvBuf;
        for(n=1;n<maxlen;n++){
        again:
            if((rc=read(fd,&c,1))==1){
                *ptr++=c;
                //std::cout<<c;
                if(c=='\n')
                    break;
            }else if(rc ==0){
                *ptr=0;
                return n-1;
            }else{
                if(errno ==EINTR)
                    goto again;
                return -1;
            }
        }
        *ptr=0;
        if(n==2&&*(ptr-2)=='\r'&&*(ptr-1)=='\n')
            n=0;
        return n;
    }
}
