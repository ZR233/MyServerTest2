#pragma once
#include "stdafx.h"



#ifndef _ADD_CAL_H_  
#define _ADD_CAL_H_  

#ifdef MYDLL_EXPORT  
#define EXPORT_DLL _declspec(dllexport)  
#else  
#define EXPORT_DLL _declspec(dllimport)  
#endif  

//�������������
class EXPORT_DLL CClient
{

public:
	CClient();
	~CClient();
	// �����������bind
	int bind(std::string username, std::string password);
	//����IP��ַ
	void setIp(std::string &ip);

	//���ö˿ں�
	void setPort(int port);
	//void setLogID(std::string &logID);
	//void setPassword(std::string &password);
	int unBind();
private:
	int count;//ָ��ID����
	std::string ip_addr;//ip��ַ
	int port;//�˿ں�
	int spID;
	//std::string logID;//�û���
	//std::string password;//����
	typedef boost::asio::ip::tcp::endpoint endpoint_type;
	typedef boost::asio::ip::tcp::socket socket_type;
	typedef boost::asio::ip::address address_type;

	boost::asio::io_service io_service;
	socket_type *socket/* = socket_type(io_service)*/;
	endpoint_type ep;
};




#undef EXPORT_DLL  

#endif 