#ifndef TOOL
#define TOOL

struct WndBount
{
	int xBount;
	int yBount;

	WndBount()
	{
		xBount = 0;
		yBount = 0;
	}
};

/*
*MoveToCenter(const HWND& hWnd,const int& sizeX,const int& sizeY,const int& offsetX=0,const int& offsetY=0)
*
*将指定窗口居中
*
*@Param：
*	HWND hWnd：需要居中的窗口句柄
*	int sizeX：窗口横向大小
*	int sizeY：窗口纵向大小
*@return bool：
*	true：居中成功
*	false：居中失败
*/
bool MoveToCenter(const HWND& hWnd, const int& sizeX, const int& sizeY, const int& offsetX = 0, const int& offsetY = 0);

/*
*WcharArrayChineseNums(const LPWSTR& str)
*
*统计宽字符串中中文字符个数
*
*@Param:
*	LPWSTR str：需要统计的字符串
*@return int：
*	字符串中汉子个数
*/
int WcharArrayChineseNums(const LPWSTR& str);

/*
*GetWindowBount(HWND hWnd);
*
*获取窗口边框大小
*
*@Param：
*	HWND hWnd：要获取边框大小的窗口句柄
*@return WndBount：
*	保存窗口边框值低字段保存x轴边框大小，高字段保存y轴边框大小
*/
WndBount GetWindowBount(HWND hWnd);

/*
*PointToPointDistance(POINT p1, POINT p2);
*
*计算两点间的距离
*
*Param:
*	p1：点1
*	p2：点2
*
*@return：
*	UINT：两点间的距离
*/
UINT PointToPointDistance(POINT p1, POINT p2);

