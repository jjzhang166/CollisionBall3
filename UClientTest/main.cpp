#include <iostream>
#include<tcpclient.h>
#include<udpclient.h>
#include<string.h>

using namespace std;


void proc(char* msg,TCPClient* pClient,void* param,int flag)
{
    if(flag==DISCONN_FLAG)
    {
        cout<<"服务断开连接"<<endl;
    }
    cout<<msg<<endl;
}


void proc(char* msg ,UDPClient* pClient,void* param,int flag)
{
    if(flag==DISCONN_FLAG)
    {
        cout<<"服务断开连接"<<endl;
    }
    cout<<msg<<endl;
}

int main()
{
    TCPClient client("120.206.61.117",DEFAULT_PORT,proc,NULL);
    //UDPClient client("183.218.185.57",DEFAULT_PORT,proc,NULL);
    if(client.ConnectServer())
    {
        cout<<"连接服务器失败:"<<client.GetLastError()<<endl;
    }
    else
    {
        cout<<"连接服务器成功"<<endl;
    }
    client.SendMsg((char*)"Hello Server",strlen("Hello Server"));
    getchar();
    return 0;
}

