#include "stdafx.h"
#include "cAmination.h"
#include"cResourcePool.h"
using namespace MyEngine;

cAmination::cAmination()
{
	m_type = UI_Amination;
	m_Amination.clear();
	m_amiConfig = BITMAP();
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
	m_maxFrame = 0;
	m_curFrame = 0;
	m_isAutoRun = TRUE;
	m_isOne = FALSE;
	m_smallRow = 0;
	m_smallRank = 0;
}

MyEngine::cAmination::cAmination(const LPWSTR & Name, const int& smallRow, const int& smallRank,const int& w, const int& h)
{
	m_type = UI_Amination;
	m_Amination.push_back((HBITMAP)LoadImage(NULL, Name,
		IMAGE_BITMAP, w, h, LR_LOADFROMFILE));
	m_isLucency = FALSE;
	InitAmiConfig();
	m_lucencyRgb = RGB(0, 0, 0);
	m_maxFrame = smallRank*smallRow;
	m_curFrame = 0;
	m_isAutoRun = TRUE;
	m_isOne = TRUE;
	m_smallRow = smallRow;
	m_smallRank = smallRank;
}

MyEngine::cAmination::cAmination(const std::string & key, const int & smallRow, const int & smallRank)
{
	m_type = UI_Amination;
	m_isUsePool = TRUE;
	m_Amination.push_back((HBITMAP)cResourcePool::GetResourcePool()->GethObjByKey(key));
	m_isLucency = FALSE;
	InitAmiConfig();
	m_lucencyRgb = RGB(0, 0, 0);
	m_maxFrame = smallRank*smallRow;
	m_curFrame = 0;
	m_isAutoRun = TRUE;
	m_isOne = TRUE;
	m_smallRow = smallRow;
	m_smallRank = smallRank;
}

MyEngine::cAmination::cAmination(const std::string & key)
{
	m_type = UI_Amination;
	m_isUsePool = TRUE;
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
	auto initlist = cResourcePool::GetResourcePool()->GetMulObjByKey(key);
	for (auto it : initlist)
	{
		m_Amination.push_back((HBITMAP)it);
	}
	m_maxFrame = m_Amination.size();
	m_curFrame = 0;
	InitAmiConfig();
	m_isAutoRun = TRUE;
	m_isOne = FALSE;
	m_smallRow = 0;
	m_smallRank = 0;
}

MyEngine::cAmination::cAmination(HBITMAP hbitmap,const int& smallRow, const int& smallRank)
{
	m_type = UI_Amination;
	m_Amination.push_back(hbitmap);
	m_isLucency = FALSE;
	InitAmiConfig();
	m_lucencyRgb = RGB(0, 0, 0);
	m_maxFrame = smallRank*smallRow;
	m_curFrame = 0;
	m_isAutoRun = TRUE;
	m_isOne = TRUE;
	m_smallRow = smallRow;
	m_smallRank = smallRank;
}

MyEngine::cAmination::cAmination(const std::initializer_list<LPWSTR>& initlist,const int& w,const int& h)
{
	m_type = UI_Amination;
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
	for (auto it : initlist)
	{
		m_Amination.emplace_back((HBITMAP)LoadImage(NULL, it, IMAGE_BITMAP, w, h, LR_LOADFROMFILE));
	}
	m_maxFrame = m_Amination.size();
	m_curFrame = 0;
	InitAmiConfig();
	m_isAutoRun = TRUE;
	m_isOne = FALSE;
	m_smallRow = 0;
	m_smallRank = 0;
}


cAmination::~cAmination()
{
	DeleteAmination();
}

void MyEngine::cAmination::SetAmination(const std::initializer_list<PWSTR>& initlist,const int& w,const int& h)
{
	if (initlist.size() == 0)
	{
		return;
	}
	DeleteAmination();
	for (auto it : initlist)
	{
		m_Amination.push_back((HBITMAP)LoadImage(NULL, it, IMAGE_BITMAP, w, h, LR_LOADFROMFILE));
	}
	InitAmiConfig();
	m_maxFrame = m_Amination.size();
	m_curFrame = 0;
	m_isOne = FALSE;
	m_isUsePool = FALSE;
}

void MyEngine::cAmination::SetAmination(const std::string key)
{
	auto initlist = cResourcePool::GetResourcePool()->GetMulObjByKey(key);
	if (initlist.size() == 0)
	{
		return;
	}
	DeleteAmination();
	for (auto it : initlist)
	{
		m_Amination.push_back((HBITMAP)it);
	}
	InitAmiConfig();
	m_maxFrame = m_Amination.size();
	m_curFrame = 0;
	m_isOne = FALSE;
	m_isUsePool = TRUE;
}

