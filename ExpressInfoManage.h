# ifndef __EXPRESS_INFO_MANAGE_
# define __EXPRESS_INFO_MANAGE_
#include "ExpressInfo.h"
#include <fstream>
//管理类
class ExpressInfoManage {
public:
	ExpressInfoManage();
	~ExpressInfoManage();

	void ShowMenu();
	void addItem();
	void Display();
	void ModifyItem();
	void RomoveItem();
	void Find();
	void Statistics();
	void DeliverySelect();
	void Sort();
private:
	ExpressInfo *Head ,*End;//头指针,尾指针
	ifstream fin;
	ofstream fout;
	void SaveToFile();
	int ListCount();
	ExpressInfo* FindID(string &id);


	void SortByDeliveryDate(bool up);
	void SortByRecipientDate(bool up);
	void SortByType(bool up);
	void SortByMoney(bool up);
	//ExpressInfo& operator[](int i);


	
	///void showListOnConsole();
	int DateStringtoInt(string & date);

};
class OrdernumMoney {
public:
	int order_num;
	double money;
	OrdernumMoney(int a, double m);
	OrdernumMoney();
};

#endif
