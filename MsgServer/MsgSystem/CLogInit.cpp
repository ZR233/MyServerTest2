#include "stdafx.h"
#include "CLogInit.h"





namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;



CLogInit::CLogInit()
{
	/*using namespace boost::gregorian;
	using namespace boost::posix_time;*/

	boost::gregorian::date today = boost::gregorian::day_clock::local_day(); // today; // 获取今天日期;


	std::string year = std::to_string(today.year());



	if (!boost::filesystem::exists("Log"))
	{
		boost::filesystem::create_directories("Log");
	}
	if (!boost::filesystem::exists("Log/"+ year))
	{
		boost::filesystem::create_directories("Log/"+ year);
	}







	// This is a simple tutorial/example of Boost.Log usage

	// The first thing we have to do to get using the library is
	// to set up the logging sinks - i.e. where the logs will be written to.
	logging::add_console_log(std::clog, keywords::format = "%TimeStamp%: %Message%");

	// One can also use lambda expressions to setup filters and formatters
	logging::add_file_log
	(
		"Log/log_%Y-%m-%d_%N.log",
		keywords::filter = expr::attr< severity_level >("Severity") >= warning,
		keywords::format = expr::stream
		<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
		/*<< " [" << expr::format_date_time< attrs::timer::value_type >("Uptime", "%O:%M:%S")
		<< "] [" << expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
		<< "] */
		<<"<" << expr::attr< severity_level >("Severity")
		<< "> " << expr::message
		/*
		keywords::format = expr::format("%1% [%2%] [%3%] <%4%> %5%")
		% expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
		% expr::format_date_time< attrs::timer::value_type >("Uptime", "%O:%M:%S")
		% expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
		% expr::attr< severity_level >("Severity")
		% expr::message
		*/
	);

	// Also let's add some commonly used attributes, like timestamp and record counter.
	logging::add_common_attributes();
	logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());

	BOOST_LOG_FUNCTION();

	// Now our logs will be written both to the console and to the file.
	// Let's do a quick test and output something. We have to create a logger for this.
	src::logger lg;

	// And output...
	BOOST_LOG(lg) << "Hello, World!";

	// Now, let's try logging with severity
	//src::severity_logger< severity_level > slg;

	// Let's pretend we also want to profile our code, so add a special timer attribute.
	slg.add_attribute("Uptime", attrs::timer());

	BOOST_LOG_SEV(slg, normal) << "A normal severity message, will not pass to the file";
	BOOST_LOG_SEV(slg, warning) << "A warning severity message, will pass to the file";
	BOOST_LOG_SEV(slg, error) << "An error severity message, will pass to the file";
}


CLogInit::~CLogInit()
{
}
