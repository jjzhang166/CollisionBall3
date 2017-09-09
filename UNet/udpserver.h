#ifndef UDPSERVER_H
#define UDPSERVER_H
#include"commen.h"
#include<sys/epoll.h>
#include<list>
#include<vector>
#include<pthread.h>
#include<string>

typedef list<sockaddr_in>::iterator listIt;

class UDPServer;
typedef void(*UServerProc)(sockaddr_in&,char*,UDPServer*,void*,int);

typedef struct tagUServerProc
{
    UServerProc func;
    void* Param;
}UServerProc_t;

class UDPServer
{
public:
    /*
     * 构造函数,初始化一些数据
     * @param proc:用户自定义回调函数
     * @param param:用户预留参数
     * @param port:服务器端口
     */
    UDPServer(UServerProc proc=NULL,void* param=NULL,long port=DEFAULT_PORT);
    virtual ~UDPServer();

    /*
     * StartServer()
     * 开启服务器
     * @return int:开启成功返回0,开启失败返回-1
     */
    int StartServer();

    /*
     * DoClientMsg
     * 处理客户端发来的消息
     */
    void DoClientMsg();

    /*
     * SendMsg(sockaddr_in addr, msg);
     * 发送消息到指定客户端
     * @param addr:指定客户端地址
     * @param msg:发送的具体消息
     * @param len:消息长度
     * @return int:成功返回发送的消息长度,失败返回-1
     */
    int SendMsg(sockaddr_in addr,char* msg,int len);

    /*
     * SendAllMsg(char *msg)
     * 发送消息到所有已经保存的客户端
     * @param msg:发送的具体消息
     * @param len:消息长度
     * @return int:成功返回发送的消息长度,失败返回-1
     */
    int SendAllMsg(char* msg,int len);

    /*
     * OnRecv(sockaddr_in addr, char *msg, int flag);
     * 接收客户端消息回调函数
     * @param addr:客户端地址
     * @param msg:消息内容
     * @param flag:消息标记
     */
    virtual void OnRecv(sockaddr_in addr,char* msg,int flag);


    /*
     * GetHostAddr()
     * 获取服务器主机地址
     * @return string:服务器主机ip
     */
    string GetHostIpAddr();

    /*
     * GetLastError()
     * 获取上一次错误描述
     * @return string:错误描述
     */
    const string& GetLastError();

    /*
     * CloseServer()
     * 主动关闭服务器
     */
    void CloseSever();
private:
    /*
     * RemoveClientAddr(sockaddr_in addr);
     * 删除客户端地址
     * @param addr:客户端地址
     */
    void RemoveClientAddr(sockaddr_in addr);

    list<sockaddr_in> m_clientAddrs;  //保存所有连接过的客户端
    long m_port;  //服务器端口
    int m_serverfd;  //服务端文件描述
    int m_epollid;  //epoll模型下的管理id
    string m_error;  //上一次错误描述
    pthread_t m_tid;  //线程id
    UServerProc_t m_proc;  //保存服务端回调函数
    bool m_exitThread;   //标记工作线程是否结束
};

#endif // UDPSERVER_H
