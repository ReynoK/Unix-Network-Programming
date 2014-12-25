#ifndef CMUTE_H_
#define CMUTE_H_

#include <pthread.h>
class CMutex{
public:
	CMutex();
	virtual ~CMutex();
	void lock();
	void unlock();
	pthread_mutex_t getMutex();
private:
	pthread_mutex_t m_mutex;
};

#endif 