#include "stdafx.h"
#include "CClient.h"
#include "CHead.h"
#include "CBind.h"
#include "CResp.h"

CClient::CClient()
{
	ip_addr = "127.0.0.1";
	port = 8801;
	spID = 12345;
	count = 0;
	socket = nullptr;
	using boost::asio::ip::tcp;
	try
	{
		ep = endpoint_type(address_type::from_string(ip_addr), port);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}


CClient::~CClient()
{
}


// 向服务器发送bind
int CClient::bind(std::string username, std::string password)
{
	using std::cout;
	using std::endl;
	try
	{
		using boost::asio::ip::tcp;


		typedef boost::asio::ip::tcp::endpoint endpoint_type;
		typedef boost::asio::ip::tcp::socket socket_type;
		typedef boost::asio::ip::address address_type;


		CHead chd;
		CBind cbd;
		CResp cr;
		socket = new socket_type(io_service);
		socket->connect(ep);
		cbd.Binder(username,password);

		std::vector<char> buf;
		chd.header(cbd.getBuf()->size() + 20, 1, spID, count);

		buf.assign(chd.getBuf()->begin(),chd.getBuf()->end());
		buf.insert(buf.end(), cbd.getBuf()->begin(), cbd.getBuf()->end());

		socket->write_some(boost::asio::buffer(buf));
		buf.clear();
		buf.resize(2000);
		size_t len= socket->read_some(boost::asio::buffer(buf));
		cout << "接收长度：" << std::to_string(len) << endl;

		buf.resize(len);
		chd.recvHead(buf);
		if (count>99999)
		{
			count=0;
		}
		++count;
		return cr.recvResp(buf);
	}
	catch (const std::exception&e)
	{
		cout << e.what() << endl;
		throw e;
	}
}
int CClient::unBind()
{
	CHead chd;
	CResp cr;
	std::vector<char> buf;
	chd.header(20, 2, spID, count);

	buf.assign(chd.getBuf()->begin(), chd.getBuf()->end());
	
	socket->write_some(boost::asio::buffer(buf));
	buf.clear();
	buf.resize(2000);
	size_t len = socket->read_some(boost::asio::buffer(buf));
	std::cout << "接收长度：" << std::to_string(len) << std::endl;

	buf.resize(len);
	chd.recvHead(buf);

	if (count>99999)
	{
		count = 0;
	}
	++count;
	if (cr.recvResp(buf) == 0)
	{
		try
		{
			delete socket;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
	} 
	return 0;
}



void CClient::setIp(std::string &ip)
{
	ip_addr = ip;
}

void CClient::setPort(int port)
{
	this->port = port;
}

//void CClient::setLogID(std::string &logID)
//{
//	this->logID = logID;
//}
//void CClient::setPassword(std::string &password)
//{
//	this->password = password;
//}