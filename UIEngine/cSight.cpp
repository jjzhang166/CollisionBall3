#include "stdafx.h"
#include "cSight.h"
#include"cGameEngine.h"
using namespace MyEngine;

cSight::cSight()
{
}


cSight::~cSight()
{
	CloseThread();
	Release();
}

const RECT MyEngine::cSight::GetRect() const
{
	return RECT();
}

bool MyEngine::cSight::Draw(HDC hDc)
{
	for (auto it : m_uiList)
	{
		it->Draw(hDc);
	}
	return false;
}

void MyEngine::cSight::addChild(cBaseUI * ui)
{
	ui->SetParent(this);
	ui->SetUid(this->m_Uid);
	m_uiList.push_back(ui);
}

void MyEngine::cSight::SetUid(UINT_PTR uid)
{
	m_Uid = uid;
	for (auto it : m_uiList)
	{
		it->SetUid(this->m_Uid);
	}
}

int MyEngine::cSight::OnTimer(int id, int iParam, string str)
{
	return 0;
}

bool MyEngine::cSight::RemoveChild(cBaseUI * child)
{
	for (auto it = std::begin(m_uiList); it != std::end(m_uiList);)
	{
		if ((*it) == child)
		{
			cGameEngine::GetEngine()->DeleteEvent(child);
			it = m_uiList.erase(it);
			delete child;
			child = nullptr;
		}
		else
		{
			++it;
		}
	}
	return false;
}

void MyEngine::cSight::RemoveAllChild()
{
	Release();
}

void MyEngine::cSight::Release()
{
	for (auto it : m_uiList)
	{
		cGameEngine::GetEngine()->DeleteEvent(it);
		delete it;
		it = nullptr;
	}
	m_uiList.clear();
}
