#pragma once
#include<map>
#include<string>
#include<vector>
#include<memory>

namespace MyEngine
{
	/*
	*class cResourcePool
	*资源池，用于统一存放并管理GDI资源句柄，节省内存提升效率
	*不要试图新建此类的对象，而要通过GetResourcePool()获取此类对象
	*/
	class cResourcePool
	{
	public:
		/*
		*GetResourcePool();
		*获取资源池对象
		*@return cResourcePool*：单例对象指针
		*/
		static cResourcePool* GetResourcePool();

		/*
		*AddObjByKey(std::string, const HGDIOBJ& hobj);
		*通过key值添加HGDIOBJ对象
		*@Param key：key值
		*@Param hobj：要存储的资源句柄
		*/
		void AddObjByKey(std::string key, const HGDIOBJ& hobj);

		/*
		*AddMulObjByKey(std::string, const std::list<HGDIOBJ> hobjList);
		*通过key值添加大量资源句柄
		*@Param key：key值
		*@Param hobjList：资源句柄列表
		*/
		void AddMulObjByKey(std::string key, const std::vector<HGDIOBJ> hobjList);

		/*
		*GethObjByKey(std::string key);
		*通过key值后去GDI对象
		*@Param key：key值
		*@return HGDIOBJ：不存在返回NULL，存在则返回相应的GDI对象
		*/
		HGDIOBJ GethObjByKey(std::string key);

		/*
		*GetMulObjByKey(std::string);
		*通过key值获取大量资源句柄
		*@Param key：key值
		*@return 资源句柄列表
		*/
		std::vector<HGDIOBJ> GetMulObjByKey(std::string key);

		/*
		*ReleaseByKey(std::string key);
		*释放指定key值的资源句柄
		*/
		bool ReleaseByKey(std::string key);
		
		void ReleaseSelf();
	private:
		cResourcePool();
		~cResourcePool();

		std::map<std::string, HGDIOBJ> m_pool;

		std::map<std::string, std::vector<HGDIOBJ>> m_mulPool;
	};
}

