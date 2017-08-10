//
//  SOCKET.hpp
//  HTTPServer
//
//  Created by suxinde on 2017/8/10.
//  Copyright © 2017年 com.su. All rights reserved.
//

// Code From http://www.cnblogs.com/liferecord/p/4843615.html

#ifndef SOCKET_hpp
#define SOCKET_hpp

#include <stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include <string.h>
#include <unistd.h>

namespace TCP {
    
    class Socket {
    
    public:
        Socket();
        ~Socket();
        int server_socket();
        int server_listen();
        int server_accept();
        int server_bind();
        void  server_init();
        void  getClient(sockaddr_in* caddr);
        ssize_t server_read(int fd,char*recvBuf,ssize_t maxlen);
        ssize_t server_write(int fd,char*sendBuf,ssize_t maxlen);
        void server_close(int confd) ;
    
    private:
        ssize_t __readline(int fd,char*recvBuf,ssize_t maxlen) ;
        ssize_t __writen(int fd,char*sendBuf,ssize_t maxlen) ;
        int listenfd;
        int confd;
        struct sockaddr_in serveraddr;
        socklen_t serverlen;
        static const int PORT=80;
    };
    
}

#endif /* SOCKET_hpp */
