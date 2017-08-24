#include "stdafx.h"
#include "cGameSight.h"
#include"cStartSight.h"
#include"Message.h"
#include<cGameEngine.h>
#include<Tool.h>
#pragma comment(lib,"NetLib.lib")
using namespace Net;
using namespace MyEngine;
#define PI 3.1f

cGameSight::cGameSight()
{
}

cGameSight::~cGameSight()
{
	CloseThread();
}

void cGameSight::OnRecv(char * buff)
{
	NetMsg* pMsg = (NetMsg*)buff;
	switch (pMsg->Type)
	{
	case Msg_AllotTag:
	{
		m_player->m_tag = pMsg->id;
		char name[MAX_PATH] = { 0 };
		sprintf(name, "玩家%d", pMsg->id);
		m_player->SetName(name);
	}
		break;
	case Msg_PlayMove:
		OtherPlayMoveMsg(*pMsg);
		break;
	case Msg_CreateBackHole:
		AddBackHole(*pMsg);
		break;
	case Msg_AddPlayer:
		AddPlayer(*pMsg);
		break;
	case Msg_DeletePlayer:
		DeletePlayerMsg(*pMsg);
		break;
	case Msg_AddFood:
		AddFood(*pMsg);
		break;
	case Msg_EatFood:
		EatedFood(*pMsg);
		break;
	case Msg_UpdateInfo:
		UpdateInfoMsg(*pMsg);
		break;
	default:
		break;
	}
}

void cGameSight::OnGoBack(void * Param)
{
	if (MessageBox(NULL, L"确定返回?", L"善意的提示", MB_OKCANCEL) == IDOK)
	{
		cGameEngine::GetEngine()->DeleteUI(this);
		cStartSight* pSight = new cStartSight;
		cGameEngine::GetEngine()->AddEngineUi(pSight);
	}
}

int cGameSight::OnTimer(int id, int iParam, string str)
{
	static int updatedelay = 5;
	MovePlayer();
	MoveOtherPlayers();
	CheckCollisionOtherPlayers();
	CheckCollisionFood();
	CheckDeleteOtherPlayers();
	CalcBackHoleScreenPos();
	CheckAttractByBackHole();
	UpdateLeadList();
	if (updatedelay == 0)
	{
		SendUpdateInfoMsg();
	}
	updatedelay == 0 ? updatedelay = 5 : --updatedelay;
	return 1;
}

void cGameSight::initMap()
{
	POINT basePt;
	basePt.x = m_player->GetX() - m_player->GetWorldX();
	basePt.y = m_player->GetY()-m_player->GetWorldY();
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_RANK; ++j)
		{
			m_Map[i][j] = new cPicture("GameBg");
			m_Map[i][j]->SetX(basePt.x + i*SCREENSIZEX);
			m_Map[i][j]->SetY(basePt.y + j*SCREENSIZEY);
			addChild(m_Map[i][j]);
		}
	}
}

void cGameSight::MovePlayer()
{
	if (m_player == nullptr)
	{
		return;
	}
	if (m_player->Move() == false)
	{
		return;
	}
	CalcMiniPlayerSite();
	CalcFoodScreenPos();
	POINT basePt;
	basePt.x = m_player->GetX() - m_player->GetWorldX();
	basePt.y = m_player->GetY()-m_player->GetWorldY();
	for (int i = 0; i < MAP_ROW; ++i)
	{
		for (int j = 0; j < MAP_RANK; ++j)
		{
			m_Map[i][j]->SetX(basePt.x + i*SCREENSIZEX);
			m_Map[i][j]->SetY(basePt.y + j*SCREENSIZEY);
		}
	}
}

