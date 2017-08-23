#pragma once
#include"cBaseUI.h"

namespace MyEngine
{

	/**
	cCircle
	圆
	*/
	class cCircle:public cBaseUI
	{
	public:
		cCircle();

		/*
		有参构造函数，初始圆的外接矩形区域
		@Param：
			center:圆心
			radius：半径
		*/
		explicit cCircle(const POINT& center, const UINT& radius);

		virtual ~cCircle();

		/*
		m_radius半径的getter和setter方法
		*/
		void SetRaduis(const UINT& radius);
		const UINT& GetRadius();

		/*
		m_center圆心的getter和setter
		*/
		void SetCenter(const POINT& center);
		const POINT GetCenter();

		/*
		SetCircleArea()
		设置圆的外接矩形区域
		@param:
			center:圆心
			radius：半径
		*/
		void SetCircle(const POINT& center,const UINT& radius);

		/*
		SetLineColor(const UINT& rgb)
		设置线段颜色
		@param：
			UINT rgb：线段rgb色
		*/
		void SetLineColor(const UINT& rgb);

		/*
		GetLineColor()
		获取线段颜色
		@return UINT：
			线段rgb色
		*/
		const UINT& GetLineColor() const;

		/*
		SetIsFill(const bool& ok)
		设置是否填充圆形区域
		@Param：
			bool ok：是否填充
		*/
		void SetIsFill(const bool& ok);

		/*
		GetIsFill()
		获取是否填充
		@return bool：
			true：填充
			false：非填充
		*/
		const bool& GetIsFill() const;

		/*
		SetFillColor(const UINT& rgb)
		设置填充色
		@Param：
			UINT rgb：填充色
		*/
		void SetFillColor(const UINT& rgb);

		/*
		GetFillColor()
		获取填充色
		@return UINT:
			填充色
		*/
		const UINT& GetFillColor() const;

		/*
		SetLineStyle(const UINT& style)
		设置线段风格
		@param:
			UINT style：线段风格
		*/
		void SetLineStyle(const UINT& style);

		/*
		GetLineStyle()
		获取线段风格
		@return UINT：
			线段风格
		*/
		const UINT& GetLineStyle(const UINT& style);

		/*
		GetRect()
		获取ui控件一个矩形区域
		@return RECT：
		ui控件的矩形区域
		*/
		virtual const RECT GetRect() const override;

		/*
		Draw(HDC hDc)
		绘制ui控件
		@Param:
		HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) override;
	private:
		int m_lineWidth;

		UINT m_LineColor;

		bool m_isFill;

		UINT m_fillColor;

		UINT m_lineStyle;

		HBRUSH m_hBrush;

		HPEN m_hPen;

		//半径
		UINT m_radius;
	};
}