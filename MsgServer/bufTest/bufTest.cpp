// bufTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


using std::cout;
using std::endl;
using namespace boost;
using boost::asio::ip::tcp;

int main()
{
	try
	{
		
		asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8801));

		tcp::socket socket(io_service);
		acceptor.accept(socket);			

	

		for (size_t i = 0; ; i++)
		{
			std::vector<char> buf(2000, 0);
			boost::system::error_code error;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			buf.erase(buf.begin() + len, buf.end());
			std::cout << "收到长度：" << std::to_string(len) << std::endl;

			for (size_t i = 0; i < len; i++)
			{
				cout << i + 1 << ":" << std::to_string((unsigned int)buf[i]) << endl;
			}



			std::vector<char> rebuf(29, 0);
			unsigned int result = 0;
			rebuf[20] = (unsigned char)result;

			system::error_code ignored_error;
			int msgL = socket.write_some(asio::buffer(rebuf), ignored_error);
		}
	


	}
	catch (const std::exception& k)
	{
		cout << k.what() << endl;

	}







    return 0;
}

