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
	//������½����

	memcpy(&logType, &buf[pt], 1);

	pt += 1;
	//�����û���
	for (int i = 0; i < 16; i++)
	{
		logName[i] = buf[i + pt];
	}
	pt += 16;
	//��������
	for (int i = 0; i < 16; i++)
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
