#ifndef CTHREADMANAGER_H
#define CTHREADMANAGER_H

#include <CThreadPool.h>

class CthreadManager{
public:
	CthreadManager();
	~CthreadManager();
	run(CJob * job,void * params);
private:
	CThreadPool * m_threadPool
};

#endif