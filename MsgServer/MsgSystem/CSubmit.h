#pragma once
class CSubmit
{
public:
	CSubmit();
	~CSubmit();
private:
	char SP_number[21];//SP����� 
	char charge_number[21];//���Ѻ��룬�ֻ�����ǰ�ӡ�86�������־�����ҽ���Ⱥ���Ҷ��û��շ�ʱΪ�գ�
							//���Ϊ�գ����������Ϣ�����ķ�����UserNumber������û�֧����
							//���Ϊȫ���ַ�����000000000000000000000������ʾ��������Ϣ�����ķ�����SP֧����*/
	unsigned int user_count;// ������ֻ�������Ϣ�����100
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


	std::vector<char> sub_buf;
	std::vector<std::string> num;//�ֻ���vector
public:
	// ����submit buf
	std::vector<char>* Submiter(std::vector<std::string> userNum, char* msg, int msg_size);
	// ����submit
	void recvSubmit(std::vector<char> &buf);


	// ȡ�������ֻ���
	std::vector<std::string>* getPhNums();
	// ȡ����Ϣ����
	std::string* getText();
	// ȡ�ֻ�������
	int getUserCount();
	// �õ���ҵ����
	std::string getCorpId();
};

