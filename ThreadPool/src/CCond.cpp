#include <CCond.h>
#include <sys/time.h>
#include "uerror.h"

CCond::CCond():m_mutex(PTHREAD_MUTEX_INITIATIZER),
				m_cond(PTHREAD_COND_INITIALIZER){

}

CCond::~CCond(){
//静态分配，无需destroy
}

//当val为0时，表示无限时间阻塞，不为0时，表示有时间的阻塞
void CCond::wait(unsigned int val){
	pthread_mutex_lock(&m_mutex);
	if(val == 0)
		pthread_cond_wait(&m_cond,&m_mutex);
	else{
		struct timeval tv;
		if(gettimeofday(&tv,&ts)<0)
			errQuit("gettimeofday error:");
		tv.tv_sec += val;
		pthread_cond_timewait(&m_cond,&m_mutex);
	}	
	pthread_mutex_unlock(&m_mutex);
}

void CCond::signal(){
	pthread_cond_signal(&m_cond);
}
