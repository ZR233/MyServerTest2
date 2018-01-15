#include "stdafx.h"
#include "CServer.h"
#include "CLogInit.h"
#include "CRecver.h"
#include "CInitialization.h"
#include "ServerBuf.h"

using std::cout;
using std::endl;
CServer::CServer()
{
	
	CInitialization init;
	init.init();
	local_port = init.client_port;
	CMPP20_long_in_port = 7890;
	CMPP20_short_in_port = 7900;
	CMPP20_short_out_port = 9168;
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

void CServer::start()
{
	thread lis(bind(&CServer::SGIPLis, this));
	thread see_msg(bind(&CServer::seeMsgs, this));

	lis.join();
	see_msg.join();

}

void CServer::SGIPLis()
{
	try
	{
		BOOST_LOG_SEV(CI.slg, warning) << "服务器开始监听";
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
				BOOST_LOG_SEV(CI.slg, warning) << "客户端连接" << socket->remote_endpoint().address();
			}

			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				BOOST_LOG_SEV(CI.slg, warning) << e.what();
				break;
			}
		}
		tg.join_all();
	}
	catch (const std::exception& k)
	{
		cout << k.what()<< endl;
		BOOST_LOG_SEV(CI.slg, warning) << k.what();
	}
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
			//接收----------------------------------------------			
			std::vector<char> buf(2000, 0);
			boost::system::error_code error;
			size_t len = socket->read_some(boost::asio::buffer(buf), error);
			buf.erase(buf.begin()+len, buf.end());
			if (error == boost::asio::error::eof)
				break; // 连接被对方断开
			else if (error)
			{ 
				throw boost::system::system_error(error); // Some other error.
				break;
			}
			std::cout << "收到长度：" << std::to_string(len) << std::endl;
			
			buf.resize(len);
			std::vector<char> temp_re_vec = cr.recv(buf);//处理接收
		
			
			//发送---------------------------------------------------------
			system::error_code ignored_error;
			int msgL = socket->write_some(asio::buffer(temp_re_vec), ignored_error);

			if (ignored_error == boost::asio::error::eof)
			{
				BOOST_LOG_SEV(CI.slg, warning) << "远程连接断开";
				break; // 连接被对方断开
			}
			else if (ignored_error) 
			{
				throw boost::system::system_error(ignored_error); // Some other error.
				break;
			}
				
			std::cout << "发送长度：" << std::to_string(msgL) << std::endl;
		}
		catch (const std::exception& x)
		{
			std::cerr << x.what() << std::endl;
			BOOST_LOG_SEV(CI.slg, warning) << x.what();
			socket->close();
			break;
		}


	}
}


// 查看已发来信息
void CServer::seeMsgs()
{
	while (true)
	{
		using namespace std;
		cout << "输入1可以查看从上次取信息至现在收到的所有信息" << endl;
		string str;
		getline(cin, str);
		if (str == "exit")
		{
			break;
		}
		else if (str == "1")
		{
			//已获得的缓存
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

			cout << "——————————————————" << endl;
			cout << "至此共" << to_string(vec.size()) << "条信息" << endl;

			cout << "——————————————————" << endl;

			BOOST_LOG_SEV(CI.slg, warning) << "服务端查看指令信息";

			if (vec.size() == 0)
			{
				cout << "没有消息" << endl;
			}
			else
			{
				for (int i = 0; i < vec.size(); i++)
				{
					string str_name(vec[i].name);
					cout << "用户：" << str_name << endl;
					string str_msg(vec[i].msg);
					cout << "消息：" << str_msg << endl;
					cout << "——————————————————" << endl;
				}
				string str_temp(vec[0].msg);
			}
		}
		Sleep(200);
	}
	
	return;
}


// 开启监听CMPP2.0 长连接
void CServer::CMPP20ListenL()
{
	try
	{
		BOOST_LOG_SEV(CI.slg, warning) << "服务器开始监听";
		asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), CMPP20_short_in_port));
		boost::thread_group tg;

		while (true)
		{
			try
			{
				shared_ptr<tcp::socket> socket(new tcp::socket(io_service));
				acceptor.accept(*socket);

				tg.create_thread(boost::bind(&CServer::DealSockProcess, this, socket));
				BOOST_LOG_SEV(CI.slg, warning) << "客户端连接" << socket->remote_endpoint().address();
			}

			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				BOOST_LOG_SEV(CI.slg, warning) << e.what();
				break;
			}
		}
		tg.join_all();
	}
	catch (const std::exception& k)
	{
		cout << k.what() << endl;
		BOOST_LOG_SEV(CI.slg, warning) << k.what();
	}
}
