#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Contact {
	string name;
	string sex;
	int age;
	string phone;
};
int choice;
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
	cout << "添加成功，现在共有" << contacts.size << "人\n";
}
void searchContacts(vector <Contact>& contacts)
{
	string name;
	bool flag;
	cout << "请输入要查找的联系人姓名" << endl;
	cin >> name;
	flag = 0;
	while()
	
	
}
do {
	showmenu();
}while (choice==1)
int main() {


	system("pause");

	return 0;
}