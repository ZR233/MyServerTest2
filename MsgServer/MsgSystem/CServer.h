#pragma once

#ifndef _ADD_CAL_H_  
#define _ADD_CAL_H_  

#ifdef MYDLL_EXPORT  
#define EXPORT_DLL _declspec(dllexport)  
#else  
#define EXPORT_DLL _declspec(dllimport)  
#endif  


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

};

#undef EXPORT_DLL  

#endif 