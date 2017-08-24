#include"stdafx.h"
#include"cGameServer.h"
#include<random>
#pragma comment(lib,"NetLib.lib")
using namespace Net;
using namespace std;
static unsigned int foodId = 0;

cGameServer::cGameServer()
{

}

cGameServer::~cGameServer()
{

}

void cGameServer::OnRecv(SOCKET sock, const char * buff)
{
	if (strcmp(buff, CLOSE_MESSAGE) == 0)
	{
		--m_onlineNums;
		if (m_onlineNums == 0)
		{
			m_clientList.clear();
			m_backHoleList.clear();
			m_foodList.clear();
			DeleteTimer(1);
		}
		return;
	}
	NetMsg* pMsg = (NetMsg*)buff;
	switch (pMsg->Type)
	{
	case Msg_Init:
	{
		printf_s("客户端：%ld发送了初始化消息\n", sock);
		++m_onlineNums;
		Client client;
		client.id = sock;
		client.pt = pMsg->pt;
		client.color = pMsg->id;
		client.vx = pMsg->v[0];
		client.vy = pMsg->v[1];
		client.radius = pMsg->v[2];
		client.physical = pMsg->v[3];
		SendInitMsg(sock);
		SendAllotTagMsg(sock);
		SendAddPlayMsg(sock,*pMsg);
		m_clientList.push_back(client);
		if (m_clientList.size() == 1)
		{
			AddTimer(1, 100);
		}
	}
		break;
	case Msg_PlayMove:
	{
		printf_s("客户端：%ld改变了速度vx->%ld, vy->%ld\n", sock, pMsg->v[0], pMsg->v[1]);
		updateClientInfo(sock, *pMsg);
		SendPlayMoveMsg(sock, *pMsg);
	}
	    break;
	case Msg_EatFood:
		printf_s("客户端：%ld吃了一个食物:%ld\n", sock, pMsg->id);
		EatedFood(sock, *pMsg);
		break;
	case Msg_UpdateInfo:
		printf_s("客户端：%ld更新了信息:(%ld,%ld)|vx->%ld,vy->%ld\n", sock, pMsg->pt.x, pMsg->pt.y, pMsg->v[0], pMsg->v[1]);
		UpdateInfoMsg(sock, *pMsg);
		break;
	case Msg_DeletePlayer:
		printf_s("客户端：%ld阵亡", pMsg->id);
		DeletePlayerMsg(*pMsg);
		break;
	default:
		break;
	}
}

