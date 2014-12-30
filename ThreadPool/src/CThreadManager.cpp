#include "CThreadManager.h"

CthreadManager::CthreadManager():m_threadPool(new CThreadPool()){

}

CthreadManager::~CthreadManager(){
	if(m_threadPool)
		delete m_threadPool;
}

void CthreadManager::run(CJob * job,void * params){
	if(m_threadPool){
		m_threadPool->run(job,params);
	}
}