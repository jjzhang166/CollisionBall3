#pragma once
#include<TCPServer.h>
#include<list>
#include<vector>
#include<string>
#include"Message.h"
#include"cMyTimer.h"

class cGameServer :public Net::CTCPServer,public cMyTimer
{
public:
	cGameServer();
	virtual  ~cGameServer();

	/*
	*OnRecv(SOCKET sock, const char* buff)
	*收到客户端消息的回调函数
	*@Param sock：消息来源sock
	*@Param buff：消息内容
	*/
	virtual void OnRecv(SOCKET sock, const char* buff) override;

	/*
	*RemoveClient(DWORD id);
	*移除指定id的客户端
	*@Param id：客户端id
	*/
	void RemoveClient(DWORD id);

	/*
    *updateClientInfo(DWORD id, NetMsg msg);
	*更新指定id的客户端信息
	*@Param id：客户端id
	*@Param msg：服务器接收的消息
	*/
	void updateClientInfo(DWORD id, NetMsg msg);
	
	/*
	*OnTimer(int id, int iParam, string str) 
	*定时器回调函数
	*/
	int OnTimer(int id, int iParam, string str) override;

	void CreateBackHole();

	void BackHoleStorm();

	void SendAllotTagMsg(DWORD id);

	void SendAddPlayMsg(DWORD id,NetMsg msg);

	void SendPlayMoveMsg(DWORD id,NetMsg msg);

	void SendInitMsg(DWORD id);

	void CreateFood();

	void EatedFood(DWORD who,NetMsg msg);

	void UpdateInfoMsg(DWORD who,NetMsg msg);

	void DeletePlayerMsg(NetMsg msg);
private:
	std::list<Client> m_clientList;  //保存客户端信息列表
	std::list<BackHole> m_backHoleList;
	std::list<_Food> m_foodList;
	int m_onlineNums = 0;
};
