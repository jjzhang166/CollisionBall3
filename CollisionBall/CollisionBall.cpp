// CollisionBall.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CollisionBall.h"
#include"TheAgency.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	cTheAgency{ hInstance };  //进入代理类
	return 0;
}
