#include "stdafx.h"
#include "CRecver.h"


CRecver::CRecver()
{
}


CRecver::~CRecver()
{
}


// 解析收到的信息
int CRecver::recv(std::vector<char> buf)
{
	CHead ch;
	CBind cb;
	CSubmit cs;
	ch.recvHead(buf);
	std::vector<std::string> temp_vec;
	switch (ch.cmdID())
	{
	case 1://收到Bind请求
		cb.recvBind(buf);
		std::cout << "------------" << std::endl;
		std::cout << "收到Bind请求" << std::endl;
		std::cout << "消息长度：" << std::to_string(ch.msgLength()) << std::endl;
		std::cout << "指令ID:" << std::to_string(ch.cmdID()) << std::endl;
		std::cout << "SN1:" << std::to_string(ch.SN1()) << std::endl;
		std::cout << "SN2:" << std::to_string(ch.SN2()) << std::endl;
		std::cout << "指令号:" << std::to_string(cb.getType()) << std::endl;
		std::cout << "用户名:" << cb.getName() << std::endl;
		std::cout << "密码:" << cb.getPass() << std::endl;
		break;
	case 0x80000001://收到Bind回应
		//memcpy(&temp, pt, 1);
		//pt += 1;

		//result = (int)temp;
		//cout << "收到应答" << endl;

		////cout << "长度：" << a << endl;

		//cout << "长度：" << to_string(hd.msgLength) << endl;
		//cout << "命令ID:" << "80000001" << endl;
		//cout << "命令序列号:" << to_string(hd.SN1) << "," << to_string(hd.SN2) << "," << to_string(hd.SN3) << endl;
		//cout << "命令结果:" << to_string(result) << endl;
		//cout << "----------------" << endl;
		break;
	case 0x80000002://收到unbind回应
		//memcpy(&temp, pt, 1);
		//pt += 1;

		//result = (int)temp;
		//cout << "收到unbind回应" << endl;
		//cout << "长度：" << to_string(hd.msgLength) << endl;
		//cout << "命令ID:" << "80000002" << endl;
		//cout << "命令序列号:" << to_string(hd.SN1) << "," << to_string(hd.SN2) << "," << to_string(hd.SN3) << endl;
		//cout << "----------------" << endl;
		break;
	case 2://收到unbind请求
		std::cout << "----------------" << std::endl;
		std::cout << "收到UnBind请求" << std::endl;
		return 1;
		break;
	case 0x80000003://收到submit回应
		//memcpy(&temp, pt, 1);
		//pt += 1;
		//result = (int)temp;
		//cout << "收到submit回应" << endl;

		////cout << "长度：" << a << endl;

		//cout << "长度：" << to_string(hd.msgLength) << endl;
		//cout << "命令ID:" << "80000003" << endl;
		//cout << "命令序列号:" << to_string(hd.SN1) << "," << to_string(hd.SN2) << "," << to_string(hd.SN3) << endl;
		//cout << "命令结果:" << to_string(result) << endl;
		//cout << "----------------" << endl;
		break;
	case 3://收到submit请求
		cs.recvSubmit(buf);
		std::cout << "--------------" << std::endl;
		std::cout << "收到submit请求" << std::endl;
		std::cout << "发送至手机号：" << std::endl;
		temp_vec = *cs.getPhNums();

		if (temp_vec.size() > 0)
		{
			for (int i = 0; i < temp_vec.size(); i++)
			{
				std::string temp_str = temp_vec[i];
				std::cout << temp_str << std::endl;
			}
		}
		std::cout << "收到手机数量：" <<std::to_string(cs.getUserCount())<< std::endl;
		std::cout << "收到企业代码：" << cs.getCorpId() << std::endl;
		std::cout << "收到消息：" << *cs.getText() << std::endl;

		
		break;




	default:
		break;
	}
	return 0;
}
