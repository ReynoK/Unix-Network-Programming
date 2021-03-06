#include "CThreadPool.h"
#include <algorithm>
#include <iostream>

using namespace std;

CThreadPool::CThreadPool(unsigned int initNum):m_initNum(initNum)
{	//清理忙列表和闲置列表
	m_busyList.clear();
	m_idleList.clear();
	createThread(initNum);
}

CThreadPool::~CThreadPool(){
	destroy();

}

//创建线程
void CThreadPool::createThread(unsigned int num){
	for(int x=0;x<num;x++){
		CWorkThread * newThread = new CWorkThread();
		newThread->setThreadPool(this);
		m_idleList.push_back(newThread);
	}
	m_varMutex.lock();
	cout<<"创建"<<m_idleList.size()<<"个线程完毕"<<endl;
	m_varMutex.unlock();

}
//
void CThreadPool::destroy(){
	for(auto &item:m_busyList)
		item->join();
	for(auto &item:m_idleList){
		item->join();
		delete item;
	}
}

//将线程移到忙队列中
void CThreadPool::moveToBusyList(CWorkThread * thread){
	//修改闲置队列，先从闲置队列中删除线程
	m_idleMutex.lock();
	auto item = find(m_idleList.begin(),m_idleList.end(),thread);
	if(item!=m_idleList.end())
		m_idleList.earse(item);
	else{
		cout<<"moveToBusyList error!"<<endl;
		exit(-1);
	}
	if(m_idleList.size()<m_minIdleNum){
		if(m_maxIdleNum+m_busyList.size()<=m_maxNum)
			createThread(m_maxIdleNum-m_idleList.size());	//扩展到最大限制闲置数列
		else
			createThread(m_maxNum-m_busyList.size()-m_idleList.size());
	}
	m_idleMutex.unlock();
	//修改忙队列，将线程加到忙队列中
	m_busyMutex.lock();
	m_busyList.push_back(thread);
	m_busyMutex.unlock();
}
//将线程移到闲置队列中
void CThreadPool::moveToIdleList(CWorkThread * thread){
	// //修改忙队列，先从忙队列中删除线程
	// m_busyMutex.lock();
	// auto item = find(m_busyList.begin(),m_busyList.end());
	// if(item!=m_busyList.end())			//寻找线程所在位置
	// 	m_busyList.earse(item);
	// else{								//出错
	// 	cout<<"moveToIdleList error!"<<endl;
	// 	exit(-1);
	// }
	// m_busyMutex.unlock();
	//修改闲置队列，将线程加入到闲置队列中
	m_idleMutex.lock();
	m_idleList.push_back(thread);
	if(m_idleList.size()>m_maxIdleNum)
		deleteIdleList(m_maxIdleNum-m_idleList.size())
	m_idleMutex.unlock();
	m_idleCCond.signal();				//唤醒正在等待空闲进程的队列
}

//删除闲置线程
void CThreadPool::deleteIdleList(unsigned int num){
	unsigned int deleteNum = num>m_idleList?m_idleList:num;
	cout<<"准备删除"<<deleteNum<<"个闲置线程"<<endl;
	// m_idleMutex.lock();						//对闲置线程队列加锁
	CWorkThread * temp = NULL;
	for(int i=0;i<deleteNum;i++){
		auto item = m_idleList.begin();		//获得闲置队列的首元素
		temp = *item;
		m_idleList.earse(item);		
		delete temp;						//delete闲置线程，防止内存泄漏
		temp = NULL;
	}
	// m_idleMutex.unlock();					//对闲置线程队列解锁
	cout<<"删除完毕"<<endl;
}

//运行线程池
void CThreadPool::run(CJob * job,void * params){
	CWorkThread * workThread = getaIdleThread();
	if(NULL!=workThread){
		moveToBusyList(workThread);
		workThread->setJob(job,params);
	}
}
//获得可用线程
CWorkThread * CThreadPool::getaIdleThread(){
	//在获得可用线程时，已经从闲置线程队列中删除，所以在放到忙队列时，无需在从闲置队列中删除
	if( m_idleList.size()==0)	//当忙线程数量到达最大数
		m_idleCCond.wait()
	m_idleMutex.lock();
	if(m_idleList.size()>0){
		CWorkThread * thread = m_idleList.pop_front();
		m_idleMutex.unlock();
		return thread;
	}else{
		m_idleMutex.unlock();
		return NULL;
	}
}
