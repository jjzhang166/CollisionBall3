#include "stdafx.h"
#include "cText.h"
using namespace std;
using namespace MyEngine;

cText::cText():m_Text("")
{
	m_type = UI_Text;
	m_bgColor = RGB(255, 255, 255);
	m_textColor = RGB(0, 0, 0);
	m_font = L"¿¬Ìå";
	m_fontHeight = 50;
	m_fontWidth = 25;
	m_mode = 1;
	m_weight = 0;
	m_fdwItalic = FALSE;
	m_fdwStrikeOut = FALSE;
	m_fdwUnderline = FALSE;
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}


MyEngine::cText::cText(const string & text)
{
	m_type = UI_Text;
	m_Text = text;
	m_bgColor = RGB(255, 255, 255);
	m_textColor = RGB(0, 0, 0);
	m_font = L"¿¬Ìå";
	m_fontHeight = 50;
	m_fontWidth = 25;
	m_mode = 1;
	m_weight = 0;
	m_fdwItalic = FALSE;
	m_fdwStrikeOut = FALSE;
	m_fdwUnderline = FALSE;
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

cText::~cText()
{
	m_hFont ? DeleteObject(m_hFont) : 1;
}

void MyEngine::cText::SetText(const string& text)
{
	m_Text = text;
}

const string & MyEngine::cText::GetText() const
{
	return m_Text;
}

bool MyEngine::cText::Append(const string& text)
{
	m_Text.append(text);
	return false;
}

void MyEngine::cText::SetTextColor(const UINT & rgb)
{
	m_textColor = rgb;
}

const UINT & MyEngine::cText::GetTextColor() const
{
	return m_textColor;
}

void MyEngine::cText::SetMode(const int & mode)
{
	m_mode = mode;
}

const int & MyEngine::cText::GetMode() const
{
	return m_mode;
}

void MyEngine::cText::SetBgColor(UINT rgb)
{
	m_bgColor = rgb;
}

const UINT & MyEngine::cText::GetBgColor() const
{
	return m_bgColor;
}

void MyEngine::cText::SetFont(const LPWSTR & font)
{
	m_font = font;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const LPWSTR & MyEngine::cText::GetFont() const
{
	return m_font;
}

void MyEngine::cText::SetFontWidth(const int& width)
{
	m_fontWidth = width;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const int & MyEngine::cText::GetFontWidth() const
{
	return m_fontWidth;
}

void MyEngine::cText::SetFontHeight(const int& height)
{
	m_fontHeight = height;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const int & MyEngine::cText::GetFonthHeight() const
{
	return m_fontHeight;
}

void MyEngine::cText::SetWeight(const UINT & weight)
{
	m_weight = weight;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const UINT & MyEngine::cText::GetWeight() const
{
	return m_weight;
}

void MyEngine::cText::SetnEscapement(const UINT & nEscapement)
{
	m_nEscapement = nEscapement;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const UINT & MyEngine::cText::GetnEscapement() const
{
	return m_nEscapement;
}

void MyEngine::cText::SetnOrientation(const UINT & nOrientation)
{
	m_nOrientation = nOrientation;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const UINT & MyEngine::cText::GetnOrientation() const
{
	return m_nOrientation;
}

void MyEngine::cText::SetfdwItalic(const BOOL & b)
{
	m_fdwItalic = b;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const BOOL & MyEngine::cText::GetfdwItalic() const
{
	return m_fdwItalic;
}

void MyEngine::cText::SetfdwUnderline(const BOOL & b)
{
	m_fdwUnderline = b;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const BOOL & MyEngine::cText::GetfdwUnderline() const
{
	return m_fdwUnderline;
}

void MyEngine::cText::SetfdwStrikeOut(const BOOL & b)
{
	m_fdwStrikeOut = b;
	DeleteObject(m_hFont);
	m_hFont = CreateFont(m_fontHeight, m_fontWidth,
		NULL, NULL, m_weight, m_fdwItalic, m_fdwUnderline
		, m_fdwStrikeOut, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH, m_font);
}

const BOOL & MyEngine::cText::GetfdwStrikeOut() const
{
	return m_fdwStrikeOut;
}

const RECT MyEngine::cText::GetRect() const
{
	RECT rect;
	rect.left = GetX();
	rect.right = GetX() + m_fontWidth*m_Text.length();
	rect.top = GetY();
	rect.bottom = GetY() + m_fontHeight;
	return  rect;
}

bool MyEngine::cText::Draw(HDC hDc)
{
	if (hDc == nullptr)
	{
		return false;
	}
	SetBkMode(hDc, m_mode);
	if (m_mode)
	{
		SetBkColor(hDc,m_bgColor);
	}
	::SetTextColor(hDc,m_textColor);
	SelectObject(hDc, m_hFont);
	TextOutA(hDc, GetX(), GetY(), m_Text.c_str(), m_Text.length());

	return true;
}