#ifndef CMUTE_H_
#define CMUTE_H_

#include <pthread.h>
class CMutex{
public:
	CMutex();
	virtual ~CMutex();
	void lock();
	void unlock();
private:
	pthread_mutex_t mutex;
};

#endif 