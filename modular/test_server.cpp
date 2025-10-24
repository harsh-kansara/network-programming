#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>
#include"server/server.h"

using namespace std;

void Server::launch(){
    //accept
    char buffer[1000];
    struct sockaddr_in client_addr;
    int client,address_length = sizeof(client_addr);
    string msg = "HTTP/1.1 200 OK\r\n Content-Type: text/html; charset=UTF-8\r\n Content-Length: 128\r\n Server: MySimpleCppServer/1.0\r\n\r\n <!DOCTYPE html>"
                "<html>"
                "<head><title>Welcome</title></head>"
                "<body>"
                "<h1>Hello from the C++ Server!</h1>"
                "<p>This is a sample page.</p>"
                "</body>"
                "</html>";
    while(1){
        client = accept(serv_socket,(struct sockaddr*)&client_addr,(socklen_t*)&address_length);
        if(client<0){
            cerr<<"Failed to accept connection\n";
            continue;
        }
        read(client, buffer, 1000);
        cout<<"Client connected from: "<<inet_ntoa(client_addr.sin_addr)<<":"<<ntohs(client_addr.sin_port)<<'\n';
        cout<<"Request:\n"<<buffer<<'\n';
        write(client,msg.c_str(),(size_t)msg.length());
        close(client);
    }
}

int main(){
    Server serv(AF_INET,SOCK_STREAM,0,80,INADDR_ANY,5);
    serv.launch();
    return 0;
}

