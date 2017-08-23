#include "stdafx.h"
#include "Lock.h"

CLock::CLock()
{
	InitializeCriticalSection(&m_criticalSection);
}

CLock::~CLock()
{
}

void CLock::Lock()
{
	EnterCriticalSection(&m_criticalSection);
}

void CLock::UnLock()
{
	LeaveCriticalSection(&m_criticalSection);
}