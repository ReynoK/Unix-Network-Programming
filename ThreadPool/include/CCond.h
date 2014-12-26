#ifndef CCOND_H
#define CCOND_H
#include <pthread.h>
#include <CMutex.h>

//define cond by self

class CCond{
public:
	CCond();
	~CCond();
	void wait(unsigned int val=0);
	void signal();
private:
	pthread_cond_t m_cond;
	pthread_mutex_t m_mutex;
};
#endif 