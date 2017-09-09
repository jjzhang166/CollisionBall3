#ifndef COMMEN
#define COMMEN
#include<iostream>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

using namespace std;

#define DEFAULT_PORT 6036
#define MAX_LISTEN 100
#define MAX_BUFF 1024
#define MAX_SELECTNUM 256
#define MAX_POLLNUM 10000

#define DISCONN_FLAG 10001
#define NORMAL_FLAG 1002

#define ST_EPOLLNUMS 10  //epoll同时最大接受数

#define CONN_OVER "connected over"

#define UDP_CONN_MSG "<connected to server>"
#define UDP_CLOSE_MSG "<closed to server>"

enum emServerMode
{
    SELECT_MODE,
    POLL_MODE,
    EPOLL_MODE,
};

#endif // COMMEN