void cGameSight::OnKeyDown(void * Param)
{
	if (m_player == nullptr)
	{
		return;
	}
	DWORD id = *((UINT_PTR*)Param);
	int lastvx = m_player->GetVx();
	int lastvy = m_player->GetVy();
	switch (id)
	{
	case VK_CONTROL:
		m_player->Accelerate();
		if (lastvx != m_player->GetVx() || lastvy != m_player->GetVy())
			SendPlayMoveMsg();
		break;
	case VK_UP:
		m_player->SetVy(-m_player->GetBasicSpeed());
		if (lastvx != m_player->GetVx() || lastvy != m_player->GetVy())
			SendPlayMoveMsg();
		break;
	case VK_LEFT:
		m_player->SetVx(-m_player->GetBasicSpeed());
		if (lastvx != m_player->GetVx() || lastvy != m_player->GetVy())
			SendPlayMoveMsg();
		break;
	case VK_RIGHT:
		m_player->SetVx(m_player->GetBasicSpeed());
		if (lastvx != m_player->GetVx() || lastvy != m_player->GetVy())
			SendPlayMoveMsg();
		break;
	case VK_DOWN:
		m_player->SetVy(m_player->GetBasicSpeed());
		if (lastvx != m_player->GetVx() || lastvy != m_player->GetVy())
			SendPlayMoveMsg();
		break;
	default:
		break;
	}
}

void cGameSight::OnKeyUp(void * Param)
{
	if (m_player == nullptr)
	{
		return;
	}
	DWORD id = *((UINT_PTR*)Param);
	switch (id)
	{
	case VK_CONTROL:
		m_player->Decelerate();
		SendPlayMoveMsg();
		break;
	default:
		break;
	}
}

void cGameSight::CalcMiniPlayerSite()
{
	if (m_player == nullptr)
	{
		return;
	}
	float x = (float)m_player->GetWorldX();
	float y = (float)m_player->GetWorldY();
	float perx = x/MAP_SIZEX;
	float pery =  y/MAP_SIZEY;
	POINT pt;
	pt.x = m_miniMapOrigin.x + perx*MINI_MAP_SZIEX;
	pt.y = m_miniMapOrigin.y + pery*MINI_MAP_SZIEY;
	m_miniPlayer->SetCenter(pt);
}

void cGameSight::initSight()
{
	m_player = new cGamePlayer;
	m_miniPlayer = new cCircle;
	m_miniPlayer->SetRaduis(3);
	m_miniPlayer->SetLineColor(RGB(255, 0, 0));
	initMap();
	m_goBack = new cButton("GoBack");
	m_goBack->SetX(SCREENSIZE.width*0.02);
	m_goBack->SetY(SCREENSIZE.height*0.02);
	m_miniMap = new cButton("MiniMap");
	m_miniMap->SetX(SCREENSIZE.width - m_miniMap->GetWidth() - 2);
	m_miniMap->SetY(2);
	m_miniMapOrigin.x = SCREENSIZE.width - m_miniMap->GetWidth() - 2;
	m_miniMapOrigin.y = 2;
	m_miniMap->SetnBount(6);
	m_miniMap->SetFirstBountColor(RGB(181, 230, 29));
	CalcMiniPlayerSite();
	m_leaderboard = new cText;
	m_leaderboard->SetText("排行榜:");
	m_leaderboard->SetTextColor(RGB(255, 127, 39));
	m_leaderboard->SetX(SCREENSIZE.width - m_miniMap->GetWidth() - 2);
	m_leaderboard->SetY(m_miniMap->GetHeight() + 10);
	addChild(m_goBack);
	addChild(m_player);
	addChild(m_miniMap);
	addChild(m_miniPlayer);
	addChild(m_leaderboard);
	initLeaderList();
	cGameEngine::GetEngine()->AddEventToUi(m_goBack, WM_LBUTTONUP, _CALLFUNC(cGameSight::OnGoBack), this);
	cGameEngine::GetEngine()->AddEventToUi(this, WM_KEYUP, _CALLFUNC(cGameSight::OnKeyUp), this);
	cGameEngine::GetEngine()->AddEventToUi(this, WM_KEYDOWN, _CALLFUNC(cGameSight::OnKeyDown), this);
	AddTimer(1, 20);
	SendInitMsg();
}

