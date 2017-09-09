#include <iostream>
#include<tcpserver.h>
#include<udpserver.h>
#include<string.h>

using namespace std;

void proc(int fd,char* msg,TCPServer* pServer,void* param,int flag)
{
    cout<<msg<<endl;
    pServer->SendMsgAll((char*)"Hello Client",strlen("Hello Client"));
}

void proc(sockaddr_in& addr,char* msg,UDPServer* pServer,void* param,int flag)
{
    cout<<"客户端:"<<inet_ntoa(addr.sin_addr)<<"["<<ntohs(addr.sin_port)<<"]"<<"发来贺电:"<<msg<<endl;
    pServer->SendAllMsg((char*)"Hello Client",strlen("Hello Client"));
}

int main()
{
    TCPServer Server(proc,NULL,DEFAULT_PORT,POLL_MODE);
    //UDPServer Server(proc);
    if(Server.StartServer())
    {
        cout<<"服务器开启失败"<<Server.GetLastError()<<endl;
    }
    else
    {
        cout<<"服务器开启成功:"<<Server.GetHostIpAddr()<<endl;
    }

    string str;
    while(true)
    {
        cin>>str;
        if(str=="exit")
        {
            Server.CloseServer();
        }
        else if(str=="quit")
        {
            break;
        }
    }
    return 0;
}
