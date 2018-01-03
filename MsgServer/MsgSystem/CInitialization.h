#pragma once

#include <iostream> 
#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>   


//通过配置文件初始化
class CInitialization
{
	
public:
	CInitialization();
	~CInitialization();
	// 初始化
	void init();
	int corpID;//企业代码

	std::string SPID;//SP接入号
	std::string charge_num;//付费号码
	std::string usr_name;//用户名
	std::string usr_pass;//密码
	int client_port;//与客户端联系端口号
	std::string unic_IP;//联通IP
	int unic_port;// 联通端口号
};

