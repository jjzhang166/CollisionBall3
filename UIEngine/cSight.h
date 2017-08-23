#pragma once
#include<list>
#include"cBaseUI.h"
#include"cMyTimer.h"

namespace MyEngine
{
	/*
	*class cSight
	*视野，管理一个视野（即当前所能看到的所有事物）的内容
	*/
	class cSight:public cMyTimer,public cBaseUI
	{
	public:
		cSight();
		virtual ~cSight();
		virtual const RECT GetRect() const override;

		/*
		*Draw(HDC hDc)
		*绘制ui控件
		*@Param:
		*HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) override;

		/*
		*addChild(cBaseUI* ui);
		*添加子节点
		*@Param ui*：子节点对象指针
		*/
		void addChild(cBaseUI* ui);

		virtual void SetUid(UINT_PTR uid) override;
		virtual int OnTimer(int id, int iParam, string str) override;

		/*
		*RemoveChild(cBaseUI* ui);
		*移除子节点
		*@Param child：子节点指针对象
		*@return bool：成功返回true，否则返回false
		*/
		bool RemoveChild(cBaseUI* child);

		/*
	    *RemoveAllChild();
		*移除所有子节点
		*/
		void RemoveAllChild();
	private:
		/*
		*释放资源
		*/
		void Release();

		std::list<cBaseUI*> m_uiList;

	protected:
		CLock m_lock;
	};
}