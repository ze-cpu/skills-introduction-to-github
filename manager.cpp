#include "manager.h"

//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器  获取所有文件中学生，教师信息
	this->initVector();

	//初始化机房容器
	this->initCompRoom();
}

//初始化机房容器，获取机房信息
void Manager::initCompRoom()
{
	ifstream ifs;
	ifs.open(COMPROOM_FILE, ios::in);

	ComputerRoom cr;
	while (ifs >> cr.m_RoomId && ifs >> cr.m_MaxNum)
	{
		crv.push_back(cr);
	}
	//cout << "当前机房数量为：" <<crv.size() << endl;
	ifs.close();
}

//初始化容器，获取学生，教师信息
void Manager::initVector()
{
	//清空容器
	sv.clear();
	tv.clear();

	ifstream ifs;
	//读取学生文件
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		sv.push_back(s);
	}
	//cout << "当前学生数量为：" << sv.size() << endl;
	ifs.close();

	//读取教师文件
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		tv.push_back(t);
	}
	//cout << "当前教师数量为：" << tv.size() << endl;
	ifs.close();
}

//管理员操作界面
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t   ------------------------------\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          1.添加账号          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          2.查看账号          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          3.查看机房          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          4.清空预约          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          0.退出登录          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t   ------------------------------\n";
	
	cout << "请输入您的选择：" << " ";
}

//管理员菜单
void Manager::managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->operMenu();
		//dynamic_cast用于在类继承层次结构中进行安全的类型转换
		Manager* man = dynamic_cast<Manager*>(manager);

		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1:  //添加账号
			//cout << "添加账号" << endl;
			man->addPerson();
			break;
		case 2:  //查看账号
			//cout << "查看账号" << endl;
			man->showPerson();
			break;
		case 3:  //查看机房
			//cout << "查看机房" << endl;
			man->showCompRoom();
			break;
		case 4:  //清空预约
			//cout << "清空预约" << endl;
			man->cleanFile();
			break;
		case 0:  //退出登录
			delete manager; //销毁掉堆区对象
			cout << "退出成功" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//检测重复  参数(id , 类型)
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = sv.begin(); it != sv.end(); it++)
		{
			if (id == (*it).m_Id)
			{
				return true;
			}
		}
	}
	else if(type == 2)
	{
		//检测教师
		for (vector<Teacher>::iterator it = tv.begin(); it != tv.end(); it++)
		{
			if (id == (*it).m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加教师" << endl;

	string fileName;
	string tip;
	string errorTip;  //重复错误提示

	int select = 0;
	while (true)
	{
		cin >> select;

		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tip = "请输入学号：";
			errorTip = "学号重复，请重新输入";
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "请输入职工编号：";
			errorTip = "职工编号重复，请重新输入";
			break;
		}
		else
		{
			cout << "输入错误，请重新输入：" << " ";
		}
	}

	ofstream ofs;
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;

	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		
		if (ret)
		{
			cout << errorTip << endl;
			continue;
		}
		else
			break;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;
	ofs.close();

	//调用初始化容器，将当前新添加的信息存入容器
	this->initVector();

	system("pause");
	system("cls");
}

//查看账号
void PrintStudent(Student& s)
{
	cout << "学号：" << s.m_Id << "\t用户名：" << s.m_Name << "\t密码：" << s.m_Pwd << endl;
}
void PrintTeacher(Teacher& t)
{
	cout << "职工编号：" << t.m_EmpId << "\t用户名：" << t.m_Name << "\t密码：" << t.m_Pwd << endl;
}
void Manager::showPerson()
{
	cout << "请选择要查看账号的类型：" << endl;
	cout << "1.学生账号" << endl;
	cout << "2.教师账号" << endl;

	int select = 0;
	while (true)
	{
		cin >> select;

		if (select == 1)
		{
			cout << "所有学生账号信息如下：" << endl;
			for_each(sv.begin(), sv.end(), PrintStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "所有教师账号信息如下：" << endl;
			for_each(tv.begin(), tv.end(), PrintTeacher);
			break;
		}
		else
		{
			cout << "输入错误，请重新输入：" << " ";
		}
	}
	
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showCompRoom()
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = crv.begin(); it != crv.end(); it++)
	{
		cout << "机房编号：" << (*it).m_RoomId << "\t机房最大容量：" << (*it).m_MaxNum << endl;
	}

	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}