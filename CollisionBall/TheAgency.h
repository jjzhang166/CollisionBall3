#pragma once

class cTheAgency
{
public:
	cTheAgency(HINSTANCE hInstance);
	~cTheAgency();
	void PreInit();  //初始化前工作
	void AfterInit();  //初始化后工作
	void LoadResource();   //加载资源
private:
	HINSTANCE m_hInstance;
};

