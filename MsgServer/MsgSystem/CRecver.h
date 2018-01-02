#pragma once
#include "CHead.h"
#include "CBind.h"
#include "CSubmit.h"
class CRecver
{
public:
	CRecver();
	~CRecver();
	// 解析收到的信息
	int recv(std::vector<char> buf);
};

