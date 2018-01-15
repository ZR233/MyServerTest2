#include "stdafx.h"
#include "CSubmit.h"


CSubmit::CSubmit()
{
	strcpy_s(SP_number, "3053112345");
	memset(charge_number, '0', 21);

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


// ����submit buf
std::vector<char>* CSubmit::Submiter(std::vector<std::string> &userNum, std::string &msg)
{
	int pt = 20;
	sub_buf.clear();
	//����SP����� 
	for (int i = 0; i < sizeof(SP_number); i++)
	{
		sub_buf.push_back(SP_number[i]);
	}
	pt += 21;

	//�������Ѻ���
	for (int i = 0; i < sizeof(charge_number); i++)
	{
		sub_buf.push_back(charge_number[i]);
	}
	pt += 21;
	//�������ն���Ϣ���ֻ�������
	user_count = userNum.size();
	sub_buf.push_back((unsigned char)user_count);
	pt += 1;
	//�������ն���Ϣ���ֻ���
	for (int i = 0; i < userNum.size(); i++)
	{
		std::vector<char> temp_ph;
		temp_ph.assign(userNum[i].begin(), userNum[i].end());
		temp_ph.resize(21);
		sub_buf.insert(sub_buf.end(),temp_ph.begin(),temp_ph.end());
		pt += 21;
	}
	//������ҵ����
	for (int i = 0; i < 5; i++)
	{
		sub_buf.push_back(corp_Id[i]);
	}
	pt += 5;
	//����ҵ����룬��SP����
	for (int i = 0; i < 10; i++)
	{
		sub_buf.push_back(service_type[i]);
	}
	pt += 10;

	//�����Ʒ�����
	sub_buf.push_back((unsigned char)fee_type);
	pt += 1;

	//����ȡֵ��Χ0-99999����������Ϣ���շ�ֵ����λΪ�֣���SP����
	for (int i = 0; i < 6; i++)
	{
		sub_buf.push_back(fee_value[i]);
	}
	pt += 6;
	//����ȡֵ��Χ0-99999�������û��Ļ��ѣ���λΪ�֣���SP���壬��ָ��SP���û����͹��ʱ�����ͻ���
	for (int i = 0; i < 6; i++)
	{
		sub_buf.push_back(given_value[i]);
	}
	pt += 6;

	//����
	sub_buf.push_back((unsigned char)agent_flag);
	pt += 1;
	//����
	sub_buf.push_back((unsigned char)morelateto_MT_flag);
	pt += 1;
	//����
	sub_buf.push_back((unsigned char)priority);
	pt += 1;
	//����
	for (int i = 0; i < 16; i++)
	{
		sub_buf.push_back(expire_time[i]);
	}
	pt += 16;
	//����
	for (int i = 0; i < 16; i++)
	{
		sub_buf.push_back(schedule_time[i]);
	}
	pt += 16;
	//����
	sub_buf.push_back((unsigned char)report_flag);
	pt += 1;
	//����
	sub_buf.push_back((unsigned char)TP_pid) ;
	pt += 1;
	//����
	sub_buf.push_back((unsigned char)TP_udhi);
	pt += 1;
	//����
	sub_buf.push_back((unsigned char)message_coding);
	pt += 1;
	//����
	sub_buf.push_back((unsigned char)message_type);
	pt += 1;
	//�����������ݳ���
	char temp_char_message_length[4];
	unsigned int temp_ml = htonl(msg.size() + 1);
	memcpy(temp_char_message_length, &temp_ml, 4);
	sub_buf.insert(sub_buf.end(), &temp_char_message_length[0], &temp_char_message_length[4]);
	pt += 4;
	//������������
	sub_buf.insert(sub_buf.end(), msg.begin(), msg.end());


	for (size_t i = 0; i < 9; i++)
	{
		sub_buf.push_back(0);
	}
	pt += (msg.size()+1);
	pt += 8;


	return &sub_buf;
}

using std::cout;
using std::endl;
// ����submit
void CSubmit::recvSubmit(std::vector<char> &buf)
{
	if (buf.size() < (20+ sizeof(SP_number) + sizeof(charge_number) + 1 ))
	{
		throw std::runtime_error("submit ��Ϣ���ȴ���");
	}
	int pt = 20;

	//����SP����� 
	for (int i = 0; i < 21; i++)
	{
		SP_number[i] = buf[i + pt];
	}
	pt += 21;

	//�������Ѻ���
	for (int i = 0; i < 21; i++)
	{
		charge_number[i] = buf[i + pt];
	}
	pt += 21;

	//�������ն���Ϣ���ֻ���
	user_count = (unsigned int)buf[pt];
	pt += 1;


	num.clear();
	for (int i = 0; i < user_count; i++)
	{
		char temp[21] = { 0 };
		for (int j = 0; j < 21; j++)
		{
			temp[j] = buf[pt + j];

		}
		temp[20] = 0;
		std::string tempstr(temp);
		num.push_back(tempstr);
		pt += 21;
	}

	//������ҵ����
	for (int i = 0; i < 5; i++)
	{
		corp_Id[i] = buf[i + pt];
	}
	pt += 5;
	//����ҵ����룬��SP����
	for (int i = 0; i < 10; i++)
	{
		service_type[i] = buf[i + pt];
	}
	pt += 10;

	//�����Ʒ�����
	fee_type = (unsigned int)buf[pt];
	pt += 1;

	//����ȡֵ��Χ0-99999����������Ϣ���շ�ֵ����λΪ�֣���SP����
	for (int i = 0; i < 6; i++)
	{
		fee_value[i] = buf[i + pt];
	}
	pt += 6;
	//����ȡֵ��Χ0-99999�������û��Ļ��ѣ���λΪ�֣���SP���壬��ָ��SP���û����͹��ʱ�����ͻ���
	for (int i = 0; i < 6; i++)
	{
		given_value[i] = buf[i + pt];
	}
	pt += 6;

	//����
	agent_flag = (unsigned int)buf[pt];
	pt += 1;
	//����
	morelateto_MT_flag = (unsigned int)buf[pt];
	pt += 1;
	//����
	priority = (unsigned int)buf[pt];
	pt += 1;
	//����
	for (int i = 0; i < 16; i++)
	{
		expire_time[i] = buf[i + pt];
	}
	pt += 16;
	//����
	for (int i = 0; i < 16; i++)
	{
		schedule_time[i] = buf[i + pt];
	}
	pt += 16;
	//����
	report_flag = (unsigned int)buf[pt];
	pt += 1;

	//����
	TP_pid = (unsigned int)buf[pt];
	pt += 1;

	//����
	TP_udhi = (unsigned int)buf[pt];
	pt += 1;

	//����
	message_coding = (unsigned int)buf[pt];
	pt += 1;

	//����
	message_type = (unsigned int)buf[pt];
	pt += 1;

	//����
	char temp_char_message_length[4];
	for (int i = 0; i < 4; i++)
	{
		temp_char_message_length[i] = buf[i + pt];
	}
	memcpy(&message_length, temp_char_message_length, 4);
	message_length = ntohl(message_length);
	pt += 4;

	//����
	message_content.clear();
	for (int i = 0; i < message_length; i++)
	{
		message_content += buf[ i+ pt];
	}
	pt += message_length;
	pt += 8;



	//if (pt != buf.size())
	//{
	//	throw std::runtime_error("submit��ʽ����");
	//}
}


// ȡ�������ֻ���
std::vector<std::string>* CSubmit::getPhNums()
{
	return &num;
}

// ȡ����Ϣ����
int CSubmit::getTextL()
{
	return message_length;
}

// ȡ����Ϣ����
std::string* CSubmit::getText()
{
	return &message_content;
}


// ȡ�ֻ�������
int CSubmit::getUserCount()
{
	return user_count;
}


// �õ���ҵ����
std::string CSubmit::getCorpId()
{
	
	char temp_char[6] = { 0 };
	memcpy(temp_char, corp_Id, 5);

	std::string temp_string(temp_char);

	return temp_string;
}
std::vector<char>* CSubmit::getBuf()
{
	return &sub_buf;
}