#include "stdafx.h"
#include "cPicture.h"
#include"cResourcePool.h"
#include<iostream>
#include<mmsystem.h>
using namespace MyEngine;
#pragma comment(lib,"msimg32.lib")


cPicture::cPicture()
{
	m_type = UI_Picture;
	m_bmpConfig = BITMAP();
	m_hBitmap = NULL;
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
}

cPicture::cPicture(const HBITMAP& hBitmap)
{
	m_type = UI_Picture;
	m_hBitmap = hBitmap;
	SetPicConfig();
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
}

cPicture::cPicture(const LPWSTR& name,int x,int y)
{
	m_type = UI_Picture;
	m_hBitmap = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, x, y, LR_LOADFROMFILE);
	SetPicConfig();
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
}

MyEngine::cPicture::cPicture(const std::string key)
{
	m_type = UI_Picture;
	m_isUsePool = TRUE;
	m_hBitmap = (HBITMAP)cResourcePool::GetResourcePool()->GethObjByKey(key);
	SetPicConfig();
	m_isLucency = FALSE;
	m_lucencyRgb = RGB(0, 0, 0);
}

cPicture::~cPicture()
{
	m_hBitmap&&!m_isUsePool? DeleteObject(m_hBitmap) : 1;
}

const RECT cPicture::GetRect() const
{
	RECT rect;
	rect.left = GetX();
	rect.right = GetX() + m_bmpConfig.bmWidth;
	rect.top = GetY();
	rect.bottom = GetY() + m_bmpConfig.bmHeight;
	return rect;
}

bool cPicture::Draw(HDC hDc)
{
	if (hDc == nullptr)
	{
		return false;
	}
	HDC hMemDc = CreateCompatibleDC(hDc);
	SelectObject(hMemDc, m_hBitmap);
	if (m_isLucency)
	{
		TransparentBlt(hDc, GetX(), GetY(), m_bmpConfig.bmWidth, m_bmpConfig.bmHeight, hMemDc, 0, 0, m_bmpConfig.bmWidth, m_bmpConfig.bmHeight, m_lucencyRgb);
	}
	else
	{
		BitBlt(hDc, GetX(), GetY(), m_bmpConfig.bmWidth, m_bmpConfig.bmHeight, hMemDc, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDc);
	return true;
}

void cPicture::SetBitmap(const HBITMAP & hBitmap)
{
	!m_isUsePool ? DeleteObject(m_hBitmap) : 1;
	m_hBitmap= hBitmap;
	SetPicConfig();
	m_isUsePool = FALSE;
}

void cPicture::SetBitmap(const LPWSTR & name,int  x,int  y)
{
	!m_isUsePool ? DeleteObject(m_hBitmap) : 1;
	m_hBitmap = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, x, y, LR_LOADFROMFILE);
	SetPicConfig();
	m_isUsePool = FALSE;
}

void MyEngine::cPicture::SetBitmapByKey(std::string key)
{
	!m_isUsePool ? DeleteObject(m_hBitmap) :1;
	m_hBitmap = (HBITMAP)cResourcePool::GetResourcePool()->GethObjByKey(key);
	SetPicConfig();
	m_isUsePool = TRUE;
}

const HBITMAP & cPicture::GetBitmap() const
{
	return m_hBitmap;
}

void cPicture::SetIsLecency(const BOOL & b)
{
	m_isLucency = b;
}

const BOOL & cPicture::IsLucency() const
{
	return m_isLucency;
}

void cPicture::SetLucency(const UINT & rgb)
{
	m_lucencyRgb = rgb;
}

const UINT & cPicture::GetLucencyColor() const
{
	return m_lucencyRgb;
}

const BITMAP & cPicture::GetConfig() const
{
	return m_bmpConfig;
}

void cPicture::SetPicConfig()
{
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bmpConfig);
}