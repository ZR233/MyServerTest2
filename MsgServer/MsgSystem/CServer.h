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

//�������������
class EXPORT_DLL CServer
{
public:
	
	CServer();
	~CServer();
	void setPort();
	// ����������
	void start();
	//��������SGIP
	void SGIPLis();
	// ����socket���߳�
	void DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
private:
	//�����˿�
	int local_port;
	//CMPP2.0 sp������֮�� ������
	int CMPP20_long_in_port;

	//CMPP2.0 SP�����ؼ������֮�� ������
	int CMPP20_short_in_port;
	//CMPP2.0 sp������֮�� ������
	//int CMPP20_short_port;

	//CMPP2.0 ����������������֮��
	int CMPP20_short_out_port;

	//mutex mut;
	CLogInit CI;

public:
	// �鿴�ѷ�����Ϣ
	void seeMsgs();
	// ��������CMPP2.0 ������
	void CMPP20ListenL();
};

#undef EXPORT_DLL  

#endif 