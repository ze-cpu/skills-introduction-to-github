#include "orderFile.h"

//��ȡ�ַ��� ���磺date:111
void subStr(string& key, string& val, string& str, map<string, string>& m)
{
	int pos = str.find(":");
	if (pos != -1)
	{
		key = str.substr(0, pos);
		val = str.substr(pos + 1, str.size() - (pos + 1));
		//val = str.substr(pos + 1) //substrĬ�϶������һ���ַ�
		m.emplace(key, val);
		//m.insert(make_pair(key, val)); 
	}
}
//���캯��
OrderFile::OrderFile()
{
	this->m_OrderData.clear();
	this->m_Size = 0;  //��¼ԤԼ����

	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;    //����
	string time;	//ʱ���
	string stuId;	//ѧ��
	string stuName; //�û���
	string roomId;	//�������
	string status;	//ԤԼ״̬

	//���ո������Ϣ
	while (ifs >> date && ifs >> time && ifs >> stuId
		&& ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//�Ѷ�����Ϣ�ַ�����ȡ 
		string key;
		string value;
		map<string, string> m;
		
		subStr(key, value, date, m);	//��ȡ����
		subStr(key, value, time, m);	//��ȡʱ���
		subStr(key, value, stuId, m);	//��ȡѧ��
		subStr(key, value, stuName, m);	//��ȡ�û���
		subStr(key, value, roomId, m);	//��ȡ�������
		subStr(key, value, status, m);	//��ȡԤԼ״̬

		this->m_Size++;  //keyֵ��1��ʼ��¼
		this->m_OrderData.insert(make_pair(this->m_Size, m));
	}
	ifs.close();

	//����m_OrderDate
	//for (map<int, map<string, string>>::iterator it = this->m_OrderData.begin(); it != this->m_OrderData.end(); it++)
	//{
	//	cout << "�� " << (*it).first + 1 << " ��ԤԼ��ԤԼ��Ϣ��" << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
	//	{
	//		cout << "key = " << mit->first << "\tval = " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

//����ԤԼ��¼
void OrderFile::updateOrder()
{
	//û��ԤԼ��¼
	if (this->m_Size == 0)
	{
		cout << "û��ԤԼ��¼" << endl;
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