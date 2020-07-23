#include "ExpressInfoManage.h"
#include <iostream>
#include <iomanip>
#include <map>
//默认构造函数,构造时从文件中读取数据
ExpressInfoManage::ExpressInfoManage() {
	Head = new ExpressInfo();
	Head->next = new ExpressInfo();
	End = Head->next;

	fin.open("data.txt",ios::in);
	if (!fin.is_open()) {
		cout << "\t\t这是一个刚初始化的系统，无快递单号信息，请先输入信息~" << endl;
	}
	else {
		//
		while (End->InputFromFile(fin)) {
			//End->InputFromFile(fin);

			End->next = new ExpressInfo;
			End = End->next;

		}
		fin.close();
		cout << "\t\t\t\t从文件中读取学生信息成功~" << endl;
	}
}
//析构函数，析构时将文件写入文本文件。
ExpressInfoManage::~ExpressInfoManage() {
	system("cls");
	cout << "\t\t正在保存.." << endl;
	for (int i = 0; i < 90000000; i++); //时延
	//先保存进文件
	SaveToFile();
	//释放内存
	for (ExpressInfo *p = Head->next,*tmp; p != End;) {
		tmp = p->next;
		delete p;
		p = tmp;
	}
	delete Head, End;
	cout << "\t\t谢谢使用..,再见~~"<<endl;
	for (int i = 0; i < 90000000; i++); //时延
}
//将链表中的数据保存在txt中
void ExpressInfoManage::SaveToFile() {
	fout.open("data.txt",ios::out);
	ExpressInfo *p = Head->next;
	while (p != End) {
		fout << p->tracking_number << "\t" 
			<<p->type << "\t"
			<< p->sender_address << "\t"
			<< p->sender_tel << "\t"
			<< p->sender_remarks << "\t"
			<<  p->recipient_address << "\t"
			<< p->recipient_tel << "\t"
			<<  p->recipient_remarks << "\t"
			<<  p->receipt_date << "\t"
			<< p->delivery_date << "\t"<< "\t" 
			<< p->signinfo<< "\t"
			<<  p->money << "\t"
			<<  p->difficult_made << "\t"
			<<  p->diff_remarks << endl;
		p = p->next;
	}
}
//返回链表中元素个数
int ExpressInfoManage::ListCount() {
	int n = 0;
	for (ExpressInfo *p = Head->next; p != End; p = p->next) {
		n++;
	}
	return n++;
}
//--------------显示主菜单
void ExpressInfoManage::ShowMenu() {
	cout.fill('*');
	cout << "\t\t**************************  快递信息管理系统  ******************************" << endl;
	cout << "\t\t*                                                                          *" << endl;
	cout << "\t\t*                           1.增加快递单号记录                             *" << endl;
	cout << "\t\t*                           2.显示快递单号记录                             *" << endl;
	cout << "\t\t*                           3.删除快递单号记录                             *" << endl;
	cout << "\t\t*                           4.修改快递单号记录                             *" << endl;
	cout << "\t\t*                           5.查找快递单号记录                             *" << endl; //二级目录【据单号，快递类别，收件日期，派送日期】
	cout << "\t\t*                           6.根据收件日期统计信息                         *" << endl; //收件日期统计快递单数量，金额
	cout << "\t\t*                           7.根据派送日期查询                             *" << endl;
	cout << "\t\t*                           8.排序快递单号信息                             *" << endl;
	cout << "\t\t*                           0.安全退出                                     *" << endl;
	cout << "\t\t*                                                                          *" << endl;
	cout << "\t\t****************************************************************************" << endl;
	//cout << "********************************************************************************" << endl
	cout.fill(' ');
	cout << "\n\t\t\n\t\t请选择：";
}
/*在末尾添加新节点*/
void ExpressInfoManage::addItem() {
	End->InputFromConsole();
	End->next = new ExpressInfo();
	End = End->next;
	cout<< "\n\t\t\n\t\t请选择：添加成功";
	system("pause");
}
void ExpressInfoManage::Display() {
	cout << "\t\t总的快递单号记录数目为："<<ListCount() << endl;
	int n = 1;
	for (ExpressInfo *p = Head->next; p != End; p = p->next) {
		cout << "\t\t------------------- "<<n<<" -------------------------------"<<endl;
		p->ShowOnConsole();
		cout << "\t\t-----------------------------------------------------"<<endl;
		n++;
	}
}
/*根据快递单号id查找，如果找到则返回当前节点的【前一个节点指针】，找不到返回NULL*/
ExpressInfo* ExpressInfoManage::FindID(string &id) {
	for (ExpressInfo *p = Head; p->next != End; p = p->next) {
		if (p->next->tracking_number == id) {
			return p;
		}
	}
	return NULL;
}
/*修改 快递单号信息*/
void  ExpressInfoManage::ModifyItem() {
	string id;
	ExpressInfo *p;
	cout << "\t\t输入需要修改的快递单号：" ;
	cin >> id;
	//获取前置指针
	if ((p = FindID(id)) == NULL) {
		cout << "\t\t没有找到，快递单号："<<id << endl;
	}
	else {
		p = p->next;
		p->InputFromConsole(id);
		cout << "修改成功！" << endl;
	}
	system("pause");
}
/*删除快递单号信息  */
void ExpressInfoManage::RomoveItem() {
	string id;
	ExpressInfo *p, *tmp;
	cout << "\t\t输入需要删除的快递单号：";
	cin >> id;
	//获取前置指针
	if ((p = FindID(id)) == NULL) {
		cout << "\t\t没有找到，快递单号：" << id << endl;
	}
	else {
		tmp = p->next; //暂存待删除
		p->next = p->next->next;
		delete tmp;
		cout << "\t\t删除成功!" << endl;
	}
	system("pause");
}

