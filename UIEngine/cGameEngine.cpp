#include "stdafx.h"
#include "cGameEngine.h"
#include"Tool.h"
using namespace std;
using namespace MyEngine;
#define TimerId 1
#define TimerDelay 18

//为控件分配Id
static UINT_PTR m_Uid = 0;

cGameEngine* g_pEngine = nullptr;

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETCURSOR:
	{
		HCURSOR hCursor = g_pEngine->GetCursor();
		SetCursor(hCursor);
	}
	break;
	case WM_LBUTTONDOWN:
		g_pEngine->DoMouseMsg(message);
		break;
	case WM_LBUTTONUP:
		g_pEngine->DoMouseMsg(message);
		break;
	case WM_KEYDOWN:
		g_pEngine->DoKeyMsg(message, wParam);
		break;
	case WM_KEYUP:
		g_pEngine->DoKeyMsg(message, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

MyEngine::SIZE cGameEngine::GetClientSize()
{
	RECT rect;
	GetClientRect(m_hWnd, &rect);
	SIZE Size;
	Size.width = rect.right - rect.left;
	Size.height = rect.bottom - rect.top;
	return Size;
}

Mouse_Status MyEngine::cGameEngine::GetMouseStatus()
{
	return m_mouseStatus;
}

ATOM MyEngine::cGameEngine::RegisterWinClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = m_hIcon; //LoadIcon(hInstance, L"");
	wcex.hCursor = m_hCursor;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = m_menuName;// MAKEINTRESOURCEW(IDC_COLLISIONBALL);
	wcex.lpszClassName = L"EngineClass";
	wcex.hIconSm = m_hIconSm;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassExW(&wcex);
}

