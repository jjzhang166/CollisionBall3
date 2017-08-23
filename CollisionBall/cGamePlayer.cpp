#include "stdafx.h"
#include "cGamePlayer.h"
#include<cGameEngine.h>
#include<random>
using namespace MyEngine;
using namespace std;

cGamePlayer::cGamePlayer()
{
	random_device rad;
	m_body = new cCircle;
	m_physicalBar = new cRectangle;
	m_bDel = false;
	m_basicSpeed = Basic_Speed;
	m_physicalValue = 100;
	m_vx = rad() % 2 == 0 ? -Basic_Speed : Basic_Speed;
	m_vy = rad() % 2 == 1 ? -Basic_Speed : Basic_Speed;
	m_exp = 0;
	m_fexp = 15.0f;
	m_worldx = rad() % (int)MAP_SIZEX - SCREENSIZEX*0.5;
	m_worldy = rad() % (int)MAP_SIZEY;
	m_worldx < 0 ? m_worldx = 10 : 1;
	m_body->SetRaduis(15);
    m_body->SetIsFill(true);
	m_body->SetFillColor(RGB(rad() % 256, rad() % 256, rad() % 256));
	m_physicalBar->SetWidth(30);
	m_physicalBar->SetHeight(4);
	m_physicalBar->SetLineWidth(2);
	m_physicalBar->SetLineColor(RGB(181, 230, 29));
	CalcScreenSite();
	addChild(m_body);
	addChild(m_physicalBar);
}

cGamePlayer::~cGamePlayer()
{
}

void cGamePlayer::SetX(const int & x)
{
	m_body->SetX(x);
	m_physicalBar->SetX(x);
}

const int & cGamePlayer::GetX() const
{
	return m_body->GetX();
}

void cGamePlayer::SetY(const int & y)
{
	m_body->SetY(y);
	m_physicalBar->SetY(y - m_body->GetRadius());
}

const int & cGamePlayer::GetY() const
{
	return m_body->GetY();
}

void cGamePlayer::DecRadius()
{
	int radius = m_body->GetRadius();
	radius > 10 ? SetRadius(radius - 1), --m_fexp : 1;
}

void cGamePlayer::SetRadius(const int & radius)
{
	switch (radius/30)
	{
	case 0:
		m_basicSpeed = Basic_Speed;
		m_vx = (m_vx / abs(m_vx))*m_basicSpeed;
		m_vy = (m_vy / abs(m_vy))*m_basicSpeed;
		break;
	case 1:
		m_basicSpeed = Basic_Speed-1;
		m_vx = (m_vx / abs(m_vx))*m_basicSpeed;
		m_vy = (m_vy / abs(m_vy))*m_basicSpeed;
		break;
	case 2:
		m_basicSpeed = Basic_Speed - 2;
		m_vx = (m_vx / abs(m_vx))*m_basicSpeed;
		m_vy = (m_vy / abs(m_vy))*m_basicSpeed;
		break;
	case 3:
		m_basicSpeed = Basic_Speed - 3;
		m_vx = (m_vx / abs(m_vx))*m_basicSpeed;
		m_vy = (m_vy / abs(m_vy))*m_basicSpeed;
		break;
	case 4:
		m_basicSpeed = Basic_Speed - 4;
		m_vx = (m_vx / abs(m_vx))*m_basicSpeed;
		m_vy = (m_vy / abs(m_vy))*m_basicSpeed;
		break;
	default:
		break;
	}
	m_body->SetRaduis(radius);
	SetPhysicalValue(m_physicalValue);
}

void cGamePlayer::CalcScreenSite()
{
	if (m_worldx < SCREENSIZEX*0.5)
	{
		SetX(m_worldx);
	}
	else if (MAP_SIZEX - m_worldx<SCREENSIZEX*0.5)
	{
		SetX(SCREENSIZEX - MAP_SIZEX + m_worldx);
	}
	else
	{
		SetX(SCREENSIZEX*0.5);
	}
	if (m_worldy < SCREENSIZEY*0.5)
	{
		SetY(m_worldy);
	}
	else if (MAP_SIZEY - m_worldy < SCREENSIZEY*0.5)
	{
		SetY(SCREENSIZEY - MAP_SIZEY + m_worldy);
	}
	else
	{
		SetY(SCREENSIZEY*0.5);
	}
}

