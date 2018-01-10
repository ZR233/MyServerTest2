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
	memset(logName, sizeof(logName),'\0');
	memset(logPass, sizeof(logPass), '\0');
	memset(reserve, sizeof(reserve), '\0');
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

std::vector<char>* CBind::Binder(std::string &logID, std::string &PassWord)
{
	memset(logName, sizeof(logName), '\0');
	memset(logPass, sizeof(logPass), '\0');
	memset(reserve, sizeof(reserve), '\0');
	if ((logID.size() >16) || (PassWord.size() >16))
	{
		throw std::runtime_error("bind时用户名密码过长");
	}
	char temp;
	bind_buf.clear();
	memcpy(&temp, &logType, 1);

	bind_buf.push_back(temp);
	logID.resize(16);
	bind_buf.insert(bind_buf.end(), logID.begin(), logID.end());
	PassWord.resize(16);
	bind_buf.insert(bind_buf.end(), PassWord.begin(), PassWord.end());

	for (int i = 0; i < 8; i++)
	{
		bind_buf.push_back('\0');
	}
	std::cout << "bind.cpp bind_buf:" << std::to_string(bind_buf.size()) << std::endl;
	return &bind_buf;

}
void CBind::recvBind(std::vector<char> &buf)
{
	memset(logName, sizeof(logName), '\0');
	memset(logPass, sizeof(logPass), '\0');
	memset(reserve, sizeof(reserve), '\0');

	int pt = 20;
	//拷贝登陆类型
	memcpy(&logType, &buf[pt], 1);

	pt += 1;
	//拷贝用户名
	for (int i = 0; i < sizeof(logName); i++)
	{
		logName[i] = buf[i + pt];
	}
	pt += 16;
	//拷贝密码
	for (int i = 0; i < sizeof(logPass); i++)
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

std::vector<char>* CBind::getBuf()
{
	return &bind_buf;
}
