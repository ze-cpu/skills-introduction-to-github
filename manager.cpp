#include "manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{
}

//�вι���
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ������  ��ȡ�����ļ���ѧ������ʦ��Ϣ
	this->initVector();

	//��ʼ����������
	this->initCompRoom();
}

//��ʼ��������������ȡ������Ϣ
void Manager::initCompRoom()
{
	ifstream ifs;
	ifs.open(COMPROOM_FILE, ios::in);

	ComputerRoom cr;
	while (ifs >> cr.m_RoomId && ifs >> cr.m_MaxNum)
	{
		crv.push_back(cr);
	}
	//cout << "��ǰ��������Ϊ��" <<crv.size() << endl;
	ifs.close();
}

//��ʼ����������ȡѧ������ʦ��Ϣ
void Manager::initVector()
{
	//�������
	sv.clear();
	tv.clear();

	ifstream ifs;
	//��ȡѧ���ļ�
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		sv.push_back(s);
	}
	//cout << "��ǰѧ������Ϊ��" << sv.size() << endl;
	ifs.close();

	//��ȡ��ʦ�ļ�
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		tv.push_back(t);
	}
	//cout << "��ǰ��ʦ����Ϊ��" << tv.size() << endl;
	ifs.close();
}

//����Ա��������
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t   ------------------------------\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          1.����˺�          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          2.�鿴�˺�          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          3.�鿴����          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          4.���ԤԼ          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t  |          0.�˳���¼          |\n";
	cout << "\t\t  |                              |\n";
	cout << "\t\t   ------------------------------\n";
	
	cout << "����������ѡ��" << " ";
}

//����Ա�˵�
void Manager::managerMenu(Identity*& manager)
{
	while (true)
	{
		manager->operMenu();
		//dynamic_cast��������̳в�νṹ�н��а�ȫ������ת��
		Manager* man = dynamic_cast<Manager*>(manager);

		int select = 0;
		cin >> select;

		switch (select)
		{
		case 1:  //����˺�
			//cout << "����˺�" << endl;
			man->addPerson();
			break;
		case 2:  //�鿴�˺�
			//cout << "�鿴�˺�" << endl;
			man->showPerson();
			break;
		case 3:  //�鿴����
			//cout << "�鿴����" << endl;
			man->showCompRoom();
			break;
		case 4:  //���ԤԼ
			//cout << "���ԤԼ" << endl;
			man->cleanFile();
			break;
		case 0:  //�˳���¼
			delete manager; //���ٵ���������
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

//����ظ�  ����(id , ����)
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//���ѧ��
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
		//����ʦ
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

//����˺�
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.��ӽ�ʦ" << endl;

	string fileName;
	string tip;
	string errorTip;  //�ظ�������ʾ

	int select = 0;
	while (true)
	{
		cin >> select;

		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tip = "������ѧ�ţ�";
			errorTip = "ѧ���ظ�������������";
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "������ְ����ţ�";
			errorTip = "ְ������ظ�������������";
			break;
		}
		else
		{
			cout << "����������������룺" << " ";
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

	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;
	ofs.close();

	//���ó�ʼ������������ǰ����ӵ���Ϣ��������
	this->initVector();

	system("pause");
	system("cls");
}

//�鿴�˺�
void PrintStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_Id << "\t�û�����" << s.m_Name << "\t���룺" << s.m_Pwd << endl;
}
void PrintTeacher(Teacher& t)
{
	cout << "ְ����ţ�" << t.m_EmpId << "\t�û�����" << t.m_Name << "\t���룺" << t.m_Pwd << endl;
}
void Manager::showPerson()
{
	cout << "��ѡ��Ҫ�鿴�˺ŵ����ͣ�" << endl;
	cout << "1.ѧ���˺�" << endl;
	cout << "2.��ʦ�˺�" << endl;

	int select = 0;
	while (true)
	{
		cin >> select;

		if (select == 1)
		{
			cout << "����ѧ���˺���Ϣ���£�" << endl;
			for_each(sv.begin(), sv.end(), PrintStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "���н�ʦ�˺���Ϣ���£�" << endl;
			for_each(tv.begin(), tv.end(), PrintTeacher);
			break;
		}
		else
		{
			cout << "����������������룺" << " ";
		}
	}
	
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showCompRoom()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = crv.begin(); it != crv.end(); it++)
	{
		cout << "������ţ�" << (*it).m_RoomId << "\t�������������" << (*it).m_MaxNum << endl;
	}

	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}