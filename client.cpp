#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<unistd.h>

using namespace std;

int main(){
    
    //socket()
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //address structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //connect()
    connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    //send and receive
    while(1){
        char op_buffer[1024];
        cout<<"Me: ";
        string message;
        getline(cin,message);
        memset(&op_buffer,0,sizeof(op_buffer));
        strcpy(op_buffer,message.c_str());
        send(sockfd, (char*)&op_buffer, strlen(op_buffer),0);

        char ip_buffer[1024] = {0};
        recv(sockfd, ip_buffer, sizeof(ip_buffer),0);
        cout<<"Server: "<<ip_buffer<<endl;
    }

    //close()
    close(sockfd);
    return 0;
}
