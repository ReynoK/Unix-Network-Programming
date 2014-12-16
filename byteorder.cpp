#include <iostream>
#include <unistd.h>
using namespace std;

typedef union{
	short s;
	char c[sizeof(s)];
}bytes;

int main(){
	bytes test;
	test.s = 0x0102;
	if(sizeof(short) == 2){
		if(test.c[0]==2&&test.c[1]==1)
			cout<<"Little-endian"<<endl;
		else if(test.c[0]==1&&test.c[1]==2)
			cout<<"Big-endian"<<endl;
		else 
			cout<<"unknow"<<endl;
	}else
		cout<<"sizeof(short):"<<sizeof(short)<<endl;
	return 0;
}