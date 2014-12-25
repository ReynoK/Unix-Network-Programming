#include "../include/CMutex.h"
#include <iostream>
using namespace std;

CMutex::CMutex(){
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutex_init(&m_mutex,&attr);
}

CMutex::~CMutex(){
	pthread_mutex_destroy(&m_mutex);
}

void CMutex::lock(){
	pthread_mutex_lock(&m_mutex);
}

void CMutex::unlock(){
	pthread_mutex_unlock(&m_mutex);
}

pthread_mutex_t CMutex::getMutex(){
	return this->m_mutex;
}