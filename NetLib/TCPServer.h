#pragma once
#include<WinSock2.h>
#include<thread>
#include<string>
#include<list>
#include"public.h"
#include"Lock.h"
#include<memory>

namespace Net
{
	//服务器模型枚举
	enum SERVER_MODE
	{
		MODE_SELECT,
		MODE_IOCP,
	};

	class CTCPServer;
	typedef void(*ServerFunc)(SOCKET sock, const char* buff,CTCPServer* pServer,LPVOID Param);
	//保存服务器回调函数和用户自定义参数结构体
	typedef struct  ServerST
	{
		ServerFunc func;
		LPVOID Param;
	};

	class CTCPServer
	{
	public:
	 	CTCPServer();

		//删除拷内构造函数
		CTCPServer(const CTCPServer& src) = delete;

		//删除拷内运算符
		CTCPServer& operator=(const CTCPServer& src) = delete;
		
		virtual ~CTCPServer();

		/*
		*StartServer(ServerFunc ServerProc, LPVOID Param = NULL, unsigned long port = PORT, SERVER_MODE mode = MODE_SELECT);
		*开启服务器
		*@Param ServerProc:指定服务器逻辑处理回调函数
		*@Param param：用户自定义参数
		*@Param port:服务器端口
		*@Param mode：指定服务器模型
		*@return bool:true开启服务器成功，false开启失败
		*/
		bool StartServer(ServerFunc ServerProc, LPVOID Param = NULL, unsigned long port = PORT, SERVER_MODE mode = MODE_SELECT);

		/*
		*GetLastError();
		*获取上一次错误
		*@return string：错误描述
		*/
		const std::string& GetLastError();

		/*
		*SendMsg(SOCKET dest, const char* buff, unsigned int len);
		*发送消息给指定的客户端
		*@Param dest：消息目的端
		*@Param buff：消息内容
		*@Param len：消息长度
		*@return bool：true发送成功，false发送失败
		*/
		bool SendMsg(SOCKET dest, const char* buff, unsigned int len);

		/*
		*SendMsgAll(const char* buff,unsigned int len);
		*发送消息给所有已连接的客户端
		*@Param buff：消息内容
		*@Param len：消息长度
		*@return bool：true发送成功，false发送失败
		*/
		bool SendMsgAll(const char* buff,unsigned int len);

		/*
		*GetHostIP()
		*获取主机的所有Ip
		*/
		std::list<std::string> GetHostIPs();

		/*
		*GetMode();
		*获取服务器模型
		*/
		const SERVER_MODE& GetMode();

		/*
		*CloseServer();
		*关闭服务器并销毁资源
		*/
		void CloseServer();

		/*
		*OnRecv(SOCKET sock, const char* buff)
		*收到客户端消息的回调函数
		*@Param sock：消息来源sock
		*@Param buff：消息内容
		*@Param len：消息长度
		*/
		virtual void OnRecv(SOCKET sock, const char* buff);
	private:
		/*
		*acceptClientProc();
		*接受客户端连接回调函数
		*/
		void acceptClientProc();

		/*
		*StartWorkThread();
		*开启工作线程
		*@return bool：true开启成功，false开启失败
		*/
		bool StartWorkThread();

		/*
		*DoModeSelectMsg();
		*处理选择模型下的客户端消息
		*/
		void DoModeSelectMsg();

		/*
		*DoIOCPMsg();
		*处理完成端口下的客户端消息
		*/
		void DoIOCPMsg();

		//服务段套接字
		SOCKET m_skServer;

		//纪录上一次错误代码
		std::string m_Error;
		
		//接受客户端连接线程
		std::list<std::thread*> m_ThredList;

		//指定服务器模型
		SERVER_MODE m_Mode;

		//保存客户端socket
		std::list<SOCKET> m_clientList;

		ServerST m_serverProc;

		CLock m_lock;

		HANDLE m_hCompletionPort;

		std::list<OVP_IO_DATA*> m_listData;

		bool m_isClose;
	};
}