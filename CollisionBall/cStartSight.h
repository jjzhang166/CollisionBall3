#pragma once
#include<cSight.h>
#include<cPicture.h>
#include<cButton.h>
#include<cText.h>
#include<cCircle.h>

class cStartSight:public MyEngine::cSight
{
public:
	cStartSight();
	virtual ~cStartSight();

	/*
	*进入游戏按钮回调函数
	*/
	void OnEntryGame(void* Param);

	/*
	*退出游戏按钮回调函数
	*/
	void OnQuit(void* Param);

	/*
	*重写定时器回调函数
	*/
	virtual int OnTimer(int id, int iParam, string str) override;

	/*
	*MoveCircle();
	*移动圆
	*/
	void MoveCircle();
private:
	MyEngine::cPicture* m_Bg;
	MyEngine::cButton* m_EntryBtn;
	MyEngine::cButton* m_QuitBtn;
	MyEngine::cText* m_Title;
	MyEngine::cCircle* m_circle;
	MyEngine::cCircle* m_circle1;
};

