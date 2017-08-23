// CollisionServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include"cGameServer.h"
#include<string>
using namespace std;

int main()
{
	cGameServer* pServer = new cGameServer;
	if (pServer->StartServer(NULL, NULL, 6036, Net::MODE_IOCP) == true)
	{
		cout << "开启服务器成功!" << endl;
	}
	
	string input;
	while (true)
	{
		cin >> input;
		if (input == "exit")
		{
			break;
		}
	}
	delete pServer;
    return 0;
}

