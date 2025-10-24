#include"../modular/client.h"
#include<unistd.h>
#include<iostream>
#include<sys/select.h>
#include<cstring>

using namespace std;

void Client::make_request(){
    if(connect(cli_socket,(struct sockaddr*)&serv_address, sizeof(serv_address)) < 0){
        //handle error
        cerr<<"Cannot connect to the chat room...\n";
        exit(1);
    }
    
    cout<<"Connected\n";
    fd_set readfs;
    char buffer[1000];


    while(1){
        FD_ZERO(&readfs);
        FD_SET(STDIN_FILENO, &readfs);
        FD_SET(cli_socket,&readfs);
        int maxfd = max(STDIN_FILENO, cli_socket);
    
        if(select(maxfd+1,&readfs,NULL,NULL,NULL)<0){
            cerr<<"select error\n";
            break;
        }

        if(FD_ISSET(STDIN_FILENO,&readfs)){
            //std input read user's message from input
            string msg;
            getline(cin,msg);
            write(cli_socket,msg.c_str(),msg.length());
        }

        if(FD_ISSET(cli_socket,&readfs)){
            //message arrived from other users
            memset(buffer,0,sizeof(buffer));
            int bytes_read = read(cli_socket,buffer,1000);
            if(bytes_read<=0){
                cout<<"Server disconnected\n";
                break;
            }
            cout<<buffer<<endl;
        }
    }
    
    close(cli_socket);

}

int main(){
    Client client(AF_INET, SOCK_STREAM,0,8055,INADDR_ANY);
    client.make_request();
    return 0;
}
