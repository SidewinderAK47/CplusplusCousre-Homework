#include "ExpressInfo.h"

#include <iostream>





//默认构造函数
ExpressInfo::ExpressInfo() {
	delivery_date = "";
	tracking_number = "";
	type = 0;
	sender_address = "";
	sender_tel = "";
	sender_remarks = "";
	recipient_address = "";
	recipient_tel = "";
	recipient_remarks = "";
	receipt_date = "";
	delivery_date = "";
	signinfo = false;
	money = 0;
	difficult_made = "";
	diff_remarks = "";
}
//析构函数
ExpressInfo::~ExpressInfo() {

}
//拷贝构造函数
ExpressInfo::ExpressInfo(ExpressInfo & info) {
	this->delivery_date = info.delivery_date;
	this->tracking_number = info.tracking_number;
	this->type = info.type;
	this->sender_address = info.sender_address;
	this->sender_tel = info.sender_tel;
	this->sender_remarks = info.sender_remarks;
	this->recipient_address = info.recipient_address;
	this->recipient_tel = info.recipient_tel;
	this->recipient_remarks = info.recipient_remarks;
	this->receipt_date = info.receipt_date;
	this->delivery_date = info.delivery_date;
	this->signinfo = info.signinfo;
	this->money = info.money;
	this->difficult_made = info.difficult_made;
	this->diff_remarks = info.diff_remarks;
	//指针不变
}

ExpressInfo& ExpressInfo::operator=(const ExpressInfo & rinfo) {
	if (this == &rinfo) {
		return *this;
	}
	this->delivery_date = rinfo.delivery_date;
	this->tracking_number = rinfo.tracking_number;
	this->type = rinfo.type;
	this->sender_address = rinfo.sender_address;
	this->sender_tel = rinfo.sender_tel;
	this->sender_remarks = rinfo.sender_remarks;
	this->recipient_address = rinfo.recipient_address;
	this->recipient_tel = rinfo.recipient_tel;
	this->recipient_remarks = rinfo.recipient_remarks;
	this->receipt_date = rinfo.receipt_date;
	this->delivery_date = rinfo.delivery_date;
	this->signinfo = rinfo.signinfo;
	this->money = rinfo.money;
	this->difficult_made = rinfo.difficult_made;
	this->diff_remarks = rinfo.diff_remarks;
	return *this;

}
istream & ExpressInfo::InputFromFile(istream & in) {
	in >> tracking_number;
	in >> type;
	in >> sender_address;
	in >> sender_tel;
	in >> sender_remarks;
	in >> recipient_address;
	in >> recipient_tel;
	in >> recipient_remarks;
	in >> receipt_date;
	in >> delivery_date;
	in >> signinfo;
	in >> money;
	in >> difficult_made;
	in >> diff_remarks;
	return in;
}
void ExpressInfo::InputFromConsole() {
	cout << "\t\t请输入快递单号<唯一>：";
	cin >> tracking_number;
	cout << "\t\t快递类别<派送1/收件单2>：";
	cin >> type;
	cout << "\t\t寄送人地址：";
	cin >> sender_address;
	cout << "\t\t寄送人电话：";
	cin >> sender_tel;
	cout << "\t\t寄件人备注：";
	cin >> sender_remarks;
	cout << "\t\t收件人地址：";
	cin >> recipient_address;
	cout << "\t\t收件人电话：";
	cin >> recipient_tel;
	cout << "\t\t收件人备注：";
	cin >> recipient_remarks;
	cout << "\t\t收件日期<yyyy-MM-dd>：";
	cin >> receipt_date;
	cout << "\t\t派送日期<yyyy-MM-dd>：";
	cin >> delivery_date;
	cout << "\t\t签收信息<是1/否0>：";
	cin >> signinfo;
	cout << "\t\t金额：";
	cin >> money;
	cout << "\t\t是否疑难件<是1/否0>：";
	cin >> difficult_made;
	if (difficult_made == 0) {
		diff_remarks = "无";
		return;
	}
	cout << "\t\t疑难件备注：";
	cin >> diff_remarks;
}
 //用户修改，指定id
void ExpressInfo::InputFromConsole(string &c) {
	tracking_number = c;
	cout << "\t\t快递类别<派送1/收件单2>：";
	cin >> type;
	cout << "\t\t寄送人地址：";
	cin >> sender_address;
	cout << "\t\t寄送人电话：";
	cin >> sender_tel;
	cout << "\t\t寄件人备注：";
	cin >> sender_remarks;
	cout << "\t\t收件人地址：";
	cin >> recipient_address;
	cout << "\t\t收件人电话：";
	cin >> recipient_tel;
	cout << "\t\t收件人备注：";
	cin >> recipient_remarks;
	cout << "\t\t收件日期<yyyy-MM-dd>：";
	cin >> receipt_date;
	cout << "\t\t派送日期<yyyy-MM-dd>：";
	cin >> delivery_date;
	cout << "\t\t签收信息<是1/否0>：";
	cin >> signinfo;
	cout << "\t\t金额：";
	cin >> money;
	cout << "\t\t是否疑难件<是1/否0>：";
	cin >> difficult_made;
	if (difficult_made == 0) {
		diff_remarks = "无";
		return;
	}
	cout << "\t\t疑难件备注：";
	cin >> diff_remarks;
}

void ExpressInfo::ShowOnConsole()
{
	string difft = difficult_made == true ? "是" : "否";
	cout << "\t\t\t\t快递单号：" << tracking_number << endl
		<< "\t\t\t\t快递类别：" << (type==1? "派送单":"收件单" )<< endl
		<< "\t\t\t\t寄送人地址：" << sender_address << endl
		<< "\t\t\t\t寄送人电话：" << sender_tel << endl
		<< "\t\t\t\t寄送人备注信息：" << sender_remarks << endl
		<< "\t\t\t\t收件人地址：" << recipient_address << endl
		<< "\t\t\t\t收件人电话：" << recipient_tel << endl
		<< "\t\t\t\t收件人备注信息：" << recipient_remarks << endl
		<< "\t\t\t\t收件日期：" << receipt_date << endl
		<< "\t\t\t\t派送日期：" << delivery_date << endl
		<< "\t\t\t\t签收信息：" << (signinfo==1? "已签收":"未签收" ) << endl
		<< "\t\t\t\t金额：" << money << endl
		<< "\t\t\t\t是否疑难件：" << difft<< endl
		<< "\t\t\t\t疑难件备注：" << diff_remarks << endl;
}
