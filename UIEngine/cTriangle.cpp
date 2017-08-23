#include "stdafx.h"
#include "cTriangle.h"
using namespace MyEngine;

cTriangle::cTriangle()
{
	m_type = UI_Triangle;
	m_firstPoint.x = 0;
	m_firstPoint.y = 0;
	m_secondPoint.x = 0;
	m_secondPoint.y = 0;
	m_thirdPoint.x = 0;
	m_thirdPoint.y = 0;
	m_FillColor = RGB(255, 255, 255);
	m_isFill = false;
	m_LineColor = RGB(0, 0, 0);
	m_Linewidth = 3;
	m_lineStyle = PS_SOLID;
	m_hPen = CreatePen(PS_SOLID, m_Linewidth, m_LineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}


MyEngine::cTriangle::cTriangle(const POINT & p1, const POINT & p2, const POINT & p3)
{
	m_type = UI_Triangle;
	m_firstPoint = p1;
	m_secondPoint = p2;
	m_thirdPoint = p3;
	m_FillColor = RGB(255, 255,0);
	m_isFill = false;
	m_LineColor = RGB(0, 255, 0);
	m_Linewidth = 3;
	m_lineStyle = PS_SOLID;
	m_hPen = CreatePen(PS_SOLID, m_Linewidth, m_LineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

cTriangle::~cTriangle()
{
	m_hPen ? DeleteObject(m_hPen) : 1;
	m_hBrush ? DeleteObject(m_hBrush) : 1;
}

void MyEngine::cTriangle::SetFirstPoint(const POINT & p1)
{
	m_firstPoint = p1;
}

void MyEngine::cTriangle::SetSecondPoint(const POINT & p2)
{
	m_secondPoint = p2;
}

void MyEngine::cTriangle::SetThirdPoint(const POINT & p3)
{
	m_thirdPoint = p3;
}

const POINT & MyEngine::cTriangle::GetFirstPoint() const
{
	return m_firstPoint;
}

const POINT & MyEngine::cTriangle::GetSecondPoint() const
{
	return m_secondPoint;
}

const POINT & MyEngine::cTriangle::GetThirdPoint() const
{
	return m_thirdPoint;
}

void MyEngine::cTriangle::SetLineColor(const UINT & rgb)
{
	m_LineColor = rgb;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_LineColor);
}

const UINT & MyEngine::cTriangle::GetLineColor() const
{
	return m_LineColor;
}

void MyEngine::cTriangle::SetLineWidth(const int & width)
{
	m_Linewidth = width;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_LineColor);
}

const int & MyEngine::cTriangle::GetLineWidth() const
{
	return m_Linewidth;
}

void MyEngine::cTriangle::SetIsFill(const bool & ok)
{
	m_isFill = ok;
	if (!m_isFill)
	{
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
}

const bool & MyEngine::cTriangle::isFill() const
{
	return m_isFill;
}

void MyEngine::cTriangle::SetFillColor(const UINT & rgb)
{
	m_FillColor = rgb;
	if (m_isFill)
	{
		DeleteObject(m_hBrush);
		m_hBrush = CreateSolidBrush(m_FillColor);
	}
}

const UINT & MyEngine::cTriangle::GetFillColor() const
{
	return m_FillColor;
}

void MyEngine::cTriangle::SetLineStyle(const UINT & style)
{
	m_lineStyle = style;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_LineColor);
}

const UINT & MyEngine::cTriangle::GetLineStyle() const
{
	return m_lineStyle;
}

const RECT MyEngine::cTriangle::GetRect() const
{
	RECT rect = { 0,0,0,0 };
	return rect;
}

bool MyEngine::cTriangle::Draw(HDC hDc)
{
	bool bRet = true;
	HPEN hPen = (HPEN)SelectObject(hDc, m_hPen);
	SetPolyFillMode(hDc, WINDING);
	HBRUSH hBrush = (HBRUSH)SelectObject(hDc, m_hBrush);
	POINT apt[3] = { m_firstPoint,m_secondPoint,m_thirdPoint };
	if (!Polygon(hDc,apt,3))
	{
		bRet = false;
	}
	SelectObject(hDc, hPen);
	SelectObject(hDc, hBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	return bRet;
}