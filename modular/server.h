#ifndef SERVER_H
#define SERVER_H

#include<sys/socket.h>
#include<netinet/in.h>

class Server {
    public:
        int domain;
        int socktype;
        int protocol;
        int port;
        unsigned long address;
        int backlog;

        struct sockaddr_in sock_address;
        
        int serv_socket;

        Server(int domain, int socktype, int protocol, int port, unsigned long address, int backlog);
        void launch();
};

#endif
