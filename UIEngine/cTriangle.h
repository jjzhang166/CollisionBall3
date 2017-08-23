#pragma once
#include"cBaseUI.h"

namespace MyEngine
{

	/*
	cTriangle
	三角形
	*/
	class cTriangle:public cBaseUI
	{
	public:
		cTriangle();

		/*
		有参构造函数，初始化构成三角形的三个点
		@Param：
			POINT p1:第一个点
			POINT p2：第二个点
			POINT p3：第三个点
		*/
		explicit cTriangle(const POINT& p1, const POINT& p2, const POINT& p3);

		virtual ~cTriangle();

		/*
	    SetFirstPoint(const POINT& p1);
		设置构成三角形的第一个点
		@Param ：
			POINT p1：坐标点
		*/
		void SetFirstPoint(const POINT& p1);

		/*
		SetSecondPoint(const POINT& p2);
		设置构成三角形的第二个点
		@Param ：
		POINT p1：坐标点
		*/
		void SetSecondPoint(const POINT& p2);

		/*
		SetThirdPoint(const POINT& p3);
		设置构成三角形的第三个点
		@Param ：
		POINT p1：坐标点
		*/
		void SetThirdPoint(const POINT& p3);

		/*
		GetFirstPoint()
		获取三角形的第一个点
		@return POINT：
			坐标点
		*/
		const POINT& GetFirstPoint() const;

		/*
		GetSecondPoint()
		获取三角形的第二个点
		@return POINT：
			坐标点
		*/
		const POINT& GetSecondPoint() const;

		/*
		GetThirdPoint() 
		获取三角形的第三个点
		@return POINT：
			坐标点
		*/
		const POINT& GetThirdPoint() const;

		/*
		SetLineColor(const UINT& rgb);
		设置线段颜色
		@Param：
			UINT rgb：线段rgb色
		*/
		void SetLineColor(const UINT& rgb);

		/*
		GetLineColor() 
		获取线段颜色
		@return UINT：
			线段颜色
		*/
		const UINT& GetLineColor() const;

		/*
		SetLineWidth(const int& width)
		设置线段宽度
		@return width：
			线段宽度
		*/
		void SetLineWidth(const int& width);

		/*
		GetLineWidth()
		获取线段宽度
		@return int：
			线段宽度
		*/
		const int& GetLineWidth() const;

		/*
		SetIsFill(const bool& ok)
		设置是否填充三角形区域
		@Param:
			bool ok:是否填充
		*/
		void SetIsFill(const bool& ok);

		/*
		IsFill()
		是否填充
		@return bool：
			true：填充
			false：非填充
		*/
		const bool& isFill() const;

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
		@return UINT：
			填充色
		*/
		const UINT& GetFillColor() const;

		/*
		SetLineStyle(const UINT&v style)
		设置线段风格
		@Param：
			UINT style:线段风格
		*/
		void SetLineStyle(const UINT& style);

		/*
		GetLineStyle()
		获取线段风格
		@return UINT：
			线段风格
		*/
		const UINT& GetLineStyle() const;

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
		POINT m_firstPoint;

		POINT m_secondPoint;

		POINT m_thirdPoint;

		UINT m_LineColor;

		int m_Linewidth;

		bool m_isFill;

		UINT m_FillColor;

		UINT m_lineStyle;

		HPEN m_hPen;

		HBRUSH m_hBrush;
	};
}