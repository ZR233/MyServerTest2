#pragma once
// Here we define our application severity levels.
enum severity_level
{
	normal,
	notification,
	warning,
	error,
	critical
};

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
	static const char* const str[] =
	{
		"normal",
		"notification",
		"warning",
		"error",
		"critical"
	};
	if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
		strm << str[lvl];
	else
		strm << static_cast< int >(lvl);
	return strm;
}

//初始化日志
class CLogInit
{
public:
	CLogInit();
	~CLogInit();
	boost::log::sources::severity_logger< severity_level > slg;
};

