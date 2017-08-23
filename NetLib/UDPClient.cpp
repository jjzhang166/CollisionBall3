#include "stdafx.h"
#include "UDPClient.h"
#pragma comment(lib,"ws2_32.lib")
using namespace Net;
using namespace std;


Net::CUDPClient::CUDPClient()
{
	m_cientProc.func = NULL;
	m_cientProc.Param = NULL;
	m_pRecvThread = nullptr;
}

CUDPClient::CUDPClient(UClientFunc proc, LPVOID Param)
{
	m_cientProc.func = proc;
	m_cientProc.Param = Param;
	m_pRecvThread = nullptr;
}

CUDPClient::~CUDPClient()
{
	CloseClient();
}

const std::string & Net::CUDPClient::GetLastError()
{
	return m_error;
}

bool CUDPClient::ConnectServer(const std::string & serverIp, unsigned long port)
{
	m_isClose = false;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		m_error = "初始化网络环境失败!->错误代码：" + WSAGetLastError();
		return false;
	}
	m_skClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_skClient == INVALID_SOCKET)
	{
		m_error = "创建套接字失败!->错误代码：" + WSAGetLastError();
		return false;
	}
	memset(&m_serverAddr, 0, sizeof(m_serverAddr));
	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_addr.S_un.S_addr = inet_addr(serverIp.c_str());
	m_serverAddr.sin_port = htons(port);
	if (SendConnectMsg() == false)
	{
		m_error == "连接服务器失败!";
		return false;
	}
	m_pRecvThread = new thread{ &CUDPClient::DoRecvMsg,this };
	return true;
}

bool Net::CUDPClient::SendMsg(char * buff, unsigned int len)
{
	if (sendto(m_skClient, buff, len, 0, (sockaddr*)&m_serverAddr, sizeof(m_serverAddr))==SOCKET_ERROR)
	{
		m_error = "向服务器发送数据失败";
		return false;
	}
	return true;
}

void Net::CUDPClient::CloseClient()
{
	SendCloseMsg();
	WSACleanup();
	closesocket(m_skClient);
	m_isClose = true;
	if (m_pRecvThread != nullptr)
	{
		m_pRecvThread->join();
		delete m_pRecvThread;
		m_pRecvThread = nullptr;
	}
}

void Net::CUDPClient::OnRecv(char * buff)
{
}

void Net::CUDPClient::DoRecvMsg()
{
	while (true)
	{
		if (m_isClose == true)
		{
			break;
		}
		char buff[BUFF_SIZE] = { 0 };
		sockaddr_in serverAddr = { 0 };
		int len = sizeof(serverAddr);
		int iRet = recvfrom(m_skClient, buff, sizeof(buff), 0, (sockaddr*)&serverAddr, &len);
		if (iRet != SOCKET_ERROR&&iRet!=0)
		{
			if (strcmp(buff, CLOSE_MESSAGE) == 0)
			{
				printf_s("服务器下线了");
				if (m_cientProc.func != NULL)
				{
					m_cientProc.func(CLOSE_MESSAGE, this, m_cientProc.Param);
				}
				else
				{
					OnRecv(CLOSE_MESSAGE);
				}
				break;
			}
			else
			{
				if (m_cientProc.func != NULL)
				{
					m_cientProc.func(buff, this, m_cientProc.Param);
				}
				else
				{
					OnRecv(buff);
				}
			}
		}
	}
}

void Net::CUDPClient::SendCloseMsg()
{
	SendMsg(CLOSE_MESSAGE, sizeof(CLOSE_MESSAGE));
}

bool Net::CUDPClient::SendConnectMsg()
{
	return SendMsg(CONNECT_MESSAGE, sizeof(CONNECT_MESSAGE));
}