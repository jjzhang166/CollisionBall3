#include "stdafx.h"
#include "TCPServer.h"
#include<thread>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace Net;

CTCPServer::CTCPServer()
{
	m_ThredList.clear();
	m_clientList.clear();
	m_listData.clear();
}

CTCPServer::~CTCPServer()
{
	CloseServer();
}

bool Net::CTCPServer::StartServer(ServerFunc ServerProc, LPVOID Param, unsigned long port, SERVER_MODE mode)
{
	m_isClose = false;
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		m_Error = "初始化网络失败!";
		return FALSE;
	}
	m_skServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_skServer == INVALID_SOCKET)
	{
		m_Error = "创建服务端套接字失败!";
		return false;
	}

	SOCKADDR_IN socketaddr;
	memset(&socketaddr, 0, sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_addr.S_un.S_addr= INADDR_ANY;
	socketaddr.sin_port = htons(port);
	if (::bind(m_skServer, (SOCKADDR*)&socketaddr, sizeof(socketaddr)) == SOCKET_ERROR)
	{
		m_Error = "绑定套接字失败!";
		return false;
	}
	if (listen(m_skServer, SOMAXCONN) == SOCKET_ERROR)
	{
		m_Error = "监听失败!";
		return false;
	}
	m_Mode = mode;
	if (StartWorkThread() == false)
	{
		m_Error = "开启工线程失败!";
		return false;
	}
	m_serverProc.func = ServerProc;
	m_serverProc.Param = Param;
	m_ThredList.emplace_back(new thread{ &CTCPServer::acceptClientProc,this });
	return true;
}

const std::string & Net::CTCPServer::GetLastError()
{
	return m_Error;
}

bool Net::CTCPServer::SendMsg(SOCKET dest, const char * buff,unsigned int len)
{
	if (send(dest, buff,len,0) == SOCKET_ERROR)
	{
		m_Error = "向客户端" + dest;
		m_Error += "发送数据失败!";
		return false;
	}
	return true;
}

bool Net::CTCPServer::SendMsgAll(const char * buff,unsigned int len)
{
	m_lock.Lock();
	for (auto it : m_clientList)
	{
		if (send(it, buff, len, 0) == SOCKET_ERROR)
		{
			m_Error = "向客户端" + it;
			m_Error += "发送数据失败!";
			m_lock.UnLock();
			return false;
		}
	}
	m_lock.UnLock();
	return true;
}

list<string> CTCPServer::GetHostIPs()
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

const SERVER_MODE & Net::CTCPServer::GetMode()
{
	return m_Mode;
}

void Net::CTCPServer::CloseServer()
{
	WSACleanup();
	closesocket(m_skServer);
	CloseHandle(m_hCompletionPort);
	m_isClose = true;
	for (auto it : m_listData)
	{
		delete it;
		it = nullptr;
	}
	m_listData.clear();
	m_clientList.clear();
	for (auto it : m_ThredList)
	{
		it->join();
		delete it;
		it = nullptr;
	}
	m_ThredList.clear();
}

void Net::CTCPServer::OnRecv(SOCKET sock, const char * buff)
{
}

void Net::CTCPServer::acceptClientProc()
{
	while (true)
	{
		if (m_isClose == true)
		{
			break;
		}
		sockaddr_in sockclientAddr;
		memset(&sockclientAddr, 0, sizeof(sockclientAddr));
		int len = sizeof(sockclientAddr);
		SOCKET clientSock = accept(m_skServer, (SOCKADDR*)&sockclientAddr, &len);
		if (clientSock != INVALID_SOCKET)
		{
			printf("客户端%ld连接了\n", clientSock);
			m_lock.Lock();
			m_clientList.push_back(clientSock);
			m_lock.UnLock();
			if (m_serverProc.func != NULL)
			{
				m_serverProc.func(clientSock, CONNECT_MESSAGE, this, m_serverProc.Param);
			}
			else
			{
				OnRecv(clientSock, CONNECT_MESSAGE);
			}
			if (m_Mode == MODE_IOCP)
			{
				CreateIoCompletionPort((HANDLE)clientSock, m_hCompletionPort, (ULONG_PTR)clientSock, 0);
				OVP_IO_DATA* pOvpIoData = new OVP_IO_DATA;
				memset(pOvpIoData, NULL, sizeof(OVP_IO_DATA));
				pOvpIoData->wsaBuf.len = sizeof(pOvpIoData->Message);
				pOvpIoData->wsaBuf.buf = (char*)pOvpIoData->Message;
				WSARecv(clientSock, &pOvpIoData->wsaBuf, 1,
					&pOvpIoData->RecvNums, &pOvpIoData->flags,
					&pOvpIoData->overlapped, NULL);
				m_lock.Lock();
				m_listData.push_back(pOvpIoData);
				m_lock.UnLock();
			}
		}
	}
}

