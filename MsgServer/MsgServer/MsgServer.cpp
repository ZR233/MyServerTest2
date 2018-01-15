// MsgServer.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<char> v;
	v.push_back('2');
	
	char a[] = "1234";
	char *b = a;
	v.assign(&a[0], &a[4]);
	v.push_back(0);
	cout << &v[0] << endl;
	cout << v.size()<<endl;

	vector<char> c;
	c.push_back('5');
	c.push_back('6');
	v.insert(v.end(), c.begin(), c.end());
	cout << &v[0] << endl;
	cout << v.size() << endl;
	string str = "12345";
	//c.resize(str.size());
	c.assign(str.begin(), str.end());
	c.resize(6);
	cout << "c:"<<&c[0] << endl;
	cout << c.size() << endl;

	vector<int> a_in;
	a_in.resize(50);
	for (size_t i = 0; i < 50; i++)
	{
		cout << a_in[i];
	}
	cout << endl;

	string str2 = "我";
	cout << str2.length() << endl;
    return 0;
}