bool MyEngine::cGameEngine::InitInstance()
{
	m_hWnd = CreateWindowW(L"EngineClass", m_title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

	if (!m_hWnd)
	{
		return true;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

HINSTANCE MyEngine::cGameEngine::GethInstance()
{
	return m_hInst;
}

void MyEngine::cGameEngine::SetCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
}

HCURSOR MyEngine::cGameEngine::GetCursor()
{
	return m_hCursor;
}

void MyEngine::cGameEngine::SetTitle(LPWSTR name)
{
	m_title = name;
}

LPWSTR MyEngine::cGameEngine::GetTitle()
{
	return m_title;
}

void MyEngine::cGameEngine::SetIcon(HICON hIcon)
{
	m_hIcon = hIcon;
}

HICON MyEngine::cGameEngine::GetIcon()
{
	return m_hIcon;
}

void MyEngine::cGameEngine::SetIconSm(HICON hIcon)
{
	m_hIconSm = m_hIconSm;
}

HICON MyEngine::cGameEngine::GetIconSm()
{
	return m_hIconSm;
}

void MyEngine::cGameEngine::SetMenuName(LPCWSTR name)
{
	m_menuName = name;
}

void MyEngine::cGameEngine::SetAccelTable(HACCEL hAccel)
{
	/*LoadAccelerators();*/
	m_hAccel = hAccel;
}

cGameEngine::cGameEngine()
{
	m_title = L"LSYENGINE";
	m_hInst = nullptr;
	m_hWnd = nullptr;
	m_menuName = NULL;
	m_hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_hIcon = LoadIcon(nullptr, IDC_ICON);
	m_hIconSm = nullptr;
	m_hAccel = nullptr;
	m_mouseStatus = Mouse_Up;
}

cGameEngine::~cGameEngine()
{
	m_lock.Lock();
	for (auto it : m_uiList)
	{
		delete it;
		it = nullptr;
	}
	m_uiList.clear();
	m_lock.UnLock();
	m_lock.Lock();
	m_evnetList.clear();
	m_lock.UnLock();
	cResourcePool::GetResourcePool()->ReleaseSelf();
}

void MyEngine::cGameEngine::DoMainMsg()
{
	
}

void MyEngine::cGameEngine::SafeAddUi(cBaseUI * ui)
{
	m_lock.Lock();
	m_uiList.push_back(ui);
	m_lock.UnLock();
}

cGameEngine* MyEngine::cGameEngine::GetEngine()
{
	if (g_pEngine == nullptr)
	{
		g_pEngine = new cGameEngine;
		return g_pEngine;
	}
	return g_pEngine;
}

void MyEngine::cGameEngine::init(HINSTANCE hInst)
{
	m_hInst = hInst;
	RegisterWinClass();
	InitInstance();
	DeleteTimer(TimerId);
	AddTimer(TimerId, TimerDelay);
}

int MyEngine::cGameEngine::LuanchEngine()
{
	MSG msg;

	while (GetMessage(&msg,nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, m_hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	ReleaseSelf();
	return msg.wParam;
}

int cGameEngine::OnTimer(int id, int iParam, string str)
{
	switch (id)
	{
	case TimerId:
		DrawUI();
		break;
	}
	return 1;
}

int cGameEngine::CenterWindow(int w, int h)
{
	if (w == 0 || h == 0)
	{
		RECT clientRect;
		GetClientRect(m_hWnd, &clientRect);
		w = clientRect.right - clientRect.left;
		h = clientRect.bottom - clientRect.top;
	}
	if (!MoveToCenter(m_hWnd,w,h))
	{
		m_wError = L"居中窗口失败";
		return -1;
	}
	return 0;
}

const LPWSTR & cGameEngine::GetLastError() const
{
	return m_wError;
}

cText * MyEngine::cGameEngine::CreateText(const string & text, const int & x, const int & y)
{
	cText* pText = new cText(text);
	pText->m_Uid = m_Uid++;
	pText->SetX(x);
	pText->SetY(y);
	m_lock.Lock();
	m_uiList.push_back(pText);
	m_lock.UnLock();
	return pText;
}

cLine * MyEngine::cGameEngine::CreateLine(const POINT & start, const POINT & end)
{
	cLine *pLine = new cLine;
	pLine->m_Uid = m_Uid++;
	pLine->SetStartPoint(start);
	pLine->SetEndPoint(end);
	SafeAddUi(pLine);
	return pLine;
}

cButton * MyEngine::cGameEngine::CreateButton(const LPWSTR & Name, const int & x, const int & y)
{
	cButton *pButton = new cButton;
	pButton->m_Uid = m_Uid++;
	pButton->SetName(Name);
	pButton->SetX(x);
	pButton->SetY(y);
	SafeAddUi(pButton);
	return pButton;
}

cButton * MyEngine::cGameEngine::CreateBitmapButton(const LPWSTR & bmpPath,const int& x, const int& y)
{
	cButton* pButton = new cButton(bmpPath);
	pButton->m_Uid = m_Uid++;
	pButton->SetX(x);
	pButton->SetY(y);
	SafeAddUi(pButton);
	return pButton;
}

cButton * MyEngine::cGameEngine::CreateBitmapButton(const HBITMAP & bitmap,const int& x, const int& y)
{
	cButton* pButton = new cButton(bitmap);
	pButton->m_Uid = m_Uid++;
	pButton->SetY(y);
	pButton->SetX(x);
	SafeAddUi(pButton);
	return pButton;
}

cButton * MyEngine::cGameEngine::CreateButtonByKey(std::string key)
{
	cButton* pButton = new cButton(key);
	pButton->m_Uid = m_Uid++;
	SafeAddUi(pButton);
	return pButton;
}

cCircle * MyEngine::cGameEngine::CreateCircle(const POINT& center, const UINT& radius)
{
	cCircle *pCirecle = new cCircle(center, radius);
	pCirecle->m_Uid = m_Uid++;
	SafeAddUi(pCirecle);
	return pCirecle;
}

cPicture * MyEngine::cGameEngine::CreatePicture(const HBITMAP & bitmap, const int & x, const int & y)
{
	cPicture *pPic = new cPicture(bitmap);
	pPic->m_Uid = m_Uid++;
	pPic->SetX(x);
	pPic->SetY(y);
	SafeAddUi(pPic);
	return pPic;
}

cPicture * MyEngine::cGameEngine::CreatePicture(const LPWSTR & Name, const int & x, const int & y, const int & w, const int & h)
{
	cPicture *pPic = new cPicture(Name, w, h);
	pPic->m_Uid = m_Uid++;
	pPic->SetX(x);
	pPic->SetY(y);
	SafeAddUi(pPic);
	return pPic;
}

cPicture * MyEngine::cGameEngine::CreatePictureByKey(std::string key)
{
	cPicture *pPic = new cPicture(key);
	pPic->m_Uid = m_Uid++;
	SafeAddUi(pPic);
	return pPic;
}

cRectangle * MyEngine::cGameEngine::CreateRectangle(const POINT& center, const int& width, const int& height)
{
	cRectangle *pRect = new cRectangle(center,width,height);
	pRect->m_Uid = m_Uid++;
	SafeAddUi(pRect);
	return pRect;
}

cTriangle * MyEngine::cGameEngine::CreateTriangle(const POINT & p1, const POINT & p2, const POINT & p3)
{
	cTriangle *pTri = new cTriangle(p1, p2, p3);
	pTri->m_Uid = m_Uid++;
	SafeAddUi(pTri);
	return pTri;
}

cPolygon * MyEngine::cGameEngine::CreatePolygon(std::initializer_list<POINT> pointList)
{
	cPolygon * pPoly = new cPolygon(pointList);
	pPoly->m_Uid = m_Uid++;
	SafeAddUi(pPoly);
	return pPoly;
}

cAmination * MyEngine::cGameEngine::CreateAmination(const std::initializer_list<LPWSTR>& pathList, const int & x, const int & y, const int& w, const int& h)
{
	cAmination* pAmi = new cAmination(pathList, w, h);
	pAmi->m_Uid = m_Uid++;
	pAmi->SetX(x);
	pAmi->SetY(y);
	SafeAddUi(pAmi);
	return pAmi;
}

cAmination * MyEngine::cGameEngine::CreateAmination(const LPWSTR & Name, const int & smallRow, const int & smallRank, const int & w, const int h)
{
	cAmination* pAmi = new cAmination(Name, smallRow, smallRank, w, h);
	pAmi->m_Uid = m_Uid++;
	SafeAddUi(pAmi);
	return pAmi;
}

cAmination * MyEngine::cGameEngine::CreateAmination(const HBITMAP & hbitmap, const int & smallrow, const int & smallrank)
{
	cAmination* pAmi = new cAmination(hbitmap, smallrow, smallrank);
	pAmi->m_Uid = m_Uid++;
	SafeAddUi(pAmi);
	return pAmi;
}

cAmination * MyEngine::cGameEngine::CreateAminationByKey(std::string key)
{
	cAmination* pAmi = new cAmination(key);
	pAmi->m_Uid = m_Uid++;
	SafeAddUi(pAmi);
	return pAmi;
}

cAmination * MyEngine::cGameEngine::CreateAminationByKey(std::string key, const int & smallRow, const int & smallRank)
{
	cAmination* pAmi = new cAmination(key, smallRow, smallRank);
	pAmi->m_Uid = m_Uid++;
	SafeAddUi(pAmi);
	return pAmi;
}

cSight * MyEngine::cGameEngine::CreateSight()
{
	cSight* pSight = new cSight;
	pSight->m_Uid = m_Uid++;
	SafeAddUi(pSight);
	return pSight;
}

void MyEngine::cGameEngine::AddEventToUi(cBaseUI * trigger, UINT_PTR eventId, SEL_CallFunc callBack,cBaseUI* handler,void* Param)
{
	UI_Event uiEvent;
	uiEvent.EventId = eventId;
	uiEvent.Trigger = trigger;
	uiEvent.CallProc = callBack;
	uiEvent.Handler= handler;
	uiEvent.Param = Param;
	m_evnetList.push_back(uiEvent);
}

int MyEngine::cGameEngine::DeleteUI(cBaseUI * pDel)
{
	m_lock.Lock();
	for (auto it = m_uiList.begin(); it != m_uiList.end(); ++it)
	{
		if (pDel == *it)
		{
			DeleteEvent(pDel->GetID());
			m_uiList.erase(it);
			delete pDel;
			pDel = nullptr;
			m_lock.UnLock();
			return 1;
		}
	}
	m_lock.UnLock();
	return 0;
}

int MyEngine::cGameEngine::DeleteUIs(std::list<cBaseUI*> pDelList)
{
	int iCount = 0;
	for (auto it:pDelList)
	{
		iCount += DeleteUI(it);
	}
	return iCount;
}

int MyEngine::cGameEngine::QuickDeleteUIs(std::list<cBaseUI*> pDelList)
{
	if (pDelList.size() == 0)
	{
		return 0;
	}
	auto pDelCur = pDelList.begin();
	int iCount = 0;
	m_lock.Lock();
	for (auto it = m_uiList.begin(); it != m_uiList.end();)
	{
		if (*it == *pDelCur)
		{
			DeleteEvent((*pDelCur)->GetID());
			it = m_uiList.erase(it);
			delete *pDelCur;
			*pDelCur = nullptr;
			++pDelCur;
			++iCount;
		}
		else
		{
			++it;
		}
	}
	m_lock.UnLock();
	return iCount;
}

BOOL MyEngine::cGameEngine::DeleteEvent(cBaseUI * ui, UINT_PTR eventId)
{
	m_lock.Lock();
	for (auto it = m_evnetList.begin(); it != m_evnetList.end(); ++it)
	{
		if (it->Trigger== ui&&it->EventId == eventId)
		{
			m_evnetList.erase(it);
			m_lock.UnLock();
			return TRUE;
		}
	}	
	m_lock.UnLock();
	return FALSE;
}

int MyEngine::cGameEngine::DeleteEvent(cBaseUI * ui)
{
	int iRet = 0;
	m_lock.Lock();
	for (auto it = m_evnetList.begin(); it != m_evnetList.end();)
	{
		if (it->Trigger == ui)
		{
			it=m_evnetList.erase(it);
			iRet++;
		}
		else
		{
			++it;
		}
	}
	m_lock.UnLock();
	return iRet;
}

int MyEngine::cGameEngine::DeleteEvent(UINT_PTR uid)
{
	m_lock.Lock();
	for (auto it = m_evnetList.begin(); it != m_evnetList.end();)
	{
		if (it->Trigger->GetID()==uid)
		{
			it=m_evnetList.erase(it);
		}
		else
		{
			++it;
		}
	}
	m_lock.UnLock();
	return 0;
}

void MyEngine::cGameEngine::DrawUI()
{
	if (!m_hWnd)
	{
		return;
	}
	HDC hDc = GetDC(m_hWnd);
	HDC hMemDc = CreateCompatibleDC(hDc);
	RECT rect;
	GetClientRect(m_hWnd, &rect);
	HBITMAP hBitMap = CreateCompatibleBitmap(hDc, rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hMemDc, hBitMap);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(hMemDc, &rect, hBrush);
	m_lock.Lock();
	for (auto it : m_uiList)
	{
		if (it!=nullptr)
		{
			it->Draw(hMemDc);
		}
	}
	m_lock.UnLock();

	BitBlt(hDc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hMemDc, 0, 0, SRCCOPY);
	
	DeleteObject(hBrush);
	DeleteObject(hBitMap);
	DeleteDC(hMemDc);
	ReleaseDC(m_hWnd, hDc);
}

void MyEngine::cGameEngine::DoMouseMsg(WPARAM wParam)
{
	switch (wParam)
	{
	case WM_LBUTTONUP:
		m_mouseStatus = Mouse_Up;
		break;
	case WM_LBUTTONDOWN:
		m_mouseStatus = Mouse_Down;
		break;
	default:
		break;
	}
	DoUiMouseEvent(wParam);
}

void MyEngine::cGameEngine::DoKeyMsg(UINT message, WPARAM wParam)
{
	UINT_PTR vkCode = LOWORD(wParam);
	DoUiKeyEvent(message, vkCode);
}

void MyEngine::cGameEngine::DoUiKeyEvent(WPARAM wParam,UINT_PTR eventId)
{
	m_lock.Lock();
	for (auto it : m_evnetList)
	{
		if (it.EventId == eventId||it.EventId==wParam)
		{
			if (it.Param == NULL)
			{
				it.Param = reinterpret_cast<void*>(&eventId);
			}
			(it.Handler->*it.CallProc)(it.Param);
		}
	}
	m_lock.UnLock();
}

void MyEngine::cGameEngine::DoUiMouseEvent(UINT_PTR eventId)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);
	m_lock.Lock();
	for (auto it=m_evnetList.rbegin();it!= m_evnetList.rend();++it)
	{
		RECT rect = (it->Trigger)->GetRect();
		if (pt.x > rect.left&&pt.x<rect.right&&pt.y>rect.top&&pt.y < rect.bottom)
		{
			if (it->EventId == eventId)
			{
				if (it->Param == NULL)
				{
					it->Param = reinterpret_cast<void*>(&eventId);
				}
				(it->Handler->*it->CallProc)(it->Param);
			}
			m_lock.UnLock();
			return;
		}
	}
	m_lock.UnLock();
}

HWND MyEngine::cGameEngine::GethWnd() const
{
	return m_hWnd;
}

void MyEngine::cGameEngine::SethWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

LONG MyEngine::cGameEngine::GetWndStyle()
{
	return GetWindowLong(m_hWnd, GWL_STYLE);
}

BOOL MyEngine::cGameEngine::ChangeWndStyle(const LONG & style)
{
	return SetWindowLong(m_hWnd, GWL_STYLE, style);
}

bool MyEngine::cGameEngine::AddEngineUi(cBaseUI * ui)
{
	for (auto it : m_uiList)
	{
		if (it == ui)
		{
			return false;
		}
	}
	ui->SetUid(m_Uid++);
	m_uiList.push_back(ui);
	return true;
}

void MyEngine::cGameEngine::ReleaseSelf()
{
	delete g_pEngine;
	g_pEngine = nullptr;
}