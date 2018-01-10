#pragma once
class CBind
{
public:
	CBind();
	~CBind();
	// 制作Bind
	std::vector<char>* Binder(char *logID, char *PassWord);
	std::vector<char>* Binder(std::string &logID, std::string &PassWord);
	// 解析Bind
	void recvBind(std::vector<char> &buf);



private:
	unsigned char logType;//登陆类型 1:SP->SMG; 2:SMG->SP; 3:SMG->SMG
	char logName[16];//登录名
	char logPass[16];//登陆密码
	char reserve[8];//保留
	std::vector<char> bind_buf;//
public:
	// 取用户名
	char* getName();
	// 取密码
	char* getPass();
	// 取登录类型。
	int getType();
	std::vector<char>* getBuf();
};

