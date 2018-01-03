#include "stdafx.h"
#include "CResp.h"


CResp::CResp()
{
}


CResp::~CResp()
{
}


// 生成应答   0：接收成功
std::vector<char> CResp::resp(int result)
{
	re_char = (unsigned char)result;
	resp_buf.clear();
	resp_buf.push_back(re_char);
	for (int i = 0; i < 8; i++)
	{
		resp_buf.push_back('\0');
	}
	return resp_buf;
}
