#pragma once
#include "Identity.h"
#include <fstream>
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include "algorithm"
#include "computerRoom.h"

//����Ա��
class Manager : public Identity
{
public:

	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//����Ա��������
	void operMenu()override;

	//����Ա�˵�
	void managerMenu(Identity*& manager);

	//����ظ�  ����(id , ����)
	bool checkRepeat(int id, int type);

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showCompRoom();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������
	void initVector();

	//ѧ������
	vector<Student> sv;

	//��ʦ����
	vector<Teacher> tv;

	//��ʼ����������
	void initCompRoom();

	//��������
	vector<ComputerRoom> crv;
};