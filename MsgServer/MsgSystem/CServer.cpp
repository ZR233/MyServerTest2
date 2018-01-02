#include "stdafx.h"
#include "CServer.h"
#include "CLogInit.h"
#include "CRecver.h"

CServer::CServer()
{
	local_port = 8801;

}


CServer::~CServer()
{
}

//设置服务器端口
void CServer::setPort()
{
}

using namespace boost;
using boost::asio::ip::tcp;
// 开启服务器
void CServer::run()
{

	BOOST_LOG_SEV(CI.slg, normal) << "A normal severity message, will not pass to the file";
	BOOST_LOG_SEV(CI.slg, warning) << "服务器启动：%Y";
	BOOST_LOG_SEV(CI.slg, error) << "An error severity message, will pass to the file";
	asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), local_port));
	boost::thread_group tg;
	while (true)
	{
		try
		{

			shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
			acceptor.accept(*socket);

			tg.create_thread(boost::bind(&CServer::DealSockProcess, this, socket));
			BOOST_LOG_SEV(CI.slg, warning) << "客户端连接";
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	tg.join_all();

}

using namespace boost;
using boost::asio::ip::tcp;
void CServer::DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	while (true)
	{
		try
		{
			CRecver cr;
			//std::string message = to_simple_string(boost::gregorian::day_clock::local_day());

			//接收
			std::vector<char> buf(1000, 0);


			boost::system::error_code error;
			size_t len = socket->read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout << "收到长度：" << std::to_string(len) << std::endl;

			cr.recv(buf);






			//发送
			system::error_code ignored_error;
			int msgL = socket->write_some(asio::buffer("dawdawd"), ignored_error);

			if (ignored_error == boost::asio::error::eof)
			{
				BOOST_LOG_SEV(CI.slg, warning) << "远程连接断开";
				break; // Connection closed cleanly by peer.
			}
			else if (ignored_error)
				throw boost::system::system_error(ignored_error); // Some other error.


			std::cout << "发送长度：" << std::to_string(msgL) << std::endl;




		}
		catch (const std::exception& x)
		{
			std::cerr << x.what() << std::endl;
			break;
		}


	}
}
