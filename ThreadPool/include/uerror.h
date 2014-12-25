#ifndef UERROR_H
#define UERROR_H
#include <cstdio>

void errQuit(char *msg){
	perror(msg);
	exit(-1);
}
#endif