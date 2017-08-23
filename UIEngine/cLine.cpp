#include "stdafx.h"
#include "cLine.h"
using namespace MyEngine;

cLine::cLine()
{
	m_type = UI_Line;
	m_startPoint.x = 0;
	m_startPoint.y = 0;
	m_endSPoint.x = 0;
	m_endSPoint.y = 0;
	m_width = 3;
	m_color = RGB(255, 255, 0);
	m_style = PS_SOLID;
	m_hPen = CreatePen(m_style, m_width, m_color);
}

cLine::cLine(const POINT & start, const POINT & end):m_startPoint(start),m_endSPoint(end),m_width(3),m_color(RGB(255,255,0))
{
	m_type = UI_Line;
	m_style = PS_SOLID;
	m_hPen = CreatePen(m_style, m_width, m_color);
}

cLine::cLine(const int & startx, const int & starty, const int & endx, const int & endy)
{
	m_type = UI_Line;
	m_startPoint.x = startx;
	m_startPoint.y = starty;
	m_endSPoint.x = endx;
	m_endSPoint.y = endy;
	m_width = 1;
	m_color = RGB(0, 0, 0);
	m_style = PS_SOLID;
	m_hPen = CreatePen(m_style, m_width, m_color);
}

cLine::~cLine()
{
	m_hPen ? DeleteObject(m_hPen) : 1;
}

void cLine::SetStartPoint(const POINT & start)
{
	m_startPoint = start;
}

void cLine::SetEndPoint(const POINT & end)
{
	m_endSPoint = end;
}

const POINT & cLine::GetStartPoint() const
{
	return m_startPoint;
}

const POINT & cLine::GetEndPoint() const
{
	return m_endSPoint;
}

void cLine::SetStartPoint(const int & x, const int & y)
{
	m_startPoint.x = x;
	m_startPoint.y = y;
}

void cLine::SetEndPoint(const int & x, const int & y)
{
	m_endSPoint.x = x;
	m_endSPoint.y = y;
}

void cLine::SetWidth(const int & w)
{
	m_width = w;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_style, m_width, m_color);
}

const int & cLine::GetWidth() const
{
	return m_width;
}

void cLine::SetColor(const UINT & rgb)
{
	m_color = rgb;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_style, m_width, m_color);
}

const UINT & cLine::GetColor() const
{
	return m_color;
}

void MyEngine::cLine::SetStyle(const UINT & style)
{
	m_style = style;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_style, m_width, m_color);
}

const UINT & MyEngine::cLine::GetStyle() const
{
	return m_style;
}

bool MyEngine::cLine::Draw(HDC hDc)
{
	HPEN hPen=(HPEN)SelectObject(hDc, m_hPen);
	if (!MoveToEx(hDc, m_startPoint.x, m_startPoint.y, nullptr))
	{
		DeleteObject(hPen);
		return false;
	}
	if (!LineTo(hDc, m_endSPoint.x, m_endSPoint.y))
	{
		DeleteObject(hPen);
		return false;
	}
	SelectObject(hDc, hPen);
	DeleteObject(hPen);
	return true;
}

const RECT MyEngine::cLine::GetRect() const
{
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 0;
	rect.bottom = 0;
	return rect;
}