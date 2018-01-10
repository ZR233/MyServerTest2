#include "stdafx.h"
#include "CClient.h"
#include "CHead.h"
#include "CBind.h"
#include "CResp.h"

CClient::CClient()
{
	spID = 12345;
	count = 0;
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
		boost::asio::io_service io_service;
		socket_type socket(io_service);
		endpoint_type ep(address_type::from_string(ip_addr), port);

		socket.connect(ep);
		cbd.Binder(username,password);

		std::vector<char> buf;
		chd.header(cbd.getBuf()->size() + 20, 1, spID, count);

		buf.assign(chd.getBuf()->begin(),chd.getBuf()->end());
		buf.insert(buf.end(), cbd.getBuf()->begin(), cbd.getBuf()->end());

		socket.write_some(boost::asio::buffer(buf));
		buf.clear();
		buf.resize(2000);
		size_t len= socket.read_some(boost::asio::buffer(buf));
		cout << "接收长度：" << std::to_string(len) << endl;

		buf.resize(len);
		chd.recvHead(buf);
		++count;
		return cr.recvResp(buf);
	}
	catch (const std::exception&e)
	{
		cout << e.what() << endl;
	}
}
int CClient::unBind()
{

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