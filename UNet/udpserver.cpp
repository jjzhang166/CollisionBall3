#include "udpserver.h"
#include<string.h>

/*
 * *OnWork(void *param)
 * 服务器工作线程
 * @Param param:UDPServer对象指针
 */
void *OnUdpWork(void* param)
{
    UDPServer* pSrever=(UDPServer*)param;
    pSrever->DoClientMsg();
    return NULL;
}

UDPServer::UDPServer(UServerProc proc,void* param,long port):
    m_port(port)
{
    m_proc.func=proc;
    m_proc.Param=param;
    m_exitThread=false;
}

UDPServer::~UDPServer()
{
    CloseSever();
}

void UDPServer::OnRecv(sockaddr_in addr,char* msg,int flag)
{
    addr.sin_family+=addr.sin_family;
    memcpy(msg,"",strlen(""));
    flag+=1;
}

int UDPServer::StartServer()
{
    m_exitThread=false;
    m_serverfd=socket(PF_INET,SOCK_DGRAM,0);
    if(m_serverfd<0)
    {
        m_error="socket failed";
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port=htons(m_port);
    socklen_t addrlen=sizeof(addr);

    int iRet=bind(m_serverfd,(sockaddr*)&addr,addrlen);
    if(iRet)
    {
        m_error="bind failed";
        return -1;
    }

    m_epollid=epoll_create(1);
    epoll_event epv;
    epv.data.fd=m_serverfd;
    epv.events=EPOLLIN;

    iRet=epoll_ctl(m_epollid,EPOLL_CTL_ADD,m_serverfd,&epv);
    if(iRet<0)
    {
        m_error="epoll_ctl_add serverfd failed";
        return -1;
    }

    iRet=pthread_create(&m_tid,NULL,OnUdpWork,this);
    if(iRet)
    {
        m_error="create work thread failed";
        return -1;
    }

    return 0;
}

void UDPServer::DoClientMsg()
{
    int iRet;
    char szBuf[MAX_BUFF]={0};
    sockaddr_in addr;
    socklen_t addrlen=sizeof(addr);
    epoll_event pEpv[1];

    while(true)
    {
        if(m_exitThread)
        {
            break;
        }
        iRet=epoll_wait(m_epollid,pEpv,1,100);
        if(iRet<0)
        {
            m_error="epoll_wait failed";
            break;
        }
        if(iRet==0)
        {
            continue;
        }
        if(pEpv[0].data.fd==m_serverfd)
        {
            memset(szBuf,0,MAX_BUFF);
            int nums=recvfrom(m_serverfd,szBuf,MAX_BUFF,0,(sockaddr*)&addr,&addrlen);
            if(nums<0)
            {
                m_error="recvfrom failed";
                continue;
            }
            if(!strcmp(szBuf,UDP_CONN_MSG))
            {
                cout<<"client "<<inet_ntoa(addr.sin_addr)<<"["<<ntohs(addr.sin_port)<<"]"<<" connected"<<endl;
                m_clientAddrs.push_back(addr);
            }
            else if(!strcmp(szBuf,UDP_CLOSE_MSG))
            {
                 cout<<"client "<<inet_ntoa(addr.sin_addr)<<"["<<ntohs(addr.sin_port)<<"]"<<" disconnected"<<endl;
                 if(m_proc.func!=NULL)
                 {
                     m_proc.func(addr,(char*)"",this,m_proc.Param,DISCONN_FLAG);
                 }
                 OnRecv(addr,(char*)"",DISCONN_FLAG);
                 RemoveClientAddr(addr);
            }
            else
            {
                if(m_proc.func!=NULL)
                {
                    m_proc.func(addr,szBuf,this,m_proc.Param,NORMAL_FLAG);
                }
                OnRecv(addr,szBuf,NORMAL_FLAG);
            }
        }
    }
}

int UDPServer::SendMsg(sockaddr_in addr,char* msg,int len)
{
    int iRet=sendto(m_serverfd,msg,len,0,(sockaddr*)&addr,sizeof(addr));
    return iRet;
}

int UDPServer::SendAllMsg(char* msg,int len)
{
    int iRet;
    for(listIt it=m_clientAddrs.begin();it!=m_clientAddrs.end();++it)
    {
        iRet=sendto(m_serverfd,msg,len,0,(sockaddr*)&(*it),sizeof(*it));
    }
    return iRet;
}

string UDPServer::GetHostIpAddr()
{
    string strAddr;
    char name[256]={0};
    int iRet=gethostname(name,256);
    if(iRet)
    {
        return strAddr;
    }
    in_addr addr;
    hostent* host=gethostbyname(name);
    char *p = host->h_addr_list[0];
    memcpy(&addr.s_addr, p, host->h_length);
    strAddr.append(inet_ntoa(addr));

    return strAddr;
}


void UDPServer::CloseSever()
{
    SendAllMsg((char*)UDP_CLOSE_MSG,strlen(UDP_CLOSE_MSG));
    m_exitThread=true;
    pthread_join(m_tid,NULL);
    close(m_serverfd);
}

const string& UDPServer::GetLastError()
{
    return m_error;
}

void UDPServer::RemoveClientAddr(sockaddr_in addr)
{
    for(listIt it=m_clientAddrs.begin();it!=m_clientAddrs.end();++it)
    {
        if(ntohs(it->sin_port)==ntohs(addr.sin_port)&&it->sin_addr.s_addr==addr.sin_addr.s_addr)
        {
            m_clientAddrs.erase(it);
            break;
        }
    }
}
