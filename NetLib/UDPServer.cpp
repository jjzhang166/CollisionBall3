#include "stdafx.h"
#include "UDPServer.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace Net;

CUDPServer::CUDPServer()
{
}


CUDPServer::~CUDPServer()
{
	CloseServer();
}

bool Net::CUDPServer::StartServer(USeverFunc proc, LPVOID Param, USERVER_MODE mode, unsigned long port )
{
	m_isClose = false;
	m_mode = mode;
	m_serverProc.func = proc;
	m_serverProc.Param = Param;
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		m_error = "初始化网络环境失败!";
		return false;
	}
	if (m_mode == UMODE_ORDINARY)
	{
		return InitOridinaryServer(port);
	}
	else
	{
		return InitIOCPServer(port);
	}
}

const std::string & Net::CUDPServer::GetLastError()
{
	return m_error;
}

const USERVER_MODE & Net::CUDPServer::GetMode()
{
	return m_mode;
}

std::list<std::string> Net::CUDPServer::GetHostIPs()
{
	list<string> hostIps;
	hostIps.clear();
	char	cHost[256];
	gethostname(cHost, 256);

	hostent *pHost = gethostbyname(cHost);
	if (pHost == NULL)
	{
		return hostIps;
	}
	in_addr addr;

	char	*p = pHost->h_addr;
	memcpy(&addr.S_un.S_addr, p, pHost->h_length);
	hostIps.emplace_back(inet_ntoa(addr));
	return hostIps;
}

bool Net::CUDPServer::SendMsg(sockaddr_in dest, char * buff, unsigned int len)
{
	if (sendto(m_sockServer, buff, len, 0, (sockaddr*)&dest, sizeof(dest)) == SOCKET_ERROR)
	{
		m_error = "向客户端";
		m_error.append(inet_ntoa(dest.sin_addr));
		m_error += "发送数据失败!";
		return false;
	}
	return true;
}

bool Net::CUDPServer::SendMsgAll(char * buff, unsigned int len)
{
	m_lock.Lock();
	for (auto it : m_clientaddrList)
	{
		if (sendto(m_sockServer, buff, len, 0, (sockaddr*)&it, sizeof(it)) == SOCKET_ERROR)
		{
			m_error = "向客户端";
			m_error.append(inet_ntoa(it.sin_addr));
			m_error += "发送数据失败!";
			m_lock.UnLock();
			return false;
		}
	}
	m_lock.UnLock();
	return false;
}

void Net::CUDPServer::CloseServer()
{
	SendCloseMsg();
	WSACleanup();
	closesocket(m_sockServer);
	CloseHandle(m_hCompletionPort);
	m_isClose = true;
	m_clientaddrList.clear();
	for (auto it : m_dataList)
	{
		delete it;
		it = nullptr;
	}
	m_dataList.clear();
	for (auto it = m_threadList.begin(); it != m_threadList.end(); ++it)
	{
		it->join();
	}
	m_threadList.clear();
}

void Net::CUDPServer::OnRecv(sockaddr_in sai, char* buff)
{
}

bool Net::CUDPServer::InitOridinaryServer(unsigned long port)
{
	m_sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sockServer == INVALID_SOCKET)
	{
		m_error = "创建套接字失败!";
		return false;
	}
	sockaddr_in socketaddr;
	memset(&socketaddr, 0, sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_port = htons(port);
	socketaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(m_sockServer, (sockaddr*)&socketaddr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		m_error = "绑定套接字失败!";
		return false;
	}

	m_threadList.emplace_back(thread{ &CUDPServer::DoOridinaryMsg,this });
	return true;
}

bool Net::CUDPServer::InitIOCPServer(unsigned long port)
{
	m_sockServer = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_sockServer == INVALID_SOCKET)
	{
		m_error = "创建套接字失败!";
		return false;
	}
	sockaddr_in serveraddr = { 0 };
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.S_un.S_addr = INADDR_ANY;
	serveraddr.sin_port = htons(port);
	int iRet = ::bind(m_sockServer, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (iRet == SOCKET_ERROR)
	{
		m_error = "绑定套接字失败!";
		return false;
	}

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (m_hCompletionPort == NULL)
	{
		m_error = "创建完成端口失败!";
		return false;
	}
	
	SYSTEM_INFO systeminfo;
	GetSystemInfo(&systeminfo);
	CreateIoCompletionPort((HANDLE)m_sockServer, m_hCompletionPort,
		(ULONG_PTR)m_sockServer, systeminfo.dwNumberOfProcessors * 2 + 2);
	for (int i = 0; i < systeminfo.dwNumberOfProcessors * 2 + 2; ++i)
	{
		m_threadList.emplace_back(thread{ &CUDPServer::DoIOCPMsg,this });
		OVP_IO_UDATA* ovpDada = new OVP_IO_UDATA;
		memset(ovpDada, 0, sizeof(OVP_IO_UDATA));
		ovpDada->wsaBuf.len = sizeof(ovpDada->Message);
		ovpDada->wsaBuf.buf = (char*)ovpDada->Message;
		ovpDada->sourceAddrLen = sizeof(ovpDada->sourceAddr);
		m_dataList.push_back(ovpDada);
		int iRet=WSARecvFrom(m_sockServer, &ovpDada->wsaBuf, 1, &ovpDada->recvNums,
			&ovpDada->flags, (sockaddr*)&ovpDada->sourceAddr, 
			&ovpDada->sourceAddrLen, &ovpDada->overlap, NULL);
	}
	return true;
}

