#include "teacher.h"

//默认构造
Teacher::Teacher()
{
}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
	//初始化教师信息
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//教师操作界面
void Teacher::operMenu()
{
	cout << "欢迎教师：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t   ------------------------------\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |         1.查看所有预约       |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          2.审核预约          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          0.退出登录          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t   ------------------------------\n";

	cout << "请输入您的选择：" << " ";
}

//教师菜单
void Teacher::teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();
		Teacher* teac = dynamic_cast<Teacher*>(teacher);

		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1:  //查看所有预约
			teac->showAllOrder();
			break;
		case 2:  //预约审核
			teac->validOrder();
			break;
		case 0:  //退出登录
			delete teacher; //销毁掉堆区对象
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

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;

	bool ret = false;
	cout << "所有预约信息如下：" << endl;
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
	if (!ret)
		cout << "无预约记录" << endl;
	system("pause");
	system("cls");
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	
	bool boolret = false;
	//cout << "审核中的记录可以取消！" << endl;

	vector<int> v; //存放最大容器中的下标编号
	int index = 0; //记录符合条件的预约记录 
	for (int i = 1; i <= of.m_Size; i++)
	{
		if(of.m_OrderData[i]["status"] == "1")
		{
			boolret = true;
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
			cout << status << endl;
		}
	}

	if (!boolret)
		cout << "没有需要审核的预约记录" << endl;
	else
	{
		cout << "请输入您要审核的预约记录，输入0返回：" << endl;
		int select = 0;
		int ret = 0;

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
					cout << "请输入审核结果" << endl;
					cout << "1.通过" << endl;
					cout << "2.不通过" << endl;

					cin >> ret;
					if (ret == 1)
					{
						of.m_OrderData[v[select - 1]]["status"] = "2";
					}
					else
					{
						of.m_OrderData[v[select - 1]]["status"] = "-1";
					}

					of.updateOrder();
					cout << "审核完毕！" << endl;
					break;
				}
			}
			cout << "输入错误，请重新输入" << endl;
		}
	}
	system("pause");
	system("cls");
}