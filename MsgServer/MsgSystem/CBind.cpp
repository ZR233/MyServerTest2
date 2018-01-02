#include "stdafx.h"
#include "CBind.h"


CBind::CBind()
{
	logType = 1;//登陆类型 1:SP->SMG; 2:SMG->SP; 3:SMG->SMG
}


CBind::~CBind()
{
}
std::vector<char>* CBind::Binder(char *logID, char *PassWord) 
{
	for (int i = 0; i < 16; i++)
	{
		logName[i] = '\0';
		logPass[i] = '\0';
	}
	for (int i = 0; i < 8; i++)
	{
		reserve[i] = '\0';
	}
	char temp;
	bind_buf.clear();
	memcpy(&temp, &logType, 1);

	bind_buf.push_back(temp);
	
	for (int i = 0; i < 16; i++)
	{
		bind_buf.push_back(logID[i]);
	}

	for (int i = 0; i < 16; i++)
	{
		bind_buf.push_back(PassWord[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		bind_buf.push_back('\0');
	}
	
	return &bind_buf;

}

void CBind::recvBind(std::vector<char> &buf)
{
	for (int i = 0; i < 16; i++)
	{
		logName[i] = '\0';
		logPass[i] = '\0';
	}
	for (int i = 0; i < 8; i++)
	{
		reserve[i] = '\0';
	}
	int pt = 20;
	//拷贝登陆类型

	memcpy(&logType, &buf[pt], 1);

	pt += 1;
	//拷贝用户名
	for (int i = 0; i < 16; i++)
	{
		logName[i] = buf[i + pt];
	}
	pt += 16;
	//拷贝密码
	for (int i = 0; i < 16; i++)
	{
		logPass[i] = buf[i + pt];
	}
	pt += 16;

}

// 取用户名
char* CBind::getName()
{
	return logName;
}


// 取密码
char* CBind::getPass()
{
	return logPass;
}


// 取登录类型。
int CBind::getType()
{
	return logType;
}
