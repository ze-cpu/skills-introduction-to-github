#include "student.h"

//Ĭ�Ϲ���
Student::Student()
{
}

//�вι���
Student::Student(int id, string name, string pwd)
{
	//��ʼ��ѧ����Ϣ
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ����������
	this->initCompRoom();
}

//ѧ����������
void Student::operMenu()  
{
	cout << "��ӭѧ������" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t   ------------------------------\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          1.����ԤԼ          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |         2.�鿴�ҵ�ԤԼ       |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |         3.�鿴����ԤԼ       |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          4.ȡ��ԤԼ          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          0.�˳���¼          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t   ------------------------------\n";

	cout << "����������ѡ��" << " ";
}

//ѧ���˵�
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
		case 1:  //����ԤԼ
			stu->applyOrder();
			break;
		case 2:  //�鿴�ҵ�ԤԼ
			stu->showMyOrder();
			break;
		case 3:  //�鿴����ԤԼ
			stu->showAllOrder();
			break;
		case 4:  //ȡ��ԤԼ
			stu->CancelOrder();
			break;
		case 0:  //�˳���¼
			delete student; //���ٵ���������
			cout << "�˳��ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//��ʼ��������������ȡ������Ϣ
void Student::initCompRoom()
{
	ifstream ifs;
	ifs.open(COMPROOM_FILE, ios::in);

	ComputerRoom cr;
	while (ifs >> cr.m_RoomId && ifs >> cr.m_MaxNum)
	{
		crv.push_back(cr);
	}
	//cout << "��ǰ��������Ϊ��" << crv.size() << endl;
	ifs.close();
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "������������Ϊ��һ������" << endl;
	cout << "����������ԤԼ���ڣ�" << endl;
	cout << "1.��һ" << endl;
	cout << "2.�ܶ�" << endl;
	cout << "3.����" << endl;
	cout << "4.����" << endl;
	cout << "5.����" << endl;

	int date = 0;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "����������������룡" << endl;
	}

	cout << "����������ԤԼʱ��Σ�" << endl;
	cout << "1.����" << endl;
	cout << "2.����" << endl;

	int time = 0;
	while (true)
	{
		cin >> time;
		if (time >= 1 && time <= 2)
		{
			break;
		}
		cout << "����������������룡" << endl;
	}

	cout << "��ѡ�������" << endl;
	cout << "1�Ż���������" << crv[0].m_MaxNum << endl;
	cout << "2�Ż���������" << crv[1].m_MaxNum << endl;
	cout << "3�Ż���������" << crv[2].m_MaxNum << endl;

	int room = 0;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "����������������룡" << endl;
	}

	cout << "ԤԼ�ɹ�������С���" << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " " << "time:" << time << " ";
	ofs << "stuId:" << this->m_Id << " " << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " " << "status:" << 1 << endl; //status ԤԼ״̬

	ofs.close();
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	
	bool ret = false;
	for (int i = 1; i <= of.m_Size; i++)
	{
		//string ͨ�� c_str() תΪ c����ַ���(const char*)��Ȼ��ͨ��atoi(cosnt char*) תΪ int
		//if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id)
		//stoi �� C++11 ��׼������ַ���ת��������  stoi(const string&)
		if(stoi(of.m_OrderData[i]["stuId"]) == this->m_Id)
		{
			ret = true;
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
			cout << "  ʱ��Σ�" << (of.m_OrderData[i]["time"] == "1" ? "����" : "����");
			cout << "  ������ţ�" << of.m_OrderData[i]["roomId"];
			string status =  "  ״̬��"; 
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_OrderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			else
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			cout << status << endl;
		}
	}
	if(!ret)
		cout << "��ԤԼ��¼��" << endl;
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile of;

	bool ret = false;
	for (int i = 1; i <= of.m_Size; i++)
	{
		ret = true;
		cout << i << "��";
		cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
		cout << "  ʱ��Σ�" << (of.m_OrderData[i]["time"] == "1" ? "����" : "����");
		cout << "  ѧ�ţ�" << of.m_OrderData[i]["stuId"];
		cout << "  �û�����" << of.m_OrderData[i]["stuName"];
		cout << "  ������ţ�" << of.m_OrderData[i]["roomId"];
		string status = "  ״̬��"; // 0-ԤԼ��ȡ����1-����У�2-ԤԼ�ɹ���-1-ԤԼʧ��
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_OrderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		else
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		cout << status << endl;
	}
	if(!ret)
		cout << "��ԤԼ��¼��" << endl;
	system("pause");
	system("cls");
}

//ȡ��ԤԼ
void Student::CancelOrder()
{
	OrderFile of;

	bool ret = false;
	//cout << "����л���ԤԼ�ɹ��ļ�¼����ȡ����" << endl;

	vector<int> v; //�����������е��±���
	int index = 0; //��¼����������ԤԼ��¼ 
	for (int i = 1; i <= of.m_Size; i++)
	{
		//�ж�������ѧ�ţ����ҷ���ɸѡ״̬(����л���ԤԼ�ɹ�)
		if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_Id &&
			(of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2"))
		{
			ret = true;
			v.push_back(i);
			index++;

			cout << index << "��";
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
			cout << "  ʱ��Σ�" << (of.m_OrderData[i]["time"] == "1" ? "����" : "����");
			cout << "  ������ţ�" << of.m_OrderData[i]["roomId"];
			string status = "  ״̬��"; 
			if (of.m_OrderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_OrderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			cout << status << endl;
		}
	}
	if (!ret)
		cout << "û�п���ȡ����ԤԼ��¼" << endl;
	else
	{
		cout << "��������Ҫȡ���ļ�¼������0���أ�" << endl;
		int select = 0;

		while (true)
		{
			cin >> select;
			if (select >= 0 && select <= v.size())
			{
				if (select == 0)
				{
					cout << "ȡ��������" << endl;
					break;
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "0";
					of.updateOrder();

					cout << "��ȡ��ԤԼ" << endl;
					break;
				}
			}
			cout << "�����������������" << endl;
		}
	}
	system("pause");
	system("cls");
}