void Net::CUDPServer::DoOridinaryMsg()
{
	while (true)
	{
		if (m_isClose == true)
		{
			break;
		}
		char buff[BUFF_SIZE] = { 0 };
		sockaddr_in sockclientaddr;
		memset(&sockclientaddr, 0, sizeof(sockclientaddr));
		int len = sizeof(sockclientaddr);
		int iRet = recvfrom(m_sockServer, buff, sizeof(buff), 0, (SOCKADDR*)&sockclientaddr, &len);
		if (iRet != SOCKET_ERROR&&iRet != 0)
		{
			if (strcmp(buff, CONNECT_MESSAGE) == 0)
			{
				printf_s("客户端%s:%ld连接了\n", inet_ntoa(sockclientaddr.sin_addr), sockclientaddr.sin_port);
				if (m_serverProc.func != NULL)
				{
					m_serverProc.func(sockclientaddr, CONNECT_MESSAGE, this, m_serverProc.Param);
				}
				else
				{
					OnRecv(sockclientaddr, CONNECT_MESSAGE);
				}
				m_clientaddrList.push_back(sockclientaddr);
			}
			else if (strcmp(buff, CLOSE_MESSAGE) == 0)
			{
				printf_s("客户端%s:%ld断开了连接\n", inet_ntoa(sockclientaddr.sin_addr), sockclientaddr.sin_port);	
				if (m_serverProc.func != NULL)
				{
					m_serverProc.func(sockclientaddr,CLOSE_MESSAGE, this, m_serverProc.Param);
				}
				else
				{
					OnRecv(sockclientaddr, CLOSE_MESSAGE);
				}
				RemoveClientAddr(sockclientaddr);
			}
			else
			{
				if (m_serverProc.func != NULL)
				{
					m_serverProc.func(sockclientaddr, buff, this, m_serverProc.Param);
				}
				else
				{
					OnRecv(sockclientaddr, buff);
				}
			}
		}
	}
}

void Net::CUDPServer::DoIOCPMsg()
{
	OVP_IO_UDATA* ovpData;
	DWORD transferred;
	DWORD sockClient;
	while (true)
	{
		if (m_isClose == true)
		{
			break;
		}
		ovpData = nullptr;
		BOOL bRet = GetQueuedCompletionStatus(m_hCompletionPort, &transferred,
			(PULONG_PTR)&sockClient, (LPOVERLAPPED*)&ovpData, 10);
		DWORD dwError = ::GetLastError();
		if (bRet != FALSE && dwError != SOCKET_ERROR && transferred != 0)
		{
			if (strcmp(ovpData->Message, CONNECT_MESSAGE) == 0)
			{
				printf_s("客户端%s:%ld连接了\n", inet_ntoa(ovpData->sourceAddr.sin_addr), ovpData->sourceAddr.sin_port);
				m_lock.Lock();
				m_clientaddrList.push_back(ovpData->sourceAddr);
				m_lock.UnLock();
			}
			else if (strcmp(ovpData->Message, CLOSE_MESSAGE) == 0)
			{
				printf_s("客户端%s:%ld断开了连接\n", inet_ntoa(ovpData->sourceAddr.sin_addr),ovpData->sourceAddr.sin_port);
				m_lock.Lock();
				RemoveClientAddr(ovpData->sourceAddr);
				m_lock.UnLock();
			}
			else
			{
				m_serverProc.func(ovpData->sourceAddr, ovpData->Message, this, m_serverProc.Param);
			}
			memset(ovpData, 0, sizeof(OVP_IO_UDATA));
			ovpData->wsaBuf.len = sizeof(ovpData->Message);
			ovpData->wsaBuf.buf = (char*)ovpData->Message;
			ovpData->sourceAddrLen = sizeof(ovpData->sourceAddr);
			WSARecvFrom(m_sockServer, &ovpData->wsaBuf, 1, &ovpData->recvNums,
				&ovpData->flags, (sockaddr*)&ovpData->sourceAddr,
				&ovpData->sourceAddrLen, &ovpData->overlap, NULL);
		}
	}
}

bool Net::CUDPServer::isHave(sockaddr_in sai)
{
	for (auto it : m_clientaddrList)
	{
		if (strcmp(inet_ntoa(sai.sin_addr), inet_ntoa(it.sin_addr))==0&&it.sin_port==sai.sin_port)
		{
			return true;
		}
	}
	return false;
}

bool Net::CUDPServer::RemoveClientAddr(sockaddr_in sai)
{
	for (auto it = m_clientaddrList.begin(); it != m_clientaddrList.end();++it)
	{
		if (strcmp(inet_ntoa(sai.sin_addr), inet_ntoa(it->sin_addr)) == 0 && sai.sin_port == it->sin_port)
		{
			m_clientaddrList.erase(it);
			return true;
		}
	}
	return false;
}

void Net::CUDPServer::SendCloseMsg()
{
	SendMsgAll(CLOSE_MESSAGE, sizeof(CLOSE_MESSAGE));
}