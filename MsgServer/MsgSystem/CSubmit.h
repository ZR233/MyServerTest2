#pragma once


//用于生成submit buf
class CSubmit
{
public:
	CSubmit();
	~CSubmit();
private:
	char SP_number[21];//SP接入号 
	char charge_number[21];//付费号码，手机号码前加“86”国别标志；当且仅当群发且对用户收费时为空；
							//如果为空，则该条短消息产生的费用由UserNumber代表的用户支付；
							//如果为全零字符串“000000000000000000000”，表示该条短消息产生的费用由SP支付。*/
	unsigned int user_count;// 向多少手机发送信息，最多100
	char corp_Id[5];
	char service_type[10];
	unsigned int fee_type;
	char fee_value[6];
	char given_value[6];
	char agent_flag;
	char morelateto_MT_flag;
	char priority;
	char expire_time[16];
	char schedule_time[16];
	char report_flag;
	char TP_pid;
	char TP_udhi;
	char message_coding;
	char message_type;
	int message_length;
	std::string message_content;


	std::vector<char> sub_buf;//submit发送缓存
	std::vector<std::string> num;//手机号vector
public:
	// 生成submit buf
	std::vector<char>* Submiter(std::vector<std::string> &userNum, std::string &msg);
	// 接收submit
	void recvSubmit(std::vector<char> &buf);


	// 取发送至手机号
	std::vector<std::string>* getPhNums();
	// 取短消息长度
	int getTextL();
	// 取短消息内容
	std::string* getText();
	// 取手机号数量
	int getUserCount();
	// 得到企业代码
	std::string getCorpId();

	std::vector<char>* getBuf();
};

