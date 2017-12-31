// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;
class shared                                    //一个拥有shared_ptr的类    
{
private:
	shared_ptr<int> p;                          //shared_ptr成员变量    
public:
	shared(shared_ptr<int> p_) :p(p_) {}          //构造函数初始化shared_ptr        
	void print()                                //输出shared_ptr的引用计数和指向的值        
	{
		cout << "count:" << p.use_count()
			<< "v =" << *p << endl;
	}
};
void print_func(shared_ptr<int> p)                //使用shared_ptr作为函数参数    
{
	//同样输出shared_ptr的引用计数和指向的值        
	cout << "count:" << p.use_count()
		<< " v=" << *p << endl;
}
int main()
{
	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);                        //构造两个自定义类         
	s1.print();
	s2.print();
	*p = 20;                                    //修改shared_ptr所指的值        
	print_func(p);
	s1.print();
}


