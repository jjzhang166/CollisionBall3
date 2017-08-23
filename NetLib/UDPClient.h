#pragma once
#include<WinSock2.h>
#include"public.h"
#include<string>
#include<thread>

namespace Net
{
	class CUDPClient;
	typedef void(*UClientFunc)(char* buff,CUDPClient* pClient,LPVOID Param);
	typedef struct UClientSt
	{
		UClientFunc func;
		LPVOID Param;
	};

	class CUDPClient
	{
	public:
		CUDPClient();
		explicit CUDPClient(UClientFunc proc, LPVOID Param=NULL);
		CUDPClient(const CUDPClient& src) = delete;
		CUDPClient& operator=(const CUDPClient& src) = delete;
		virtual ~CUDPClient();

		/*
		*GetLastError();
		*获取上一次错误描述
		*@return string：错误描述
		*/
		const std::string& GetLastError();

		/*
		*BindServer(const std::string& serverIp,unsigned long port=PORT);
		*连接服务器
		*@Param serverIp：服务器ip
		*@Param PORT：服务器端口
		*/
		bool ConnectServer(const std::string& serverIp,unsigned long port=PORT);

		/*
		*SendMsg(char* buff, unsigned int len);
		*发送消息给服务端
		*@Param buff：消息内容
		*@Param len：消息长度
		*/
		bool SendMsg(char* buff, unsigned int len);

		/*
		*CloseClient();
		*关闭客户端并销毁资源
		*/
		void CloseClient();

		/*
		*OnRecv(char* buff);
		*收到服务器消息的回调函数
		*@Param buff：消息内容
		*/
		virtual void OnRecv(char* buff);
	private:
		/*
		*DoServerMsg();
		*处理服务端发来的消息
		*/
		void DoRecvMsg();

		/*
		*SendCloseMsg();
		*发送客户端下线消息到服务器
		*/
		void SendCloseMsg();

		/*
		*SendConnectMsg();
		*发送连接消息到服务器
		*/
		bool SendConnectMsg();

		sockaddr_in m_serverAddr;
		SOCKET m_skClient;
		UClientSt m_cientProc;
		std::string m_error;
		std::thread* m_pRecvThread;
		bool m_isClose;
	};
}