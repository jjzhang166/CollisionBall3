#pragma once
#include"cBaseUI.h"

namespace MyEngine
{
	/*
	cLine
	直线
	*/
	class cLine:public cBaseUI
	{
	public:
		cLine();

		/*
		有参构造函数，初始化直线坐标点及其他一些性质
		@Param：
			POINT start：构成直线的第一个点
			POINT end：构成直线的第二个点
		*/
		explicit cLine(const POINT& start, const POINT& end);

		/*
		有参构造函数，初始化直线坐标点及其他一些性质
		@Param：
			int startx：第一个点的x坐标
			int starty：第一个点的y坐标
			int endx：第二个点的x坐标
			int endy：第二个点的y坐标
		*/
		explicit cLine(const int& startx, const int& starty, const int& endx, const int& endy);

		virtual ~cLine();

		/*
		SetStartPoint(const POINT&  start)
		设置构成直线的第一个坐标点
		@Param：
			POINT start：第一个坐标点的值
		*/
		void SetStartPoint(const POINT& start);

		/*
		SetEndPoint(const POINT& end)
		设置构成直线的第二个坐标点
		@param：
			POINT end：第二个坐标点的值
		*/
		void SetEndPoint(const POINT& end);

		/*
		GetStartPoint()
		获取第一个坐标点的值
		@return POINT：
			第一个坐标点的值
		*/
		const POINT& GetStartPoint() const;

		/*
		GetEndPoint()
		获第二个坐标点的值
		@return POINT：
			第二个坐标点的值
		*/
		const POINT& GetEndPoint() const;

		/*
		SetStartPoint(const POINT&  start)
		设置构成直线的第一个坐标点
		@Param：
			int x：第一个坐标点的x坐标
			int y：第一个坐标点的y坐标
		*/
		void SetStartPoint(const int& x, const int& y);

		/*
		SetEndPoint(const POINT& end)
		设置构成直线的第二个坐标点
		@param：
			int x：第二个坐标点的x坐标
			int y：第二个坐标点的y坐标
		*/
		void SetEndPoint(const int& x, const int& y);

		/*
		SetWidht(const int& w)
		设置直线宽度
		@Param ：
			int w：直线宽度
		*/
		void SetWidth(const int& w);

		/*
		GetWidth()
		获取直线宽度
		@return int：
			直线宽度
		*/
		const int& GetWidth() const;

		/*
		SetColor(const UINT& rgb)
		设置直线颜色
		@Param：
			UINT rgb：直线颜色rgb色
		*/
		void SetColor(const UINT& rgb);

		/*
		GetColor()
		获取直线颜色
		@return UINT：
			直线颜色
		*/
		const UINT& GetColor() const;

		/*
		SetStyle(const UINT& style)
		设置直线风格
		@Param：
			UINT style：直线风格
		*/
		void SetStyle(const UINT& style);

		/*
		GetStyle()
		获取直线风格
		@return UINT：
			直线风格
		*/
		const UINT& GetStyle() const;

	   /*
		Draw(HDC hDc)
		绘制ui控件
		@Param:
			HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) override;


		/*
		GetRect()
		获取ui控件一个矩形区域
		@return RECT：
		ui控件的矩形区域
		*/
		virtual const RECT GetRect() const override;
	private:
		POINT m_startPoint;

		POINT m_endSPoint;

		int m_width;

		UINT m_color;

		UINT m_style;

		HPEN m_hPen;
	};
}