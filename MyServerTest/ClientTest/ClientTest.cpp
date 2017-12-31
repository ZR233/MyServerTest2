// ClientTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;
using boost::asio::ip::tcp;
int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 3200);

		tcp::socket socket(io_service);
		socket.connect(end_point);
		while (true)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout << "收到服务器时间：";
			std::cout.write(buf.data(), len);
			std::cout << endl;

			Sleep(200);
			time_t now = time(0);
			std::string message = ctime(&now);

			boost::system::error_code ignored_error;
			socket.write_some(boost::asio::buffer(message), ignored_error);

			std::cout << message << std::endl;


			system("pause");
			
		}

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

