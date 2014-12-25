#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H
#include <vector.h>
#include <list.h>
#include "CWorkThread.h"
#include "CMutex.h"

using namespace std;
//defien threadpool
class CThreadPool{
public:
	CThreadPool(unsigned int initNum=10);
	~CThreadPool();
	createThread(unsigned int num);
	destroy();
	moveToBusyList(CWorkThread * thread);
	moveToIdleList(CWorkThread * thread);

private:
	list<CWorkThread*> m_busyList;
	list<CWorkThread*> m_idleList;

	unsigned int m_initNum;
	unsigned int m_maxIdleNum=20;
	unsigned int m_minIdleNum=5;
	unsigned int m_maxNum=40;
	unsigned int m_IdleNum=0;

	CMutex m_busyMutex;
	CMutex m_idleMutex;
};

#endif 