#pragma once
#include<list>
#include<vector>
#include"cMyTimer.h"
#include"cText.h"
#include"cButton.h"
#include"cPicture.h"
#include"cAmination.h"
#include"cTriangle.h"
#include"cLine.h"
#include"cRectangle.h"
#include"cCircle.h"
#include"cPolygon.h"
#include"cSight.h"
#include"cResourcePool.h"
#include"Lock.h"
#include<thread>

namespace MyEngine
{
	 typedef struct SIZE
	{
		int width;
		int height;
	};

	/*
	cGameEngine
	UI引擎类，管理所有界面上的图形显示，图形类指针创建后用
	户无需主动删除，UI引擎类在程序结束时会自动删除，用户也
	可在需要时主动删除。
	该类采用单实例设计模式，不要试图新建此类的对象，
	而要通过GetEngine()获取此类对象。
	*/
	class cGameEngine :public cMyTimer
	{
	public:
		/*
		*GetEngine();
		*获取单实例引擎对象
		*/
		static cGameEngine* GetEngine();

		/*
		*init(HINSTANCE hInst, LPWSTR Title = L"LSYENGINE);
		*初始化引擎
		*@Param hInst:实例句柄
		*@Param title:窗口标题
		*/
		void init(HINSTANCE hInst);

		/*
		*LuanchEngine();
		*运行引擎，调用前提是已经调用了init();
		*/
		int LuanchEngine();

		/*
		OnTimer(int id,int iParam,string str)
		处理定时器消息回调函数
		@Param
			int id:回调定时器id
			int iParam:定时器附加参数
			string str：定时器描述
		@return int：
			0：表示该定时器将被删除
		*/
		virtual int OnTimer(int id, int iParam, string str);

		/*
		CenterWindow(int w = 0, int h = 0)
		将客户窗口居中,必须在init()之后使用才有效
		@Param:
			int w：窗口宽度
			int h：窗口高度
		@return int：
			0：成功居中
			-1：居中失败
		*/
		int CenterWindow(int w = 0, int h = 0);

		/*
		GetLastError()
		获取上一次错误信息
		@return const LPWSTR&:
			错误信息串
		*/
		const LPWSTR& GetLastError() const;

		/*
		CreateText(const LPWSTR& text,const int& x,const int& y)
		创建一个Text文本
		@Param
			string text:文本内容
			int x:文本x坐标
			int y:文本y坐标
		@return cText：
			成功则返回创建的文本指针，失败则返回nullptr
		*/
		cText* CreateText(const std::string& text, const int& x , const int& y );

		/*
		CreateLine(const POINT& start,const POINT& end)
		创建一条直线
		@Param：
			POINT start：直线起点
			POINT end：直线终点
		@return cLine*:
			创建的直线对象指针
		*/
		cLine* CreateLine(const POINT& start, const POINT& end);

		/*
		CreateButton(const LPWSTR& Name,cosnt int& x,const int& y)
		创建一个按钮
		@Param：
			LPWSTR Name:按钮名
			int x:按钮x坐标
			int y：按钮y坐标
		@return cButton*：
			创建的按钮对象指针
		*/
		cButton* CreateButton(const LPWSTR& Name, const int& x, const int& y);

		/*
		CreateBitmapButton(const LPWSTR& bmpPath,const int& x,const int& y)
		创建图片按钮
		@Param:
			LPWSTR bmpPath：位图资源路径
			int x:按钮x坐标
			int y:按钮y坐标
		@return：
			创建的按钮对象指针
		*/
		cButton* CreateBitmapButton(const LPWSTR& bmpPath,const int& x,const int& y);

		/*
		CreateBitmapButton(const HBITMAP& hbitmap,const int& x,const int& y)
		创建图片按钮
		@Param:
			HBITMAP hbitmap：位图资源句柄
			int x:按钮x坐标
			int y:按钮y坐标
		@return：
			创建的按钮对象指针
		*/
		cButton* CreateBitmapButton(const HBITMAP& bitmap,const int& x,const int& y);

