// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define  SCREENSIZE cGameEngine::GetEngine()->GetClientSize()
#define MAP_SIZEX 2550.0f
#define MAP_SIZEY 1800.0f
#define MINI_MAP_SZIEX 200.0f
#define MINI_MAP_SZIEY 140.0f
#define SCREENSIZEX 850.0f
#define SCREENSIZEY 600.0f
#define MAP_ROW 3
#define MAP_RANK 3
