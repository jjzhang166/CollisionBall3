#pragma once

enum Msg_Type
{
	Msg_Init,
	Msg_AddFood,
	Msg_UpdateInfo,
	Msg_UpdatePhysical,
	Msg_EatFood,
	Msg_AllotTag,
	Msg_AddPlayer,
	Msg_DeletePlayer,
	Msg_PlayMove,
	Msg_CreateBackHole,
	Msg_DeleteBackHole,
};

struct NetMsg
{
	Msg_Type Type;   //消息类型
	POINT pt;
	DWORD id;    //各种标记
	DWORD id1;  //各种标记1
	unsigned int v[4];  //其它信息
};

struct Client
{
	DWORD id;
	POINT pt;
};