void ExpressInfoManage::Find() {
	string id, receipt_date, delivery_date;
	int type,count;
	ExpressInfo * p=NULL;

	cout << "\n\t\t\t\t*********** 查找子目录 **************" << endl;
	cout << "\n\t\t\t\t\t1.按单号查找\n";
	cout << "\t\t\t\t\t2.按快递类别查找\n";
	cout << "\t\t\t\t\t3.按收件日期查找\n";
	cout << "\t\t\t\t\t4.按派送日期查找\n";
	cout << "\t\t\t\t\t5.返回主目录\n";
	cout << "\n\t\t\t\t************************************" << endl;
	for (int n = 1; n;) {
		if (n == 1) {
			cout << "\n\t\t\t\t请选择：";
		}
		else {
			cout << "\n\t\t\t\t请重新选择：";
		}

		string x;
		cin >> x;
		char c;
		if (x.length() != 1)
		{
			n++;
			cout << "\n\t\t\t输入错误!\n";
		}
		else
		{
			c = x[0];
		}

		switch (c){
		case '1': 
			cout << "\t\t\t\t请输入需要查找的快递单号：";
			cin >> id;
			if ((p=FindID(id)) == NULL){
				cout << "\t\t\t\t没找到对快递单号："+id;
			}
			else {
				cout << "\t\t\t\t----------------------------------" << endl;
				p->next->ShowOnConsole();
				cout << "\t\t\t\t----------------------------------" << endl;
			}
			n = 0;
			system("pause");
			break;
		case '2': 
			cout << "\t\t\t\t请输入需要查找的快递类别<派送1/收件单2>：";
			cin >> type; //缺少检查，建设输入正确
			count = 0;
			for (ExpressInfo *p = Head->next; p != End; p = p->next) {
				if (p->type == type) {
					count++;
					cout << "\t\t\t\t----------------------------------" << endl;
					p->ShowOnConsole();
					cout << "\t\t\t\t----------------------------------" << endl;
				}
			}
			if (!count) {
				cout << "\t\t\t\t该类型快递信息" << endl;
			}
			n = 0;
			system("pause");
			break;
		case '3': 
			cout << "\t\t\t\t请输入需要查找的收件日期<yyyy-MM-dd>：";
			cin >> receipt_date;//缺少检查，建设输入正确
			count = 0;
			for (ExpressInfo *p = Head->next; p != End; p = p->next) {
				if (p->receipt_date == receipt_date) {
					count++;
					cout << "\t\t\t\t----------------------------------" << endl;
					p->ShowOnConsole();
					cout << "\t\t\t\t----------------------------------" << endl;
				}
			}
			if (!count) {
				cout << "\t\t\t\t该日期无数据" << endl;
			}
			n = 0;
			system("pause");
			break;
		case '4': 
			cout << "\t\t\t\t请输入需要查找的派送日期<yyyy-MM-dd>：";
			cin >> delivery_date;//缺少检查，建设输入正确
			count = 0;
			for (ExpressInfo *p = Head->next; p != End; p = p->next) {
				if (p->delivery_date == delivery_date) {
					count++;
					cout << "\t\t\t\t----------------------------------" << endl;
					p->ShowOnConsole();
					cout << "\t\t\t\t----------------------------------" << endl;
				}
			}

			if (!count) {
				cout << "\t\t\t\t该日期无数据" << endl;
			}
			n = 0;
			system("pause");
			break;

		case '5': n = 0;  break;
		}
	}
}
/*根据日期统计数据*/
void ExpressInfoManage::Statistics() {
	string delivery_date;
	int count;
	double money;
	cout << "\n\t\t\t\t*********** 统计数据子目录 **************" << endl;
	cout << "\n\t\t\t\t\t1.按日期统计\n";
	cout << "\t\t\t\t\t2.按月份统计\n";
	cout << "\t\t\t\t\t3.按年份统计\n";
	cout << "\t\t\t\t\t4.按输入日期统计\n";
	cout << "\t\t\t\t\t5.返回主目录\n";
	cout << "\n\t\t\t\t************************************" << endl;
	for (int n = 1; n;) {
		if (n == 1) {
			cout << "\n\t\t\t\t请选择：";
		}
		else {
			cout << "\n\t\t\t\t请重新选择：";
		}

		string x;
		cin >> x;
		char c;
		if (x.length() != 1){
			n++;
			cout << "\n\t\t\t输入错误!\n";
		}
		else{
			c = x[0];
		}

		map<string, OrdernumMoney>::iterator it;
		map<string, OrdernumMoney> Map;
		//
		string substr;
		switch (c) {
			case '1':
				Map.clear();
				for (ExpressInfo *p = Head->next; p != End; p = p->next) {
					it = Map.find(p->delivery_date);
					if (it != Map.end()) {
						(it->second).order_num++;
						(it->second).money += (p->money);
					}
					else {
						OrdernumMoney t(1, p->money);
						Map[p->delivery_date] = t;
					}
				}
				cout << "\t\t\t\t统计结果：\n";
				cout << "\t\t\t\t日期\t订单数目统计\t金额统计：\n";
				for (it = Map.begin(); it != Map.end(); it++) {
					cout << "\t\t\t\t" << it->first << "\t" << it->second.order_num<<"\t"<<it->second.money <<endl;
				}


				n = 0;
				system("pause");
				break;
			case '2':
				Map.clear();
				for (ExpressInfo *p = Head->next; p != End; p = p->next) {
					substr = (p->delivery_date).substr(0, 7);
					it = Map.find(substr);
					if (it != Map.end()) {
						(it->second).order_num++;
						(it->second).money += (p->money);
					}
					else {
						OrdernumMoney t(1, p->money);
						Map[substr] = t;
					}
				}
				cout << "\t\t\t\t统计结果：\n";
				cout << "\t\t\t\t月份\t订单数目统计\t金额统计：\n";
				for (it = Map.begin(); it != Map.end(); it++) {
					cout << "\t\t\t\t" << it->first << "\t" << it->second.order_num << "\t" << it->second.money << endl;
				}
				n = 0;
				system("pause");
				break;
			case '3':
				Map.clear();
				for (ExpressInfo *p = Head->next; p != End; p = p->next) {
					substr = (p->delivery_date).substr(0, 4);
					it = Map.find(substr);
					if (it != Map.end()) {
						(it->second).order_num++;
						(it->second).money += (p->money);
					}
					else {
						OrdernumMoney t(1, p->money);
						Map[substr] = t;
					}
				}
				cout << "\t\t\t\t统计结果：\n";
				cout << "\t\t\t\t年份\t订单数目统计\t金额统计：\n";
				for (it = Map.begin(); it != Map.end(); it++) {
					cout << "\t\t\t\t" << it->first << "\t" << it->second.order_num << "\t" << it->second.money << endl;
				}
				n = 0;
				system("pause");
				break;
			case '4':
				cout << "\t\t\t\t请输入需要查找的派送日期<yyyy-MM-dd>：";
				cin >> delivery_date;//缺少检查，建设输入正确
				count = 0;
				money = 0;
				for (ExpressInfo *p = Head->next; p != End; p = p->next) {
					if (p->delivery_date == delivery_date) {
						count++;
						money += (p->money);
					}
				}

				if (!count) {
					cout << "\t\t\t\t该日期无数据" << endl;
				}
				else {
					cout << "\t\t\t\t日期\t订单数目统计\t金额统计：\n";
					cout << "\t\t\t\t" << delivery_date << "\t" << count << "\t" << money << endl;
				}
				n = 0;
				system("pause");
				break;
			case '5': n = 0;  break;
		}

	}
}
/* 根据派送日期显示未签收的快递单，显示所有疑难件 */
void ExpressInfoManage::DeliverySelect() {
	string delivery_date;
	int count;
	cout << "\n\t\t\t\t*********** 派送数据查询目录 **************" << endl;
	cout << "\n\t\t\t\t\t1.查询未签收的派送单" << endl;
	cout << "\t\t\t\t\t2.查询派送单中疑难件" << endl;
	cout << "\t\t\t\t\t3.返回主目录\n" << endl;
	cout << "\n\t\t\t\t************************************" << endl;
	for (int n = 1; n;) {
		if (n == 1) {
			cout << "\n\t\t\t\t请选择：";
		}
		else {
			cout << "\n\t\t\t\t请重新选择：";
		}

		string x;
		cin >> x;
		char c;
		if (x.length() != 1) {
			n++;
			cout << "\n\t\t\t输入错误!\n";
		}
		else {
			c = x[0];
		}
		switch (c) {
		case '1':
			cout << "\t\t\t\t请输入需要查找的派送日期<yyyy-MM-dd>：";
			cin >> delivery_date;//缺少检查，建设输入正确
			count = 0;
			for (ExpressInfo *p = Head->next; p != End; p = p->next) {
				if (p->delivery_date == delivery_date && p->type==1 &&p->signinfo==0) { //该日期，且为派送单 未签收
					count++;
					cout << "\t\t\t\t----------------------------------" << endl;
					p->ShowOnConsole();
					cout << "\t\t\t\t----------------------------------" << endl;
				}
			}
			if (!count) {
				cout << "\t\t\t\t该日期无数据" << endl;
			}
			system("pause");
			n = 0;
			break;
		case '2':
			cout << "\t\t\t\t请输入需要查找的派送日期<yyyy-MM-dd>：";
			cin >> delivery_date;//缺少检查，建设输入正确
			count = 0;
			for (ExpressInfo *p = Head->next; p != End; p = p->next) {
				if (p->delivery_date == delivery_date && p->type == 1 && p->difficult_made == 1) { //该日期，且为派送单 未签收
					count++;
					cout << "\t\t\t\t----------------------------------" << endl;
					p->ShowOnConsole();
					cout << "\t\t\t\t----------------------------------" << endl;
				}
			}
			if (!count) {
				cout << "\t\t\t\t该日期无数据" << endl;
			}
			system("pause");
			n = 0;
			break;
		case '3': n = 0;  break;
		}
	}
}
void  ExpressInfoManage::Sort() {
	
	cout << "\n\t\t\t\t*********** 排序显示子目录 **************" << endl;
	cout << "\n\t\t\t\t\t1.按收件日期排序显示" << endl;
	cout << "\t\t\t\t\t2.按派送日期排序显示" << endl;
	cout << "\t\t\t\t\t3.按类型排序显示" << endl;
	cout << "\t\t\t\t\t4.按金额排序显示" << endl;
	cout << "\t\t\t\t\t5.返回主目录" << endl;
	cout << "\n\t\t\t\t************************************" << endl;
	for (int n = 1; n;) {
		if (n == 1) {
			cout << "\n\t\t\t\t请选择：";
		}
		else {
			cout << "\n\t\t\t\t请重新选择：";
		}

		string x;
		cin >> x;
		char c;
		if (x.length() != 1) {
			n++;
			cout << "\n\t\t\t输入错误!\n";
		}
		else {
			c = x[0];
		}
		switch (c) {
			case '1':
				cout << "\t\t\t\t选择排序模式<升序Y/降序N>：";
				cin >> c;
				if (c == 'Y' || c == 'y') {
					SortByDeliveryDate(true);
				}
				else {
					SortByDeliveryDate(false);
				}
				Display();
				n = 0;
				system("pause");
				break;
			case '2':
				cout << "\t\t\t\t选择排序模式<升序Y/降序N>：";
				cin >> c;
				if (c == 'Y' || c == 'y') {
					SortByRecipientDate(true);
				}
				else {
					SortByRecipientDate(false);
				}
				Display();

				n = 0;
				system("pause");
				break;
			case '3':
				cout << "\t\t\t\t选择排序模式<派送单在前Y/收件单在前N>：";
				cin >> c;
				if (c == 'Y' || c == 'y') {
					SortByType(true);
				}
				else {
					SortByType(false);
				}
				Display();
				n = 0;
				system("pause");
				break;
			case '4':
				cout << "\t\t\t\t选择排序模式<升序Y/降序N>：";
				cin >> c;
				if (c == 'Y' || c == 'y') {
					SortByMoney(true);
				}
				else {
					SortByMoney(false);
				}
				Display();
				n = 0;
				system("pause");
				break;
			case '5': n = 0; system("pause"); break;
			default: {
				
			}

		}
	}
}
/*更具派送日期排序 从小到大排序*/
void ExpressInfoManage::SortByDeliveryDate(bool up) {
	if (up == true) {
		ExpressInfo *tmp=new ExpressInfo; 

		ExpressInfo *tmptail=tmp,*prev;
		string t1,t2;
		while (Head->next != End) {
			t1= "9999-12-31"; //链表中取出，取最小的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->delivery_date;
				//cout << t2 << " " << t1<<endl;
				if ( t2<t1 ) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout<<ListCount()<<endl;
	}
	else {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		string t1, t2;
		while (Head->next != End) {
			t1 = "0000-00-00"; //链表中取出，取最大的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->delivery_date;
				//cout << t2 << " " << t1 << endl;
				if (t2 > t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
}

/*更具接收日期排序 从小到大排序*/
void ExpressInfoManage::SortByRecipientDate(bool up) {
	
	if (up) {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		string t1, t2;
		while (Head->next != End) {
			t1 = "9999-12-31"; //链表中取出，取最小的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->receipt_date;
				//cout << t2 << " " << t1 << endl;
				if (t2 < t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
	else {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		string t1, t2;
		while (Head->next != End) {
			t1 = "0000-00-00"; //链表中取出，取最大的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->receipt_date;
				//cout << t2 << " " << t1 << endl;
				if (t2 > t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
}
void ExpressInfoManage::SortByType(bool up) {
	if (up) {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		int t1, t2;
		while (Head->next != End) {
			t1 = 99;	//链表中取出，取最小的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->type;
				//cout << t2 << " " << t1 << endl;
				if (t2 < t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
	else {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		int t1, t2;
		while (Head->next != End) {
			t1 = 0;				//链表中取出，取最大的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->type;
				//cout << t2 << " " << t1 << endl;
				if (t2 > t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
}
void ExpressInfoManage::SortByMoney(bool up) {
	if (up) {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		int t1, t2;
		while (Head->next != End) {
			t1 = 0x0fffffff;	//链表中取出，取最小的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->money;
				//cout << t2 << " " << t1 << endl;
				if (t2 < t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
	else {
		ExpressInfo *tmp = new ExpressInfo;

		ExpressInfo *tmptail = tmp, *prev;
		int t1, t2;
		while (Head->next != End) {
			t1 = -1;				//链表中取出，取最大的点
			prev = Head->next;
			for (ExpressInfo * p = Head; p->next != End; p = p->next) {
				t2 = p->next->money;
				//cout << t2 << " " << t1 << endl;
				if (t2 > t1) {
					t1 = t2;
					prev = p;
				}
			}
			//cout << "__" << t1 << endl;
			tmptail->next = prev->next; //将节点挂到tmp末尾 
			tmptail = tmptail->next;//tmptail 后移
			prev->next = prev->next->next;//摘下该节点
		}
		//将tmp挂会到空的list中
		tmptail->next = End;
		Head->next = tmp->next;
		delete tmp;
		//cout << ListCount() << endl;
	}
}


int ExpressInfoManage::DateStringtoInt(string & date) {
	
	return 0;
}




OrdernumMoney::OrdernumMoney(int a, double m) {
	money = m;
	order_num=a;
}
OrdernumMoney::OrdernumMoney() {
}