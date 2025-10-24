#ifndef CLIENT_H
#define CLIENT_H

#include<sys/socket.h>
#include<netinet/in.h>

class Client{
    public:
        int domain;
        int socktype;
        int protocol;
        int port;
        unsigned long address;

        int cli_socket;

        struct sockaddr_in serv_address;

        Client(int domain, int socktype, int protocol, int port, unsigned long address);
        void make_request();
};

#endif
