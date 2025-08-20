#include "student.h"

//默认构造
Student::Student()
{
}

//有参构造
Student::Student(int id, string name, string pwd)
{
	//初始化学生信息
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房容器
	this->initCompRoom();
}

//学生操作界面
void Student::operMenu()  
{
	cout << "欢迎学生代表：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t   ------------------------------\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          1.申请预约          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |         2.查看我的预约       |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |         3.查看所有预约       |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          4.取消预约          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          0.退出登录          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t   ------------------------------\n";

	cout << "请输入您的选择：" << " ";
}

//学生菜单
void Student::studentMenu(Identity*& student)
{
	while (true)
	{
		student->operMenu();
		Student* stu = dynamic_cast<Student*>(student);

		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1:  //申请预约
			stu->applyOrder();
			break;
		case 2:  //查看我的预约
			stu->showMyOrder();
			break;
		case 3:  //查看所有预约
			stu->showAllOrder();
			break;
		case 4:  //取消预约
			stu->CancelOrder();
			break;
		case 0:  //退出登录
			delete student; //销毁掉堆区对象
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

//初始化机房容器，获取机房信息
void Student::initCompRoom()
{
	ifstream ifs;
	ifs.open(COMPROOM_FILE, ios::in);

	ComputerRoom cr;
	while (ifs >> cr.m_RoomId && ifs >> cr.m_MaxNum)
	{
		crv.push_back(cr);
	}
	//cout << "当前机房数量为：" << crv.size() << endl;
	ifs.close();
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放日期为周一到周五" << endl;
	cout << "请输入申请预约日期：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;

	int date = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}

	cout << "请输入申请预约时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;

	int time = 0;
	while (true)
	{
		cin >> time;
		if (time >= 1 && time <= 2)
		{
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}

	cout << "请选择机房：" << endl;
	cout << "1号机房容量：" << crv[0].m_MaxNum << endl;
	cout << "2号机房容量：" << crv[1].m_MaxNum << endl;
	cout << "3号机房容量：" << crv[2].m_MaxNum << endl;

	int room = 0;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入错误，请重新输入！" << endl;
	}

	cout << "预约成功！审核中……" << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " " << "time:" << time << " ";
	ofs << "stuId:" << this->m_Id << " " << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " " << "status:" << 1 << endl; //status 预约状态

	ofs.close();
	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	
	bool ret = false;
	for (int i = 1; i <= of.m_Size; i++)
	{
		//string 通过 c_str() 转为 c风格字符串(const char*)，然后通过atoi(cosnt char*) 转为 int
		//if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		//stoi 是 C++11 标准引入的字符串转整数函数  stoi(const string&)
		if(stoi(of.m_OrderData[i]["stuId"]) == this->m_Id)
		{
			ret = true;
			cout << "预约日期：周" << of.m_OrderData[i]["date"];
			cout << "  时间段：" << (of.m_OrderData[i]["time"] == "1" ? "上午" : "下午");
			cout << "  机房编号：" << of.m_OrderData[i]["roomId"];
			string status =  "  状态："; 
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_OrderData[i]["status"] == "0")
			{
				status += "预约已取消";
			}
			else
			{
				status += "预约失败，审核未通过";
			}
			cout << status << endl;
		}
	}
	if(!ret)
		cout << "无预约记录！" << endl;
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;

	bool ret = false;
	for (int i = 1; i <= of.m_Size; i++)
	{
		ret = true;
		cout << i << "、";
		cout << "预约日期：周" << of.m_OrderData[i]["date"];
		cout << "  时间段：" << (of.m_OrderData[i]["time"] == "1" ? "上午" : "下午");
		cout << "  学号：" << of.m_OrderData[i]["stuId"];
		cout << "  用户名：" << of.m_OrderData[i]["stuName"];
		cout << "  机房编号：" << of.m_OrderData[i]["roomId"];
		string status = "  状态："; // 0-预约已取消，1-审核中，2-预约成功，-1-预约失败
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_OrderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		else
		{
			status += "预约失败，审核未通过";
		}
		cout << status << endl;
	}
	if(!ret)
		cout << "无预约记录！" << endl;
	system("pause");
	system("cls");
}

//取消预约
void Student::CancelOrder()
{
	OrderFile of;

	bool ret = false;
	//cout << "审核中或者预约成功的记录可以取消！" << endl;

	vector<int> v; //存放最大容器中的下标编号
	int index = 0; //记录符合条件的预约记录 
	for (int i = 1; i <= of.m_Size; i++)
	{
		//判断是自身学号，并且符合筛选状态(审核中或者预约成功)
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id &&
			(of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2"))
		{
			ret = true;
			v.push_back(i);
			index++;

			cout << index << "、";
			cout << "预约日期：周" << of.m_OrderData[i]["date"];
			cout << "  时间段：" << (of.m_OrderData[i]["time"] == "1" ? "上午" : "下午");
			cout << "  机房编号：" << of.m_OrderData[i]["roomId"];
			string status = "  状态："; 
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			cout << status << endl;
		}
	}
	if (!ret)
		cout << "没有可以取消的预约记录" << endl;
	else
	{
		cout << "请输入您要取消的记录，输入0返回：" << endl;
		int select = 0;

		while (true)
		{
			cin >> select;
			if (select >= 0 && select <= v.size())
			{
				if (select == 0)
				{
					cout << "取消操作！" << endl;
					break;
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "0";
					of.updateOrder();

					cout << "已取消预约" << endl;
					break;
				}
			}
			cout << "输入错误，请重新输入" << endl;
		}
	}
	system("pause");
	system("cls");
}