#include "CThreadPool.h"
#include <algorithm>
#include <iostream>

using namespace std;

CThreadPool::CThreadPool(unsigned int initNum):m_curNum(initNum),
												m_initNum(initNum)
{	//清理忙列表和闲置列表
	m_busyList.clear();
	m_idleList.clear();
	createThread(initNum);
}

CThreadPool::~CThreadPool(){

}

//创建线程
void CThreadPool::createThread(unsigned int num){
	for(int x=0;x<=num;x++){
		CWorkThread * newThread = new CWorkThread();
		newThread->setThreadPool(this);
		m_idleList.push_back(newThread);
		m_curNum++;
	}
}

void CThreadPool::destroy(){

}

//
void CThreadPool::moveToBusyList(CWorkThread * thread){
	m_busyMutex.lock();
	m_busyMutex.unlock();
}
//将线程移到闲置队列中
void CThreadPool::moveToIdleList(CWorkThread * thread){
	m_busyMutex.lock();
	auto item = find(m_busyList.begin(),m_busyList.end());
	if(item!=m_busyList.end())			//寻找线程所在位置
		m_busyList.earse(item);
	else{								//出错
		cout<<"moveToIdleList error!"<<endl;
		exit(-1);
	}
	m_busyMutex.unlock();

	m_idleMutex.lock();
	m_idleList.push_back(thread);
	//have something for example over maxIdleNum
	
	m_idleMutex.unlock();
}