#include"client.h"
#include<iostream>

using namespace std;

Client::Client(int domain, int socktype, int protocol, int port, unsigned long address){
    this->domain = domain;
    this->socktype = socktype;
    this->protocol = protocol;
    this->port = port;
    this->address = address;

    this->cli_socket = socket(domain, socktype, protocol);
    if(cli_socket < 0){
        //handle error
    }

    this->serv_address.sin_family = domain;
    this->serv_address.sin_port = htons(port);
    this->serv_address.sin_addr.s_addr = address;
    
}
