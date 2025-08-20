#pragma once
#include "Identity.h"
#include "globalFile.h"
#include "computerRoom.h"
#include <fstream>
#include <vector>
#include "orderFile.h"
#include <algorithm>
#include <string>

//学生类
class Student : public Identity
{
public:

	//默认构造
	Student();

	//有参构造
	Student(int id, string name, string pwd);

	//学生操作界面
	//建议使用override关键字显式标记，编译器会检查重写正确性
	void operMenu()override;

	//学生菜单
	void studentMenu(Identity*& student);

	//初始化机房容器，获取机房信息
	void initCompRoom();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void CancelOrder();

	//机房容器
	vector<ComputerRoom> crv;

	//学生学号
	int m_Id = 0;

};