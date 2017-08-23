#pragma once
#include<cSight.h>
#include<cCircle.h>
#include<cText.h>
#include<cRectangle.h>
#include<string>
#define Basic_Speed 5
#define OneExp 10
#define OneFExp 0.3f
#define Basic_Exp 20
#define Basic_Volume 310.0f
#define Basic_Radius 15
#define MAX_RADIUS 250.0f
#define MAX_PHYSICAL 100.0f
#define ONE_PHYSICAL 1.2

class cGamePlayer :
	public MyEngine::cSight
{
public:
	cGamePlayer();
	~cGamePlayer();

	/*
	SetX(const int& x);
	设置ui控件x坐标
	@Param ：
	int x：新的x坐标
	*/
	virtual void SetX(const int& x) override;

	/*
	GetX()
	获取ui控件x坐标
	@return const int&:
	ui控件当前x坐标
	*/
	virtual const int& GetX() const override;

	/*
	SetY(const int& y)
	设置ui控件y坐标
	@Param ：
	int y:新的y坐标
	*/
	virtual void SetY(const int& y) override; 

	/*
	GetY()
	获取ui控件当前y坐标
	@return int：
	当前y坐标
	*/
	virtual const int& GetY() const override;

	void DecRadius();  //减少半径
	void SetRadius(const int& radius);

	/*
	*CalcScreenSite();
	*根据玩家世界坐标计算屏幕坐标
	*/
	void CalcScreenSite();

	/*
	*Move();
	*移动角色
	*@return bool：true：位置发生了移动，false没有发生移动
	*/
	bool Move();

	void SetVx(const int& vx);
	const int& GetVx();
	void SetVy(const int& vy);
	const int& GetVy();

	void SetWorldX(const int& x);
	void SetWorldY(const int& y);
	const int& GetWorldX();
	const int& GetWorldY();

	void AddExp(int value);
	void SetExp(int value);
	const int& GetExp();

	const int& GetBasicSpeed();

	const void SetPhysicalValue(const int& value);
	const int& GetPhysicalValue();
	 
	MyEngine::cCircle* GetBody();

	void AccPhysical(int f=1);  //增加体力值

	void DecPhysical(); //减少体力值

	void Accelerate();  //加速

	void Decelerate();  //减速

	void SetbDel(bool b);

	bool GetbDel();
private:
	int m_vx;  //x轴方向上的速度
	int m_vy;   //y轴方向上的速度
	int m_worldx;   //世界坐标系上的x坐标
	int m_worldy;   //世界坐标系上的y坐标
	int m_exp ;  //经验值
	float m_fexp;
	int m_basicSpeed;
	int m_physicalValue; //体力值
	MyEngine::cCircle* m_body;
	MyEngine::cRectangle* m_physicalBar;
	bool m_bDel;
public:
	int m_tag = 0;    //标签
};

