#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include"commen.h"
#include<string>
#include<pthread.h>

class TCPClient;
typedef void(*TClientProc)(char*,TCPClient*,void*,int);

typedef struct tagTClientProc
{
    TClientProc func;
    void* Param;
}TClientPorc_t;

class TCPClient
{
public:
    /*
     * 构造函数初始化一些数据
     * @param serverIp:指定服务器ip
     * @param serverPort:指定服务器端口
     * @param proc:指定用户自定义函数,如果选择继承此类来实现自己的网络客户端类则指定此函数为空即可
     * @param param:用户自定函数的预留参数
     */
    TCPClient(string serverIp,long serverPort,TClientProc proc=NULL,void* param=NULL);
    virtual ~TCPClient();

    /*
     * ConnectServer()
     * 向服务器发起连接
     * @return int:成功返回0,失败返回-1
     */
    int ConnectServer();

    /*
     * OnRecv(char *msg, int flag)
     * 服务器消息回调函数
     * @param msg:消息内容
     * @param flag:消息标记
     */
    virtual void OnRecv(char* msg,int flag);

    /*
     * SendMsg(char *msg, int len)
     * 发送消息到服务器
     * @param msg:消息内容
     * @param len:消息长度
     * @return int:发送成功返回发送的消息长度,否则返回-1
     */
    int SendMsg(char* msg,int len);

    /*
     * DoServerMsg();
     * 处理服务器发来的消息
     */
    void DoServerMsg();

    /*
     * DisConnect();
     * 客户端主动断开连接
     */
    void DisConnect();

    /*
     * GetLastError()
     * 获取上一次错误描述
     * @return string:错误描述
     */
    const string& GetLastError();
private:
    pthread_t m_tid;
    TClientPorc_t m_proc;   //保存回调函数的结构体
    int m_serverFd;   //服务器文件描述
    string m_serverIp;  //服务器ip
    long m_serverPort;  //服务器端口
    string m_error;     //保存上一次的错误描述
    bool m_exitThread;  //标记是否退出工作线程
};

#endif // TCPCLIENT_H
