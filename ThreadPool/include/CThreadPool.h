#ifndef CTHREADPOOL_H
#define CTHREADPOOL_H
#include <vector.h>
#include <list.h>
#include "CWorkThread.h"
#include "CMutex.h"
#include "CCond.h"

using namespace std;
//defien threadpool
class CThreadPool{
public:
	CThreadPool(unsigned int initNum=10);
	~CThreadPool();
	void createThread(unsigned int num);
	void destroy();
	void run();
	void moveToBusyList(CWorkThread * thread);
	void moveToIdleList(CWorkThread * thread);
	void deleteIdleList(unsigned int num);
	CWorkThread * getaIdleThread();
private:
	list<CWorkThread*> m_busyList;
	list<CWorkThread*> m_idleList;

	unsigned int m_initNum;
	static const unsigned int m_maxIdleNum=30;
	static const unsigned int m_minIdleNum=5;
	static const unsigned int m_maxNum=40;		
	
	CMutex m_busyMutex;
	CMutex m_idleMutex;
	CMutex m_varMutex;

	CCond m_idleCCond;
};

#endif 