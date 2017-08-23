#include "stdafx.h"
#include "cResourcePool.h"
#include<utility>
using namespace MyEngine;
using namespace std;

//单例设计模式
cResourcePool* theOne = nullptr;

cResourcePool* MyEngine::cResourcePool::GetResourcePool()
{
	if (theOne == nullptr)
	{
		theOne = new cResourcePool;
		return theOne;
	}
	return theOne;
}

void MyEngine::cResourcePool::AddObjByKey(string key, const HGDIOBJ & hobj)
{
	m_pool[key] = hobj;
}

void MyEngine::cResourcePool::AddMulObjByKey(std::string key, const std::vector<HGDIOBJ> hobjList)
{
	m_mulPool[key] = hobjList;
}

HGDIOBJ MyEngine::cResourcePool::GethObjByKey(string key)
{
	auto it=m_pool.find(key);
	if (it != std::end(m_pool))
	{
		return it->second;
	}
	return NULL;
}

std::vector<HGDIOBJ> MyEngine::cResourcePool::GetMulObjByKey(std::string key)
{
	auto it = m_mulPool.find(key);
	if (it != end(m_mulPool))
	{
		return it->second;
	}
	return vector<HGDIOBJ>();
}

bool MyEngine::cResourcePool::ReleaseByKey(std::string key)
{
	bool bRet = false;
	auto it = m_pool.find(key);
	if (it != std::end(m_pool))
	{
		DeleteObject(it->second);
		m_pool.erase(it);
		bRet = true;
	}
	auto mulIt = m_mulPool.find(key);
	if (mulIt != std::end(m_mulPool))
	{
		for (auto obj : mulIt->second)
		{
			DeleteObject(obj);
		}
		mulIt->second.clear();
		m_mulPool.erase(mulIt);
		bRet = true;
	}
	return bRet;
}

void MyEngine::cResourcePool::ReleaseSelf()
{
	if (theOne != nullptr)
	{
		delete theOne;
		theOne = nullptr;
	}
}

cResourcePool::cResourcePool()
{
}

cResourcePool::~cResourcePool()
{
	for (auto ait : m_pool)
	{
		DeleteObject(ait.second);
	}
	m_pool.clear();
	for (auto bit : m_mulPool)
	{
		for (auto it : bit.second)
		{
			DeleteObject(it);
		}
		bit.second.clear();
	}
	m_mulPool.clear();
}