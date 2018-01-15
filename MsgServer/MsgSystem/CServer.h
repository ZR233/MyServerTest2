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
	void start();
	//开启监听SGIP
	void SGIPLis();
	// 处理socket的线程
	void DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
private:
	//监听端口
	int local_port;
	//CMPP2.0 sp与网关之间 长连接
	int CMPP20_long_in_port;

	//CMPP2.0 SP与网关间或网关之间 短连接
	int CMPP20_short_in_port;
	//CMPP2.0 sp与网关之间 长连接
	//int CMPP20_short_port;

	//CMPP2.0 短信网关与汇接网关之间
	int CMPP20_short_out_port;

	//mutex mut;
	CLogInit CI;

public:
	// 查看已发来信息
	void seeMsgs();
	// 开启监听CMPP2.0 长连接
	void CMPP20ListenL();
};

#undef EXPORT_DLL  

#endif 