void cGameSight::SendInitMsg()
{
	if (m_player == nullptr)
	{
		return;
	}
	NetMsg msg;
	msg.Type = Msg_Init;
	msg.id = m_player->GetBody()->GetFillColor();
	msg.pt.x = m_player->GetWorldX();
	msg.pt.y = m_player->GetWorldY();
	msg.v[0] = m_player->GetVx();
	msg.v[1] = m_player->GetVy();
	msg.v[2] = m_player->GetBody()->GetRadius();
	msg.v[3] = m_player->GetPhysicalValue();
	this->SendMsg((char*)&msg, sizeof(msg));
}

void cGameSight::SendPlayMoveMsg()
{
	if (m_player == nullptr)
	{
		return;
	}
	NetMsg msg;
	msg.Type = Msg_PlayMove;
	msg.pt.x = m_player->GetWorldX();
	msg.pt.y = m_player->GetWorldY();
	msg.v[0] = m_player->GetVx();
	msg.v[1] = m_player->GetVy();
	this->SendMsg((char*)&msg, sizeof(msg));
}

void cGameSight::AddPlayer(NetMsg msg)
{
	if (m_player == nullptr)
	{
		return;
	}
	cGamePlayer* pPlayer = new cGamePlayer;
	pPlayer->GetBody()->SetIsFill(true);
	pPlayer->GetBody()->SetFillColor(msg.id);
	pPlayer->SetWorldX(msg.pt.x);
	pPlayer->SetWorldY(msg.pt.y);
	pPlayer->m_tag = msg.id1;
	char name[MAX_PATH] = { 0 };
	sprintf(name, "玩家%d", pPlayer->m_tag);
	pPlayer->SetName(name);
	pPlayer->SetVx(msg.v[0]);
	pPlayer->SetVy(msg.v[1]);
	pPlayer->SetRadius(msg.v[2]);
	pPlayer->SetPhysicalValue(msg.v[3]);
	int difx = pPlayer->GetWorldX() - m_player->GetWorldX();
	int dify = pPlayer->GetWorldY() - m_player->GetWorldY();
	pPlayer->SetX(m_player->GetX() + difx);
	pPlayer->SetY(m_player->GetY() + dify);
	cCircle* pMiniPlayer = new cCircle;
	pMiniPlayer->SetX(m_miniMapOrigin.x + (float)(pPlayer->GetWorldX() / MAP_SIZEX)*MINI_MAP_SZIEX);
	pMiniPlayer->SetY(m_miniMapOrigin.y + (float)(pPlayer->GetWorldY() / MAP_SIZEY)*MINI_MAP_SZIEY);
	pMiniPlayer->SetRaduis(3);
	pMiniPlayer->SetLineColor(msg.id);
	m_otherminiPlayers.push_back(pMiniPlayer);
	m_otherPlayers.push_back(pPlayer);
	addChild(pPlayer);
	addChild(pMiniPlayer);
}

void cGameSight::OtherPlayMoveMsg(NetMsg msg)
{
	auto it1 = m_otherPlayers.begin();
	for (;it1!=m_otherPlayers.end();++it1)
	{
		if ((*it1)->m_tag == msg.id)
		{
			(*it1)->SetVx(msg.v[0]);
			(*it1)->SetVy(msg.v[1]);
		}
	}
}

void cGameSight::MoveOtherPlayers()
{
	if (m_player == nullptr)
	{
		return;
	}
	auto it1 = m_otherPlayers.begin();
	auto it2 = m_otherminiPlayers.begin();
	for (; it1 != m_otherPlayers.end(); ++it1, ++it2)
	{
		(*it1)->Move();
		int difx = (*it1)->GetWorldX() - m_player->GetWorldX();
		int dify = (*it1)->GetWorldY() - m_player->GetWorldY();
		(*it1)->SetX(m_player->GetX() + difx);
		(*it1)->SetY(m_player->GetY() + dify);
		(*it2)->SetX(m_miniMapOrigin.x + (float)((*it1)->GetWorldX() / MAP_SIZEX)*MINI_MAP_SZIEX);
		(*it2)->SetY(m_miniMapOrigin.y + (float)((*it1)->GetWorldY() / MAP_SIZEY)*MINI_MAP_SZIEY);
	}
}

