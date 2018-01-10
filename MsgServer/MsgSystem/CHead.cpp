#include "stdafx.h"
#include "CHead.h"


CHead::CHead()
{
	msg_length = 0;
	cmd_ID = 0;
	SN_1 = 0;
	SN_2 = 0;
	SN_3 = 0;
}


CHead::~CHead()
{
}


// 制作消息头
std::vector<char>* CHead::header(int msgL, int CID, int spID, int num)
{
	msg_length = htonl(msgL);
	cmd_ID = htonl(CID);
	SYSTEMTIME st = { 0 }; //获得系统当前时间
	GetLocalTime(&st);
	int SNT = st.wMonth * 100000000 + st.wDay * 1000000 + st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
	SN_1 = htonl(3053100000 + spID);
	SN_2 = htonl(SNT);
	SN_3 = htonl(num);
	char temp[4];
	head_buf.clear();
	memcpy(temp, &msg_length, 4);
	for (int i = 0; i < 4; i++)
	{
		head_buf.push_back(temp[i]);
	}
	memcpy(temp, &cmd_ID, 4);
	for (int i = 0; i < 4; i++)
	{
		head_buf.push_back(temp[i]);
	}
	memcpy(temp, &SN_1, 4);
	for (int i = 0; i < 4; i++)
	{
		head_buf.push_back(temp[i]);
	}
	memcpy(temp, &SN_2, 4);
	for (int i = 0; i < 4; i++)
	{
		head_buf.push_back(temp[i]);
	}
	memcpy(temp, &SN_3, 4);
	for (int i = 0; i < 4; i++)
	{
		head_buf.push_back(temp[i]);
	}
	return &head_buf;
}


// 解析消息头
void CHead::recvHead(std::vector<char> &buf)
{
	char temp[4];
	int pt = 0;
	//拷贝消息长度
	for (int i = 0; i < 4; i++)
	{
		temp[i] = buf[i];
	}
	memcpy(&msg_length, temp, 4);
	msg_length = ntohl(msg_length);
	pt += 4;
	//拷贝指令ID
	for (int i = 0; i < 4; i++)
	{
		temp[i] = buf[i+ pt];
	}
	memcpy(&cmd_ID, temp, 4);
	cmd_ID = ntohl(cmd_ID);
	pt += 4;
	//拷贝SN1
	for (int i = 0; i < 4; i++)
	{
		temp[i] = buf[i + pt];
	}
	memcpy(&SN_1, temp, 4);
	SN_1 = ntohl(SN_1);
	pt += 4;
	//拷贝SN2
	for (int i = 0; i < 4; i++)
	{
		temp[i] = buf[i + pt];
	}
	memcpy(&SN_2, temp, 4);
	SN_2 = ntohl(SN_2);
	pt += 4;
	//拷贝SN3
	for (int i = 0; i < 4; i++)
	{
		temp[i] = buf[i + pt];
	}
	memcpy(&SN_3, temp, 4);
	SN_3 = ntohl(SN_3);
}


// 消息长度
unsigned int CHead::msgLength()
{
	return msg_length;
}


// 指令ID
unsigned int CHead::cmdID()
{
	return cmd_ID;
}


// SN1
unsigned int CHead::SN1()
{
	return SN_1;
}


// SN2
unsigned int CHead::SN2()
{
	return SN_2;
}


// SN3
unsigned int CHead::SN3()
{
	return SN_3;
}
std::vector<char>* CHead::getBuf()
{
	return &head_buf;
}