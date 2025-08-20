#pragma once
#include <iostream>
#include "globalFile.h"
#include <fstream>
#include <map>

class OrderFile
{
public:

	//构造函数
	OrderFile();

	//更新预约
	void updateOrder();

	//记录预约条数
	int m_Size = 0;

	//记录所有预约信息的容器 key:记录预约条数  value:记录每条预约信息
	map<int, map<string, string>> m_OrderData;

};