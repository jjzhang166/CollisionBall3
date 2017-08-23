#pragma once
#include"cBaseUI.h"
#include<vector>
#include<initializer_list>

namespace MyEngine {


	/*
	Polygon
	对边形
	根据多边形基点循序依次连接形成多边形
	*/
	class cPolygon:public cBaseUI
	{
	public:
		cPolygon();

		/*
		有参构造函数，初始化多边形基点
		@Param：
			std::initializer_list<POINT> pointList:多边形基点列表，构成多边形的坐标点
		*/
		explicit cPolygon(const std::initializer_list<POINT> pointList);

		virtual ~cPolygon();

		virtual const RECT GetRect() const override;

		/*
		SetPolygon(const std::initializer_list<POINT>& pointList)
		设置构成多变行的基点
		@Param：
			std::initializer_list<POINT> pointList:多边形基点列表，构成多边形的坐标点
		*/
		void SetPolygon(const std::initializer_list<POINT>& pointList);

		/*
		AlterOnePoint(const POINT& oldPoint,cosnt POINT& newPoint);
		修改多变行的某一坐标点
		@Param：
			POINT oldPoint ：旧的坐标点
			POINT newPoint：新的坐标点
		*/
		void AlterOnePoint(const POINT& oldPoint, const POINT& newPoint);

		/*
		Draw(HDC hDc)
		绘制ui控件
		@Param:
		HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) override;

		/*
		SetWidth(const unsigned& width)
		设置多边形边缘宽度
		@Param：
			unsigned width：多边形边缘宽度
		*/
		void SetLineWidth(const unsigned& width);

		/*
		GetWidth()
		获取多边形边缘宽度
		@return unsigned：
			多边形边缘宽度
		*/
		const unsigned& GetLineWidth() const;

		/*
		SetLineColor(const UINT& rgb);
		设置多边形基线颜色
		@Param：
			UINT rgb：基线rgb色
		*/
		void SetLineColor(const UINT& rgb);

		/*
		GetLineColor()
		获取基线rgb色
		@return UINT：
			rgb色
		*/
		const UINT& GetLineColor() const;

		/*
		*SetLineStyle();
		*设置线条风格
		*@Param:
		*	style:线条风格
		*/
		void SetLineStyle(const UINT& style);
		const UINT& GetLineStyle();

		/*
		SetFill(cosnt BOOL& b)
		设置是否填充多边形
		@Param：
			BOOL b:TRUE表示填充，FALSE表示不填充
		*/
		void SetFill(const BOOL& b);

		/*
		IsFill()
		判断是否为填充多边形
		@return BOOL：
			TRUE:为填充多边形
			FALSE：不为填充多边形
		*/
		const BOOL& IsFill() const;

		/*
		SetFillColor(cosnt UINT& rgb)
		设置填充色
		@Param：
			UINT rgb：填充rgb色
		*/
		void SetFillColor(const UINT& rgb);

		/*
		GetFillColor()
		获取填充色
		@return UINT：
			填充色
		*/
		const UINT& GetFillColor() const;
	private:
		std::vector<POINT> m_pointList;

		unsigned m_sideNums;

		unsigned m_lineWidth;

		UINT m_lineColor;
		
		UINT m_lineStyle;

		BOOL m_isFill;

		UINT m_fillColor;

		HBRUSH m_hBrush;

		HPEN m_hPen;
	};
}