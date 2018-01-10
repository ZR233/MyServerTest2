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
	//取缓存
	std::vector<char>* getBuf();
private:
	unsigned int msg_length;//整条信息长度
	unsigned int cmd_ID;//指令ID
	unsigned int SN_1;
	unsigned int SN_2;
	unsigned int SN_3;
	std::vector<char> head_buf;//储存head buf
	
};