void cGameSight::CalcFoodScreenPos()
{
	if (m_player == nullptr)
	{
		return;
	}
	for (auto it : m_foodList)
	{
		it->SetX(it->m_worldPos.x - m_player->GetWorldX() + m_player->GetX());
		it->SetY(it->m_worldPos.y - m_player->GetWorldY() + m_player->GetY());
	}
}

void cGameSight::AddFood(NetMsg msg)
{
	if (m_player == nullptr)
	{
		return;
	}
	cFood* pFood = new cFood;
	pFood->m_worldPos = msg.pt;
	pFood->SetRaduis(8);
	pFood->SetIsFill(true);
	pFood->SetFillColor(msg.id1);
	pFood->m_tag = msg.id;
	pFood->SetX(msg.pt.x - m_player->GetWorldX() + m_player->GetX());
	pFood->SetY(msg.pt.y - m_player->GetWorldY() + m_player->GetY());
	
	cCircle* pMiniFood = new cCircle;
	pMiniFood->SetLineColor(msg.id1);
	pMiniFood->SetRaduis(1);
	pMiniFood->SetX(m_miniMapOrigin.x + (float)(pFood->m_worldPos.x / MAP_SIZEX)*MINI_MAP_SZIEX);
	pMiniFood->SetY(m_miniMapOrigin.y + (float)(pFood->m_worldPos.y / MAP_SIZEY)*MINI_MAP_SZIEY);
	m_miniFoods.push_back(pMiniFood);
	m_foodList.push_back(pFood);
	addChild(pFood);
	addChild(pMiniFood);
}

bool cGameSight::Draw(HDC hDc)
{
	cSight::Draw(hDc);
	if (m_player != nullptr)
	{
		m_player->Draw(hDc);
	}
	m_miniMap->Draw(hDc);
	if (m_miniPlayer != nullptr)
	{
		m_miniPlayer->Draw(hDc);
	}
	for (auto it1 : m_miniFoods)
	{
		it1->Draw(hDc);
	}
	for (auto it : m_otherminiPlayers)
	{
		it->Draw(hDc);
	}

	return true;
}

void cGameSight::CheckCollisionFood()
{
	if (m_player == nullptr)
	{
		return;
	}
	auto it1 = m_foodList.begin();
	auto it2 = m_miniFoods.begin();
	for (; it1 != m_foodList.end();)
	{
		int distance = PointToPointDistance((*it1)->GetCenter(), m_player->GetBody()->GetCenter());
		if (distance < (*it1)->GetRadius() + m_player->GetBody()->GetRadius())
		{
			m_player->AddExp(OneExp);
			SendEatFoodMsg((*it1)->m_tag);
			RemoveChild(*it1);
			it1 = m_foodList.erase(it1);
			RemoveChild(*it2);
			it2 = m_miniFoods.erase(it2);
		}
		else
		{
			++it1;
			++it2;
		}
	}
}

void cGameSight::SendEatFoodMsg(DWORD id)
{
	NetMsg smsg;
	smsg.Type = Msg_EatFood;
	smsg.id = id;
	SendMsg((char*)&smsg, sizeof(smsg));
}

void cGameSight::EatedFood(NetMsg msg)
{
	auto it1 = m_foodList.begin();
	auto it2 = m_miniFoods.begin();
	for (; it1 != m_foodList.end(); ++it1, ++it2)
	{
		if ((*it1)->m_tag == msg.id)
		{
			RemoveChild(*it1);
			it1 = m_foodList.erase(it1);
			RemoveChild(*it2);
			it2 = m_miniFoods.erase(it2);
			return;
		}
	}
}

void cGameSight::SendUpdateInfoMsg()
{
	if (m_player == nullptr)
	{
		return;
	}
	NetMsg msg;
	msg.Type = Msg_UpdateInfo;
	msg.id1 = m_player->GetBody()->GetFillColor();
	msg.pt.x = m_player->GetWorldX();
	msg.pt.y = m_player->GetWorldY();
	msg.v[0] = m_player->GetVx();
	msg.v[1] = m_player->GetVy();
	msg.v[2] = m_player->GetBody()->GetRadius();
	msg.v[3] = m_player->GetPhysicalValue();
	SendMsg((char*)&msg, sizeof(msg));
}

