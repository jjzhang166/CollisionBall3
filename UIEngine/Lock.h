#pragma once

/*
*class CLock
*»¥³âËø
*/
class CLock
{
public:
	CLock();
	virtual ~CLock();
	/*
	*Lock();
	*¼ÓËø
	*/
	void Lock();

	/*
	*UnLock();
	*½âËø
	*/
	void UnLock();
private:
	CRITICAL_SECTION m_criticalSection;
};