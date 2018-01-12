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


// 解析收到的信息
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
	case 1://收到Bind请求
		cb.recvBind(buf);
		std::cout << "------------" << std::endl;
		std::cout << "收到Bind请求" << std::endl;
		std::cout << "消息长度：" << std::to_string(ch.msgLength()) << std::endl;
		std::cout << "指令ID:" << std::to_string(ch.cmdID()) << std::endl;
		std::cout << "SN1:" << std::to_string(ch.SN1()) << std::endl;
		std::cout << "SN2:" << std::to_string(ch.SN2()) << std::endl;
		std::cout << "SN3:" << std::to_string(ch.SN3()) << std::endl;
		std::cout << "指令号:" << std::to_string(cb.getType()) << std::endl;
		std::cout << "用户名:" << cb.getName() << std::endl;
		std::cout << "密码:" << cb.getPass() << std::endl;
		if ((std::string(cb.getName()) == user_name)&&((std::string(cb.getPass()) == password)))
		{
			std::cout << "登陆成功" << std::endl;
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
			throw std::runtime_error("用户名密码错误");
		}
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
		std::cout << "收到submit请求" << std::endl;
		std::cout << "发送至手机号：" << std::endl;
		if (cs.getPhNums()->size() != 0)
		{
			temp_vec = *cs.getPhNums();
		}
		else
		{
			throw std::runtime_error("没有发送手机号");
		}

		if (temp_vec.size() > 0)
		{
			for (int i = 0; i < temp_vec.size(); i++)
			{
				std::string temp_str = temp_vec[i];
				if (temp_str.size() != 11)
				{
					std::cout << "手机号格式错误:" ;
				}
				else
				{
					request_from_client.PH_vec.push_back(temp_str);
				}
				std::cout << temp_str << std::endl;
			}
		}
		std::cout << "收到手机数量：" <<std::to_string(cs.getUserCount())<< std::endl;
		std::cout << "收到企业代码：" << cs.getCorpId() << std::endl;
		std::cout << "收到消息：" << *cs.getText() << std::endl;

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
