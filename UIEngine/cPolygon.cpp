#include "stdafx.h"
#include "cPolygon.h"

using namespace MyEngine;

cPolygon::cPolygon()
{
	m_type = UI_Polygon;
	m_pointList.clear();
	m_lineColor = RGB(0, 255, 255);
	m_sideNums = 0;
	m_lineWidth = 2;
	m_fillColor = RGB(0, 0, 0);
	m_lineStyle = PS_SOLID;
	m_isFill = FALSE;
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}


MyEngine::cPolygon::cPolygon(const std::initializer_list<POINT> pointList)
{
	m_type = UI_Polygon;
	m_pointList.resize(pointList.size());
	m_pointList.assign(pointList);
	m_lineColor = RGB(0, 255, 255);
	m_sideNums = m_pointList.size();
	m_lineWidth = 4;
	m_fillColor = RGB(0, 0, 0);
	m_lineStyle = PS_SOLID;
	m_isFill = FALSE;
	m_hPen = CreatePen(PS_SOLID, m_lineWidth, m_lineColor);
	m_hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

cPolygon::~cPolygon()
{
	m_hPen ? DeleteObject(m_hPen) : 1;
	m_hBrush ? DeleteObject(m_hBrush) : 1;
}

const RECT MyEngine::cPolygon::GetRect() const
{
	RECT rect;
	rect.left = 0;
	rect.right = 0;
	rect.top = 0;
	rect.bottom = 0;
	return rect;
}

void MyEngine::cPolygon::SetPolygon(const std::initializer_list<POINT>& pointList)
{
	m_pointList.resize(pointList.size());
	m_pointList.assign(pointList);
	m_sideNums = m_pointList.size();
}

void MyEngine::cPolygon::AlterOnePoint(const POINT & oldPoint, const POINT & newPoint)
{
	for (auto it = std::begin(m_pointList); it != std::end(m_pointList); ++it)
	{
		if (it->x == oldPoint.x&&it->y == oldPoint.y)
		{
			*it = newPoint;
		}
	}
}

bool MyEngine::cPolygon::Draw(HDC hDc)
{
	if (hDc == NULL)
	{
		return false;
	}
	bool bRet = true;
	POINT *apt = new POINT[m_sideNums];
	HPEN hPen = (HPEN)SelectObject(hDc, m_hPen);
	HBRUSH hBrush = (HBRUSH)SelectObject(hDc, m_hBrush);
	for (size_t i = 0; i < m_sideNums ; ++i)
	{
		apt[i] = m_pointList[i];
	}
	SetPolyFillMode(hDc,WINDING);
	if (!Polygon(hDc, apt, m_sideNums))
	{
		bRet = false;
	}
	SelectObject(hDc, hPen);
	SelectObject(hDc, hBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	delete[] apt;
	apt = nullptr;
	return bRet;
}

void MyEngine::cPolygon::SetLineWidth(const unsigned & width)
{
	m_lineWidth = width;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
}

const unsigned & MyEngine::cPolygon::GetLineWidth() const
{
	return m_lineWidth;
}

void MyEngine::cPolygon::SetLineColor(const UINT & rgb)
{
	m_lineColor = rgb;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
}

const UINT & MyEngine::cPolygon::GetLineColor() const
{
	return m_lineColor;
}

void MyEngine::cPolygon::SetLineStyle(const UINT & style)
{
	m_lineStyle = style;
	DeleteObject(m_hPen);
	m_hPen = CreatePen(m_lineStyle, m_lineWidth, m_lineColor);
}

const UINT & MyEngine::cPolygon::GetLineStyle()
{
	return m_lineStyle;
}

void MyEngine::cPolygon::SetFill(const BOOL & b)
{
	m_isFill = b;
}

const BOOL & MyEngine::cPolygon::IsFill() const
{
	return m_isFill;
}

void MyEngine::cPolygon::SetFillColor(const UINT & rgb)
{
	m_fillColor = rgb;
	DeleteObject(m_hBrush);
	m_hBrush = CreateSolidBrush(m_fillColor);
}

const UINT & MyEngine::cPolygon::GetFillColor() const
{
	return m_fillColor;
}