/********************************************************************************
************************键盘鼠标所有虚拟键键值宏定义****************************
**************************BEGIN*************************************************
*********************************************************************************/
#define UVK_LBUTTON	1	//鼠标左键
#define UVK_RBUTTON	2	//鼠标右键
#define UVK_CANCEL	3	//Cancel
#define UVK_MBUTTON	4	//鼠标中键
#define UVK_XBUTTON1	5
#define UVK_XBUTTON2	6
#define UVK_BACK	8 	//Backspace
#define UVK_TAB	9 	//Tab
#define UVK_CLEAR	12 	//Clear
#define UVK_RETURN	13 	//Enter
#define UVK_SHIFT	16 	//Shift
#define UVK_CONTROL	17 	//Ctrl
#define UVK_MENU	18 	//Alt
#define UVK_PAUSE	19 	//Pause
#define UVK_CAPITAL	20	//Caps Lock
#define UVK_KANA	21
#define UVK_HANGUL	21
#define UVK_JUNJA	23
#define UVK_FINAL	24
#define UVK_HANJA	25
#define UVK_KANJI	25 //*
#define UVK_ESCAPE	27	//Esc
#define UVK_CONVERT	28
#define UVK_NONCONVERT	29
#define UVK_ACCEPT	30
#define UVK_MODECHANGE	31
#define UVK_SPACE	32	//Space
#define UVK_PRIOR	33	//Page Up
#define UVK_NEXT	34	//Page Down
#define UVK_END	35	//End
#define UVK_HOME	36	//Home
#define UVK_LEFT	37	//Left Arrow
#define UVK_UP	38	//Up Arrow
#define UVK_RIGHT	39	//Right Arrow
#define UVK_DOWN	40	//Down Arrow
#define UVK_SELECT	41	//Select
#define UVK_PRINT	42	//Print
#define UVK_EXECUTE	43	//Execute
#define UVK_SNAPSHOT	44	//Snapshot
#define UVK_INSERT	45	//Insert
#define UVK_DELETE	46	//Delete
#define UVK_HELP	47	//Help
#define U0 48	 //0
#define U1 49	//1
#define U2 50	//2
#define U3 51	//3
#define U4 52	//4
#define U5 53	//5
#define U6 54	//6
#define U7 55	//7
#define U8 56	//8
#define U9 57	//9
#define UA 65	//A
#define UB 66 //B
#define UC 67	//C
#define UD 68 //D
#define UE 69	//E
#define UF 70	//F
#define UG 71	//G
#define UH 72	//H
#define UI 73	//I
#define UJ 74	//J
#define UK 75	//K
#define UL 76	//L
#define UM 77	//M
#define UN 78	//N
#define UO 79	//O
#define UP 80	//P
#define UQ 81	//Q
#define UR 82	 //R
#define US 83	//S
#define UT 84	//T
#define UU 85	//U
#define UV 86	//V
#define UW 87	//W
#define UX 88 //X
#define UY 89	 //Y
#define UZ 90	  //Z
#define UVK_LWIN	 91
#define UVK_RWIN 92
#define UVK_APPS	93
#define UVK_SLEEP 95
#define UVK_NUMPAD0 96 //小键盘 0
#define UVK_NUMPAD1 97 //小键盘 1
#define UVK_NUMPAD2 98 //小键盘 2
#define UVK_NUMPAD3 99 //小键盘 3
#define UVK_NUMPAD4 100  //	小键盘 4
#define UVK_NUMPAD5	101	//小键盘 5
#define UVK_NUMPAD6	102	//小键盘 6
#define UVK_NUMPAD7	103	//小键盘 7
#define UVK_NUMPAD8	104	//小键盘 8
#define UVK_NUMPAD9	105	//小键盘 9
#define UVK_MULTIPLY	106	//小键盘 *
#define UVK_ADD	107	//小键盘 +
#define UVK_SEPARATOR	108	//小键盘 Enter
#define UVK_SUBTRACT	109	//小键盘 -
#define UVK_DECIMAL	110	//小键盘 .
#define UVK_DIVIDE	111	//小键盘 /
#define UVK_F1	112	//F1
#define UVK_F2	113	//F2
#define UVK_F3	114	//F3
#define UVK_F4	115	//F4
#define UVK_F5	116	//F5
#define UVK_F6	117	//F6
#define UVK_F7	118	//F7
#define UVK_F8	119	//F8
#define UVK_F9	120	//F9
#define UVK_F10	121	//F10
#define UVK_F11	122	//F11
#define UVK_F12	123	//F12
#define UVK_F13	124
#define UVK_F14	125
#define UVK_F15	126
#define UVK_F16	127
#define UVK_F17	128
#define UVK_F18	129
#define UVK_F19	130
#define UVK_F20	131
#define UVK_F21	132
#define UVK_F22	133
#define UVK_F23	134
#define UVK_F24	135
#define UVK_NUMLOCK	144	//Num Lock
#define UVK_SCROLL	145	//Scroll
#define UVK_LSHIFT	160
#define UVK_RSHIFT	161
#define UVK_LCONTROL	162
#define UVK_RCONTROL	163
#define UVK_LMENU	164
#define UVK_RMENU	165
#define UVK_BROWSER_BACK	166
#define UVK_BROWSER_FORWARD	167
#define UVK_BROWSER_REFRESH	168
#define UVK_BROWSER_STOP	169
#define UVK_BROWSER_SEARCH	170
#define UVK_BROWSER_FAVORITES	171
#define UVK_BROWSER_HOME	172
#define UVK_VOLUME_MUTE	173	//VolumeMute
#define UVK_VOLUME_DOWN	174	//VolumeDown
#define UVK_VOLUME_UP	175	//VolumeUp
#define UVK_MEDIA_NEXT_TRACK	176
#define UVK_MEDIA_PREV_TRACK	177
#define UVK_MEDIA_STOP	178
#define UVK_MEDIA_PLAY_PAUSE	179
#define UVK_LAUNCH_MAIL	180
#define UVK_LAUNCH_MEDIA_SELECT	181
#define UVK_LAUNCH_APP1	182
#define UVK_LAUNCH_APP2	183
#define UVK_OEM_1	186 //; :
#define UVK_OEM_PLUS	187 //= +
#define UVK_OEM_COMMA	188
#define UVK_OEM_MINUS	189 //- _
#define UVK_OEM_PERIOD	190
#define UVK_OEM_2	191 //  / ?
#define UVK_OEM_3	192	//` ~
#define UVK_OEM_4	219  // [{
#define UVK_OEM_5	220	// \ |
#define UVK_OEM_6	221   // ] }
#define UVK_OEM_7	222	 // ' "
#define UVK_OEM_8	223
#define UVK_OEM_102	226
#define UVK_PACKET	231
#define UVK_PROCESSKEY	229
#define UVK_ATTN	  246
#define UVK_CRSEL	247
#define UVK_EXSEL	248
#define UVK_EREOF	249
#define UVK_PLAY	250
#define UVK_ZOOM	251
#define UVK_NONAME	252
#define UVK_PA1	253
#define UVK_OEM_CLEAR	254
/***********************************************************************
***************************END****************************************
**********************************************************************/

#endif // !TOOL