#pragma once

//��������Ӧ��buf
class CResp
{
public:
	CResp();
	~CResp();
	// ����Ӧ��   0�����ճɹ�
	std::vector<char> resp(int result);
private:
	std::vector<char> resp_buf;
	unsigned char re_char;
};
