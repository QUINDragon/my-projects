#include<iostream>
#include<vector>
#include<string>
#include<limits>		//numeric__limits依赖
#include<algorithm>
#include <fstream>
#include"sqlite3.h"
using namespace std;
struct Contact {
	string name;
	string sex;
	int age;
	string phone;
};
const string DATA_FILE = "contacts.txt";
auto findContact( vector<Contact>& contacts,  string& name) 
{
	return find_if(contacts.begin(), contacts.end(),
		[&]( Contact& c) { return c.name == name; });
}
void savetofile(const vector<Contact>& contacts)
{
	ofstream outfile(DATA_FILE);
	if (!outfile)
	{
		cerr << "无法打开" << DATA_FILE << "进行保存！"<<endl;
		return;
	}
	for (const auto& c:contacts)
	{
		outfile << c.name << " " << c.sex << " " << c.age << " " << c.phone << endl;
	}
	outfile.close();
	cout << "保存成功"<<endl;
}
void loadfromfile(vector<Contact>& contacts)
{
	ifstream infile(DATA_FILE);
	if (!infile)
	{
		return;
	}
	contacts.clear();
	Contact temp;
	while (infile >> temp.name >> temp.sex >> temp.age >> temp.phone)
	{
		contacts.push_back(temp);
	}
	infile.close();
	cout << "已从" << DATA_FILE << "读取" << contacts.size() << "位联系人" << endl;
}
void showmenu()				//菜单面板
{
	cout << "=====通讯录管理系统====="<<endl;
	cout << "1.添加联系人" << endl;
	cout << "2.删除联系人" << endl;
	cout << "3.查找联系人" << endl;
	cout << "4.修改联系人" << endl;
	cout << "5.显示所有联系人" << endl;
	cout << "0.退出" << endl;
	cout << "*************************" << endl;
	cout << "请输入：" << endl;
}
void addContact(/*const string& name, const string& sex, const string& phone, int age,*/ vector <Contact>& contacts)		//1.添加联系人
{
	Contact newContact;
	cout << "请输入姓名" << endl;
	cin >> newContact.name;
	cout << "请输入性别" << endl;
	cin >> newContact.sex;
	cout << "请输入年龄" << endl;
	cin >> newContact.age;
	cout << "请输入电话号码" << endl;
	cin >> newContact.phone;
	contacts.push_back(newContact);
	cout << "添加成功，现在共有" << contacts.size() << "人\n";
}
void searchContacts(vector <Contact>& contacts)							//2.查找联系人
{
	string name;
	bool flag=0;
	cout << "请输入要查找的联系人姓名" << endl;
	cin >> name;
	flag = 0;
	for (const auto& c : contacts)
	{
		if (name == c.name)
		{
			cout << name<<" "<< c.age <<" " << c.phone<<" " << c.sex << endl;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "抱歉您所查找的联系人不存在" << endl;
	}
		
}
void delContact(vector<Contact>& contacts)
{
	char choice;
	string name;
	cout << "请输入要删除的联系人" << endl;
	cin >> name;
	/*for (auto& it : contacts)
	{
		if (name == it.name)
		{
			flag = 1;
			break;
		}
	}*/
	auto it = contacts.begin();
	for (;it != contacts.end();++it)
	{
		if (it->name == name)
		{
			break;
		}
	}

	if(it!=contacts.end())
	{
		while (true) 
		{
			cout << "确定要删除吗？(y/n)" << endl;
			cin >> choice;
			string temp = it->name;
			switch (choice)
			{
				
				case 'y':contacts.erase(it);
					cout << "已删除联系人" << temp << endl;
					return;
				case 'n':return;
				default:cout<<"您输入的指令有误" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

	}
	else
	{
		cout << "您所输入的联系人不存在" << endl;
		return;
	}

}
void editContact(vector<Contact>& contacts)
{
	int choice=-1;
	string newname;
	string newphone;
	string name;
	string newsex;
	int newage;
	cout << "请输入要修改的联系人" << endl;
	cin >> name;
	auto it = findContact(contacts,name);
	if (it == contacts.end())
	{
		cout << "您输入的联系人不存在" << endl;
		return;
	}
	else
	{

		while (choice != 0)
		{
			cout << "请选择要修改的选项" << endl;
			cout << "1.姓名" << endl;
			cout << "2.电话号码" << endl;
			cout << "3.年龄" << endl;
			cout << "4.性别" << endl;
			cout << "0.退出修改" << endl;
			cout << "***************" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:cout << "请输入修改后的姓名" << endl;
				cin >> newname;
				it->name = newname;
				break;
			case 2:cout << "请输入修改后的电话号码" << endl;
				cin >> newphone;
				it->phone = newphone;
				break;
			case 3:cout << "请输入修改后的年龄" << endl;
				cin >> newage;
				it->age = newage;
				break;
			case 4:cout << "请输入修改后的性别" << endl;
				cin >> newsex;
				it->sex = newsex;
				break;
			case 0:return;
			default:cout << "您输入的选项无效" << endl;
				break;
			}
		}
	}
}
void showallContact(const vector<Contact>& contacts)
{
	if (contacts.empty())
	{
		cout << "通讯录为空" << endl;
		return;
	}
	else
	{
		for (auto it = contacts.begin();it != contacts.end();++it)
			cout << it->name << " " << it->sex << " " << it->age << " " << it->phone << endl;
	}
}

int main() 
{
	int choice = -1;
	vector<Contact>addressbook;
	loadfromfile(addressbook);
	do {
		showmenu();
		cin >> choice;
		switch (choice)
		{
		case 0:cout << "感谢使用系统, 再见" << endl;
			break;
		case 1:addContact(addressbook);
			savetofile(addressbook);
			break;
		case 2:delContact(addressbook);
			savetofile(addressbook);
			break;
		case 3:searchContacts(addressbook);
			break;
		case 4:editContact(addressbook);
			savetofile(addressbook);
			break;
		case 5:showallContact(addressbook);
			break;
		}
	} while (choice!=0);
	return 0;
}