#include "tcpserver.h"
#include<string.h>

/*
 * *OnWork(void *param)
 * 服务器工作线程
 * @Param param:TcpServer对象指针
 */
void *OnWork(void* param)
{
    TCPServer* pServer=static_cast<TCPServer*>(param);
    switch (pServer->GetServerMode())
    {
    case SELECT_MODE:
        pServer->DoSelectMsg();
        break;
    case POLL_MODE:
        pServer->DoPollMsg();
        break;
    case EPOLL_MODE:
        pServer->DoEpollMsg();
        break;
    default:
        break;
    }
    return NULL;
}

TCPServer::TCPServer(TServerProc proc,void* Param,long port,emServerMode mode,int ListenNum):
    m_port(port),m_mode(mode),m_listenNum(ListenNum)
{
    m_proc.func=proc;
    m_proc.Param=Param;
    m_nfds=NULL;
    m_exitThread=false;
}

TCPServer::~TCPServer()
{
    CloseServer();
}

void TCPServer::OnRecv(int clientfd,char* msg,int flag)
{
    clientfd+=1;
    memcpy(msg,"",strlen(""));
    flag+=1;
}

int TCPServer::StartServer()
{
    m_exitThread=false;
    if(InitFd())
    {
        return -1;
    }

    switch (m_mode)
    {
    case SELECT_MODE:
        m_maxClients=100;
        break;
    case POLL_MODE:
        m_maxClients=5000;
        if(InitPollMode())
        {
             return -1;
        }
        break;
    case EPOLL_MODE:
        m_maxClients=5000;
        if(InitEpollMode())
        {
            return -1;
        }
        break;
    default:
        break;
    }

    int iRet=pthread_create(&m_tid,NULL,OnWork,this);
    if(iRet)
    {
        m_error="start work thread failed!";
        return -1;
    }

    return 0;
}

void TCPServer::DoSelectMsg()
{
    int iRet;
    sockaddr_in addr;
    char szBuf[MAX_BUFF]={0};
    socklen_t addrlen=sizeof(addr);
    while(true)
    {
        if(m_exitThread)
        {
            break;
        }
        FD_ZERO(&m_fdset);
        FD_SET(m_serverfd,&m_fdset);
        for(mapIt it=m_clientMap.begin();it!=m_clientMap.end();++it)
        {
            FD_SET(it->first,&m_fdset);
        }
        timeval tv={0,100};
        iRet=select(MAX_SELECTNUM,&m_fdset,NULL,NULL,&tv);
        if(iRet<0)
        {
            m_error="select failed";
            break;
        }
        if(iRet==0)
        {
            continue;
        }
        if(FD_ISSET(m_serverfd,&m_fdset))
        {
            int clientfd=accept(m_serverfd,(sockaddr*)&addr,&addrlen);
            if(clientfd<0)
            {
                m_error="accept fialed";
                break;
            }
            if(m_clientMap.size()+1>=static_cast<unsigned>(m_maxClients))
            {
                int iRet=write(clientfd,CONN_OVER,strlen(CONN_OVER));
                if(iRet<0)
                {
                    m_error="write failed";
                }
                close(clientfd);
                continue;
            }
            m_clientMap.insert(make_pair(clientfd,addr));
            cout<<inet_ntoa(addr.sin_addr)<<"["<<ntohs(addr.sin_port)<<"]"<<" connected"<<endl;
        }
        else
        {
            for(mapIt it=m_clientMap.begin();it!=m_clientMap.end();)
            {
                if(FD_ISSET(it->first,&m_fdset))
                {
                    memset(szBuf,0,MAX_BUFF);
                    iRet=read(it->first,szBuf,MAX_BUFF);
                    if(iRet<0)
                    {
                        m_error="read failed";
                        break;
                    }
                    else if(iRet==0)
                    {
                        if(m_proc.func!=NULL)
                        {
                            m_proc.func(it->first,(char*)"",this,m_proc.Param,DISCONN_FLAG);
                        }
                        OnRecv(it->first,(char*)"",DISCONN_FLAG);
                        cout<<inet_ntoa(it->second.sin_addr)<<"["<<ntohs(it->second.sin_port)<<"]"<<" disconnected"<<endl;
                        mapIt temp=it++;
                        m_clientMap.erase(temp);
                    }
                    else
                    {
                        if(m_proc.func!=NULL)
                        {
                            m_proc.func(it->first,szBuf,this,m_proc.Param,NORMAL_FLAG);
                        }
                        OnRecv(it->first,szBuf,NORMAL_FLAG);
                        ++it;
                    }
                }
                else
                {
                    ++it;
                }
            }
        }

    }
}

