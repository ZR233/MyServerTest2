#pragma once

#include <iostream> 
#include <boost/property_tree/ptree.hpp>    
#include <boost/property_tree/ini_parser.hpp>   


//ͨ�������ļ���ʼ��
class CInitialization
{
	
public:
	CInitialization();
	~CInitialization();
	// ��ʼ��
	void init();
	int corpID;//��ҵ����

	std::string SPID;//SP�����
	std::string charge_num;//���Ѻ���
	std::string usr_name;//�û���
	std::string usr_pass;//����
	int client_port;//��ͻ�����ϵ�˿ں�
	std::string unic_IP;//��ͨIP
	int unic_port;// ��ͨ�˿ں�
};

