#include "tcpclient.h"
#include<string.h>

/*
 * OnTClientWork(void *param)
 * TCP协议下的客户端工作线程
 */
void *OnTClientWork(void* param)
{
    TCPClient* pClient=(TCPClient*)param;
    pClient->DoServerMsg();
    return NULL;
}


TCPClient::TCPClient(string serverIp,long serverPort,TClientProc proc,void* param)
{
    m_serverIp=serverIp;
    m_serverPort=serverPort;
    m_proc.func=proc;
    m_proc.Param=param;
    m_exitThread=false;
}

TCPClient::~TCPClient()
{
    DisConnect();
}

void TCPClient::OnRecv(char* msg,int flag)
{
   memcpy(msg,"",strlen(""));
   flag+=1;
}

int TCPClient::ConnectServer()
{
    m_exitThread=false;
    m_serverFd=socket(PF_INET,SOCK_STREAM,0);
    if(m_serverFd<0)
    {
        m_error="socket failed";
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(m_serverPort);
    addr.sin_addr.s_addr=inet_addr(m_serverIp.c_str());
    socklen_t addrlen=sizeof(addr);

    int iRet=connect(m_serverFd,(sockaddr*)&addr,addrlen);
    if(iRet)
    {
        m_error="connect failed";
        return -1;
    }

    iRet=pthread_create(&m_tid,NULL,OnTClientWork,this);
    if(iRet)
    {
        m_error="start workd thread failed";
        return -1;
    }

    return 0;
}

int TCPClient::SendMsg(char* msg,int len)
{
    return write(m_serverFd,msg,len);
}

void TCPClient::DoServerMsg()
{
    char szBuf[MAX_BUFF]={0};
    while(true)
    {
        if(m_exitThread)
        {
            break;
        }
        int iRet=read(m_serverFd,szBuf,MAX_BUFF);
        if(iRet<0)
        {
            m_error="read failed";
            break;
        }
        else if(iRet==0)
        {
            if(m_proc.func!=NULL)
            {
                m_proc.func(szBuf,this,m_proc.Param,DISCONN_FLAG);
            }
            OnRecv(szBuf,DISCONN_FLAG);
            DisConnect();
        }
        else
        {
            if(m_proc.func!=NULL)
            {
                m_proc.func(szBuf,this,m_proc.Param,NORMAL_FLAG);
            }
            OnRecv(szBuf,DISCONN_FLAG);
        }
    }
}

 void TCPClient::DisConnect()
 {
     m_exitThread=true;
     pthread_join(m_tid,NULL);
     close(m_serverFd);
 }

 const string& TCPClient::GetLastError()
 {
     return m_error;
 }
