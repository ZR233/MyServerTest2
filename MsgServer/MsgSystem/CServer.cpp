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

//���÷������˿�
void CServer::setPort()
{
}

using namespace boost;
using boost::asio::ip::tcp;
// ����������
void CServer::run()
{

	BOOST_LOG_SEV(CI.slg, normal) << "A normal severity message, will not pass to the file";
	BOOST_LOG_SEV(CI.slg, warning) << "������������%Y";
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
			BOOST_LOG_SEV(CI.slg, warning) << "�ͻ�������";
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

			//����
			std::vector<char> buf(1000, 0);


			boost::system::error_code error;
			size_t len = socket->read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout << "�յ����ȣ�" << std::to_string(len) << std::endl;

			cr.recv(buf);






			//����
			system::error_code ignored_error;
			int msgL = socket->write_some(asio::buffer("dawdawd"), ignored_error);

			if (ignored_error == boost::asio::error::eof)
			{
				BOOST_LOG_SEV(CI.slg, warning) << "Զ�����ӶϿ�";
				break; // Connection closed cleanly by peer.
			}
			else if (ignored_error)
				throw boost::system::system_error(ignored_error); // Some other error.


			std::cout << "���ͳ��ȣ�" << std::to_string(msgL) << std::endl;




		}
		catch (const std::exception& x)
		{
			std::cerr << x.what() << std::endl;
			break;
		}


	}
}
