#pragma once
#include "Identity.h"
#include "orderFile.h"
#include <vector>

//教师类
class Teacher : public Identity
{
public:

	//默认构造
	Teacher();

	//有参构造
	Teacher(int empId, string name, string pwd);

	//教师操作界面
	void operMenu()override; 

	//教师菜单
	void teacherMenu(Identity*& teacher);

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//教师职工编号
	int m_EmpId = 0;

};