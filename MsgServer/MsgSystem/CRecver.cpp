#include "stdafx.h"
#include "CRecver.h"
#include "ServerBuf.h"
#include "CResp.h"

CRecver::CRecver()
{
	connected_flag = 0;
	user_name = "qweqeqqew213120";
	password = "1awdawdqwe210";
}


CRecver::~CRecver()
{
}


// �����յ�����Ϣ
std::vector<char> CRecver::recv(std::vector<char> &buf)
{
	CHead ch;
	CBind cb;
	CSubmit cs;
	CResp cr;
	boost::mutex mu;
	ch.recvHead(buf);
	std::vector<std::string> temp_vec;
	std::vector<char> resp;
	for (int i = 0; i < 20; i++)
	{
		resp.push_back(buf[i]);
	}
	switch (ch.cmdID())
	{
	case 1://�յ�Bind����
		cb.recvBind(buf);
		std::cout << "------------" << std::endl;
		std::cout << "�յ�Bind����" << std::endl;
		std::cout << "��Ϣ���ȣ�" << std::to_string(ch.msgLength()) << std::endl;
		std::cout << "ָ��ID:" << std::to_string(ch.cmdID()) << std::endl;
		std::cout << "SN1:" << std::to_string(ch.SN1()) << std::endl;
		std::cout << "SN2:" << std::to_string(ch.SN2()) << std::endl;
		std::cout << "ָ���:" << std::to_string(cb.getType()) << std::endl;
		std::cout << "�û���:" << cb.getName() << std::endl;
		std::cout << "����:" << cb.getPass() << std::endl;
		if ((std::string(cb.getName()) == user_name)&&((std::string(cb.getPass()) == password)))
		{
			std::cout << "��½�ɹ�" << std::endl;
			for (int i = 0; i < 9; i++)
			{
				resp.push_back(cr.resp(0)[i]);
			}
			connected_flag = 1;
		memcpy(request_from_client.name, cb.getName(), 16);
		memcpy(request_from_client.pass, cb.getPass(), 16);
		}
		else
		{
			throw std::runtime_error("�û����������");
		}
		break;
	case 0x80000001://�յ�Bind��Ӧ
		//memcpy(&temp, pt, 1);
		//pt += 1;

		//result = (int)temp;
		//cout << "�յ�Ӧ��" << endl;

		////cout << "���ȣ�" << a << endl;

		//cout << "���ȣ�" << to_string(hd.msgLength) << endl;
		//cout << "����ID:" << "80000001" << endl;
		//cout << "�������к�:" << to_string(hd.SN1) << "," << to_string(hd.SN2) << "," << to_string(hd.SN3) << endl;
		//cout << "������:" << to_string(result) << endl;
		//cout << "----------------" << endl;
		break;
	case 0x80000002://�յ�unbind��Ӧ
		//memcpy(&temp, pt, 1);
		//pt += 1;

		//result = (int)temp;
		//cout << "�յ�unbind��Ӧ" << endl;
		//cout << "���ȣ�" << to_string(hd.msgLength) << endl;
		//cout << "����ID:" << "80000002" << endl;
		//cout << "�������к�:" << to_string(hd.SN1) << "," << to_string(hd.SN2) << "," << to_string(hd.SN3) << endl;
		//cout << "----------------" << endl;
		break;
	case 2://�յ�unbind����
		std::cout << "----------------" << std::endl;
		std::cout << "�յ�UnBind����" << std::endl;
		break;
	case 0x80000003://�յ�submit��Ӧ
		//memcpy(&temp, pt, 1);
		//pt += 1;
		//result = (int)temp;
		//cout << "�յ�submit��Ӧ" << endl;

		////cout << "���ȣ�" << a << endl;

		//cout << "���ȣ�" << to_string(hd.msgLength) << endl;
		//cout << "����ID:" << "80000003" << endl;
		//cout << "�������к�:" << to_string(hd.SN1) << "," << to_string(hd.SN2) << "," << to_string(hd.SN3) << endl;
		//cout << "������:" << to_string(result) << endl;
		//cout << "----------------" << endl;
		break;
	case 3://�յ�submit����
		if (connected_flag != 1)
		{
			for (int i = 0; i < 9; i++)
			{
				resp.push_back(cr.resp(1)[i]);
			}
			return resp;
		}
		cs.recvSubmit(buf);
		std::cout << "--------------" << std::endl;
		std::cout << "�յ�submit����" << std::endl;
		std::cout << "�������ֻ��ţ�" << std::endl;
		temp_vec = *cs.getPhNums();

		if (temp_vec.size() > 0)
		{
			for (int i = 0; i < temp_vec.size(); i++)
			{
				std::string temp_str = temp_vec[i];
				if (temp_str.size() != 11)
				{
					std::cout << "�ֻ��Ÿ�ʽ����:" ;
				}
				else
				{
					request_from_client.PH_vec.push_back(temp_str);
				}
				std::cout << temp_str << std::endl;
			}
		}
		std::cout << "�յ��ֻ�������" <<std::to_string(cs.getUserCount())<< std::endl;
		std::cout << "�յ���ҵ���룺" << cs.getCorpId() << std::endl;
		std::cout << "�յ���Ϣ��" << *cs.getText() << std::endl;


		request_from_client.msgL = cs.getTextL();
		request_from_client.msg = *cs.getText();


		for (int i = 0; i < 9; i++)
		{
			resp.push_back(cr.resp(0)[i]);
		}
		
		try
		{
			mu.lock();
			request_from_client_vec.insert(request_from_client_vec.begin(), request_from_client);
			mu.unlock();
		}
		catch (const std::exception&)
		{
			mu.unlock();
		}
		break;
	default:
		break;
	}
	return resp;
}
