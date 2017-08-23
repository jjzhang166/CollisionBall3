#include "stdafx.h"
#include "cRectangle.h"
using namespace MyEngine;

cRectangle::cRectangle()
{
	m_type = UI_Rectangle;
	SetX(0);
	SetY(0);
	m_width = 2;
	m_height = 2;
	m_fillColor = RGB(255, 255, 255);
	m_isFill = false;
	m_lineColor = RGB(255, 0, 0);
	m_Linewidth = 1;
	m_lineStyle = PS_SOLID;
}

MyEngine::cRectangle::cRectangle(const POINT & center, const int & width, const int & height)
{
	m_type = UI_Rectangle;
	SetX(center.x);
	SetY(center.y);
	m_width = width;
	m_height = height;
	m_fillColor = RGB(255, 255, 255);
	m_isFill = false;
	m_lineColor = RGB(255, 0, 0);
	m_Linewidth = 1;
	m_lineStyle = PS_SOLID;
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_lineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

cRectangle::~cRectangle()
{
	m_hPen ? DeleteObject(m_hPen) : 1;
	m_hBrush ? DeleteObject(m_hBrush) : 1;
}

void MyEngine::cRectangle::SetCenter(const POINT & center)
{
	SetX(center.x);
	SetY(center.y);
}

void MyEngine::cRectangle::SetWidth(const int & width)
{
	m_width = width;
}

const int & MyEngine::cRectangle::GetWidth()
{
	return m_width;
}

void MyEngine::cRectangle::SetHeight(const int & height)
{
	m_height = height;
}

const int & MyEngine::cRectangle::GetHeight()
{
	return m_height;
}

const RECT MyEngine::cRectangle::GetRect() const
{
	RECT rect;
	rect.left = GetX() - m_width / 2;
	rect.right = GetX() + m_width / 2;
	rect.top = GetY() - m_height / 2;
	rect.bottom = GetY() + m_height / 2;
	return rect;
}

void MyEngine::cRectangle::SetLineColor(const UINT & rgb)
{
	m_lineColor = rgb;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_lineColor);
}

const UINT & MyEngine::cRectangle::GetLineColor() const
{
	return m_lineColor;
}

void MyEngine::cRectangle::SetLineWidth(const int & linewidth)
{
	m_Linewidth = linewidth;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_lineColor);
}

const int & MyEngine::cRectangle::GetLineWidth()
{
	return m_Linewidth;
}

void MyEngine::cRectangle::SetIsFill(const bool & ok)
{
	m_isFill = ok;
	if (!m_isFill)
	{
		DeleteObject(m_hBrush);
		m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
}

const bool & MyEngine::cRectangle::isFIll() const
{
	return m_isFill;
}

void MyEngine::cRectangle::SetFillColor(const UINT & rgb)
{
	m_fillColor = rgb;
	DeleteObject(m_hBrush);
	m_hBrush = CreateSolidBrush(m_fillColor);
}

const UINT & MyEngine::cRectangle::GetFillColor() const
{
	return m_fillColor;
}

void MyEngine::cRectangle::SetLineStyle(const UINT & style)
{
	m_lineStyle = style;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_Linewidth, m_lineColor);
}

const UINT & MyEngine::cRectangle::GetLineStyle() const
{
	return m_lineStyle;
}

bool MyEngine::cRectangle::Draw(HDC hDc)
{
	HPEN hPen=(HPEN)SelectObject(hDc, m_hPen);
	HBRUSH hBrush=(HBRUSH)SelectObject(hDc, m_hBrush);
	RECT rect = GetRect();
	Rectangle(hDc, rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hDc, hPen);
	SelectObject(hDc,hBrush);
	return true;
}