bool Net::CTCPServer::StartWorkThread()
{
	if (m_Mode == MODE_SELECT)
	{
		m_ThredList.emplace_back(new thread{ &CTCPServer::DoModeSelectMsg,this });
	}
	else
	{
		m_hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		for (int i = 0; i < systemInfo.dwNumberOfProcessors * 2; ++i)
		{
			m_ThredList.emplace_back(new thread{ &CTCPServer::DoIOCPMsg,this });
		}
	}
	return true;
}

void Net::CTCPServer::DoModeSelectMsg()
{
	while (true)
	{
		if (m_isClose == true)
		{
			break;
		}
		fd_set fdRead = { 0 };
		m_lock.Lock();
		for (auto it : m_clientList)
		{
			FD_SET(it, &fdRead);
		}
		m_lock.UnLock();
		timeval tv = { 0 ,100 };
		int iRet = select(0, &fdRead, NULL, NULL, &tv);
		if (iRet !=SOCKET_ERROR)
		{
			for (int i = 0; i <fdRead.fd_count; ++i)
			{
				if (FD_ISSET(fdRead.fd_array[i], &fdRead))
				{
					char buff[BUFF_SIZE] = { 0 };
					int iRet = recv(fdRead.fd_array[i], buff, sizeof(buff), 0);
					if (iRet == 0 || iRet == SOCKET_ERROR)
					{
						printf("客户端 %ld 断开了链接\n", fdRead.fd_array[i]);
						m_lock.Lock();
						m_clientList.remove(fdRead.fd_array[i]);
						m_lock.UnLock();
						if (m_serverProc.func != NULL)
						{
							m_serverProc.func(fdRead.fd_array[i], CLOSE_MESSAGE, this, m_serverProc.Param);
						}
						else
						{
							OnRecv(fdRead.fd_array[i], CLOSE_MESSAGE);
						}
						closesocket(fdRead.fd_array[i]);
					}
					else
					{
						if (m_serverProc.func != NULL)
						{
							m_serverProc.func(fdRead.fd_array[i], buff, this, m_serverProc.Param);
						}
						else
						{
							OnRecv(fdRead.fd_array[i], buff);
						}
					}
				}
			}
		}
	}
}

void Net::CTCPServer::DoIOCPMsg()
{
	OVP_IO_DATA* pOvpData;
	DWORD Transferred;
	DWORD socketClient;
	while (true)
	{
		if (m_isClose == true)
		{
			break;
		}
		BOOL bRet=GetQueuedCompletionStatus(m_hCompletionPort, &Transferred, (PULONG_PTR)&socketClient,
			(LPOVERLAPPED*)&pOvpData, INFINITE);
		DWORD dwError = ::GetLastError();
		if (Transferred == 0 || bRet == FALSE || dwError==SOCKET_ERROR)
		{
			if (Transferred == 0)
			{
				printf_s("客户端%ld断开了连接\n", socketClient);
				m_lock.Lock();
				m_clientList.remove(socketClient);
				m_listData.remove(pOvpData);
				m_lock.UnLock();
				delete pOvpData;
				pOvpData = nullptr;
				if (m_serverProc.func != NULL)
				{
					m_serverProc.func(socketClient, CLOSE_MESSAGE, this, m_serverProc.Param);
				}
				else
				{
					OnRecv(socketClient, CLOSE_MESSAGE);
				}
				closesocket(socketClient);
			}
		}
		else
		{
			if (m_serverProc.func != NULL)
			{
				m_serverProc.func(socketClient, pOvpData->Message,
					this, m_serverProc.Param);
			}
			else
			{
				OnRecv(socketClient, pOvpData->Message);
			}
			memset(pOvpData, NULL, sizeof(OVP_IO_DATA));
			pOvpData->wsaBuf.len = sizeof(pOvpData->Message);
			pOvpData->wsaBuf.buf = (char*)pOvpData->Message;
			WSARecv(socketClient, &pOvpData->wsaBuf, 1, &pOvpData->RecvNums,
				&pOvpData->flags, &pOvpData->overlapped, NULL);
		}
	}
}