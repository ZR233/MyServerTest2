#pragma once
class CHead
{
public:
	CHead();
	~CHead();
	// ������Ϣͷ
	std::vector<char>* header(int msgL, int CID, int spID, int num);
	// ������Ϣͷ
	void recvHead(std::vector<char> &buf);
	// ��Ϣ����
	unsigned int msgLength();
	// ָ��ID
	unsigned int cmdID();
	// SN1
	unsigned int SN1();
	// SN2
	unsigned int SN2();
	// SN3
	unsigned int SN3();
	//ȡ����
	std::vector<char>* getBuf();
private:
	unsigned int msg_length;//������Ϣ����
	unsigned int cmd_ID;//ָ��ID
	unsigned int SN_1;
	unsigned int SN_2;
	unsigned int SN_3;
	std::vector<char> head_buf;//����head buf
	
};

