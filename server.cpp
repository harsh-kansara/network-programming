#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

using namespace std;

int main(){
    //socket()
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //sockaddr structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //bind()
    bind(sockfd, (struct sockaddr*)&serverAddr,sizeof(serverAddr));

    //listen()
    listen(sockfd,4);

    //accept()
    int client_sock = accept(sockfd, nullptr, nullptr);

    //server and client
    while(1){
        char buffer[1024] = {0};
        recv(client_sock, buffer, sizeof(buffer),0);
        cout<<"Client: "<<buffer<<endl;
    
        char op_buffer[1024];
        cout<<"Me: ";
        string message;
        getline(cin,message);
        memset(&op_buffer,0,sizeof(op_buffer));
        strcpy(op_buffer,message.c_str());
        send(client_sock, (char*)op_buffer, strlen(op_buffer),0);
        
    }
    //close
    close(sockfd);
    return 0;
}
