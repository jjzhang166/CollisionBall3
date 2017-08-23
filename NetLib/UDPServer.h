#pragma once
#include<WinSock2.h>
#include<thread>
#include<string>
#include<list>
#include"public.h"
#include"Lock.h"

namespace Net
{
	class CUDPServer;
	typedef void(*USeverFunc)(sockaddr_in sai, char* buff, CUDPServer* pSever, LPVOID Param);
	struct UServerST
	{
		USeverFunc func;
		LPVOID Param;
	};

	//服务器模型枚举
	enum USERVER_MODE
	{
		UMODE_ORDINARY,
		UMODE_IOCP,
	};

	class CUDPServer
	{
	public:
		CUDPServer();
		CUDPServer(const CUDPServer& src) = delete;
		CUDPServer& operator=(const CUDPServer& src) = delete;
		virtual ~CUDPServer();

		/*
		*StartServer();
		*开启服务器
		*@Param proc：服务器回调函数
		*@Param param：用户自定义，回调参数
		*@Param mode：指定服务器模型
		*@Param port：服务器端口
		*@return bool：true开启成功，false开启失败
		*/
		bool StartServer(USeverFunc proc,LPVOID Param=NULL,USERVER_MODE mode = UMODE_ORDINARY, unsigned long port = PORT);

		/*
		*GetLastError();
		*获取上一次的错误描述
		*@return string：错误详细描述
		*/
		const std::string& GetLastError();

		/*
		*GetMode();
		*获取服务器模型
		*@return USERVER_MODE：服务器模型标识
		*/
		const USERVER_MODE& GetMode();

		/*
		*GetHostIP()
		*获取主机的所有Ip
		*/
		std::list<std::string> GetHostIPs();

		/*
		*SendMsg(sockaddr_in dest, char* buff, unsigned int len);
		*发送消息给指定客户端
		*@Param dest：目标客户端地址
		*@Param buff：消息内容
		*@Param len：消息长度
		*/
		bool SendMsg(sockaddr_in dest, char* buff, unsigned int len);

		/*
		*SendMsgAll(char*buff, unsigned int len);
		*发送消息给所有客户端
		*@Param buff：消息内容
		*@len：消息长度
		*/
		bool SendMsgAll(char*buff, unsigned int len);

		/*
		*CloseServer();
		*关闭服务器并销毁所有资源
		*/
		void CloseServer();

		/*
		*OnRecv();
		*收到客户端消息的回调函数
		*@Param buff：消息内容
		*/
		virtual void OnRecv(sockaddr_in sai, char* buff);
	private:
		/*
		*InitOridinaryServer(unsigned long port);
		*初始化普通模型服务器
		*@Param port：服务器端口
		*@return bool：true初始化成功，false初始化失败
		*/
		bool InitOridinaryServer(unsigned long port);

		/*
		*InitIOCPServer(unsigned long port);
		*初始化完成端口模型服务器
		*@Param port：服务器端口
		*@return bool：true初始化成功，false初始化失败
		*/
		bool InitIOCPServer(unsigned long port);

		/*
		*DoOridinaryMsg();
		*处理普通模式下的客户端消息
		*/
		void DoOridinaryMsg();

		/*
		*DoIOCPMsg();
		*处理完成端口模式下的客户端消息
		*/
		void DoIOCPMsg();

		/*
		*isHave(sockaddr_in sai);
		*某一客户端是否存在
		*@return bool：true存在，false不存在
		*/
		bool isHave(sockaddr_in sai);

		/*
		*RemoveClientAddr(sockaddr_in sai);
		*移除指定客户端
		*@Param sai：指定的客户端地址
		@return bool：true成功，false失败
		*/
		bool RemoveClientAddr(sockaddr_in sai);

		/*
		*SendCloseMsg();
		*发送服务器关闭消息
		*/
		void SendCloseMsg();

		SOCKET m_sockServer;

		std::string m_error;

		USERVER_MODE m_mode;

		std::list<std::thread> m_threadList;

		std::list<sockaddr_in> m_clientaddrList;

		std::list<OVP_IO_UDATA*> m_dataList;

		UServerST m_serverProc;

		HANDLE m_hCompletionPort;

		CLock m_lock;

		bool m_isClose;
	};
}