void MyEngine::cAmination::SetAmination(const std::string key, const int & smallRow, const int & smallRank)
{
	DeleteAmination();
	m_Amination.push_back((HBITMAP)cResourcePool::GetResourcePool()->GethObjByKey(key));
	InitAmiConfig();
	m_maxFrame = smallRank*smallRow;
	m_curFrame = 0;
	m_isOne = TRUE;
	m_smallRow = smallRow;
	m_smallRank = smallRank;
	m_isUsePool = TRUE;

}

void MyEngine::cAmination::SetAmination(const LPWSTR & name, const int & smallRow, const int & smallRank)
{
	DeleteAmination();
	m_Amination.push_back((HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	InitAmiConfig();
	m_maxFrame = smallRank*smallRow;
	m_curFrame = 0;
	m_isOne = TRUE;
	m_smallRow = smallRow;
	m_smallRank = smallRank;
	m_isUsePool = FALSE;
}

const std::vector<HBITMAP>& MyEngine::cAmination::GetAmination() const
{
	return m_Amination;
}

const RECT MyEngine::cAmination::GetRect() const
{
	RECT rect;
	rect.left = GetX();
	rect.right = GetX() + m_amiConfig.bmWidth;
	rect.top = GetY();
	rect.bottom = GetY() + m_amiConfig.bmHeight;
	return rect;
}

bool MyEngine::cAmination::Draw(HDC hDc)
{
	if (hDc == NULL)
	{
		return false;
	}
	HDC hMemDc = CreateCompatibleDC(hDc);
	if (m_isOne)
	{
		SelectObject(hMemDc, m_Amination[0]);
		int xSize = m_amiConfig.bmWidth / m_smallRank;
		int ySize = m_amiConfig.bmHeight / m_smallRow;
		if (m_isLucency)
		{
			TransparentBlt(hDc, GetX(), GetY(), xSize, ySize,
				hMemDc, (m_curFrame%m_smallRank)*xSize,
				(m_curFrame / m_smallRank)*ySize, xSize,
				ySize, m_lucencyRgb);
		}
		else
		{
			BitBlt(hDc, GetX(), GetY(), xSize, ySize, hMemDc,
				(m_curFrame%m_smallRank)*xSize, (m_curFrame
					/ m_smallRank)*ySize, SRCCOPY);
		}
	}
	else
	{
		SelectObject(hMemDc, m_Amination[m_curFrame]);
		if (m_isLucency)
		{
			TransparentBlt(hDc, GetX(), GetY(), m_amiConfig.bmWidth, m_amiConfig.bmHeight, hMemDc, 0, 0, m_amiConfig.bmWidth, m_amiConfig.bmHeight, m_lucencyRgb);
		}
		else
		{
			BitBlt(hDc, GetX(), GetY(), m_amiConfig.bmWidth, m_amiConfig.bmHeight, hMemDc, 0, 0, SRCCOPY);
		}
	}
	if (m_isAutoRun)
	{
		IncFrame();
	}
	DeleteDC(hMemDc);
	return true;
}

void MyEngine::cAmination::SetIsLucnecy(const BOOL & b)
{
	m_isLucency = b;
}

const BOOL & MyEngine::cAmination::GetIsLucency() const
{
	return m_isLucency;
}

void MyEngine::cAmination::SetLucnecyColor(const UINT & rgb)
{
	m_lucencyRgb = rgb;
}

const UINT & MyEngine::cAmination::GetLucnecyColor() const
{
	return m_lucencyRgb;
}

const BITMAP & MyEngine::cAmination::GetConfig() const
{
	return m_amiConfig;
}

void MyEngine::cAmination::IncFrame(const int& curFrame)
{
	if (!m_maxFrame)
	{
		return;
	}
	if (curFrame)
	{
		m_curFrame = curFrame;
	}
	else
	{
		m_curFrame = (m_curFrame + 1) % m_maxFrame;
	}
}

void MyEngine::cAmination::SetAutoRun(const BOOL & b)
{
	m_isAutoRun = b;
}

const BOOL & MyEngine::cAmination::IsAutoRun() const
{
	return m_isAutoRun;
}

void MyEngine::cAmination::SetSmallRowAndRank(const int & row, const int & rank)
{
	m_smallRow = row;
	m_smallRank = rank;
	m_maxFrame = row*rank;
}

void MyEngine::cAmination::SetCurFrame(const int & curFrame)
{
	m_curFrame = curFrame;
}

const int & MyEngine::cAmination::GetCurFrame() const
{
	return m_curFrame;
}

void MyEngine::cAmination::InitAmiConfig()
{
	GetObject(m_Amination[0], sizeof(BITMAP), &m_amiConfig);
}

void MyEngine::cAmination::DeleteAmination()
{
	m_isUsePool ? m_Amination.clear() : "";
	for (auto it : m_Amination)
	{
		DeleteObject(it);
	}
	m_Amination.clear();
}