void TCPServer::DoPollMsg()
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
        iRet=poll(m_nfds,m_clientMap.size()+1,100);
        if(iRet<0)
        {
            m_error="poll failed";
            break;
        }
        if(iRet==0)
        {
            continue;
        }
        if(m_nfds[0].revents&POLLIN)
        {
            int clientfd=accept(m_serverfd,(sockaddr*)&addr,&addrlen);
            if(clientfd<0)
            {
                m_error="accept failed";
                break;
            }
            if(m_clientMap.size()+1>=static_cast<unsigned>(m_maxClients))
            {
                int iRet=write(clientfd,CONN_OVER,strlen(CONN_OVER));
                if(iRet<0)
                {
                    m_error="write failed";
                }
                close(clientfd);
                continue;
            }
            cout<<inet_ntoa(addr.sin_addr)<<"["<<ntohs(addr.sin_port)<<"]"<<" connected"<<endl;
            m_clientMap.insert(make_pair(clientfd,addr));
            m_nfds[m_clientMap.size()].fd=clientfd;
            m_nfds[m_clientMap.size()].events=POLLIN;
        }
        else
        {
            int count=m_clientMap.size();
            for(int i=1;i<=count;++i)
            {
                if(m_nfds[i].revents&POLLIN)
                {
                    memset(szBuf,0,MAX_BUFF);
                    iRet=read(m_nfds[i].fd,szBuf,MAX_BUFF);
                    if(iRet<0)
                    {
                        m_error="read failed";
                        break;
                    }
                    else if(iRet==0)
                    {
                        mapIt it=m_clientMap.find(m_nfds[i].fd);
                        m_nfds[i]=m_nfds[count];
                        if(m_proc.func!=NULL)
                        {
                            m_proc.func(it->first,(char*)"",this,m_proc.Param,DISCONN_FLAG);
                        }
                        OnRecv(m_nfds[i].fd,(char*)"",DISCONN_FLAG);
                        cout<<inet_ntoa(it->second.sin_addr)<<"["<<ntohs(it->second.sin_port)<<"]"<<" disconnected"<<endl;
                        m_clientMap.erase(it);
                    }
                    else
                    {
                        if(m_proc.func!=NULL)
                        {
                            m_proc.func(m_nfds[i].fd,szBuf,this,m_proc.Param,NORMAL_FLAG);
                        }
                        OnRecv(m_nfds[i].fd,szBuf,NORMAL_FLAG);
                    }
                }
            }
        }
    }
}

void TCPServer::DoEpollMsg()
{
    int nCount;
    char szBuf[MAX_BUFF]={0};
    sockaddr_in addr;
    socklen_t addrlen=sizeof(addr);
    while(true)
    {
        if(m_exitThread)
        {
            break;
        }
        nCount=epoll_wait(m_epollid,m_epvs,ST_EPOLLNUMS,100);
        if(nCount<0)
        {
            m_error="epoll_wait failed";
            break;
        }
        if(nCount==0)
        {
            continue;
        }

        for(int i=0;i<nCount;++i)
        {
            if(m_epvs[i].data.fd==m_serverfd)
            {
                int clientfd=accept(m_serverfd,(sockaddr*)&addr,&addrlen);
                if(clientfd<0)
                {
                    m_error="accept failed";
                    break;
                }
                if(m_clientMap.size()+1>static_cast<unsigned>(m_maxClients))
                {
                    int iRet=write(clientfd,CONN_OVER,strlen(CONN_OVER));
                    if(iRet<0)
                    {
                        m_error="write failed";
                    }
                    break;
                }
                cout<<inet_ntoa(addr.sin_addr)<<"["<<ntohs(addr.sin_port)<<"]"<<" connected"<<endl;
                epoll_event epv;
                epv.data.fd=clientfd;
                epv.events=EPOLLIN;
                epoll_ctl(m_epollid,EPOLL_CTL_ADD,clientfd,&epv);
                m_clientMap.insert(make_pair(clientfd,addr));
            }
            else
            {
                memset(szBuf,0,MAX_BUFF);
                int iRet=read(m_epvs[i].data.fd,szBuf,MAX_BUFF);
                if(iRet<0)
                {
                    m_error="read failed";
                    break;
                }
                else if(iRet==0)
                {
                    mapIt it=m_clientMap.find(m_epvs[i].data.fd);
                    cout<<inet_ntoa(it->second.sin_addr)<<"["<<ntohs(it->second.sin_port)<<"]"<<" disconnected"<<endl;
                    if(m_proc.func!=NULL)
                    {
                        m_proc.func(it->first,(char*)"",this,m_proc.Param,DISCONN_FLAG);
                    }
                    epoll_ctl(m_epollid,EPOLL_CTL_DEL,it->first,NULL);
                    OnRecv(m_epvs[i].data.fd,(char*)"",DISCONN_FLAG);
                    m_clientMap.erase(it);
                }
                else
                {
                    if(m_proc.func!=NULL)
                    {
                        m_proc.func(m_epvs[i].data.fd,szBuf,this,m_proc.Param,NORMAL_FLAG);
                    }
                    OnRecv(m_epvs[i].data.fd,szBuf,NORMAL_FLAG);
                }
            }
        }
    }
}

