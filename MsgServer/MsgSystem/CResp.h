#pragma once

//��������Ӧ��buf
class CResp
{
public:
	CResp();
	~CResp();
	// ����Ӧ��   0�����ճɹ�
	std::vector<char> resp(int result);
	int recvResp(std::vector<char> &buf);
private:
	std::vector<char> resp_buf;
	unsigned char re_char;
};

