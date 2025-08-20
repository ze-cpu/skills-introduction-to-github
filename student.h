#pragma once
#include "Identity.h"
#include "globalFile.h"
#include "computerRoom.h"
#include <fstream>
#include <vector>
#include "orderFile.h"
#include <algorithm>
#include <string>

//ѧ����
class Student : public Identity
{
public:

	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, string name, string pwd);

	//ѧ����������
	//����ʹ��override�ؼ�����ʽ��ǣ�������������д��ȷ��
	void operMenu()override;

	//ѧ���˵�
	void studentMenu(Identity*& student);

	//��ʼ��������������ȡ������Ϣ
	void initCompRoom();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void CancelOrder();

	//��������
	vector<ComputerRoom> crv;

	//ѧ��ѧ��
	int m_Id = 0;

};