#ifndef __EXPRESS_INFO_2019_
#define __EXPRESS_INFO_2019_

#include <string>
//#include "ExpressInfoManage.h"
using namespace std;
class ExpressInfoManage;

class ExpressInfo {
private:
	string tracking_number; //快递单号 [20]  不可重复唯一
	int type;			//快递类别[1或者2]        [1]为派送单，2为收件单
	string sender_address; //寄送人地址[50]
	string sender_tel; //寄送人电话[20]
	string sender_remarks; //寄件人备注[50]
	string recipient_address; //收件人地址[50]
	string recipient_tel;// 号码
	string recipient_remarks;//备注

	string receipt_date;//2019-01-20  [10] 收件日期
	string delivery_date;//2019-01-19 [10] 派送日期

	int signinfo;//是否签收  1/0 [5]  1签收、0未签收
	double money;//10位		[10]
	bool  difficult_made; //是否为疑难件 [5] 1是 0否 
	string diff_remarks; //[50] 疑难件备注
	
	ExpressInfo * next; // 存储下一个节点位置

	void InputFromConsole(); //控制读入

	istream &  InputFromFile(istream & in); //文件读入
	void InputFromConsole(string &c); //用户修改，指定id   重构上述函数修改时候使用

	void ShowOnConsole(); //在控制台中打印对象


public:
	//构造函数
	ExpressInfo();
	ExpressInfo(ExpressInfo & info);
	~ExpressInfo();	//析构函数
		//重载赋值构造函数
	ExpressInfo& operator=(const ExpressInfo & info);
	//友元类
	friend ExpressInfoManage;

	

};

#endif
