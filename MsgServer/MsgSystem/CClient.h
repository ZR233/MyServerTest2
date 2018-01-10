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
};

#undef EXPORT_DLL  

#endif 