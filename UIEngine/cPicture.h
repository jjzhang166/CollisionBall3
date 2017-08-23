#pragma once
#include<string>
#include"cBaseUI.h"

namespace MyEngine
{

	/*
	cPicture
	图片
	*/
	class cPicture:public cBaseUI
	{
	public:
		cPicture();

		/*
		*有参构造函数
		@Param:
			HBITMAP hBitmap:位图句柄
		*/
		explicit cPicture(const HBITMAP& hBitmap);

		/*
		有参构造函数
		@Param：
			LPWSTR name：图片路径名
			int w：指定图片宽度,w=0为原图宽度
			int h：制定图片高度，h=0原图高度
		*/
		explicit cPicture(const LPWSTR& name,int w=0,int h=0);

		/*
		通过key值初始化图片
		*@Param:
		*	key:key值
		*/
		explicit cPicture(const std::string key);
		
		virtual ~cPicture();

		/*
		GetRect()
		获取ui控件一个矩形区域
		@return RECT：
		ui控件的矩形区域
		*/
		virtual const RECT GetRect() const  override;

		/*
		Draw(HDC hDc)
		绘制ui控件
		@Param:
		HDC hDc:设备DC
		*/
		virtual bool Draw(HDC hDc) override;

		/*
		SetBitmap(const HBITMAP& hBitmap)
		指定一个位图句柄
		@Param：
			HBITMAP hBitmap：为图句柄
		*/
		void SetBitmap(const HBITMAP& hBitmap);

		/*
		SetBitmap(const LPWSTR& name,int w,int y)
		通过一个路径加载一个位图
		@Param：
			LPWSTR name:图片路径名
			int w：指定图片宽度，w=0原图宽度
			int h：制定图片高度，h=0原图高度
		*/
		void SetBitmap(const LPWSTR& name, int  w = 0, int  h = 0);

		/*
		*SetBitmapByKey(std::string key);
		*通过key值设置图片
		*@Param 
		*	key：key值
		*/
		void SetBitmapByKey(std::string key);

		/*
		GetBitmap()
		获取图片句柄
		@return
			图片句柄
		*/
		const HBITMAP& GetBitmap() const;

		/*
		SetIsLucency(const BOOL& b)
		设置图片是否具有透明色
		@Param：
			BOOL b：是否具有透明色
		*/
		void SetIsLecency(const BOOL& b);

		/*
		IsLucnecy()
		图片是否具有透明色
		@return BOOL：
			TRUE：具有透明色
			FALSE：不具有透明色
		*/
		const BOOL& IsLucency() const;

		/*
		SetLucencyColor(const UINT& rgb)
		设置图片透明rgb色
		@Param:
			UINT rgb:透明色
		*/
		void SetLucency(const UINT& rgb);

		/*
		GetLucencyColor()
		获取透明色
		@return UINT：
			透明色
		*/
		const UINT& GetLucencyColor() const;

		/*
		GetConfig()
		获取图片信息
		@return BITMAP：
			图片详细信息
		*/
		const BITMAP& GetConfig() const;
	private:
		/*
		SetPicConfig()
		设置图片信息
		*/
		void SetPicConfig();

		HBITMAP m_hBitmap;

		BOOL m_isLucency;

		UINT m_lucencyRgb;

		BITMAP m_bmpConfig;
	};
}