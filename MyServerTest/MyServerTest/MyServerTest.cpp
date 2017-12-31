// MyServerTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

using namespace boost;
using boost::asio::ip::tcp;


void run(shared_ptr<tcp::socket> socket)
{
	while (true)
	{
		time_t now = time(0);
		std::string message = ctime(&now);

		system::error_code ignored_error;
		socket->write_some(asio::buffer(message), ignored_error);

		std::cout << message << std::endl;
		Sleep(200);
		boost::array<char, 128> buf;
		boost::system::error_code error;

		size_t len = socket->read_some(boost::asio::buffer(buf), error);

		if (error == boost::asio::error::eof)
			break; // Connection closed cleanly by peer.
		else if (error)
			throw boost::system::system_error(error); // Some other error.

		std::cout << "�յ��ͻ���ʱ�䣺";
		std::cout.write(buf.data(), len);
		std::cout << std::endl;

	}
}


int main()
{

	try
	{
		asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));

		for (;;)
		{
	/*		tcp::socket socket(io_service);*/
			shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
			acceptor.accept(*socket);
			boost::thread_group tg;
			tg.create_thread(boost::bind(run, socket));
			//boost::thread thrd(run, socket);
			//thrd.join();

			
			tg.join_all();

		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}




	
	
	
	
	return 0;
}

