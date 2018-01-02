#include "stdafx.h"
#include "CSubmit.h"


CSubmit::CSubmit()
{
	strcpy_s(SP_number, "3053112345");
	memcpy(charge_number, "000000000000000000000", 21);
	user_count = 0;
	memcpy(corp_Id, "12345", 5);
	strcpy_s(service_type, "23333");
	fee_type = 2;
	strcpy_s(fee_value, "00000");
	strcpy_s(given_value, "00000");
	agent_flag = 0;
	morelateto_MT_flag = 0;
	priority = 0;
	expire_time[0] = 0;
	schedule_time[0] = 0;
	report_flag = 0;
	TP_pid = 0;
	TP_udhi = 0;
	message_coding = 15;
	message_type = 0;
	message_length = 0;
}


CSubmit::~CSubmit()
{
}


// 生成submit buf
std::vector<char>* CSubmit::Submiter(std::vector<std::string> userNum, char* msg, int msg_size)
{



	return &sub_buf;
}


// 接收submit
void CSubmit::recvSubmit(std::vector<char> &buf)
{
	int pt = 20;
	//拷贝SP接入号 
	for (int i = 0; i < 21; i++)
	{
		SP_number[i] = buf[i + pt];
	}
	pt += 21;

	//拷贝付费号码
	for (int i = 0; i < 21; i++)
	{
		charge_number[i] = buf[i + pt];
	}
	pt += 21;
	//拷贝接收短消息的手机号
	user_count = (unsigned int)buf[pt];
	pt += 1;
	num.clear();
	for (int i = 0; i < user_count; i++)
	{
		char temp[21];
		for (int j = 0; j < 21; j++)
		{
			temp[j] = buf[pt + j];
		}
		std::string tempstr(temp);
		num.push_back(tempstr);
		pt += 21;
	}
	//拷贝企业代码
	for (int i = 0; i < 5; i++)
	{
		corp_Id[i] = buf[i + pt];
	}
	pt += 5;
	//拷贝业务代码，由SP定义
	for (int i = 0; i < 10; i++)
	{
		service_type[i] = buf[i + pt];
	}
	pt += 10;

	//拷贝计费类型
	fee_type = (unsigned int)buf[pt];
	pt += 1;

	//拷贝取值范围0-99999，该条短消息的收费值，单位为分，由SP定义
	for (int i = 0; i < 6; i++)
	{
		fee_value[i] = buf[i + pt];
	}
	pt += 6;
	//拷贝取值范围0-99999，赠送用户的话费，单位为分，由SP定义，特指由SP向用户发送广告时的赠送话费
	for (int i = 0; i < 6; i++)
	{
		given_value[i] = buf[i + pt];
	}
	pt += 6;

	//拷贝
	agent_flag = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	morelateto_MT_flag = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	priority = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	for (int i = 0; i < 16; i++)
	{
		expire_time[i] = buf[i + pt];
	}
	pt += 16;
	//拷贝
	for (int i = 0; i < 16; i++)
	{
		schedule_time[i] = buf[i + pt];
	}
	pt += 16;
	//拷贝
	report_flag = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	TP_pid = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	TP_udhi = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	message_coding = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	message_type = (unsigned int)buf[pt];
	pt += 1;
	//拷贝
	char temp_char_message_length[4];
	for (int i = 0; i < 4; i++)
	{
		temp_char_message_length[i] = buf[i + pt];
	}
	memcpy(&message_length, temp_char_message_length, 4);
	message_length = ntohl(message_length);
	pt += 4;
	//拷贝
	message_content.clear();
	for (int i = 0; i < message_length; i++)
	{
		message_content += buf[ i+ pt];
	}


}


// 取发送至手机号
std::vector<std::string>* CSubmit::getPhNums()
{
	return &num;
}


// 取短消息内容
std::string* CSubmit::getText()
{
	return &message_content;
}


// 取手机号数量
int CSubmit::getUserCount()
{
	return user_count;
}


// 得到企业代码
std::string CSubmit::getCorpId()
{
	
	char temp_char[6] = { 0 };
	memcpy(temp_char, corp_Id, 5);

	std::string temp_string(temp_char);

	return temp_string;
}