		/*
		*CreateButtonByKey(std::string key);
		*通过key值新建一个Button，要求该资源已经加载进资源池
		*@Param：
		*	key：key值
		*/
		cButton* CreateButtonByKey(std::string key);
		
		/*
		CreateCircle(const RECT& rect)
		创建一个圆
		@Param：
			center:圆心
			radius：半径
		@return cCircle*：
			创建的圆对象指针
		*/
		cCircle* CreateCircle(const POINT& center,const UINT& radius);

		/*
		CreatePicture(const HBITMAP& bitmap,const int& x,const int& y)
		创建一个图片
		@Param:
			HBITMAP bitmap：位图句柄
			int x：图片x坐标
			int y：图片y坐标
		@return cPicture*：
			创建的图片对象指针
		*/
		cPicture* CreatePicture(const HBITMAP& bitmap,const int& x,const int& y);

		/*
		CreatePicture(const LPWSTR& name,const int& x,const int& y,const int& w = 0, const int& h = 0)
		根据图片路径创建一个图片
		@Param:
		LPWSTR Name：图片路径名
		int x：图片x坐标
		int y：图片y坐标
		int w：指定图片宽度
		int h：指定图片高度
		@return cPicture*：
		创建的图片对象指针
		*/
		cPicture* CreatePicture(const LPWSTR& Name, const int& x, const int& y, const int& w = 0, const int& h = 0);

		/*
		*CreatePictureByKey(std::string key);
		*通过key值新建一张图片，要求该资源已经加载进资源池
		*@Param：
		*	key：key值
		*/
		cPicture* CreatePictureByKey(std::string key);

		/*
		CreateRectangle(const RECT& rect)
		创建一个矩形
		@Param center:矩形中心点
		@Param width：矩形宽度
		@Param height：矩形高度
		@return cRectangle*：
			创建的矩形对象指针
		*/
		cRectangle* CreateRectangle(const POINT& center, const int& width, const int& height);

		/*
		CreateTriangle(const POINT& p1,const POINT& p2,const POINT p3)
		创建一个三角形
		@Param：
			POINT p1:构成三角行的第一个点
			POINT p2：构成三角形的第二个点
			POINT p3：构成三角形的第三个点
		@return cTriangle*：
			创建的三角形对象指针
		*/
		cTriangle* CreateTriangle(const POINT& p1, const POINT& p2, const POINT& p3);

		/*
		CreatePolygon(std::initializer_list<POINT> pointList)
		创建一个多边形
		@Param：
			initializer_list<POINT> pointList:构成多边形的基础点列表
		@return cPolygon*：
			创建的多边形对象指针
		*/
		cPolygon* CreatePolygon(std::initializer_list<POINT> pointList);

		/*
		CreateAmination(const std::initializer_list<LPWSTR>& pathList,const int& x,const int& y)
		创建动画资源
		@Param：
			std::initializer_list pathList：动画资源路径名列表
			int x：动画x坐标
			int y：动画y坐标
		@return cAmination*:
			动画对象指针
		*/
		cAmination *CreateAmination(const std::initializer_list<LPWSTR>& pathList, const int &x, const int& y, const int& w= 0, const int& h = 0);

		/*
		CreateAmination(const LPWSTR& Name,const int& smallRow,const int& smallRank,const int& w = 0,const int h = 0);
		一整张大图创建一个动画
		@Param：
			LPWSTR Name：图片路径
			int smallrow：小图行数
			int smallRank：小图列数
		*/
		cAmination* CreateAmination(const LPWSTR& Name,const int& smallRow,const int& smallRank,const int& w = 0,const int h = 0);

		/*
		CreateAmination(const LPWSTR& Name,const int& smallRow,const int& smallRank,const int& w = 0,const int h = 0);
		一整张大图创建一个动画
		@Param：
			HBITMAP hbitmap：位图资源句柄
			int smallrow：小图行数
			int smallRank：小图列数
		*/
		cAmination* CreateAmination(const HBITMAP& hbitmap, const int& smallrow, const int& smallrank);

