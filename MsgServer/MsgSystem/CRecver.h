#pragma once
#include "CHead.h"
#include "CBind.h"
#include "CSubmit.h"


//对接收到的buf进行处理 
class CRecver
{
public:
	CRecver();
	~CRecver();
	// 解析收到的信息
	std::vector<char> recv(std::vector<char> &buf);
private:
	bool connected_flag;
	std::string user_name;
	std::string password;
	Srequest_from_client request_from_client;
};

