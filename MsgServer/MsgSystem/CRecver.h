#pragma once
#include "CHead.h"
#include "CBind.h"
#include "CSubmit.h"
class CRecver
{
public:
	CRecver();
	~CRecver();
	// �����յ�����Ϣ
	int recv(std::vector<char> buf);
};

