#pragma once

#define _CALLFUNC(SEL_CALLFUNC) static_cast<MyEngine::SEL_CallFunc>(&SEL_CALLFUNC)

namespace MyEngine
{
	class cBaseUI;
	typedef void(*CallEeventBack)(void *param);
	typedef void(cBaseUI::*SEL_CallFunc)(void* Param);

	typedef struct _UI_Event
	{
		cBaseUI* Trigger;
		UINT_PTR EventId;
		cBaseUI* Handler;
		SEL_CallFunc CallProc;
		void* Param;
	}UI_Event;

	enum UI_Type
	{
		UI_Base,
		UI_Amination,
		UI_Button,
		UI_Circle,
		UI_Line,
		UI_Picture,
		UI_Polygon,
		UI_Rectangle,
		UI_Text,
		UI_Triangle,
	};

	/*
	cBaseUI
	所有UI类的基类
	*/
	class cBaseUI
	{
	public:
		cBaseUI();
		/*
		有参构造函数
		@Param :
			int x：ui控件x坐标
			int y : ui控件y坐标
		*/
		explicit cBaseUI(const int& x, const int& y);

		friend class cGameEngine;

		virtual ~cBaseUI();

		/*
		SetX(const int& x);
		设置ui控件x坐标
		@Param ：
			int x：新的x坐标
		*/
		virtual void SetX(const int& x);

		/*
		GetX()
		获取ui控件x坐标
		@return const int&:
			ui控件当前x坐标
		*/
		virtual const int& GetX() const;

		/*
		SetY(const int& y)
		设置ui控件y坐标
		@Param ：
			int y:新的y坐标
		*/
		virtual void SetY(const int& y);

		/*
		GetY()
		获取ui控件当前y坐标
		@return int：
			当前y坐标
		*/
		virtual const int& GetY() const;

		/*
		GetRect()
		获取ui控件一个矩形区域
		@return RECT：
			ui控件的矩形区域
		*/
		virtual const RECT GetRect() const=0;

		/*
		Draw(HDC hDc)
		绘制ui控件
		@Param:
			HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) = 0;

		/*
		GetType()
		获取控件种类
		@return UI_Type：
			控件种类
		*/
		virtual const UI_Type& GetType() const;

		/*
		GetID()
		获取控件ID
		@return UINT_PTR:
			控件ID，若未分配ID这返回-1，只有通过cGameEngine创建的控件或加入cGameEngine的控件才会分配ID
		*/
		virtual const UINT_PTR& GetID() const;
		virtual void SetUid(UINT_PTR Uid);

		void SetParent(cBaseUI* parent);
		cBaseUI* GetParent();
	protected:
		int m_x;
		int m_y;
		UI_Type m_type;
		UINT_PTR m_Uid = -1;

		//标记是否使用了资源池中的资源
		BOOL m_isUsePool;

		cBaseUI* m_parent;
	};
}