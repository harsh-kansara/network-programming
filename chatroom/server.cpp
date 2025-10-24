#include"../modular/server/server.h"
#include<unistd.h>
#include<arpa/inet.h>
#include<iostream>
#include<map>
#include<sys/select.h>
#include<cstring>

using namespace std;

void Server::launch(){
    char buffer[1000];
    map<int, sockaddr_in> connections;
    struct sockaddr_in client_address;
    int client,cliaddr_length = sizeof(client_address);
    cout<<"Chat room is live, waiting for people to join\n";

    fd_set readfs;

    while(1){
        FD_ZERO(&readfs);
        FD_SET(serv_socket, &readfs);
        int max_fd = serv_socket;

        for(auto &each: connections){
            FD_SET(each.first, &readfs);
            max_fd = max(each.first, max_fd);
        }

        if(select(max_fd+1, &readfs,NULL,NULL,NULL) < 0){
            cerr<<"select() error\n";
            continue;
        }

        if(FD_ISSET(serv_socket,&readfs)){
            //new connection aya    
            client = accept(serv_socket,(struct sockaddr*)&client_address,(socklen_t *)&cliaddr_length);
            if(client<0){
                cerr<<"Failed to accept connection...\n";
                continue;
            }
            connections[client] = client_address;
            cout<<inet_ntoa(client_address.sin_addr)<<":"<<ntohs(client_address.sin_port)<<" just joined! "<<connections.size()<<" person(s) in the room\n";
        }

        for(auto it=connections.begin();it!=connections.end();){
            if(FD_ISSET(it->first,&readfs)){
                memset(buffer,0,sizeof(buffer));
                int bytes_read = read(it->first, buffer, 1000);
                if(bytes_read<=0){
                    cout<<"Client disconnected: "<<it->first<<endl;
                    close(it->first);
                    it = connections.erase(it);
                    if(connections.empty()) cout<<"Nobody's in the room\n";
                    continue;
                }
                string msg = string(inet_ntoa(it->second.sin_addr)) + ":" + to_string(ntohs(it->second.sin_port)) + " says=" + buffer;
                for(auto &[cli, addr]:connections){
                    if(cli!=it->first){
                        write(cli,msg.c_str(),msg.length());
                    }
                }
            }
            ++it;
        }

    }
    for(auto &each: connections){
        close(each.first);
    }
    close(serv_socket);
}

int main(){
    Server server(AF_INET, SOCK_STREAM,0,8055,INADDR_ANY,5);
    server.launch();
    return 0;
}
