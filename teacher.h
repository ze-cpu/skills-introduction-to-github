#pragma once
#include "Identity.h"
#include "orderFile.h"
#include <vector>

//��ʦ��
class Teacher : public Identity
{
public:

	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int empId, string name, string pwd);

	//��ʦ��������
	void operMenu()override; 

	//��ʦ�˵�
	void teacherMenu(Identity*& teacher);

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	//��ʦְ�����
	int m_EmpId = 0;

};