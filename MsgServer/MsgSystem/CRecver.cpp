#include "stdafx.h"
#include "CRecver.h"


CRecver::CRecver()
{
}


CRecver::~CRecver()
{
}


// �����յ�����Ϣ
int CRecver::recv(std::vector<char> buf)
{
	CHead ch;
	CBind cb;
	CSubmit cs;
	ch.recvHead(buf);
	std::vector<std::string> temp_vec;
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
		return 1;
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
				std::cout << temp_str << std::endl;
			}
		}
		std::cout << "�յ��ֻ�������" <<std::to_string(cs.getUserCount())<< std::endl;
		std::cout << "�յ���ҵ���룺" << cs.getCorpId() << std::endl;
		std::cout << "�յ���Ϣ��" << *cs.getText() << std::endl;

		
		break;




	default:
		break;
	}
	return 0;
}
