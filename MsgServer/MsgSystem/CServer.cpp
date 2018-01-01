#include "stdafx.h"
#include "CServer.h"


CServer::CServer()
{
	local_port = 3200;
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
				
		
				

		/*	shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
			acceptor.accept(*socket);
			DealSockProcess(socket);*/




			//tg.join_all();

		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	
}

using namespace boost;
using boost::asio::ip::tcp;
void CServer::DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	while (true)
	{
		try
		{
		std::string message = to_simple_string(boost::gregorian::day_clock::local_day());

		system::error_code ignored_error;
		socket->write_some(asio::buffer(message), ignored_error);
		//socket->write(asio::buffer(message));

		
		std::cout << message << std::endl;
		
		
		Sleep(200);
		boost::array<char, 128> buf;
		boost::system::error_code error;
		
			size_t len = socket->read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout << "收到客户端时间：";
			//std::cout.write(buf.data(), len);
			std::cout << std::endl;
		}
		catch (const std::exception& x)
		{
			std::cerr << x.what() << std::endl;
			break;
		}
		

	}
}
