#pragma once
#include<cAmination.h>
#define Hole_Radius 45

class cBackHole:public MyEngine::cAmination
{
public:
	cBackHole();
	~cBackHole();

	void SetWorldPos(const POINT& pt);  
	POINT GetWorldPos();

	void DecLifeCycle();  //减少生命周期
	void SetLifeCycle(int cycle);
	int GetLifeCycle();

	void SetControlRadius(int controlradius);
	int GetControlRadius();

	void SetPower(int power);
	int GetPower();

	POINT GetCenter();  //获取屏幕坐标中心点
private:
	POINT m_worldPos;
	int m_lifecycle;  //生命周期
	int m_controlRadius; //影响半径
	int m_power;
};