#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>//用_getch();
#include "ExpressInfoManage.h"
#include <iomanip>
#include <windows.h>
using namespace std;

int main()
{
	int i = 0;
	bool quit = false;

	cout.fill('*'); 
	cout <<"\t\t"<< setw(50)<<"*" << endl;
	cout.fill(' ');
	cout << "\t\t*"<<setw(34)<<"欢迎来到快递信息系统"<< setw(15)<<"*"<< endl; //49位
	cout << "\t\t*"<<setw(49)<<"*" << endl;
	cout << "\t\t*" << setw(49) << "*" << endl;
	cout << "\t\t*" << setw(49) << "*" << endl;
	cout << "\t\t*" << setw(49) << "*" << endl;
	cout << "\t\t*" << setw(49) << "*" << endl;
	cout << "\t\t*" << setw(49) << "*" << endl;
	cout << "\t\t*" << setw(37) << "Copyright 2019 Sidewinder" <<setw(12)<<"*" << endl; //居中
	cout << "\t\t*" << setw(34) << "All Rights Reserved"  <<setw(15)<<"*" << endl; //居中
	cout.fill('*');
	cout << "\t\t" << setw(50) << "*" << endl;
	cout << "正在进入系统，请等待" << endl;

	ExpressInfoManage Manage;

	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		Sleep(5 * 100);
	}
	system("pause");



	while (!quit){
		system("cls");
		Manage.ShowMenu();
		char c;
		string x;
		cin >> x;
		if (x.length() != 1)
		{
			cout << "\n\t\t\t\t输入出错！！！\n";
			for (int i = 0; i < 300000000; i++);
			continue;
		}
		else
			c = x[0];
		switch (c){
		case '1':	Manage.addItem();	break;
		case '2':	Manage.Display(); system("pause");  break;
		case '3':	Manage.RomoveItem();  break;
		case '4':	Manage.ModifyItem();  break;
		case '5':	Manage.Find();  break;
		case '6':	Manage.Statistics();  break;
		case '7':	Manage.DeliverySelect(); break;
		case '8':	Manage.Sort(); break;
		case '0':		quit = true; break;
		
		default:
				cout << "\n\t\t\t\t输入出错！！！\n"; 
				for (int i = 0; i < 300000000; i++); //延迟一小会
				break;
		}
	}

	return 0;
}