#include<iostream>
#include "server.h"

using namespace std;

Server::Server(int domain, int socktype, int protocol, int port, unsigned long address, int backlog){
    this->domain = domain;
    this->socktype = socktype;
    this->protocol = protocol;
    this->port = port;
    this->address = address;
    this->backlog = backlog;

    this->serv_socket = socket(domain, socktype, protocol);
    if(serv_socket<0){
        cerr<<"Failed to \n";
        exit(1);
    }

    this->sock_address.sin_family = domain;
    this->sock_address.sin_port = htons(port);
    this->sock_address.sin_addr.s_addr = address;
    int test = bind(serv_socket, (struct sockaddr*)&sock_address, sizeof(sock_address));
    if(test < 0){
        cerr<<"Failed to bind...\n"<<test<<"\n";
        exit(1);
    }

    if(listen(serv_socket, backlog) < 0){
        cerr<<"Failed to listen for connections...\n";
        exit(1);
    }
    
    cout<<"Server listening on socket...\n";
}
