#pragma once
#include "stdafx.h"

#ifndef _ADD_CAL_H_  
#define _ADD_CAL_H_  

#ifdef MYDLL_EXPORT  
#define EXPORT_DLL _declspec(dllexport)  
#else  
#define EXPORT_DLL _declspec(dllimport)  
#endif  

//服务器程序入口
class EXPORT_DLL CClient
{
public:
	CClient();
	~CClient();
	// 向服务器发送bind
	int bind(std::string username, std::string password);
	//设置IP地址
	void setIp(std::string &ip);

	//设置端口号
	void setPort(int port);
	//void setLogID(std::string &logID);
	//void setPassword(std::string &password);
	int unBind();
private:
	int count;//指令ID计数
	std::string ip_addr;//ip地址
	int port;//端口号
	int spID;
	//std::string logID;//用户名
	//std::string password;//密码
};

#undef EXPORT_DLL  

#endif 