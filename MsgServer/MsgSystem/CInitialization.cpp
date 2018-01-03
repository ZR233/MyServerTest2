#include "stdafx.h"
#include "CInitialization.h"


CInitialization::CInitialization()
{
}


CInitialization::~CInitialization()
{
}


// ��ʼ��
void CInitialization::init()
{
	boost::property_tree::ptree pt;
	try
	{
		boost::property_tree::ini_parser::read_ini("Config.ini", pt);  // �򿪶��ļ�  
		corpID = pt.get<int>("Service.��ҵ����");
		SPID = pt.get<std::string>("Service.SP�����");
		charge_num = pt.get<std::string>("Service.���Ѻ���");
		usr_name = pt.get<std::string>("Service.�û���");
		usr_pass = pt.get<std::string>("Service.����");
		client_port = pt.get<int>("Service.��ͻ�����ϵ�˿ں�");
		unic_IP = pt.get<std::string>("Service.��ͨIP");
		unic_port = pt.get<int>("Service.��ͨ�˿ں�");
	}
	catch (const std::exception&)
	{
		pt.put<std::string>("Service.��ҵ����", "12345");  // д�ֶ�  
		pt.put<std::string>("Service.SP�����", "3053112345");
		pt.put<std::string>("Service.���Ѻ���", "0");
		pt.put<std::string>("Service.�û���", "zr12345678");
		pt.put<std::string>("Service.����", "1234567890");
		pt.put<std::string>("Service.��ͻ�����ϵ�˿ں�", "8801");
		pt.put<std::string>("Service.��ͨIP", "127.0.0.1");
		pt.put<std::string>("Service.��ͨ�˿ں�", "8802");

		boost::property_tree::ini_parser::write_ini("Config.ini", pt); // д���ļ�    
	}
	return;
}
