#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define SIZE 10

int main(){
    int ret;
    char buf[SIZE]="";
    int readLen;
    fd_set rd_set;
    struct timeval waittime;
    waittime.tv_sec = 5;
    waittime.tv_usec = 50;
    while(1){
        FD_ZERO(&rd_set);   //reset rd_set
        FD_SET(0,&rd_set);
        waittime.tv_sec = 5;    //each call reset struct timeval,to prevet timeval modefied by select
        waittime.tv_usec = 50;
        ret = select(1,&rd_set,NULL,NULL,&waittime);
        if(ret<0)   //error
            cout<<"select error!"<<endl;
        else if(ret==0){    //time out
            cout<<"time out!"<<endl;
        }
        else if(FD_ISSET(0,&rd_set)){
            readLen = read(0,buf,SIZE);
	    if(readLen<0)
		continue;
	    else if(readLen==0)
		break;
            write(1,buf,readLen);
        }
    }   
}
