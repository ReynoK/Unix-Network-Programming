#ifndef CWORKTHREAD_H
#define CWORKTHREAD_H
#include "Cjob.h"
#include "CCond.h"
#include "CThreadPool.h"

//工作线程
class CWorkThread{
public:
	CWorkThread();
	virtual ~CWorkThread();
	void start(void*);
	void run();				//运行工作线程	
	void setJob(CJob*job);	//设置任务
	Cjob*getJob();
	void join();
	unsigned int getThreadID();
	void setThreadPool(CThreadPool * threadPool);
protected:
private:
	pthread_t  m_threadID;	//线程程ID
	void * m_jobParams;
	CCond m_cond;		//条件变量
	bool m_isStop;
	CThreadPool m_threadPool;
};

#endif 