bool cGamePlayer::Move()
{
	if (m_vx == 0 && m_vy == 0)
	{
		return false;
	}
	m_worldx += m_vx;
	m_worldy += m_vy;
	m_worldx < 0 ? m_worldx = 0 : 1;
	m_worldx > MAP_SIZEX ? m_worldx = MAP_SIZEX : 1;
	m_worldy < 0 ? m_worldy = 0 : 1;
	m_worldy > MAP_SIZEY ? m_worldy = MAP_SIZEY : 1;
	CalcScreenSite();
	return true;
}

void cGamePlayer::SetVx(const int & vx)
{
	m_vx = vx;
}

const int & cGamePlayer::GetVx()
{
	return m_vx;
}

void cGamePlayer::SetVy(const int & vy)
{
	m_vy = vy;
}

const int & cGamePlayer::GetVy()
{
	return m_vy;
}

void cGamePlayer::SetWorldX(const int & x)
{
	m_worldx = x;
}

void cGamePlayer::SetWorldY(const int & y)
{
	m_worldy = y;
}

const int & cGamePlayer::GetWorldX()
{
	return m_worldx;
}

const int & cGamePlayer::GetWorldY()
{
	return m_worldy;
}

void cGamePlayer::AddExp(int value)
{
	m_exp += value;
	float f = (value / OneExp)*OneFExp;
	m_fexp += f;
	SetRadius(static_cast<int>(m_fexp));
	AccPhysical(f > 1 ? f : 1);
}

void cGamePlayer::SetExp(int value)
{
	m_exp = value;
}

const int & cGamePlayer::GetExp()
{
	return m_exp;
}

const int & cGamePlayer::GetBasicSpeed()
{
	return m_basicSpeed;
}

const void cGamePlayer::SetPhysicalValue(const int & value)
{
	m_physicalValue = value;
	float per = m_physicalValue / MAX_PHYSICAL;
	float updatevalue = per*m_body->GetRadius() * 2;
	m_physicalBar->SetWidth(updatevalue < 2 ? 2 : updatevalue);
}

const int & cGamePlayer::GetPhysicalValue()
{
	return m_physicalValue;
}

cCircle * cGamePlayer::GetBody()
{
	return m_body;
}

void cGamePlayer::AccPhysical(int f)
{
	int addValue = MAX_RADIUS / m_body->GetRadius()*ONE_PHYSICAL;
	m_physicalValue += (addValue *f + 1);
	m_physicalValue >= MAX_PHYSICAL ? m_physicalValue=MAX_PHYSICAL : 1;
	SetPhysicalValue(m_physicalValue);
}

void cGamePlayer::DecPhysical()
{
	m_physicalValue >1 ? --m_physicalValue : 1;
	SetPhysicalValue(m_physicalValue);
}

void cGamePlayer::Accelerate()
{
	if (m_physicalValue>1)
	{
		m_vx = (m_vx / abs(m_vx))*(m_basicSpeed < 2 ? 2 : m_basicSpeed) * 2;
		m_vy = (m_vy / abs(m_vy))*(m_basicSpeed < 2 ? 2 : m_basicSpeed) * 2;
		DecPhysical();
	}
	else
	{
		Decelerate();
	}
}

void cGamePlayer::Decelerate()
{
	m_vx = (m_vx / abs(m_vx))*m_basicSpeed;
	m_vy = (m_vy / abs(m_vy))*m_basicSpeed;
}

void cGamePlayer::SetbDel(bool b)
{
	m_bDel = b;
}

bool cGamePlayer::GetbDel()
{
	return m_bDel;
}