void cGameSight::UpdateInfoMsg(NetMsg msg)
{
	if (m_player == nullptr)
	{
		return;
	}
	auto it1 = m_otherPlayers.begin();
	auto it2 = m_otherminiPlayers.begin();
	for (; it1 != m_otherPlayers.end(); ++it1, ++it2)
	{
		if((*it1)->m_tag == msg.id)
		{
			(*it1)->SetVx(msg.v[0]);
			(*it1)->SetVy(msg.v[1]);
			(*it1)->SetRadius(msg.v[2]);
			(*it1)->SetPhysicalValue(msg.v[3]);
			(*it1)->SetWorldX(msg.pt.x);
			(*it1)->SetWorldY(msg.pt.y);
			int difx = (*it1)->GetWorldX() - m_player->GetWorldX();
			int dify = (*it1)->GetWorldY() - m_player->GetWorldY();
			(*it1)->SetX(m_player->GetX() + difx);
			(*it1)->SetY(m_player->GetY() + dify);
			(*it2)->SetX(m_miniMapOrigin.x + (float)((*it1)->GetWorldX() / MAP_SIZEX)*MINI_MAP_SZIEX);
			(*it2)->SetY(m_miniMapOrigin.y + (float)((*it1)->GetWorldY() / MAP_SIZEY)*MINI_MAP_SZIEY);
		}
	}
}

void cGameSight::CheckCollisionOtherPlayers()
{
	if (m_player == nullptr)
	{
		return;
	}
	for (auto it:m_otherPlayers)
	{
		int distance = PointToPointDistance(it->GetBody()->GetCenter(), m_player->GetBody()->GetCenter());
		if (distance < it->GetBody()->GetRadius() + m_player->GetBody()->GetRadius() - 2)
		{
			int iRet = DoCollision(it);
			if (iRet == 1)
			{
				it->SetbDel(true);
				m_player->AddExp((it->GetBody()->GetRadius() - Basic_Radius+1)*Basic_Exp);
				SendDeletePlayerMsg(it->m_tag);
			}
			if (iRet == -1)
			{
				MessageBox(cGameEngine::GetEngine()->GethWnd(), L"你已经死亡", L"恶意的提示", MB_OK);
				RemoveChild(m_player);
				RemoveChild(m_miniPlayer);
				m_player = nullptr;
				m_miniPlayer = nullptr;
				CloseClient();
				DeleteTimer(1);
			}
			return;
		}
	}
}

int cGameSight::DoCollision(cGamePlayer * pPlayer)
{
	if (m_player == nullptr)
	{
		return 0;
	}
	//基于半径和体力计算权重，通过比较权重来判断那个玩家阵亡
	int selfWidth = pow(m_player->GetBody()->GetRadius(), 2)*m_player->GetPhysicalValue();
	int hisWidth = pow(pPlayer->GetBody()->GetRadius(), 2)*pPlayer->GetPhysicalValue();
	if (selfWidth > hisWidth)
	{
		return 1;
	}
	else if (selfWidth < hisWidth)
	{
		return -1;
	}
	return 0;
}

void cGameSight::CheckDeleteOtherPlayers()
{
	auto it1 = m_otherPlayers.begin();
	auto it2 = m_otherminiPlayers.begin();
	for (; it1 != m_otherPlayers.end(); ++it1, ++it2)
	{
		if ((*it1)->GetbDel()==true)
		{
			RemoveChild(*it1);
			RemoveChild(*it2);
			m_otherPlayers.erase(it1);
			m_otherminiPlayers.erase(it2);
			break;
		}
	}
}

void cGameSight::SendDeletePlayerMsg(DWORD id)
{
	NetMsg smsg;
	smsg.Type = Msg_DeletePlayer;
	smsg.id = id;
	SendMsg((char*)&smsg, sizeof(smsg));
}

