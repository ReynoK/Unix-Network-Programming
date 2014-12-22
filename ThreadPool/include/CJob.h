#ifndef CJOB_H
#define CJOB_H
#include <string>
using namespace std;

class CJob{
public:
	CJob(string name=""):name(name){}
	virtual void run(void * params)=0;
	string getName();
	void setName(string name);
private:
	string name;
};
#endif