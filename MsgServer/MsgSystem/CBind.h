#pragma once
class CBind
{
public:
	CBind();
	~CBind();
	// ����Bind
	std::vector<char>* Binder(char *logID, char *PassWord);
	// ����Bind
	void recvBind(std::vector<char> &buf);



private:
	unsigned char logType;//��½���� 1:SP->SMG; 2:SMG->SP; 3:SMG->SMG
	char logName[16];//��¼��
	char logPass[16];//��½����
	char reserve[8];//����
	std::vector<char> bind_buf;//
public:
	// ȡ�û���
	char* getName();
	// ȡ����
	char* getPass();
	// ȡ��¼���͡�
	int getType();
};