void cGameSight::DeletePlayerMsg(NetMsg msg)
{
	for (auto it : m_otherPlayers)
	{
		if (it->m_tag == msg.id)
		{
			it->SetbDel(true);
		}
	}
}

void cGameSight::AddBackHole(NetMsg msg)
{
	if (m_player == nullptr)
	{
		return;
	}
	cBackHole* pBackHole = new cBackHole;
	pBackHole->SetWorldPos(msg.pt);
	pBackHole->SetControlRadius(msg.v[0]);
	pBackHole->SetLifeCycle(msg.v[1]);
	pBackHole->SetPower(msg.v[2]);
	int difx = msg.pt.x - m_player->GetWorldX();
	int dify = msg.pt.y - m_player->GetWorldY();
	pBackHole->SetX(difx + m_player->GetX());
	pBackHole->SetY(dify + m_player->GetY());
	m_backholeList.push_back(pBackHole);
	addChild(pBackHole);
}

void cGameSight::CalcBackHoleScreenPos()
{
	if (m_player == nullptr)
	{
		return;
	}
	for (auto it = m_backholeList.begin();it!=m_backholeList.end();)
	{
		if ((*it)->GetLifeCycle()>0)
		{
			POINT pos = (*it)->GetWorldPos();
			int difx = pos.x - m_player->GetWorldX();
			int dify = pos.y - m_player->GetWorldY();
			(*it)->SetX(difx + m_player->GetX());
			(*it)->SetY(dify + m_player->GetY());
			(*it)->DecLifeCycle();
			++it;
		}
		else
		{
			RemoveChild(*it);
			it = m_backholeList.erase(it);
		}
	}
}

void cGameSight::CheckAttractByBackHole()
{
	if (m_player == nullptr)
	{
		return;
	}
	for (auto it : m_backholeList)
	{
		POINT p1 = it->GetCenter();
		POINT p2 = m_player->GetBody()->GetCenter();
		int distance = PointToPointDistance(p1, p2) - m_player->GetBody()->GetRadius();
		if (distance < it->GetControlRadius())
		{
			distance < Hole_Radius ? m_player->DecRadius() : 1;
			int dirx = p1.x - p2.x;
			int diry = p1.y - p2.y;
			int lastx = m_player->GetWorldX();
			int lasty = m_player->GetWorldY();
			dirx != 0 ? m_player->SetWorldX(lastx + (dirx / abs(dirx))*it->GetPower()) : 1;
			diry != 0 ? m_player->SetWorldY(lasty + (diry) / abs(diry)*it->GetPower()) : 1;
			m_player->CalcScreenSite();
		}
	}
}

void cGameSight::initLeaderList()
{
	int basicx = SCREENSIZE.width - m_miniMap->GetWidth() + 40;
	int basicy = m_miniMap->GetHeight() + 65;
	for (int i = 0; i < 6; ++i)
	{
		cText* text = new cText("");
		text->SetFontHeight(20);
		text->SetFontWidth(10);
		text->SetTextColor(RGB(255, 0, 0));
		text->SetX(basicx);
		text->SetY(basicy + i * 22);
		m_leaderList.push_back(text);
		addChild(text);
	}
}

void cGameSight::UpdateLeadList()
{
	if (m_player == nullptr)
	{
		return;
	}
	char name[MAX_PATH] = { 0 };
	int num[11] = { 0 };
	num[5] = 1 << 30;
	for (auto it : m_otherPlayers)
	{
		for (int i = 0; i <=5; ++i)
		{
			if (it->GetBody()->GetRadius()<=num[i])
			{
				num[i - 1] = it->GetBody()->GetRadius();
				num[i + 5] = it->m_tag;
				break;
			}
		}
	}
	for (int i = 4; i>=0; --i)
	{
		if (num[i] == 0)
			break;
		sprintf(name, "玩家%d:%d", num[i + 6], num[i]);
		m_leaderList[4 - i]->SetText(name);
	}
	sprintf(name, "自己:%d", m_player->GetBody()->GetRadius());
	m_leaderList[5]->SetText(name);
}
