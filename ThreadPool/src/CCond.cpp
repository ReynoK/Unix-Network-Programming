#include <CCond.h>

CCond::CCond():m_mutex(PTHREAD_MUTEX_INITIATIZER),
				m_cond(PTHREAD_COND_INITIALIZER){

}

CCond::~CCond(){
//静态分配，无需destroy
}

void CCond::wait(){
	pthread_mutex_lock(&m_mutex);
	pthread_cond_wait(&m_cond,&m_mutex);
	pthread_mutex_unlock(&m_mutex);
}

void CCond::signal(){
	pthread_cond_signal(&m_cond);
}
