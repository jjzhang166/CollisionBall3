#include "stdafx.h"
#include "cBackHole.h"

cBackHole::cBackHole()
{
	SetAmination("BackHole");
	SetIsLucnecy(true);
	SetLucnecyColor(RGB(255, 255, 255));
}

cBackHole::~cBackHole()
{
}

void cBackHole::SetWorldPos(const POINT & pt)
{
	m_worldPos = pt;
}

POINT cBackHole::GetWorldPos()
{
	return m_worldPos;
}

void cBackHole::DecLifeCycle()
{
	--m_lifecycle;
}

void cBackHole::SetLifeCycle(int cycle)
{
	m_lifecycle = cycle;
}

int cBackHole::GetLifeCycle()
{
	return m_lifecycle;
}

void cBackHole::SetControlRadius(int controlradius)
{
	m_controlRadius = controlradius;
}

int cBackHole::GetControlRadius()
{
	return m_controlRadius;
}

void cBackHole::SetPower(int power)
{
	m_power = power;
}

int cBackHole::GetPower()
{
	return m_power;
}

POINT cBackHole::GetCenter()
{
	POINT pt;
	pt.x = GetX() + GetConfig().bmWidth / 2;
	pt.y = GetY() + GetConfig().bmHeight / 2;
	return pt;
}