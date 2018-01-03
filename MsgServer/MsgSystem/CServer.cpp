#include "stdafx.h"
#include "CServer.h"
#include "CLogInit.h"
#include "CRecver.h"
#include "CInitialization.h"
#include "ServerBuf.h"

CServer::CServer()
{
	
	CInitialization init;
	init.init();
	local_port = init.client_port;

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
	BOOST_LOG_SEV(CI.slg, warning) << "����������";
	asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), local_port));
	boost::thread_group tg;
	tg.create_thread(boost::bind(&CServer::seeMsgs, this));
	while (true)
	{
		try
		{

			shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
			acceptor.accept(*socket);

			tg.create_thread(boost::bind(&CServer::DealSockProcess, this, socket));
			BOOST_LOG_SEV(CI.slg, warning) << "�ͻ�������"<<socket->remote_endpoint().address();
		}

		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			BOOST_LOG_SEV(CI.slg, warning) << e.what();
		}
	}
	tg.join_all();

}

using namespace boost;
using boost::asio::ip::tcp;
void CServer::DealSockProcess(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	CRecver cr;
	while (true)
	{
		try
		{
			//std::string message = to_simple_string(boost::gregorian::day_clock::local_day());
			//����----------------------------------------------
			std::vector<char> buf(1000, 0);
			boost::system::error_code error;
			size_t len = socket->read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // ���ӱ��Է��Ͽ�
			else if (error)
			{ 
				throw boost::system::system_error(error); // Some other error.
				break;
			}
				
			std::cout << "�յ����ȣ�" << std::to_string(len) << std::endl;

			std::vector<char> temp_re_vec = cr.recv(buf);//�������
			//����---------------------------------------------------------
			system::error_code ignored_error;
			int msgL = socket->write_some(asio::buffer(temp_re_vec), ignored_error);

			if (ignored_error == boost::asio::error::eof)
			{
				BOOST_LOG_SEV(CI.slg, warning) << "Զ�����ӶϿ�";
				break; // ���ӱ��Է��Ͽ�
			}
			else if (ignored_error) 
			{
				throw boost::system::system_error(ignored_error); // Some other error.
				break;
			}
				
			std::cout << "���ͳ��ȣ�" << std::to_string(msgL) << std::endl;
		}
		catch (const std::exception& x)
		{
			std::cerr << x.what() << std::endl;
			BOOST_LOG_SEV(CI.slg, warning) << x.what();
			break;
		}


	}
}


// �鿴�ѷ�����Ϣ
void CServer::seeMsgs()
{
	while (true)
	{
		using namespace std;
		cout << "����1���Բ鿴���ϴ�ȡ��Ϣ�������յ���������Ϣ" << endl;
		string str;
		getline(cin, str);
		if (str == "exit")
		{
			break;
		}
		else if (str == "1")
		{
			//�ѻ�õĻ���
			std::vector<Srequest_from_client> vec;
			boost::mutex mu;
			try
			{
				using namespace std;

				mu.lock();
				vec = request_from_client_vec;
				request_from_client_vec.clear();
				mu.unlock();


			}
			catch (const std::exception&)
			{
				mu.unlock();
			}

			cout << "������������������������������������" << endl;
			cout << "���˹�" << to_string(vec.size()) << "����Ϣ" << endl;

			cout << "������������������������������������" << endl;

			BOOST_LOG_SEV(CI.slg, warning) << "����˲鿴ָ����Ϣ";

			if (vec.size() == 0)
			{
				cout << "û����Ϣ" << endl;
			}
			else
			{
				for (int i = 0; i < vec.size(); i++)
				{
					string str_name(vec[i].name);
					cout << "�û���" << str_name << endl;
					string str_msg(vec[i].msg);
					cout << "��Ϣ��" << str_msg << endl;
					cout << "������������������������������������" << endl;
				}
				string str_temp(vec[0].msg);
			}
		}
		Sleep(200);
	}
	
	return;
}
