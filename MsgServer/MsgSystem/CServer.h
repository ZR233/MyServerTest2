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
	char name[16];//登录名
	char pass[16];//密码
	unsigned int msgL;//收到的消息长度
	char msg[1000];//收到的消息
	std::vector<std::string> PH_vec;//推送号码
};
class EXPORT_DLL CServer
{
public:
	CServer();
	~CServer();
	void setPort();
	// 开启服务器
	void run();
	// 处理socket的线程
	void DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
private:
	//监听端口
	int local_port;
	//mutex mut;
	CLogInit CI;
	std::vector<Srequest_from_client> request_from_client;
};

#undef EXPORT_DLL  

#endif 