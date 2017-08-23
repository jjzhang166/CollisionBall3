#pragma once
#include"cBaseUI.h"
#include<string>

namespace MyEngine
{
	//按钮状态枚举
	enum Mouse_Status
	{
		Mouse_Up,   //鼠标按下
		Mouse_Down,   //鼠标弹起
	};

	/*
	cButton
	按钮
	*/
	class cButton :public cBaseUI
	{
	public:
		cButton();

		/*
		有参构造函数，初始化按钮名称和宽高
		@Param:
			LPWSTR Name:按钮名称
			int width:按钮宽度
			int height：按钮高度
		*/
		explicit cButton(const LPWSTR& Name,const int& width,const int& height);

		/*
		有参构造函数，以图片初始化按钮
		@Param LPWSTR：
			LPWSTR bmpPath:图片路径
		*/
		explicit cButton(const LPWSTR& bmpPath);

		/*
		有参构造函数，以图片初始化按钮
		@Param LPWSTR：
			HBITMAP hbitmap:位图句柄
		*/
		explicit cButton(const HBITMAP& hbitmap);

		/*
		*通过key值初始化图片按钮
		*@Param 
		*	key：key值
		*/
		explicit cButton(std::string key);

		virtual ~cButton();

		/*
		SetName()
		设置按钮名称
		@Param：
			LPWSTR name:按钮名
		*/
		void SetName(const LPWSTR& Name);

		/*
		GetName()
		获取按钮名
		@return LPWSTR：
			按钮名
		*/
		const LPWSTR& GetName() const;

		/*
		SetWidth(const int& width)
		设置按钮宽度
		@Param：
			int width：按钮宽度
		*/
		void SetWidth(const int& width);

		/*
		GetWidth()
		获取按钮宽度
		@return int：
			按钮宽度
		*/
		const int& GetWidth() const;

		/*
		SetHeight(const int& height)
		设置按钮高度
		@Param：
			int height：按钮高度
		*/
		void SetHeight(const int& Height);

		/*
		GetHeight()
		获取按钮高度
		@return int：
			按钮高度
		*/
		const int& GetHeight() const;

		/*
		SetBount(const int& n)
		设置按钮边框宽度
		@Param：
			int n：按钮边框宽度
		*/
		void SetnBount(const int& n);

		/*
		GetBount()
		获取按钮边框宽度
		@return int：
			按钮边框宽度
		*/
		const int& GetBount() const;

		/*
		*m_firstBountColor、m_secBountColor：第一边框色和第二边框色的setter和getter方法
		*/
	    void SetFirstBountColor(const UINT& rgb);
		void SetSecBountColor(const UINT& rgb);
		const UINT& GetFirstBountColor();
		const UINT& GetSecBountColor();

		/*
		SetFirstColor(const UINT& rgb)
		设置按钮第一颜色
		@Param:
			UINT rgb:RGB色
		*/
		void SetfirstColor(const UINT& rgb);

		/*
		GetFirstColor()
		获取按钮第一颜色
		@return UINT:
			按钮第一颜色
		*/
		const UINT& GetfirstColor() const;

		/*
		SetSecondColor(const UINT& rgb)
		设置第二颜色
		@Param：
			UINT rgb：RGB色
		*/
		void SetSecondColor(const UINT& rgb);

		/*
		GetsecondColor()
		获取按钮第二颜色
		@return UINT：
			按钮第二颜色
		*/
		const UINT& GetSecondColor() const;

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

		/*
		DrawNormal(HDC hDc)
		绘制无背景图片的按钮
		@Param：
			HDC hDc：窗口设备DC
		*/
		bool DrawNormal(HDC hDc);

		/*
		DrawBitmapBtn
		绘制背景图片按钮
		@Param：
			HDC hDc：窗口设备DC
		*/
		bool DrawBitmapBtn(HDC hDc);

		/*
		SetFont(const LPWSTR& font);
		设置字体
		@Param：
			LPWSTR font：字体
		*/
		void SetFont(const LPWSTR& font);

		/*
		GetFont()
		获取按钮文本字体
		@return LPWSTR：
			按钮文本字体
		*/
		const LPWSTR& GetFont() const;

		/*
		SetFontColor()
		设置字体颜色
		@Param：
			UINT rgb：rgb色
		*/
		void SetFontColor(const UINT& rgb);

		/*
		GetFontColor()
		获取字体颜色
		@return UINT：
			字体颜色
		*/
		const UINT& GetFontColor() const;

		/*
		SetBmpBtn(const LPWSTR& bmpPath)
		设置按钮背景图片
		@Param：
			LPWSTR bmpPath：图片路径
		*/
		void SetBmpBtn(const LPWSTR& bmpPath);

		/*
		SetBmpBtn(const HBITMAP& hbitmap)
		设置按钮背景图片
		@Param：
			HBITMAP hbitmap：位图句柄
		*/
		void SetBmpBtn(const HBITMAP& hbitmap);
	private:
		/*
		ChangeColor()
		改变按钮背景色,当按钮得到和失去焦点时会改变背景色
		*/
		void ChangeColor();

		/*
		ChangeBountColor()
		当鼠标按下和弹起时改变按钮边框颜色
		@param：
		Btn_Status clicked:鼠标是否按下
		*/
		void ChangeBountColor(Mouse_Status clicked);

		LPWSTR m_Name;

		int m_width;

		int m_height;

		//边框宽度
		int m_nBount;

		UINT m_BountColor;

		UINT m_firstBountColor;

		UINT m_secBountColor;

		//按钮为未获取得焦点时的背景色
		UINT m_firstColor;

		//按钮获取焦点时的背景色
		UINT m_secondColor;

		LPWSTR m_font;

		UINT m_fontColor;

		UINT m_bgColor;

		HBITMAP m_bgBitmap;

		HFONT m_hFont;

		HPEN m_hPen;

		HBRUSH m_hBrush;
	};
}