		/*
		*CreateAminationByKey(std::string key);
		*通过key值新建一个多图片动画，要求该资源已经加载进资源池
		*@Param：
		*	key：key值
		*/
		cAmination* CreateAminationByKey(std::string key);

		/*
		*CreateAminationByKey(std::string key, const int& smallRow, const int& smallRank);
		*通过key值新建一张大图动画，要求该资源已经加载进资源池
		*@Param：
		*	key：key值
		*/
		cAmination* CreateAminationByKey(std::string key, const int& smallRow, const int& smallRank);

		/*
		*CreateSight
		*创建一个视野
		*@return cSight* ：视野对象指针
		*/
		cSight* CreateSight();

		/*
		AddEventToUI(const cBaseUI* ui,UINT_PTR eventIdCallEventBack callBack)
		为UI控件添加事件处理函数
		@Param：
			trigger:事件的触发者
			eventId:事件id用于区分为何种事件
			callBack:事件处理回调函数
			handler:事件的处理者
			Param:预留参数，当为空时返回事件id
		*/
		void AddEventToUi(cBaseUI* trigger, UINT_PTR eventId, SEL_CallFunc callBack, cBaseUI* handler, void* Param = NULL);

		/*
		int DeleteUI(cBaseUI *pDel);
		删除指定ui控件
		@Param :
			pDel：指定要删除的ui控件的指针
		@return int：
			0：未找到删除项
			1：删除成功
		*/
		int DeleteUI(cBaseUI* pDel);

		/*
		DeleteUIs(std::list<cBseUI*> pDelList)
		删除多个UI元素
		@Param pDelList：
			std::list<cBaseUI*> pDelList：需要删除的UI列表
		@return int：
			删除的个数
		*/
		int DeleteUIs(std::list<cBaseUI*> pDelList);

		/*
		QuickDeleteUIs(std::initializer_list<cBaseUI*> pDelList)
		快速删除多个UI控件，仅限删除列表中的控件顺序与创建顺序一致
		@Param:
			std::initializer_list<cBaseUI*> pDelList:需要删除的UI列表
		@return int：
			实际删除的UI控件个数
		*/
		int QuickDeleteUIs(std::list<cBaseUI*> pDelList);

		/*
		DeleteEvent(cBaseUI* ui,UINT_PTR eventId)
		删除UI控件的指定事件
		@Param：
			cBaseUI* ui：指定要删除的控件对象指针
			UINT_PTR eventId：事件id
		@return BOOL:
			TRUE：删除成功
			FALSE：删除失败
		*/
		BOOL DeleteEvent(cBaseUI* ui, UINT_PTR eventId);

		/*
		DeleteEvent(cBaseUI* ui);
		删除指定ui控件的所有事件
		@Param ui:指定的ui控件
		@return int：失败返回0，成功返回删除的事件个数
		*/
		int DeleteEvent(cBaseUI* ui);

		/*
		DeleteEvent(cBaseUI* ui)
		删除某一UI控件相关联的所有事件
		@Param：
			uid：指定的ui控件的id号
		@return int：
			删除的事件个数
		*/
		int DeleteEvent(UINT_PTR uid);

		/*
		DrawUI();
		 绘制UI界面
		*/
		void DrawUI();

		/*
		DoMouseMsg()
		处理鼠标消息
		@Param：
			WPARAM wParam：鼠标消息详细信息
		*/
		void DoMouseMsg(WPARAM wParam);

		/*
		DoKeyMsg(LPARAM lParam)
		处理键盘按键按下消息
		@Param：
			LPARAM lParam：消息的详细信息
		*/
		void DoKeyMsg(UINT message,WPARAM wParam);

		/*
		DoUiKeyEvent(const UINT_PTR& eventId)
		处理ui控件键盘事件
		@Param：
			UINT_PTR eventId：事件id
		*/
		void DoUiKeyEvent(WPARAM wParam,UINT_PTR eventId);

		/*
		DoUiMouseEvent(const UINT_PTR& eventId)
		处理ui控件鼠标事件
		@Param:
			UINT_PTR eventId：事件id
		*/
		void DoUiMouseEvent(UINT_PTR eventId);

