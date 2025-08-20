#pragma once
#include "manager.h"
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "Identity.h"
#include <fstream>

//登录功能  参数：操作文件名，操作身份类型
void LoginIn(string fileName, int type)
{
	//父类指针  用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//文件存在，准备接收用户信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1) //学生
	{
		cout << "请输入您的学号：" << endl;
		cin >> id;
	}
	else if (type == 2) //教师
	{
		cout << "请输入您的职工编号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//判断是否验证成功
	bool isAuthenticated = false;

	if (type == 1)
	{
		//学生身份验证
		//文件中读取的id号，姓名，密码
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//cout << fId << "\t" << fName << "\t" <<fPwd <<endl;
			//判断文件信息是否和用户输入信息一致
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "学生验证登录成功！" << endl;
				person = new Student(id, name, pwd);

				system("pause");
				system("cls");

				//进入学生子菜单
				//studentMenu(person);
				if (Student* stu = dynamic_cast<Student*>(person))
					stu->studentMenu(person);
				isAuthenticated = true;
				break;
			}
		}

	}
	else if (type == 2)
	{
		//教师身份验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功！" << endl;
				person = new Teacher(id, name, pwd);

				system("pause");
				system("cls");

				//进入教师子菜单
				//teacherMenu(person);
				if (Teacher* teac = dynamic_cast<Teacher*>(person))
					teac->teacherMenu(person);
				isAuthenticated = true;
				break;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "管理员验证登录成功！" << endl;
				person = new Manager(name, pwd);

				system("pause");
				system("cls");

				//进入管理员子菜单
				//managerMenu(person);
				if (Manager* man = dynamic_cast<Manager*>(person))
					man->managerMenu(person);
				isAuthenticated = true;
				break;
			}
		}
	}
	if (!isAuthenticated)
	{
		cout << "验证登录失败！" << endl;

		system("pause");
		system("cls");
	}
}

void mainMenu()
{
	int select = 0; //用于接受用户选择
	while (true)
	{
		cout << "====================  欢迎来到me的机房预约系统  ====================" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t   ------------------------------\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          1.学生代表          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          2.老    师          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          3.管 理 员          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          0.退    出          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t   ------------------------------\n";

		cout << "请输入您的选择：" << " ";
		cin >> select;

		switch (select)  //根据用户选择实现不同接口
		{
		case 1: //学生
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //教师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3: //管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return;
		default:
			cout << "输入有误，请重新选择" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}