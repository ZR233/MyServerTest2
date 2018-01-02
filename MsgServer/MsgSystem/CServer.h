#pragma once
#include "stdafx.h"
#include "CLogInit.h"

#ifndef _ADD_CAL_H_  
#define _ADD_CAL_H_  

#ifdef MYDLL_EXPORT  
#define EXPORT_DLL _declspec(dllexport)  
#else  
#define EXPORT_DLL _declspec(dllimport)  
#endif  

struct	Srequest_from_client {
	char name[16];//��¼��
	char pass[16];//����
	unsigned int msgL;//�յ�����Ϣ����
	char msg[1000];//�յ�����Ϣ
	std::vector<std::string> PH_vec;//���ͺ���
};
class EXPORT_DLL CServer
{
public:
	CServer();
	~CServer();
	void setPort();
	// ����������
	void run();
	// ����socket���߳�
	void DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
private:
	//�����˿�
	int local_port;
	//mutex mut;
	CLogInit CI;
	std::vector<Srequest_from_client> request_from_client;
};

#undef EXPORT_DLL  

#endif 