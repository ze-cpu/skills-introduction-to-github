#pragma once
#include "manager.h"
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "Identity.h"
#include <fstream>

//��¼����  �����������ļ����������������
void LoginIn(string fileName, int type)
{
	//����ָ��  ����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	//�ļ����ڣ�׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1) //ѧ��
	{
		cout << "����������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2) //��ʦ
	{
		cout << "����������ְ����ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	//�ж��Ƿ���֤�ɹ�
	bool isAuthenticated = false;

	if (type == 1)
	{
		//ѧ�������֤
		//�ļ��ж�ȡ��id�ţ�����������
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//cout << fId << "\t" << fName << "\t" <<fPwd <<endl;
			//�ж��ļ���Ϣ�Ƿ���û�������Ϣһ��
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				person = new Student(id, name, pwd);

				system("pause");
				system("cls");

				//����ѧ���Ӳ˵�
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
		//��ʦ�����֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				person = new Teacher(id, name, pwd);

				system("pause");
				system("cls");

				//�����ʦ�Ӳ˵�
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
		//����Ա�����֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)
		{
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				person = new Manager(name, pwd);

				system("pause");
				system("cls");

				//�������Ա�Ӳ˵�
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
		cout << "��֤��¼ʧ�ܣ�" << endl;

		system("pause");
		system("cls");
	}
}

void mainMenu()
{
	int select = 0; //���ڽ����û�ѡ��
	while (true)
	{
		cout << "====================  ��ӭ����me�Ļ���ԤԼϵͳ  ====================" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t   ------------------------------\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          1.ѧ������          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          2.��    ʦ          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          3.�� �� Ա          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t  |          0.��    ��          |\n";
		cout << "\t\t  |                              |\n";
		cout << "\t\t   ------------------------------\n";

		cout << "����������ѡ��" << " ";
		cin >> select;

		switch (select)  //�����û�ѡ��ʵ�ֲ�ͬ�ӿ�
		{
		case 1: //ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: //��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3: //����Ա
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}