//client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PROT 8888
void process_conn_client(int s){
    ssize_t size = 0;
    char buffer[1024];
    for(;;){
        size = read(0,buffer,1024);
        if(size>0){
            write(s,buffer,size);
            size = read(s,buffer,1024);
            write(1,buffer,size);
        }
    }
}
int main(void){
    int s;
    struct sockaddr_in server;
    int err;
    s = socket(AF_INET,SOCK_STREAM,0);
    //create socket 
    if(s<0){
        printf("create socket error!");
        exit(-1);
    }
    //set sockaddr_in to 0
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PROT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);
    //connect
    connect(s,(struct sockaddr*)&server,sizeof(struct sockaddr));
    process_conn_client(s);
    close(s);
}