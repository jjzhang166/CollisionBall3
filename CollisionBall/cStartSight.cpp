#include "stdafx.h"
#include "cStartSight.h"
#include<cGameEngine.h>
#include"cGameSight.h"
#include"cBackHole.h"
#include<random>
#include<Tool.h>
using namespace MyEngine;

cStartSight::cStartSight()
{
	MyEngine::SIZE size = cGameEngine::GetEngine()->GetClientSize();
	m_Title = new cText("碰撞球");
	m_Title->SetTextColor(RGB(0,255,0));
	m_Title->SetFontWidth(35);
	m_Title->SetFontHeight(70);
	m_Title->SetX(size.width*0.17);
	m_Title->SetY(size.height*0.1);
	m_Bg =new cPicture("startBg");
	m_Bg->SetX(0);
	m_Bg->SetY(0);
	m_EntryBtn = new cButton("Entry");
	m_EntryBtn->SetX(size.width*0.2);
	m_EntryBtn->SetY(size.height*0.3);
	m_QuitBtn = new cButton("Quit");
	m_QuitBtn->SetX(size.width*0.2);
	m_QuitBtn->SetY(size.height*0.45);
	m_circle = new cCircle(POINT{ 400,250 }, 65);
	m_circle->SetIsFill(true);
	m_circle->SetLineColor(RGB(233, 90, 5));
	m_circle->SetFillColor(RGB(128, 0, 128));
	m_circle1 = new cCircle(POINT{ 100,300},50);
	m_circle1->SetIsFill(true);
	m_circle1->SetLineColor(RGB(233, 90, 5));
	m_circle1->SetFillColor(RGB(0, 0, 0));
	addChild(m_Bg);
	addChild(m_circle);
	addChild(m_circle1);
	addChild(m_Title);
	addChild(m_EntryBtn);
	addChild(m_QuitBtn);
	cBackHole* pBackHoe = new cBackHole;
	pBackHoe->SetAmination("BackHole");
	pBackHoe->SetX(200);
	pBackHoe->SetY(300);
	pBackHoe->SetIsLucnecy(true);
	pBackHoe->SetLucnecyColor(RGB(255, 255, 255));
	addChild(pBackHoe);
	cGameEngine::GetEngine()->AddEventToUi(m_EntryBtn, WM_LBUTTONUP,_CALLFUNC(cStartSight::OnEntryGame),this);
	cGameEngine::GetEngine()->AddEventToUi(m_QuitBtn, WM_LBUTTONUP, _CALLFUNC(cStartSight::OnQuit), this);
	AddTimer(1, 10);
}

cStartSight::~cStartSight()
{
}

void cStartSight::OnEntryGame(void * Param)
{
	cGameSight* pGameSight = new cGameSight;
	if (pGameSight->ConnectSever("192.168.156.1") == true)
	{
		cGameEngine::GetEngine()->DeleteUI(this);
		pGameSight->initSight();
		cGameEngine::GetEngine()->AddEngineUi(pGameSight);
	}
	else
	{
		MessageBox(NULL, L"连接服务器失败!", L"恶意的提示", MB_OK);
		delete pGameSight;
		pGameSight= nullptr;
	}
}

void cStartSight::OnQuit(void * Param)
{
	PostQuitMessage(0);
}

int cStartSight::OnTimer(int id, int iParam, string str)
{
	MoveCircle();
	return 1;
}

void cStartSight::MoveCircle()
{
	random_device rad;
	MyEngine::SIZE size = cGameEngine::GetEngine()->GetClientSize();
	static int vx = rad() % 3 + 1;
	static int vy = rad() % 3 + 1;
	static int vx1 = -(rad() % 3 + 1);
	static int vy1 = rad() % 3 + 1;
	int len = PointToPointDistance(m_circle->GetCenter(), m_circle1->GetCenter());
	if (len< (m_circle->GetRadius() + m_circle1->GetRadius()))
	{
		vx = -vx;
		vy=-vy;
		vx1=-vx1;
		vy1=-vy1;
	}
	m_circle->GetX() < 0 ? vx = rad() % 3 + 1 : m_circle->SetX(m_circle->GetX() + vx);
	m_circle->GetX() > size.width ? vx = -(rad() % 3 + 1) : m_circle->SetX(m_circle->GetX() + vx);
	m_circle->GetY() < 0 ? vy = rad() % 3 + 1 : m_circle->SetY(m_circle->GetY() + vy);
	m_circle->GetY() > size.height ? vy = -(rad() % 3 + 1) : m_circle->SetY(m_circle->GetY() + vy);
	m_circle1->GetX() < 0 ? vx1 = rad() % 3 + 1 : m_circle1->SetX(m_circle1->GetX() + vx1);
	m_circle1->GetX() > size.width ? vx1 = -(rad() % 3 + 1) : m_circle1->SetX(m_circle1->GetX() + vx1);
	m_circle1->GetY() < 0 ? vy1 = rad() % 3 + 1 : m_circle1->SetY(m_circle1->GetY() + vy1);
	m_circle1->GetY() > size.height ? vy1 = -(rad() % 3 + 1) : m_circle1->SetY(m_circle1->GetY() + vy1);
}
