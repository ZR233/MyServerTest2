#pragma once
class CHead
{
public:
	CHead();
	~CHead();
	// 制作消息头
	std::vector<char>* header(int msgL, int CID, int spID, int num);
	// 解析消息头
	void recvHead(std::vector<char> &buf);
	// 消息长度
	unsigned int msgLength();
	// 指令ID
	unsigned int cmdID();
	// SN1
	unsigned int SN1();
	// SN2
	unsigned int SN2();
	// SN3
	unsigned int SN3();

private:
	unsigned int msg_length;
	unsigned int cmd_ID;
	unsigned int SN_1;
	unsigned int SN_2;
	unsigned int SN_3;
	std::vector<char> head_buf;
	
};

