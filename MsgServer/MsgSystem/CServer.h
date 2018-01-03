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

//服务器程序入口
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

public:
	// 查看已发来信息
	void seeMsgs();
};

#undef EXPORT_DLL  

#endif 