emServerMode TCPServer::GetServerMode()
{
    return m_mode;
}

void TCPServer::SetMaxConn(const int& nums)
{
    switch (m_mode)
    {
    case SELECT_MODE:
        m_maxClients=nums<=MAX_SELECTNUM?nums:MAX_SELECTNUM;
        break;
    case POLL_MODE:
        m_maxClients=nums<=MAX_POLLNUM?nums:MAX_POLLNUM;
        break;
    case EPOLL_MODE:
        m_maxClients=nums;
        break;
    default:
        break;
    }
}

const int& TCPServer::GetMaxConn()
{
    return m_maxClients;
}

sockaddr_in TCPServer::GetClientAddr(int fd)
{
    mapIt it=m_clientMap.find(fd);
    if(it==m_clientMap.end())
    {
        return sockaddr_in();
    }
    return it->second;
}

int TCPServer::SendMsg(int fd,char* msg,int len)
{
    int iRet=write(fd,msg,len);
    return iRet;
}

int TCPServer::SendMsgAll(char* msg,int len)
{
    int iRet=0;
    for(mapIt it=m_clientMap.begin();it!=m_clientMap.end();++it)
    {
        iRet=write(it->first,msg,len);
    }
    return iRet;
}

string TCPServer::GetHostIpAddr()
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
    char *p=host->h_addr;
    memcpy(&addr.s_addr,p,host->h_length);
    strAddr.append(inet_ntoa(addr));

    return strAddr;
}

void TCPServer::CloseServer()
{
    m_exitThread=true;
    pthread_join(m_tid,NULL);
    close(m_serverfd);
    mapIt it;
    for(it=m_clientMap.begin();it!=m_clientMap.end();++it)
    {
        close(it->first);
    }
    if(m_nfds!=NULL)
    delete[] m_nfds;
}

int TCPServer::InitFd()
{
    m_serverfd=socket(PF_INET,SOCK_STREAM,0);
    if(m_serverfd<0)
    {
        m_error="socket failed!";
        return -1;
    }

    sockaddr_in addr;
    socklen_t addrlen;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(m_port);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addrlen=sizeof(addr);

    int iRet=bind(m_serverfd,(sockaddr*)&addr,addrlen);
    if(iRet)
    {
        m_error="bind socket failed!";
        return -1;
    }

    iRet=listen(m_serverfd,m_listenNum);
    if(iRet)
    {
        m_error="listen socket faild!";
        return -1;
    }

    return 0;
}

int TCPServer::InitPollMode()
{
    m_nfds=new pollfd_s[m_maxClients];
    if(m_nfds==NULL)
    {
        m_error="new pollfd failed";
        return -1;
    }
    m_nfds[0].fd=m_serverfd;
    m_nfds[0].events=POLLIN;
    return 0;
}

int TCPServer::InitEpollMode()
{
    m_epollid=epoll_create(1);
    if(m_epollid<0)
    {
        m_error="epoll_create failed";
        return -1;
    }
    epoll_event epv;
    epv.events=EPOLLIN;
    epv.data.fd=m_serverfd;

    int iRet=epoll_ctl(m_epollid,EPOLL_CTL_ADD,m_serverfd,&epv);
    if(iRet)
    {
        m_error="epoll_ctlP_add serverfd failed";
        return -1;
    }
    return 0;
}

 const string& TCPServer::GetLastError()
 {
     return m_error;
 }
