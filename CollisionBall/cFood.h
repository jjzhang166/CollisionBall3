#pragma once
#include "cCircle.h"
class cFood :
	public MyEngine::cCircle
{
public:
	cFood();
	~cFood();
	unsigned int m_tag; //标签
	POINT m_worldPos;  //世界坐标
};