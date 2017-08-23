#pragma once
#include"cBaseUI.h"

namespace MyEngine
{
	/*
	cRectangle
	矩形
	*/
	class cRectangle:public cBaseUI
	{
	public:
		cRectangle();

		/*
		*通过举行中心点和宽，高初始化矩形
		*@Param center：矩形中心点
		*/
		explicit cRectangle(const POINT& center, const int& width = 2, const int& height = 2);

		virtual ~cRectangle();

		/*
		*SetRect(const POINT& center)
		*设置矩形中心点
		*@Param center：中心点
		*/
		void SetCenter(const POINT& center);

		/*
		*SetWidth(const int& width);
		*设置举行宽度
		*@Param width：宽度
		*/
		void SetWidth(const int& width);
		const int& GetWidth();

		/*
		*SetHeight(const int& height);
		*设置举行高度
		*@Param height：矩形高度
		*/
		void SetHeight(const int& height);
		const int& GetHeight();

		/*
		GetRect()
		获取ui控件一个矩形区域
		@return RECT：
			ui控件的矩形区域
		*/
		virtual const RECT GetRect() const override;

		/*
		SetLineColor(const UINT& rgb)
		设置线段颜色
		@Param:
			UINT rgb：线段颜色
		*/
		void SetLineColor(const UINT& rgb);

		/*
		GetLineColor()
		获取线段颜色
		@return UINT:
			线段颜色
		*/
		const UINT& GetLineColor() const;

		/*
		*SetLineWidth(const int& linewidth);
		*设置边框线的宽度
		*/
		void SetLineWidth(const int& linewidth);
		const int& GetLineWidth();

		/*
		SetIsFill(const bool& ok)
		设置是否填充矩形区域
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
		const bool& isFIll() const;

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
		Draw(HDC hDc)
		绘制ui控件
		@Param:
		HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) override;
	private:
		int m_width;

		int m_height;

		int m_Linewidth;

		UINT m_lineColor;

		bool m_isFill;

		UINT m_fillColor;

		UINT m_lineStyle;

		HPEN m_hPen;

		HBRUSH m_hBrush;
	};
}