// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <iostream>
//#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>

#include <iostream>
#include <vector>


#include <boost/date_time.hpp>
#include <boost/thread/thread.hpp>
#include <string>
#include <memory>
#include <functional>
#include <boost/bind/bind.hpp>

//日志
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <boost/log/sources/logger.hpp>

#include <boost/log/support/date_time.hpp>

//目录操作
#include<fstream>  
#include<boost/filesystem.hpp>  


//日期
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
// TODO: 在此处引用程序需要的其他头文件


struct	Srequest_from_client {
	char name[16];//登录名
	char pass[16];//密码
	unsigned int msgL;//收到的消息长度
	std::string msg;//收到的消息
	std::vector<std::string> PH_vec;//推送号码
};

