#include "stdafx.h"
#include "CBind.h"


CBind::CBind()
{
	logType = 1;//��½���� 1:SP->SMG; 2:SMG->SP; 3:SMG->SMG
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
		throw std::runtime_error("bindʱ�û����������");
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
	//������½����
	memcpy(&logType, &buf[pt], 1);

	pt += 1;
	//�����û���
	for (int i = 0; i < sizeof(logName); i++)
	{
		logName[i] = buf[i + pt];
	}
	pt += 16;
	//��������
	for (int i = 0; i < sizeof(logPass); i++)
	{
		logPass[i] = buf[i + pt];
	}
	pt += 16;

}

// ȡ�û���
char* CBind::getName()
{
	return logName;
}


// ȡ����
char* CBind::getPass()
{
	return logPass;
}


// ȡ��¼���͡�
int CBind::getType()
{
	return logType;
}

std::vector<char>* CBind::getBuf()
{
	return &bind_buf;
}