void cGameServer::RemoveClient(DWORD id)
{
	for (auto it = std::begin(m_clientList); it != std::end(m_clientList);)
	{
		if (it->id == id)
		{
			it = m_clientList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void cGameServer::updateClientInfo(DWORD id, NetMsg msg)
{
	for (auto& it : m_clientList)
	{
		if (it.id == id)
		{
			it.color = msg.id1;
			it.pt = msg.pt;
			it.vx = msg.v[0];
			it.vy = msg.v[1];
			it.radius = msg.v[2];
			it.physical = msg.v[3];
		}
	}
	
}

int cGameServer::OnTimer(int id, int iParam, string str)
{
	CreateFood();
	BackHoleStorm();
	return 1;
}

void cGameServer::CreateBackHole()
{
	random_device rad;
	BackHole backHole;
	backHole.pt.x = rad() % (int)MAP_SIZEX;
	backHole.pt.y = rad() % (int)MAP_SIZEY;
	backHole.lifecycle = rad() %200  + 150;
	backHole.controlRadius = 50 + 30 + rad() % 70;
	backHole.power = 3 + rad() % 5;
	printf_s("黑洞:(%ld,%ld) || lifecycke:%ld || radius:%ld || power:%ld\n",
		backHole.pt.x, backHole.pt.y, backHole.lifecycle,
		backHole.controlRadius, backHole.power);
	NetMsg msg;
	msg.Type = Msg_CreateBackHole;
	msg.pt = backHole.pt;
	msg.v[0] = backHole.controlRadius;
	msg.v[1] = backHole.lifecycle;
	msg.v[2] = backHole.power;
	SendMsgAll((char*)&msg, sizeof(msg));
}

void cGameServer::BackHoleStorm()
{
	static unsigned int stormcycle = 300;
	if (stormcycle == 0)
	{
		printf_s("产生了一个黑洞风暴!\n");
		random_device rad;
		int nums = rad() % 10 + 8;
		for (int i = 0; i < nums; ++i)
		{
			CreateBackHole();
		}
	}
	stormcycle == 0 ? stormcycle = 100 : --stormcycle;
}

void cGameServer::SendAllotTagMsg(DWORD id)
{
	NetMsg msg;
	msg.Type = Msg_AllotTag;
	msg.id = id;
	SendMsg(id, (char*)&msg, sizeof(msg));
}

void cGameServer::SendAddPlayMsg(DWORD id,NetMsg msg)
{
	NetMsg smsg;
	for (auto it : m_clientList)
	{
		smsg.Type = Msg_AddPlayer;
		smsg.id = msg.id;
		smsg.pt = msg.pt;
		smsg.id1 = id;
		smsg.v[0] = msg.v[0];
		smsg.v[1] = msg.v[1];
		smsg.v[2] = msg.v[2];
		smsg.v[3] = msg.v[3];
		SendMsg(it.id, (char*)&smsg, sizeof(smsg));
	}
}

void cGameServer::SendPlayMoveMsg(DWORD id, NetMsg msg)
{
	NetMsg smsg;
	smsg.Type = Msg_PlayMove;
	smsg.id = id;
	smsg.pt = msg.pt;
	smsg.v[0] = msg.v[0];
	smsg.v[1] = msg.v[1];
	for (auto it : m_clientList)
	{
		if (it.id != id)
		{
			SendMsg(it.id, (char*)&smsg, sizeof(smsg));
		}
	}
}

void cGameServer::SendInitMsg(DWORD id)
{
	for (auto it : m_clientList)
	{
		NetMsg smsg;
		smsg.Type = Msg_AddPlayer;
		smsg.id = it.color;
		smsg.pt = it.pt;
		smsg.id1 = it.id;
		smsg.v[0] = it.vx;
		smsg.v[1] = it.vy;
		smsg.v[2] = it.radius;
		smsg.v[3] = it.physical;
		SendMsg(id, (char*)&smsg, sizeof(smsg));
	}
	for (auto it : m_foodList)
	{
		NetMsg smsg;
		smsg.Type = Msg_AddFood;
		smsg.id =it.id;
		smsg.pt = it.pt;
		smsg.id1 = it.color;
		SendMsgAll((char*)&smsg, sizeof(smsg));
	}
}

void cGameServer::CreateFood()
{
	if (m_foodList.size() >= MAX_FOOD)
	{
		return;
	}
	static unsigned int delay = 3;
	if (delay == 0)
	{
		random_device rad;
		_Food food;
		food.id = foodId++;
		food.pt.x = rad() % static_cast<int>(MAP_SIZEX);
		food.pt.y = rad() % static_cast<int>(MAP_SIZEY);
		food.color = RGB(rad() % 256, rad() % 256, rad() % 256);
		m_foodList.push_back(food);
		NetMsg smsg;
		smsg.Type = Msg_AddFood;
		smsg.id = food.id;
		smsg.pt = food.pt;
		smsg.id1 = food.color;
		printf_s("增加一个食物：(%ld,%ld)\n", food.pt.x, food.pt.y);
		SendMsgAll((char*)&smsg, sizeof(smsg));
	}
	delay == 0 ? delay = 3 : --delay;
}

void cGameServer::EatedFood(DWORD who,NetMsg msg)
{
	for (auto it = m_foodList.begin(); it != m_foodList.end(); ++it)
	{
		if (it->id == msg.id)
		{
			m_foodList.erase(it);
			break;
		}
	}
	for (auto it : m_clientList)
	{
		if (it.id != who)
		{
			NetMsg smsg;
			smsg.Type = Msg_EatFood;
			smsg.id = msg.id;
			SendMsg(it.id, (char*)&smsg, sizeof(smsg));
		}
	}
}

void cGameServer::UpdateInfoMsg(DWORD who, NetMsg msg)
{
	for (auto& it : m_clientList)
	{
		if (it.id == who)
		{
			it.color = msg.id1;
			it.pt = msg.pt;
			it.vx = msg.v[0];
			it.vy = msg.v[1];
			it.radius = msg.v[2];
			it.physical = msg.v[3];
		}
		else
		{
			NetMsg smsg;
			smsg.Type = Msg_UpdateInfo;
			smsg.id = who;
			smsg.id1 = msg.id1;
			smsg.pt = msg.pt;
			smsg.v[0] = msg.v[0];
			smsg.v[1] = msg.v[1];
			smsg.v[2] = msg.v[2];
			smsg.v[3] = msg.v[3];
			SendMsg(it.id, (char*)&smsg, sizeof(smsg));
		}
	}
}

void cGameServer::DeletePlayerMsg(NetMsg msg)
{
	for (auto it = m_clientList.begin(); it != m_clientList.end();)
	{
		if (it->id== msg.id)
		{
			it = m_clientList.erase(it);
		}
		else
		{
			NetMsg smsg;
			smsg.Type = Msg_DeletePlayer;
			smsg.id = msg.id;
			SendMsg(it->id, (char*)&smsg, sizeof(smsg));
			++it;
		}
	}
}