// AsyncServerTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace boost::asio;
using namespace std;

class server
{
	typedef server this_type;
	typedef ip::tcp::acceptor acceptor_type;
	typedef ip::tcp::endpoint endpoint_type;
	typedef ip::tcp::socket socket_type;
	typedef ip::address address_type;
	typedef boost::shared_ptr<socket_type> sock_ptr;

private:
	io_service m_io;
	acceptor_type m_acceptor;

public:
	server() : m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 3200))
	{
		accept();
	}

	void run() { m_io.run(); }

	void accept()
	{
		sock_ptr sock(new socket_type(m_io));
		m_acceptor.async_accept(*sock, boost::bind(&this_type::accept_handler, this, boost::asio::placeholders::error, sock));
	}

	void accept_handler(const boost::system::error_code& ec, sock_ptr sock)
	{
		if (ec)
		{
			return;
		}


		cout << "Client:";
		cout << sock->remote_endpoint().address() << endl;



		sock->async_write_some(buffer("hello asio"), boost::bind(&this_type::write_handler, this, boost::asio::placeholders::error));
		// ������Ϻ��������������io_service����Ϊû���¼���������������
		Sleep(200);


		shared_ptr<vector<char>> str(new vector<char>(100, 0));
		sock->async_read_some(buffer(*str), boost::bind(&this_type::write_handler, this, boost::asio::placeholders::error));


		cout << str << endl;

		accept();
	}

	void write_handler(const boost::system::error_code&ec)
	{
		cout << "send msg complete" << endl;
	}
};

int main()
{
	try
	{
		cout << "Server start." << endl;
		server srv;
		srv.run();
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}

	return 0;
}