#include "stdafx.h"
#include "cButton.h"
#include"Tool.h"
#include"cResourcePool.h"
#include"cGameEngine.h"
using namespace MyEngine;

cButton::cButton()
{
	m_type = UI_Button;
	m_bgBitmap = NULL;
	m_firstBountColor = RGB(0, 255, 0);
	m_secBountColor = RGB(127, 127, 127);
	m_firstColor = RGB(153,217,234);
	m_font = L"楷体";
	m_fontColor = RGB(250, 0, 0);
	m_height = 30;
	m_Name = L"Button";
	m_nBount = 3;
	m_secondColor= RGB(255, 255, 255);
	m_width = 100;
	m_bgColor = m_firstColor;
	m_BountColor = m_firstBountColor;
	m_hFont = CreateFont(m_height - 8, (m_height - 8)/2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
	m_hBrush = CreateSolidBrush(m_firstColor);
}

MyEngine::cButton::cButton(const LPWSTR & Name, const int & width, const int & height)
{
	m_type = UI_Button;
	m_bgBitmap = NULL;
	m_firstBountColor = RGB(0, 255, 0);
	m_secBountColor = RGB(127, 127, 127);
	m_firstColor = RGB(153, 217, 234);
	m_font = L"楷体";
	m_fontColor = RGB(255, 0, 0);
	m_height = height;
	m_Name = Name;
	m_nBount = 3;
	m_secondColor = RGB(255, 255, 255);
	m_width = width;
	m_bgColor = m_firstColor;
	m_BountColor = m_firstBountColor;
	m_hFont = CreateFont(m_height - 8, (m_height - 8) / 2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

MyEngine::cButton::cButton(const LPWSTR & bmpPath)
{
	m_type = UI_Button;
	m_bgBitmap = (HBITMAP)LoadImage(nullptr, bmpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(m_bgBitmap, sizeof(BITMAP), &bitmap);
	m_firstBountColor = RGB(0, 255, 0);
	m_secBountColor = RGB(127, 127, 127);
	m_firstColor = RGB(153, 217, 234);
	m_font = L"楷体";
	m_fontColor = RGB(250, 0, 0);
	m_height = bitmap.bmHeight;
	m_width = bitmap.bmWidth;
	m_Name = L"Button";
	m_nBount = 3;
	m_secondColor = RGB(255, 255, 255);
	m_bgColor = m_firstColor;
	m_BountColor = m_firstBountColor;
	m_hFont = CreateFont(m_height - 8, (m_height - 8) / 2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

MyEngine::cButton::cButton(const HBITMAP & hbitmap)
{
	m_type = UI_Button;
	m_bgBitmap = hbitmap;
	BITMAP bitmap;
	GetObject(m_bgBitmap, sizeof(BITMAP), &bitmap);
	m_firstBountColor = RGB(0, 255, 0);
	m_secBountColor = RGB(127, 127, 127);
	m_firstColor = RGB(153, 217, 234);
	m_font = L"楷体";
	m_fontColor = RGB(250, 0, 0);
	m_height = bitmap.bmHeight;
	m_Name = L"Button";
	m_nBount = 3;
	m_secondColor = RGB(255, 255, 255);
	m_width = bitmap.bmWidth;
	m_bgColor = m_firstColor;
	m_BountColor = m_firstBountColor;
	m_hFont = CreateFont(m_height - 8, (m_height - 8) / 2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

MyEngine::cButton::cButton(std::string key)
{
	m_type = UI_Button;
	m_isUsePool = TRUE;
	m_bgBitmap = (HBITMAP)cResourcePool::GetResourcePool()->GethObjByKey(key);
	BITMAP bitmap;
	GetObject(m_bgBitmap, sizeof(BITMAP), &bitmap);
	m_firstBountColor = RGB(0, 255, 0);
	m_secBountColor = RGB(127, 127, 127);
	m_firstColor = RGB(153, 217, 234);
	m_font = L"楷体";
	m_fontColor = RGB(250, 0, 0);
	m_height = bitmap.bmHeight;
	m_width = bitmap.bmWidth;
	m_Name = L"Button";
	m_nBount = 3;
	m_secondColor = RGB(255, 255, 255);
	m_bgColor = m_firstColor;
	m_BountColor = m_firstBountColor;
	m_hFont = CreateFont(m_height - 8, (m_height - 8) / 2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

cButton::~cButton()
{
	m_bgBitmap &&!m_isUsePool? DeleteObject(m_bgBitmap) : 1;
	m_hFont ? DeleteObject(m_hFont) : 1;
	m_hPen ? DeleteObject(m_hPen) : 1;
	m_hBrush ? DeleteObject(m_hBrush) : 1;
}

void MyEngine::cButton::SetName(const LPWSTR & Name)
{
	m_Name = Name;
}

const LPWSTR & MyEngine::cButton::GetName() const
{
	return m_Name;
}

void MyEngine::cButton::SetWidth(const int & width)
{
	m_width = width;
}

const int & MyEngine::cButton::GetWidth() const
{
	return m_width;
}

void MyEngine::cButton::SetHeight(const int & Height)
{
	m_height = Height;
	m_hFont = CreateFont(m_height - 8, (m_height - 8) / 2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const int & MyEngine::cButton::GetHeight() const
{
	return m_height;
}

void MyEngine::cButton::SetnBount(const int & n)
{
	m_nBount = n;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
}

const int & MyEngine::cButton::GetBount() const
{
	return m_nBount;
}

void MyEngine::cButton::SetFirstBountColor(const UINT & rgb)
{
	m_firstBountColor = rgb;
	m_BountColor = rgb;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
}

void MyEngine::cButton::SetSecBountColor(const UINT & rgb)
{
	m_secBountColor = rgb;
}

const UINT & MyEngine::cButton::GetFirstBountColor()
{
	return m_firstBountColor;
}

const UINT & MyEngine::cButton::GetSecBountColor()
{
	return m_secBountColor;
}

void MyEngine::cButton::SetfirstColor(const UINT & rgb)
{
	m_firstColor = rgb;
	if (!m_bgBitmap)
	{
		m_bgColor = m_firstColor;
		DeleteObject(m_hBrush);
		m_hBrush = CreateSolidBrush(m_bgColor);
	}
}

const UINT & MyEngine::cButton::GetfirstColor() const
{
	return m_firstColor;
}

void MyEngine::cButton::SetSecondColor(const UINT & rgb)
{
	m_secondColor = rgb;
}

const UINT & MyEngine::cButton::GetSecondColor() const
{
	return m_secondColor;
}

const RECT MyEngine::cButton::GetRect() const
{
	RECT rect;
	rect.left = GetX();
	rect.right = GetX() + m_width;
	rect.top = GetY();
	rect.bottom = GetY() + m_height;
	return rect;
}

bool MyEngine::cButton::Draw(HDC hDc)
{
	ChangeBountColor(cGameEngine::GetEngine()->GetMouseStatus());
	if (!m_bgBitmap)
	{
		return DrawNormal(hDc);
	}
	else
	{
		return DrawBitmapBtn(hDc);
	}
}

bool MyEngine::cButton::DrawNormal(HDC hDc)
{
	if (hDc == NULL)
	{
		return false;
	}
	ChangeColor();
	unsigned wordLen = lstrlenW(m_Name);  //字符个输
	//统计按钮名称中汉子个数
	int num = WcharArrayChineseNums(m_Name);
	HFONT hFont = (HFONT)SelectObject(hDc, m_hFont);
	HPEN hPen = (HPEN)SelectObject(hDc, m_hPen);
	HBRUSH hBrush = (HBRUSH)SelectObject(hDc, m_hBrush);
	//绘制按钮形象
	RECT rect = GetRect();
	Rectangle(hDc, rect.left, rect.top, rect.right, rect.bottom);
	//绘制按钮名称
	SetBkMode(hDc, NULL);
	SetTextColor(hDc, m_fontColor);
	TextOut(hDc, rect.left + (m_width -((m_height-8)/2)*(wordLen + num)) / 2,
		rect.top + 4, m_Name, wordLen);
	//还原hDc设置及删除句柄资源
	SelectObject(hDc, hPen);
	SelectObject(hDc, hBrush);
	SelectObject(hDc, hFont);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(hFont);
	return true;
}

bool MyEngine::cButton::DrawBitmapBtn(HDC hDc)
{
	if (hDc == NULL)
	{
		return false;
	}

	HDC hMemDc = CreateCompatibleDC(hDc);
	SelectObject(hMemDc, m_bgBitmap);
	BitBlt(hDc, GetX(), GetY(), m_width, m_height, hMemDc, 0, 0, SRCCOPY);

	RECT rect = GetRect();
	HPEN hPen = (HPEN)SelectObject(hDc, m_hPen);
	HBRUSH hBrush = (HBRUSH)SelectObject(hDc, m_hBrush);
	Rectangle(hDc, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(hDc,hPen);
	SelectObject(hDc, hBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteDC(hMemDc);
	return true;
}

void MyEngine::cButton::SetFont(const LPWSTR & font)
{
	m_font = font;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_height-8,(m_height-8)/2, NULL, NULL, 400, FALSE,
		FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const LPWSTR & MyEngine::cButton::GetFont() const
{
	return m_font;
}

void MyEngine::cButton::SetFontColor(const UINT & rgb)
{
	m_fontColor = rgb;
}

const UINT & MyEngine::cButton::GetFontColor() const
{
	return m_fontColor;
}

void MyEngine::cButton::ChangeColor()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(cGameEngine::GetEngine()->GethWnd(), &pt);
	RECT rect = GetRect();
	if (pt.x > rect.left&&pt.x<rect.right&&pt.y>rect.top&&pt.y < rect.bottom)
	{
		m_bgColor = m_secondColor;
		DeleteObject(m_hBrush);
		m_hBrush = CreateSolidBrush(m_bgColor);
	}
	else
	{
		m_bgColor = m_firstColor;
		DeleteObject(m_hBrush);
		m_hBrush = CreateSolidBrush(m_bgColor);
	}
}

void MyEngine::cButton::ChangeBountColor(Mouse_Status clicked)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(cGameEngine::GetEngine()->GethWnd(), &pt);
	RECT rect = GetRect();
	if (pt.x > rect.left&&pt.x<rect.right&&pt.y>rect.top&&pt.y < rect.bottom)
	{
		if (clicked == Mouse_Down)
		{
			m_BountColor = m_secBountColor;
			DeleteObject(m_hPen);
			m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
		}
		else if (clicked == Mouse_Up)
		{
			m_BountColor = m_firstBountColor;
			DeleteObject(m_hPen);
			m_hPen = CreatePen(PS_SOLID, m_nBount, m_BountColor);
		}
	}
}

void MyEngine::cButton::SetBmpBtn(const LPWSTR & bmpPath)
{
	m_bgBitmap = (HBITMAP)LoadImage(nullptr, bmpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(m_bgBitmap, sizeof(BITMAP), &bitmap);
	m_width = bitmap.bmWidth;
	m_height = bitmap.bmHeight;
	DeleteObject(m_hBrush);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

void MyEngine::cButton::SetBmpBtn(const HBITMAP & hbitmap)
{
	m_bgBitmap = hbitmap;
	BITMAP bitmap;
	GetObject(m_bgBitmap, sizeof(BITMAP), &bitmap);
	m_width = bitmap.bmWidth;
	m_height = bitmap.bmHeight;
	DeleteObject(m_hBrush);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}