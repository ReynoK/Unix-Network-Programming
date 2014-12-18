//server.c
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#define PROT 8888
void process_client_connect(int client_socket);
int main(void){
    //create server socket 
    struct sockaddr_in server_addr;
    //create client socket
    struct sockaddr_in client_addr;
    int pid = 0;
    int server_socket,client_socket;
    int err;
    server_socket = socket(AF_INET,SOCK_STREAM,0);
    if( server_socket<0 ){
        printf("socket error!\n");
        exit(-1);
    }
    //set sockaddr_in to 0
    bzero(&server_addr,sizeof(server_addr));
    //set sockaddr_in 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PROT);                    //bind to port 8888
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);        //bind any ip
    //bind address and port 
    err = bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(err < 0){
        printf("bind error!\n");
        exit(-1);
    }
    //create listen
    err = listen(server_socket,2);
    if(err<0){
        printf("lister error!\n");
        exit(-1);
    }
    for(;;){
        int addlen = sizeof(struct sockaddr);
        client_socket = accept(server_socket,(struct sockaddr*)&client_addr,(socklen_t*)&addlen);
        if(client_socket<0){
            continue;
        }
        //create cholid proccessing
        pid = fork();
        if(pid==0){
            close(server_socket);
            process_client_connect(client_socket);
        }
        else{
            close(client_socket);
        }
    }
}
void process_client_connect(int client_socket){
    ssize_t size = 0;
    char buffer[1024];
    for(;;){
        size = read(client_socket,buffer,1024);
        if(size == 0){
            printf("server-connetc down");
            return;
        }
        sprintf(buffer,"%d bytes altogether\n",size);
        write(client_socket,buffer,strlen(buffer)+1);
    }
}