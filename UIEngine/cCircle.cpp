#include "stdafx.h"
#include "cCircle.h"

using namespace MyEngine;

cCircle::cCircle()
{
	m_type = UI_Circle;
	m_radius = 10;
	m_fillColor = RGB(255, 255, 255);
	m_isFill = false;
	m_LineColor = RGB(0, 0, 0);
	m_lineWidth = 3;
	m_lineStyle = PS_SOLID;
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_LineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

MyEngine::cCircle::cCircle(const POINT& center, const UINT& radius)
{
	m_type = UI_Circle;
	SetX(center.x);
	SetY(center.y);
	m_radius = radius;
	m_fillColor = RGB(255, 255, 255);
	m_isFill = false;
	m_LineColor = RGB(0, 0, 0);
	m_lineWidth = 3;
	m_lineStyle = PS_SOLID;
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_LineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

cCircle::~cCircle()
{
	m_hPen ? DeleteObject(m_hPen) : 1;
	m_hBrush ? DeleteObject(m_hBrush) : 1;
}

void MyEngine::cCircle::SetRaduis(const UINT & radius)
{
	m_radius = radius;
}

const UINT & MyEngine::cCircle::GetRadius()
{
	return m_radius;
}

void MyEngine::cCircle::SetCenter(const POINT & center)
{
	SetX(center.x);
	SetY(center.y);
}

const POINT MyEngine::cCircle::GetCenter()
{
	POINT pt{ GetX(),GetY() };
	return pt;
}

void MyEngine::cCircle::SetCircle(const POINT & center, const UINT & radius)
{
	SetX(center.x);
	SetY(center.y);
	m_radius = radius;
}

void MyEngine::cCircle::SetLineColor(const UINT & rgb)
{
	m_LineColor = rgb;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_LineColor);
}

const UINT & MyEngine::cCircle::GetLineColor() const
{
	return m_LineColor;
}

void MyEngine::cCircle::SetIsFill(const bool & ok)
{
	m_isFill = ok;
	if (!m_isFill)
	{
		DeleteObject(m_hBrush);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
}

const bool & MyEngine::cCircle::GetIsFill() const
{
	return m_isFill;
}

void MyEngine::cCircle::SetFillColor(const UINT & rgb)
{
	m_fillColor = rgb;
	if (m_isFill)
	{
		DeleteObject(m_hBrush);
		m_hBrush = CreateSolidBrush(m_fillColor);
	}
}

const UINT & MyEngine::cCircle::GetFillColor() const
{
	return m_fillColor;
}

void MyEngine::cCircle::SetLineStyle(const UINT & style)
{
	m_lineStyle = style;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_LineColor);
}

const UINT & MyEngine::cCircle::GetLineStyle(const UINT & style)
{
	return m_lineStyle;
}

const RECT MyEngine::cCircle::GetRect() const
{
	RECT rect;
	rect.left = GetX()-m_radius;
	rect.right = GetX() + m_radius;
	rect.top = GetY()-m_radius;
	rect.bottom = GetY() + m_radius;
	return rect;
}

bool MyEngine::cCircle::Draw(HDC hDc)
{
	bool bRet = true;
	HPEN hPen=(HPEN)SelectObject(hDc, m_hPen);
	HBRUSH hBrush=(HBRUSH)SelectObject(hDc, m_hBrush);
	RECT rect{ GetX() - m_radius,GetY() - m_radius,GetX() + m_radius,GetY() + m_radius };
	if (!Ellipse(hDc,rect.left,rect.top,rect.right,rect.bottom))
	{
		bRet = false;
	}
	SelectObject(hDc, hPen);
	SelectObject(hDc, hBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	return bRet;
}