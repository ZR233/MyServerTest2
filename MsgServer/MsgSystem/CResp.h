#pragma once

//用于生成应答buf
class CResp
{
public:
	CResp();
	~CResp();
	// 生成应答   0：接收成功
	std::vector<char> resp(int result);
private:
	std::vector<char> resp_buf;
	unsigned char re_char;
};

