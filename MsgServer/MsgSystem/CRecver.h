#pragma once
#include "CHead.h"
#include "CBind.h"
#include "CSubmit.h"


//�Խ��յ���buf���д��� 
class CRecver
{
public:
	CRecver();
	~CRecver();
	// �����յ�����Ϣ
	std::vector<char> recv(std::vector<char> &buf);
private:
	bool connected_flag;
	std::string user_name;
	std::string password;
	Srequest_from_client request_from_client;
};

