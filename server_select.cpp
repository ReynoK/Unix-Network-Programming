#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <iostream>
using namespace std;
#define PORT 8888
#define MAXSIZE 255

int main(){
	int serverSocket,clientSocket,sockfd;
	int result;
	int maxfd;
	int clients[FD_SETSIZE];
	int maxi;
	int i,n;
	char buf[MAXSIZE];
	fd_set rdset,allset;
	int nready;
	struct sockaddr_in sockaddr,clientaddr;
	socklen_t addrLen;
	serverSocket = socket(AF_INET,SOCK_STREAM,0);
	if(serverSocket<0)
		perror("socket error:");

	//set sockaddr_in
	bzero(&sockaddr,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT);
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind address
	if( bind(serverSocket,(struct sockaddr*)&sockaddr,sizeof(sockaddr)) <0 )
		perror("bind error:");

	//listen set 
	if(listen(serverSocket,20) < 0)
		perror("listen error:");

	maxfd = serverSocket;
	//reset clients
	for(auto &item : clients)
		item = -1;
	maxi = -1; //index into clients[] array

	FD_ZERO(&allset);
	FD_SET(serverSocket,&allset);

	
	//start server
	while(1){
		rdset = allset;	//allset is use to record foregoing fdset
		nready = select(maxfd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(serverSocket,&rdset)){
			addrLen = sizeof(sockaddr);
			cout<<"start listen"<<endl;
			clientSocket = accept(serverSocket,(struct sockaddr*)&clientaddr,&addrLen);
			//save clientSocket into clients array
			for(i=0;i<FD_SETSIZE;i++)
				if(clients[i]<0){
					clients[i]=clientSocket;
					break;
				}
			//to many client
			if(i == FD_SETSIZE){
				cout<<"too many clients"<<endl;
				exit(-1);
			}
			FD_SET(clientSocket,&allset);
			if(i>maxi)
				maxi = i;	//new socket is max index in client[] array
			//clientSocket is maxfd?
			if(maxfd<clientSocket)
				maxfd = clientSocket;

			if((--nready) <= 0)	//no anthor descriptor
				continue;
		}

		for(i=0;i<=maxi;i++){
			if((sockfd=clients[i])<0)
				continue;
			if(FD_ISSET(sockfd,&rdset)){
				if((n=read(sockfd,buf,MAXSIZE))==0){
					close(sockfd);
					FD_CLR(sockfd,&allset); //delete descriptor from allset 
					clients[i]=-1;
				}else{
					write(sockfd,buf,n);
				}
				if((--nready)<=0)
					break;		//no more readable descriptor
			}
		}
	}
}