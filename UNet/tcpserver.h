#ifndef TCPSERVER_H
#define TCPSERVER_H
#include"commen.h"
#include<map>
#include<signal.h>
#include<sys/select.h>
#include<poll.h>
#include<sys/epoll.h>
#include<pthread.h>
#include<vector>

typedef map<int,sockaddr_in>::iterator mapIt;
typedef pollfd pollfd_s;

class TCPServer;
typedef void(*TServerProc)(int,char*,TCPServer*,void*,int);

typedef struct tagTServerProc
{
    TServerProc func;
    void* Param;
}TServerProc_t;

class TCPServer
{
public:
    /*
     * 构造函数用于初始化一些参数
     * @param proc:用户自定义回调函数
     * @param Param:用户预留参数
     * @param port:服务器端口
     * @param mode:制定所用到的服务器模型
     * @param listennum:指定服务器监听队列最大容量
     */
    TCPServer(TServerProc proc=NULL,void* Param=NULL,long port=DEFAULT_PORT,emServerMode mode=SELECT_MODE,int ListenNum=10);

    virtual ~TCPServer();

    /*
     * OnRecv(int clientfd)
     * 接收客户端消息的纯虚回调函数
     * @param clientfd:发来消息的客户端文件描述
     * @param msg:消息内容(可以是任意值)
     * @param flag:消息标记,当flag值为DISCONN_FLAG表示客户端断开连接,当
     * flag值为NORMAL_FLAG时表示客户端发送过来的为正常消息
     */
    virtual void OnRecv(int clientfd,char* msg,int flag);

    /*
     * StartServer()
     * 开启服务器
     * @return int:开启成功返回0,失败返回-1
     */
    int StartServer();

    /*
     * GetLastError()
     * 获取上一次发生的错误
     * @return string:错误描述
     */
    const string& GetLastError();

    /*
     * DoSelectMsg();
     * 处理选择模型下的事件
     */
    void DoSelectMsg();

    /*
     * DoPollMsg();
     * 处理Poll模型下的事件
     */
    void DoPollMsg();

    /*
     * DoEpollMsg();
     * 处理Epoll模型下的事件
     */
    void DoEpollMsg();

    /*
     * GetServerMode();
     * 获取服务器模型
     */
    emServerMode GetServerMode();

    /*
     * m_maxClient
     * 最大客户短连接数的getter和setter方法
     * 作者select模型下设置的最大上限为512,默认为100
     * POLL模型下设置的最大上限为2048,默认为512
     * EPOLL模型下没有最大上限,默认为1024
     */
    void SetMaxConn(const int& nums);
    const int& GetMaxConn();

    /*
     * GetClientAddr(int fd)
     * 根据客户端文件描述获得客户端ip地址和端口
     * @param fd:客户端文件描述
     * @return sockaddr_in:存在则返回指定客户端的sockaddr_in结构体,不存在返回空结构体
     */
    sockaddr_in GetClientAddr(int fd);

    /*
     * SendMsg(int fd, char *szBuf)
     * 向指定客户端发送数据
     * @param fd:目的客户端文件描述
     * @param szBuf:发送的消息具体内容
     * @param len:消息长度
     * @return int:成功返回发送的字节数,失败返回-1
     */
    int SendMsg(int fd,char* msg,int len);

    /*
     * SendMsgAll(int fd, char *szBuf)
     * 向所有客户端发送数据
     * @param szBuf:发送的消息具体内容
     * @param len:消息长度
     * @return int:成功返回发送的字节数,失败返回-1
     */
    int SendMsgAll(char* msg,int len);

    /*
     * GetHostIpAddr()
     * 获取服务器主机地址
     * @return string:主机ip
     */
    string GetHostIpAddr();

    /*
     * CloseServer();
     * 主动关闭服务器
     */
    void CloseServer();
private:
    /*
     * InitSock()
     * 初始化服务端文件描述
     * @return int:初始化成功返回0,失败返回-1
     */
    int InitFd();

    /*
     * InitSelectMode()
     * 初始化选择模型服务器
     * @return int:初始化成功返回0,初始化失败返回-1
     */
    int InitSelectMode();

    /*
     * InitPollMode()
     * 初始化Poll模型服务器
     * @return int:初始化成功返回0,初始化失败返回-1
     */
    int InitPollMode();

    /*
     * InitEpollMode()
     * 初始化epoll模型服务器
     * @return int:初始化成功返回0,初始化失败返回-1
     */
    int InitEpollMode();

    int m_serverfd;  //服务器文件描述
    std::map<int,sockaddr_in> m_clientMap; //客户端映射集合
    pthread_t m_tid; //线程id
    long m_port; //服务器端口
    emServerMode m_mode;  //服务器模型
    string m_error;  //错误描述串
    int m_listenNum;  //同时监听数
    fd_set m_fdset;  //文件描述集合
    pollfd_s* m_nfds;  //poll文件描述数组
    int m_maxClients;  //最大客户端连接数
    int m_epollid;      //epoll模型下的管理id
    TServerProc_t m_proc;  //保存用户自定义回调函数
    epoll_event m_epvs[ST_EPOLLNUMS]; //
    bool m_exitThread;  //标记是否退出工作线程
};

#endif // TCPSERVER_H
