#pragma once
#include <iostream>
#include "globalFile.h"
#include <fstream>
#include <map>

class OrderFile
{
public:

	//���캯��
	OrderFile();

	//����ԤԼ
	void updateOrder();

	//��¼ԤԼ����
	int m_Size = 0;

	//��¼����ԤԼ��Ϣ������ key:��¼ԤԼ����  value:��¼ÿ��ԤԼ��Ϣ
	map<int, map<string, string>> m_OrderData;

};