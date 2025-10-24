#include<iostream>
#include<unistd.h>
#include"client.h"

using namespace std;

void Client::make_request(){
    if(connect(cli_socket,(struct sockaddr*)&serv_address, sizeof(serv_address)) < 0){
        //handle error
        cerr<<"Error connecting to server...\n";
        exit(1);
    }
    
    char buffer[1000];
    string msg = "Hello from client!";

        send(this->cli_socket,msg.c_str(),msg.length(),0);
        recv(this->cli_socket,buffer,1000,0);
        cout<<"Server said:\n"<<buffer<<endl;
        close(cli_socket);

}
int main(){
    Client cli(AF_INET, SOCK_STREAM,0,80,INADDR_ANY);
    cli.make_request();
    return 0;
}
