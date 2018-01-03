#include "stdafx.h"
#include "CInitialization.h"


CInitialization::CInitialization()
{
}


CInitialization::~CInitialization()
{
}


// 初始化
void CInitialization::init()
{
	boost::property_tree::ptree pt;
	try
	{
		boost::property_tree::ini_parser::read_ini("Config.ini", pt);  // 打开读文件  
		corpID = pt.get<int>("Service.企业代码");
		SPID = pt.get<std::string>("Service.SP接入号");
		charge_num = pt.get<std::string>("Service.付费号码");
		usr_name = pt.get<std::string>("Service.用户名");
		usr_pass = pt.get<std::string>("Service.密码");
		client_port = pt.get<int>("Service.与客户端联系端口号");
		unic_IP = pt.get<std::string>("Service.联通IP");
		unic_port = pt.get<int>("Service.联通端口号");
	}
	catch (const std::exception&)
	{
		pt.put<std::string>("Service.企业代码", "12345");  // 写字段  
		pt.put<std::string>("Service.SP接入号", "3053112345");
		pt.put<std::string>("Service.付费号码", "0");
		pt.put<std::string>("Service.用户名", "zr12345678");
		pt.put<std::string>("Service.密码", "1234567890");
		pt.put<std::string>("Service.与客户端联系端口号", "8801");
		pt.put<std::string>("Service.联通IP", "127.0.0.1");
		pt.put<std::string>("Service.联通端口号", "8802");

		boost::property_tree::ini_parser::write_ini("Config.ini", pt); // 写到文件    
	}
	return;
}
