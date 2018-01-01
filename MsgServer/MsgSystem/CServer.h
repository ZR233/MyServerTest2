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
	// ����������
	void run();
	// ����socket���߳�
	void DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);
private:
	//�����˿�
	int local_port;
	//mutex mut;

};

#undef EXPORT_DLL  

#endif 