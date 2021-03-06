# CollisionBall
一个联网的趣味性小游戏，碰碰球，在游戏中通过操纵自己的小球吃掉随机产生的食物，不断壮大自己，或者撞击其它玩家，通过自己的体力和大小之间的关系和他人的体力与大小之间的关系决定谁是胜利者，还有30s一波的随机黑洞，刺激！！！项目附带自己编写的一个网络库。代码在NetLib文件夹.


### 游戏玩法介绍
玩家通过上下左右建控制自己的角色移动，按住ctrl键角色将会加速，加速时会消耗体力值，体力值为零时将不能加速，玩家通过吃掉每隔一段时间随机生成的食物来壮大自己并补充体力值，玩家间之间通过碰撞来消灭敌人，不要以为体积大的一定能消灭体积小的，没这回事，若是玩家的体力值过低，体积比自己小的敌人也能打败自己，若是体力值和体积之间的权值相等则互不能伤害。游戏中玩家可以在右上方的小地图来查看自己当前的真实位置，游戏中也有每30s一波的黑洞风暴，玩家若是靠近黑洞则会被黑洞拉扯，拉扯到黑洞内侧时玩家的体积将会飞速降低，所以千万别被黑洞拉扯到内部，否则千年道行一朝丧。
### 其它说明
游戏中使用的UI库为本人前段时间编写的UIEngne库，该库简单使用如有兴趣可转到项目地址查看：http://git.oschina.net/lsylovews/uiengine

### 游戏效果图
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220106_c2d35ff7_1296205.jpeg "1.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220113_e79ff7eb_1296205.jpeg "2.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220120_6766297a_1296205.jpeg "3.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220127_edfab294_1296205.jpeg "4.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220135_08b3dba9_1296205.jpeg "7.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220143_d982c9c7_1296205.jpeg "8.JPG")

### 服务器效果图
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220206_0377f762_1296205.jpeg "5.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0823/220222_f6b05515_1296205.jpeg "6.JPG")

### 2017/8/25 00：25第一次更新
添加了游戏玩家名字标识的功能，同时添加了游戏其它玩家体积排行榜的功能，其它玩家取前五个体积最大的玩家列于游戏屏幕右边。自己的体积列于最下方。
### 效果图
![输入图片说明](https://git.oschina.net/uploads/images/2017/0825/002843_fb138e68_1296205.jpeg "捕获.JPG")
![输入图片说明](https://git.oschina.net/uploads/images/2017/0825/002850_a599918a_1296205.jpeg "捕获1.JPG")

### Net网络库介绍
该网络库主要实现了TCP协议下的服务器和客户端，还有UDP协议下的服务器和客户端。
TCP版的服务器主要包含两种网络模型select选择模型和效率、处理并发都较高(具体有多高看运行的PC性能如何)的IOCP完成端口模型
UDP版的服务器主要包含普通模型和IOCP完成端口模型。
### Net网络库使用示例

### TCPServer使用示例一：通过编写自定义回调函数

```
void ServerProc(SOCKET sock, const char* buff, CTCPServer* pServer, LPVOID Param)  //客户端消息回调函数
{
    Do............(进行一些处理)
}


int main()
{
	CUDPServer server;
	if (server.StartServer(ServerProc //客户端消息回调函数,NULL //回调函数预留参数,6036//服务器端口,UMODE_IOCP //服务器模型) == true)
	{
		cout << "开启服务器成功" << endl;
	}
	else
	{
		cout << server.GetLastError() << endl;
	}
	getchar();  //防止服务器退出
	return 0;
}

```
### TCPServer使用示例二：通过继承该类扩展为自己的服务器类
```
#include<TCPServer.h>

class SelfServer :public Net::CTCPServer
{
public:
	SelfServer();
	virtual  ~SelfServer();

	/*
	*OnRecv(SOCKET sock, const char* buff)
	*重写CTCPServer类中的收到客户端消息的回调函数
	*@Param sock：消息来源sock
	*@Param buff：消息内容
	*/
	virtual void OnRecv(SOCKET sock, const char* buff){ ..........}

...................
private:
  ...............
  .............

};

#include"SelfServer.h"

int main()
{
SelfServer Server;
Server.StartServer(NULL, NULL, 6036, Net::MODE_IOCP);
getchar()//防止服务器直接退出
return 0;
}

```
 **其它网络库中的类使用方法如上的CTCPServer都有两种使用方法一种是自定义回调函数，一种是继承后重写消息回调函数** 

### 2017/9/9 22：25新增Linux下的网络库UNet
该网络库也和windows下的一样包含TCP和UDP协议下的客户端和服务端该网络模型TCP服务端包含select模型(相比于Windos下的select模型并发数要大，最优处理数在几百，最大可达2048，这里我限制它的最大为512),poll模型（select的改良版，提升并发数，效率没有很大提升）,epoll模型（既提升了了并发数又提升了效率），用户可根据自身需要选择自己所需的模型。这里我使用的Linux为Ubuntu16.04 LTS

### 简要介绍一下如何使用该网络库
首先进入UNet文件夹,使用makefile文件编译出.so动态链接库然后在执行install.sh文件进行安装，
操作如图所示：
![输入图片说明](https://git.oschina.net/uploads/images/2017/0909/223139_69e2cda9_1296205.jpeg "makeAndinstall.jpg")
其中的make命令是使用makefile将代码编译为Linux下的.so共享库（和Woindows下的dll类似），安装命令主要是将生成的.so移动至Linux下的/usr/lib文件夹下，并将.h文件移动至/usr/include文件夹下，这两个文件夹书Linux内核存放用户库文件和头文件的地方。最后一个CS命令可以忽略，这个是本人自己写的Linux下的一个截屏软件，主要是在Linux下没找到一个好用的截屏软件，有兴趣可在我的项目中找到http://git.oschina.net/lsylovews/jiepingruanjian

### 使用示例请查看UClientTest文件夹和UserverTest文件夹下的main.cpp文件
两个文件都是使用makefile进行编译的.makefile本质上还是使用的gcc指令，只是一次性调用而已不要像传统方法一样一个指令一个指令敲