		/*
		GethWnd()
		获取绑定的窗口句柄
		@return HWND：
			窗口句柄
		*/
		HWND GethWnd() const;

		/*
		SethWnd(HWND hWnd);
		设置窗口句柄
		@Param:
			HWND hWnd：绑定的窗口句柄
		*/
		void SethWnd(HWND hWnd);

		/*
		GetWndStyle()
		获取窗口风格
		@return LONG:
			窗口当前风格
		*/
		LONG GetWndStyle();

		/*
		ChangeWndStyle(const LONG& style)
		改变窗口风格
		@Param：
			LONG style:新的窗口风格
		@return BOOL：
			TRUE：改变成功
			FALSE：改变失败
		*/
		BOOL ChangeWndStyle(const LONG& style);

		/*
		*AddEngineUi
		*向引擎内添加UI控件
		*@Param ui*：添加进引擎的ui控件
		*@return bool：添加成功返回true，如果该控件已经存在引擎内则返回false
		*/
		bool AddEngineUi(cBaseUI* ui);

		void ReleaseSelf();

		/*
		*GetClientSize();
		*获取客户区窗口尺寸
		*@return SIZE：返回客户区尺寸
		*/
		SIZE GetClientSize();

		/*
	    *GetMouseStatus();
		*获取鼠标状态
		*@return Mouse_Status:返回鼠标当前状态，是否按下
		*按下返回Mouse_Down，否则返回Mouse_Up
		*/
		Mouse_Status GetMouseStatus();

		/*
		*RegisterWinClass();
		*注册窗口类
		*/
		ATOM RegisterWinClass();

		/*
		*InitInstance();
		*创建窗口句柄，并实例化
		*@return bool：成功返回true，失败返回false
		*/
		bool InitInstance();

		/*
		*GethInstance();
		*获取程序实例句柄
		*/
		HINSTANCE GethInstance();

		/*
		*SetCursor();
		*设置鼠标光标，必需在调用init()之前设置才会生效
		*@Param hCursor：光标资源句柄
		*/
		void SetCursor(HCURSOR hCursor);
		HCURSOR GetCursor();

		/*
		*SetTitle(LPWSTR name);
		*设置主窗口标题，必需在调用init()之前设置才会生效
		*LPWSTR name：窗口标题
		*/
		void SetTitle(LPWSTR name);
		LPWSTR GetTitle();

		/*
		*SetIcon(LPWSTR name)
		*设置程序icon，必需在调用init()之前设置才会生效
		*@Param hIcon：icon资源句柄
		*/
		void SetIcon(HICON hIcon);
		HICON GetIcon();

		/*
		*设置程序小图标，必需在调用init()之前设置才会生效
		*@Param hIcon：icon资源句柄
		*/
		void SetIconSm(HICON hIcon);
		HICON GetIconSm();

		/*
		*SetMenuName(LPCWSTR name);
		*设置窗口菜单项，必需在调用init()之前设置才会生效
		*@Param name：菜单项名称
		*/
		void SetMenuName(LPCWSTR name);

		/*
		*SetAccelTable(HACCEL hAccel);
		*设置快捷键表
		*/
		void SetAccelTable(HACCEL hAccel);
	private:
		cGameEngine();
		virtual ~cGameEngine();

		/*
		*处理主窗口消息循环
		*/
		void DoMainMsg();

		void SafeAddUi(cBaseUI* ui);

		HWND m_hWnd;

		//错误信息
		LPWSTR m_wError;

		//保存UI控件列表
		std::list<cBaseUI*> m_uiList;

		std::list<UI_Event> m_evnetList;

		//互斥锁
		CLock m_lock;

		Mouse_Status m_mouseStatus;

		HINSTANCE m_hInst;

		LPWSTR m_title;

		HICON m_hIcon;

		HICON m_hIconSm;

		HCURSOR m_hCursor;

		LPCWSTR m_menuName;

		HACCEL m_hAccel;
	};
}