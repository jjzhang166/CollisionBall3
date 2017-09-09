#include "udpclient.h"
#include<string.h>

/*
 * OnUClientWork(void *param)
 * UDPCLient下的工作线程
 */
void* OnUClientWork(void* param)
{
    UDPClient* pClient=(UDPClient*)param;
    pClient->DoServerMsg();
    return NULL;
}


UDPClient::UDPClient(string serverIp,long serverPort,UClientProc proc,void* param)
{
    m_serverAddr.sin_family=AF_INET;
    m_serverAddr.sin_port=htons(serverPort);
    m_serverAddr.sin_addr.s_addr=inet_addr(serverIp.c_str());
    m_proc.func=proc;
    m_proc.param=param;
    m_exitThread=false;
}

UDPClient::~UDPClient()
{
    DisConnect();
}

void UDPClient::OnRecv(char* msg,int flag)
{
    memcpy(msg,"",strlen(""));
    flag+=1;
}

int UDPClient::ConnectServer()
{
    m_exitThread=false;
    m_clientfd=socket(PF_INET,SOCK_DGRAM,0);
    if(m_clientfd<0)
    {
        m_error="socket failed";
        return -1;
    }

    int iRet=sendto(m_clientfd,UDP_CONN_MSG,strlen(UDP_CONN_MSG),0,(sockaddr*)&m_serverAddr,sizeof(m_serverAddr));
    if(iRet<0)
    {
        m_error="send conn msg failed";
        return -1;
    }

    iRet=pthread_create(&m_tid,NULL,OnUClientWork,this);
    if(iRet)
    {
        m_error="start work thread failed";
        return -1;
    }

    return 0;
}

int UDPClient::SendMsg(char* msg,int len)
{
    return sendto(m_clientfd,msg,len,0,(sockaddr*)&m_serverAddr,sizeof(m_serverAddr));
}

const string& UDPClient::GetLastError()
{
    return m_error;
}

void UDPClient::DoServerMsg()
{
    int iRet;
    char szBuf[MAX_BUFF]={0};
    sockaddr_in addr;
    socklen_t addrlen=sizeof(addr);
    while(true)
    {
        if(m_exitThread)
        {
            break;
        }
        memset(szBuf,0,MAX_BUFF);
        iRet=recvfrom(m_clientfd,szBuf,MAX_BUFF,0,(sockaddr*)&addr,&addrlen);
        if(iRet<0)
        {
            m_error="recvfrom failed";
            break;
        }
        if(!strcmp(szBuf,UDP_CLOSE_MSG))
        {
            if(m_proc.func!=NULL)
            {
                m_proc.func((char*)"",this,m_proc.param,DISCONN_FLAG);
            }
            OnRecv((char*)"",DISCONN_FLAG);
            DisConnect();
        }
        else
        {
            if(m_proc.func!=NULL)
            {
                m_proc.func(szBuf,this,m_proc.param,NORMAL_FLAG);
            }
            OnRecv(szBuf,NORMAL_FLAG);
        }
    }
}

void UDPClient::DisConnect()
{
    m_exitThread=true;
    sendto(m_clientfd,UDP_CLOSE_MSG,strlen(UDP_CLOSE_MSG),0,(sockaddr*)&m_serverAddr,sizeof(m_serverAddr));
    pthread_join(m_tid,NULL);
    close(m_clientfd);
}
