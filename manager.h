#pragma once
#include "Identity.h"
#include <fstream>
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include "algorithm"
#include "computerRoom.h"

//管理员类
class Manager : public Identity
{
public:

	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//管理员操作界面
	void operMenu()override;

	//管理员菜单
	void managerMenu(Identity*& manager);

	//检测重复  参数(id , 类型)
	bool checkRepeat(int id, int type);

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showCompRoom();

	//清空预约记录
	void cleanFile();

	//初始化容器
	void initVector();

	//学生容器
	vector<Student> sv;

	//教师容器
	vector<Teacher> tv;

	//初始化机房容器
	void initCompRoom();

	//机房容器
	vector<ComputerRoom> crv;
};