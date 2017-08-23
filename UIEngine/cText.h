#pragma once
#include"cBaseUI.h"

namespace MyEngine
{

	/*
	cText
	文本
	*/
	class cText:public cBaseUI
	{
	public:
		cText();

		/*
		带参构造函数
		@Param 
			LPWSTR text：文本内容
		*/
		explicit cText(const LPWSTR& text);

		virtual ~cText();

		/*
		SetText(LPWSTR text)
		设置文本控件内容
		@Param 
			LPWSTR text:新的文本内容
		*/
		void SetText(const LPWSTR& text);

		/*
		GetText()
		获取文本控件内容
		const LPWSTR&：
			当前文本内容
		*/
		const LPWSTR& GetText() const;

		/*
		Append(LPWSTR text)
		向当前文本内容末尾添加内容
		@return bool:
			true:添加成功
			false：添加失败
		*/
		bool Append(const LPWSTR& text);

		/*
		SetTextColor(const UINT& rgb)
		设置文本内容颜色
		@Param 
			UINT rgb:新设置的文本内容颜色
		*/
		void SetTextColor(const UINT& rgb);

		/*
		GetTextColor()
		获取当前文本内容颜色
		@return UINT:
			当前文本颜色
		*/
		const UINT& GetTextColor() const;

		/*
		SetMode(const int& mode)
		设置文本背景模式
		@Param:
			int mode：新的文本背景模式
		*/
		void SetMode(const int& mode);

		/*
		GetMode()
		获取当前文本背景模式
		@return int:
			当前文本背景模式
		*/
		const int& GetMode() const;

		/*
		SetBgColor(UINT rgb)
		设置当前文本背景颜色
		@Param：
			UINT rgb：新的文本背景颜色
		*/
		void SetBgColor(UINT rgb);

		/*
		GetBgColor()
		获取当前文本背景颜色
		@return UINT:
			当前文本背景颜色
		*/
		const UINT& GetBgColor() const;

		/*
		SetFont(const LPWSTR& font);
		设置字体
		@Param ：
			LPWSTR font：新的字体
		*/
		void SetFont(const LPWSTR& font);

		/*
		GetFont()
		获取当前字体
		@return LPWSTR:
			当前字体
		*/
		const LPWSTR& GetFont() const;

		/*
		SetFontWidth(const int& width)
		设置字体宽度
		@Param ：
			int width：新的字体宽度
		*/
		void SetFontWidth(const int& width);

		/*
		GetFontWidth()
		获取字体宽度
		@return int：
			当前字体宽度
		*/
		const int& GetFontWidth() const;

		/*
		SetFontHeight(const int& height)
		设置字体高度
		@Param ：
			int height：新的字体高度
		*/
		void SetFontHeight(const int& height);

		/*
		GetFontHeight()
		获取字体高度
		@return int：
			当前字体高度
		*/
		const int& GetFonthHeight() const;

		/*
		SetWeight(const UINT& weight)
		设置字体重量
		@Param：
			UINT weight：字体重量
		*/
		void SetWeight(const UINT& weight);

		/*
		GetWeight()
		获取字体重量
		@return UINT：
			字体重量
		*/
		const UINT& GetWeight() const;

		/*
		SetnEscapement(const UINT& nEscapement);
		指定移位向量和设备X轴之间的一个角度，以十分之一度为单位。移位向量平行于正文行的基线
		@Param：
			UINT nEscapement：角度大小
		*/
		void SetnEscapement(const UINT& nEscapement);

		/*
		GetnEscapement()
		获取移位向量和设备X轴之间的角度
		@return UINT：
			角度大小
		*/
		const UINT& GetnEscapement() const;

		/*
		SetnOrientation(const UINT& nOrientation);
		指定每个字符的基线和设备X轴之间的角度。
		@Param：
			UINT nOrientation：角度大小
		*/
		void  SetnOrientation(const UINT& nOrientation);

		/*
		GetnOrientation()
		获取每个字符的基线和设备X轴之间的角度。
		@return UINT：
			角度大小
		*/
		const UINT& GetnOrientation() const;

		/*
		SetfdwItalic(const BOOL& b)
		设置字体是否为斜体
		@Param：
			BOOL b：是否为斜体
		*/
		void SetfdwItalic(const BOOL& b);

		/*
		GetfdwItalic()
		获取字体是否为斜体
		@return BOOL：
			TRUE ：斜体
			FALSE：非斜体
		*/
	     const BOOL& GetfdwItalic() const;

		 /*
		 SetfdwUnderline(const BOOL& b)
		 设置字体是否增加下划线
		 @Param:
			BOOL b：是否增加下划线
		 */
		 void  SetfdwUnderline(const BOOL& b);

		 /*
		  GetfdwUnderline()
		  获取文本是否有下划线
		  @return BOOL：
			TRUE：有下划线
			FALSE：没有下划线
		 */
		 const BOOL& GetfdwUnderline() const;

		 /*
		 SetfdwStrikeOut(const BOOL& b)
		 设置字体是否增加删除线
		 @Param：
			BOOL b：是否增加删除线
		 */
		 void SetfdwStrikeOut(const BOOL& b);

		 /*
		 GetfdwStrikeOut()
		 获取文本是否有删除线
		 @return BOOL：
			TRUE：有删除线
			FALSE：没有删除线
		 */
		 const BOOL& GetfdwStrikeOut() const;

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
		LPWSTR m_Text;

		UINT m_textColor;

		int m_mode;

		int m_bgColor;

		LPWSTR m_font;

		int m_fontWidth;

		int m_fontHeight;

		//字体重量
		UINT m_weight;

		//指定移位向量和设备X轴之间的一个角度
		//，以十分之一度为单位。移位向量平行于正文行的基线。
		UINT m_nEscapement;
		
		//指定每个字符的基线和设备X轴之间的角度。
		UINT m_nOrientation;
		
		//设置字体是否为斜体
		BOOL m_fdwItalic;

		//设置字体是否增加下划线
		BOOL m_fdwUnderline;

		//设置字体是否增加删除线
		BOOL m_fdwStrikeOut;

		HFONT m_hFont;
	};
}