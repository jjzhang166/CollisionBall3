#include "stdafx.h"
#include "resource.h"
#include"TheAgency.h"
#include"cStartSight.h"
#include<cGameEngine.h>
#include<cResourcePool.h>
#include<Tool.h>
using namespace MyEngine;
#pragma comment(lib,"UiEngine.lib")

cTheAgency::cTheAgency(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	PreInit();
	cGameEngine::GetEngine()->init(hInstance);
	AfterInit();
	cGameEngine::GetEngine()->LuanchEngine();
}

cTheAgency::~cTheAgency()
{
}

void cTheAgency::PreInit()
{
	LoadResource();
	cGameEngine::GetEngine()->SetTitle(L"Åö×²Çò");
	HCURSOR hCursor = LoadCursor(m_hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	cGameEngine::GetEngine()->SetCursor(hCursor);
	HICON hicon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON1));
	cGameEngine::GetEngine()->SetIcon(hicon);
}

void cTheAgency::AfterInit()
{
	WndBount wn = GetWindowBount(cGameEngine::GetEngine()->GethWnd());
	cGameEngine::GetEngine()->CenterWindow(SCREENSIZEX + wn.xBount, SCREENSIZEY + wn.yBount);
	LONG style = cGameEngine::GetEngine()->GetWndStyle();
	style &= ~WS_MAXIMIZEBOX;
	style &= ~WS_THICKFRAME;
	cGameEngine::GetEngine()->ChangeWndStyle(style);
	cStartSight* startSight = new cStartSight;
	cGameEngine::GetEngine()->AddEngineUi(startSight);
}

void cTheAgency::LoadResource()
{
	cResourcePool::GetResourcePool()->AddObjByKey("startBg", (HBITMAP)LoadImage(NULL,
		L"collisionBall/startBg.bmp", IMAGE_BITMAP, SCREENSIZEX, SCREENSIZEY, LR_LOADFROMFILE));
	cResourcePool::GetResourcePool()->AddObjByKey("Entry", (HBITMAP)LoadImage(NULL,
		L"collisionBall/EntryBtn.bmp", IMAGE_BITMAP, 100, 30, LR_LOADFROMFILE));
	cResourcePool::GetResourcePool()->AddObjByKey("Quit", (HBITMAP)LoadImage(NULL,
		L"collisionBall/QuitBtn.bmp", IMAGE_BITMAP, 100, 30, LR_LOADFROMFILE));
	cResourcePool::GetResourcePool()->AddObjByKey("GameBg", (HBITMAP)LoadImage(NULL,
		L"collisionBall/gameBg.bmp", IMAGE_BITMAP, SCREENSIZEX, SCREENSIZEY, LR_LOADFROMFILE));
	cResourcePool::GetResourcePool()->AddObjByKey("GoBack", (HBITMAP)LoadImage(NULL,
		L"collisionBall/goback.bmp", IMAGE_BITMAP, 30, 20, LR_LOADFROMFILE));
	cResourcePool::GetResourcePool()->AddObjByKey("MiniMap", (HBITMAP)LoadImage(NULL,
		L"collisionBall/miniMap.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	vector<HGDIOBJ> list;
	WCHAR Name[MAX_PATH] = { 0 };
	for (int i = 1; i <= 32; ++i)
	{
		wsprintf(Name, L"collisionBall/backhole/hole%d.bmp", i);
		list.push_back(LoadImage(NULL,Name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	}
	cResourcePool::GetResourcePool()->AddMulObjByKey("BackHole", list);
}
