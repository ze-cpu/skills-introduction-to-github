#include "orderFile.h"

//截取字符串 例如：date:111
void subStr(string& key, string& val, string& str, map<string, string>& m)
{
	int pos = str.find(":");
	if (pos != -1)
	{
		key = str.substr(0, pos);
		val = str.substr(pos + 1, str.size() - (pos + 1));
		//val = str.substr(pos + 1) //substr默认读到最后一个字符
		m.emplace(key, val);
		//m.insert(make_pair(key, val)); 
	}
}
//构造函数
OrderFile::OrderFile()
{
	this->m_OrderData.clear();
	this->m_Size = 0;  //记录预约条数

	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;    //日期
	string time;	//时间段
	string stuId;	//学号
	string stuName; //用户名
	string roomId;	//机房编号
	string status;	//预约状态

	//按空格读入信息
	while (ifs >> date && ifs >> time && ifs >> stuId
		&& ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//把读入信息字符串截取 
		string key;
		string value;
		map<string, string> m;
		
		subStr(key, value, date, m);	//截取日期
		subStr(key, value, time, m);	//截取时间段
		subStr(key, value, stuId, m);	//截取学号
		subStr(key, value, stuName, m);	//截取用户名
		subStr(key, value, roomId, m);	//截取机房编号
		subStr(key, value, status, m);	//截取预约状态

		this->m_Size++;  //key值从1开始记录
		this->m_OrderData.insert(make_pair(this->m_Size, m));
	}
	ifs.close();

	//测试m_OrderDate
	//for (map<int, map<string, string>>::iterator it = this->m_OrderData.begin(); it != this->m_OrderData.end(); it++)
	//{
	//	cout << "第 " << (*it).first + 1 << " 条预约的预约信息：" << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
	//	{
	//		cout << "key = " << mit->first << "\tval = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

//更新预约记录
void OrderFile::updateOrder()
{
	//没有预约记录
	if (this->m_Size == 0)
	{
		cout << "没有预约记录" << endl;
		return; 
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);

	for (int i = 1; i <= this->m_Size; i++)
	{
		ofs << "date:" << this->m_OrderData[i]["date"] << " ";
		ofs << "time:" << this->m_OrderData[i]["time"] << " ";
		ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_OrderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << endl;
	}
	ofs.close();
}