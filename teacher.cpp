#include "teacher.h"

//Ĭ�Ϲ���
Teacher::Teacher()
{
}

//�вι���
Teacher::Teacher(int empId, string name, string pwd)
{
	//��ʼ����ʦ��Ϣ
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//��ʦ��������
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ��" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t   ------------------------------\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |         1.�鿴����ԤԼ       |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          2.���ԤԼ          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          0.�˳���¼          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t   ------------------------------\n";

	cout << "����������ѡ��" << " ";
}

//��ʦ�˵�
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
		case 1:  //�鿴����ԤԼ
			teac->showAllOrder();
			break;
		case 2:  //ԤԼ���
			teac->validOrder();
			break;
		case 0:  //�˳���¼
			delete teacher; //���ٵ���������
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

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	OrderFile of;

	bool ret = false;
	cout << "����ԤԼ��Ϣ���£�" << endl;
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
	if (!ret)
		cout << "��ԤԼ��¼" << endl;
	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	
	bool boolret = false;
	//cout << "����еļ�¼����ȡ����" << endl;

	vector<int> v; //�����������е��±���
	int index = 0; //��¼����������ԤԼ��¼ 
	for (int i = 1; i <= of.m_Size; i++)
	{
		if(of.m_OrderData[i]["status"] == "1")
		{
			boolret = true;
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
			cout << status << endl;
		}
	}

	if (!boolret)
		cout << "û����Ҫ��˵�ԤԼ��¼" << endl;
	else
	{
		cout << "��������Ҫ��˵�ԤԼ��¼������0���أ�" << endl;
		int select = 0;
		int ret = 0;

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
					cout << "��������˽��" << endl;
					cout << "1.ͨ��" << endl;
					cout << "2.��ͨ��" << endl;

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
					cout << "�����ϣ�" << endl;
					break;
				}
			}
			cout << "�����������������" << endl;
		}
	}
	system("pause");
	system("cls");
}