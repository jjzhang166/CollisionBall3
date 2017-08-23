#pragma once
#include<cSight.h>
#include<cPicture.h>
#include<cButton.h>
#include<cCircle.h>
#include<cText.h>
#include<TCPClient.h>
#include"cGamePlayer.h"
#include"cFood.h"
#include"cBackHole.h"
#include<vector>
#include<list>

struct NetMsg;

class cGameSight:public MyEngine::cSight,public Net::CTCPClient
{
public:
	cGameSight();
	virtual ~cGameSight();

	/*
	*OnRecv(char* buff);
	*收到服务器消息的回调函数
	*@Param buff:消息内容
	*/
	virtual void OnRecv(char* buff);

	/*
	*OnGoBack(void* Param);
	*回退按钮回调函数
	*/
	void OnGoBack(void* Param);

	/*
	*int OnTimer(int id, int iParam, string str)
	*定时器回调函数
	*/
	virtual int OnTimer(int id, int iParam, string str) override;
	
	/*
	*initMap();
	*初始化地图
	*/
	void initMap();

	/*
	*MovePlayer();
	*移动玩家
	*/
	void MovePlayer();

	//键盘按下
	void OnKeyDown(void *Param);
	//键盘弹起
	void OnKeyUp(void* Param);

	/*
	*CalcMiniPlayerSite();
	*计算小地图中玩家位置
	*/
	void CalcMiniPlayerSite();

	/*
	*initSight();
	*初始化整个视野上的事物
	*/
	void initSight();

	void SendInitMsg();

	void SendPlayMoveMsg();

	void AddPlayer(NetMsg msg);

	void OtherPlayMoveMsg(NetMsg msg);

	void MoveOtherPlayers();

	void CalcFoodScreenPos();

	void AddFood(NetMsg msg);

	//重写绘制函数
	virtual bool Draw(HDC hDc) override;

	void CheckCollisionFood();

	void SendEatFoodMsg(DWORD id);

	void EatedFood(NetMsg msg);

	void SendUpdateInfoMsg();

	void UpdateInfoMsg(NetMsg msg);

	void CheckCollisionOtherPlayers();

	/*
	*DoCollision(cGamePlayer* pPlayer);
	*处理自己与其它玩家之间碰撞事件
	*@Param pPlayer：其它玩家
	*@return int：如何两者都没事返回0，如果自己阵亡返回-1，敌方阵亡放回1
	*/
	int DoCollision(cGamePlayer* pPlayer);

	void CheckDeleteOtherPlayers();

	void SendDeletePlayerMsg(DWORD id);

	void DeletePlayerMsg(NetMsg msg);

	void AddBackHole(NetMsg msg);

	void CalcBackHoleScreenPos();

	void CheckAttractByBackHole();

	//void initLeaderList();

	//void UpdateLeadList();  //更新排行榜
private:
	MyEngine::cPicture* m_Map[MAP_ROW][MAP_RANK]; 
	MyEngine::cButton* m_goBack;
	MyEngine::cButton* m_miniMap;
	MyEngine::cCircle* m_miniPlayer;
	cGamePlayer* m_player;
	std::list<cGamePlayer*> m_otherPlayers;
	std::list<MyEngine::cCircle*> m_otherminiPlayers;
	std::list<cFood*> m_foodList;
	std::list<MyEngine::cCircle*> m_miniFoods;
	std::list<cBackHole*> m_backholeList;
	POINT m_miniMapOrigin;  //小地图原点
	bool m_KeyIsDown[2] = { false,false };
	//MyEngine::cText* m_leaderboard;  //显示排行榜
	//vector<MyEngine::cText*> m_leaderList;  //排行榜列表
};