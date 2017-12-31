// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;
class shared                                    //һ��ӵ��shared_ptr����    
{
private:
	shared_ptr<int> p;                          //shared_ptr��Ա����    
public:
	shared(shared_ptr<int> p_) :p(p_) {}          //���캯����ʼ��shared_ptr        
	void print()                                //���shared_ptr�����ü�����ָ���ֵ        
	{
		cout << "count:" << p.use_count()
			<< "v =" << *p << endl;
	}
};
void print_func(shared_ptr<int> p)                //ʹ��shared_ptr��Ϊ��������    
{
	//ͬ�����shared_ptr�����ü�����ָ���ֵ        
	cout << "count:" << p.use_count()
		<< " v=" << *p << endl;
}
int main()
{
	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);                        //���������Զ�����         
	s1.print();
	s2.print();
	*p = 20;                                    //�޸�shared_ptr��ָ��ֵ        
	print_func(p);
	s1.print();
}


