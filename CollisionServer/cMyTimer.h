#pragma once
#include <string>
#include <list>
#include<thread>
#include<Lock.h>
using namespace std;

struct stTimer
{
	unsigned id;//id号
	unsigned timeElapse;	//定时器运行的间隔时间
	unsigned timeLastRun;	//定时器上次运行的时间
	int iParam;				//预留参数
	string strParam;		//预留参数
	bool bDel;				//是否要被删除
	stTimer()
	{
		timeElapse = 0;
		timeLastRun = 0;
		id = 0;
		iParam = 0;
		bDel = false;
	}
};

typedef list<stTimer> TimerList;
typedef list<stTimer>::iterator itTimerLisst;

class cMyTimer
{
public:
	cMyTimer();
	virtual ~cMyTimer();
	//添加定时器
	void AddTimer(unsigned timeId,unsigned timeElapse,int param = 0,char* p = NULL);

	//删除定时器
	void DeleteTimer(unsigned id);

	//定时器逻辑处理
	//返回的值就是该定时器新的间隔时间
	virtual int OnTimer(int id,int iParam,string str) = 0;

	//检测是否有定时器需要删除
	void CheckDelTimer();

	//检测并运行定时器
	void TimerRun();

	bool QuitThread();
private:
	void OnThread();

	TimerList m_timerList;	//保存所有定时器

	bool m_isClose;

	thread* m_pThread;

	Net::CLock m_lock;
};