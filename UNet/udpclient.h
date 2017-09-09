#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include"commen.h"
#include<string>
#include<pthread.h>

class UDPClient;
typedef void(*UClientProc)(char*,UDPClient*,void*,int);

typedef struct tagUClientProc
{
    UClientProc func;
    void* param;
}UClientProc_t;

/*
 * UDPClient
 * UDP协议下的客户端,可通过直接使用自定义回调函数来使用此类,
 * 或者通过继承此类重写OnRecv来拓展为自己的UDP客户端
 */
class UDPClient
{
public:
    /*
     * 构造函数,初始化一些数据
     * @param serverIp:服务器ip
     * @param serverPort:服务器端口
     * @param proc:用户自定义回调函数,通过继承重写OnRecv,则将其指定为NULL即可
     * @param param:用户自定回调函数的预留参数
     */
    UDPClient(string serverIp,long serverPort,UClientProc proc=NULL,void* param=NULL);
    virtual ~UDPClient();

    /*
     * OnRecv(char *msg, int flag);
     * 接收服务器消息回调函数
     * @param msg:消息内容
     * @param flag:消息标记,flag为DSICONN_FLAG表示服务器断开连接,
     * flag为NORMAPO_FLAG表示为正常消息
     */
    virtual void OnRecv(char* msg,int flag);

    /*
     * ConnectServer()
     * 链接服务器
     * @return int:成功返回0;失败返回-1
     */
    int ConnectServer();

    /*
     * SendMsg(char *msg, int len)
     * 向服务器发送消息
     * @param msg:消息内容
     * @param len:消息长度
     */
    int SendMsg(char* msg,int len);

    /*
     * GetLastError()
     * 获取上一次的错误描述
     * @return string:错误描述
     */
    const string& GetLastError();

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
private:
    int m_clientfd;  //文件描述
    pthread_t m_tid; //线程id
    UClientProc_t m_proc; //保存回调函数的结构体
    sockaddr_in m_serverAddr; //保存服务器地址
    string m_error;  //上一次错误码
    bool m_exitThread;  //标记是否退出工作线程
};

#endif // UDPCLIENT_H
