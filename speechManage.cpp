#include "speechManage.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <fstream>
#include <windows.h> 


Manage::Manage() {
	//��ʼ������
	initSpeaker();

	//����ѡ��
	createSpeaker();

	//��ȡ�����¼
	loadRecord();

}

Manage::~Manage()
{

}
void Manage::initMenu()
{
	cout << "**********************************************\n";
	cout << "**************** ��ӭ�μ��ݽ����� ************\n";
	cout << "**************** 1���μ��ݽ����� *************\n";
	cout << "**************** 2���鿴�����¼ *************\n";
	cout << "**************** 3����ձ�����¼ *************\n";
	cout << "**************** 0���˳��������� *************\n";
	cout << "**********************************************\n";
}

void Manage::exitSystem()
{
	cout << "Bye\n";
	system("pause");
	exit(0);
}

void Manage::initSpeaker()
{
	//��֤����Ϊ��
	v1.clear();
	v2.clear();
	v3.clear();
	m_speak.clear();
	//��ʼ����������
	m_index = 1;

	m_record.clear();
}

void Manage::createSpeaker()
{
	string named = "ABCDEFGHIJKL";
	for (int i = 0; i < named.size(); i++)
	{
		//��ʼ��ѡ������
		string name = "ѡ��";
		name += named[i];
		speaker sp;
		sp.m_name = name;

		//��ʼ������
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}

		//��ʼ��ѡ�ֱ��
		v1.push_back(i + 10001);

		//��ţ���������map������
		m_speak.insert(make_pair(i + 10001, sp));
	}
}

void Manage::gameStart()
{
	//��һ�ֱ���
	//1����ǩ
	drawLots();
	Sleep(2000);
	//2������
	Competition();
	Sleep(2000);
	//3����ʾ�������
	showScore();
	//�ڶ��ֱ�������ͬ��һ�֣�ֻ�Ǳ���������+1���������̲���
	m_index++;
	//1����ǩ
	drawLots();
	Sleep(2000);
	//2������
	Competition();
	Sleep(2000);
	//3����ʾ���ս��
	showScore();
	//4���������
	saveRecord();
	cout << "�������������лл����\n";
	//���ñ���
	//��ʼ������
	initSpeaker();
	//����ѡ��
	createSpeaker();
	//��ȡ�����¼
	loadRecord();
	system("pause");
	system("cls");
}

void Manage::drawLots()
{
	cout << "��" << m_index << "�ֱ���ѡ�ֳ�ǩ\n";
	cout << "-------------------------------------\n";
	cout << "��ǩ��˳�����£�\n";
	if (m_index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << "\n";
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << "\n";
	}
	cout << "-------------------------------------\n";
	system("pause");
	cout << endl;

}

void Manage::Competition()
{
	cout << "-----------��" << m_index << "�ֱ�����ʽ��ʼ-------------\n";
	multimap<double, int, greater<int>> groupScore;//��ʱ�������������(key)��ѡ�ֱ��(value)
	int num = 0;//��¼��Ա����6��һ��
	vector<int> v_Src;  //�μӱ�������Ա����
	if (m_index == 1)
		v_Src = v1;
	else
		v_Src = v2;
	//��������ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)//10����ί
		{
			double score = (rand() % 401 + 600) / 10.f;  //600~1000
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());  //����
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(),0.0f);//��ȡ�ܷ�
		double avg = sum / (double)d.size();//���ƽ����
		//ÿ���˵�ƽ����
		//cout << "���: " << *it << " ѡ�֣�" << m_speak[*it].m_name << "��ȡ��ƽ����Ϊ��" << avg << endl;//��ӡƽ����
		m_speak[*it].m_score[m_index - 1] = avg;
		//6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); 
				it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << " ������" << m_speak[it->second].m_name
					<< " �ɼ���" << m_speak[it->second].m_score[m_index - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin();
				it != groupScore.end() && count < 3; it++, count++)
			{
				if (m_index == 1)
					v2.push_back((*it).second);
				else
					v3.push_back((*it).second);
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "--------------��" << m_index << "�ֱ�������--------------------\n";
	system("pause");
}

void Manage::showScore()
{
	cout << "-------��" << m_index << "�ֽ����������£�-----------------------\n";
	vector<int>v;
	if (m_index == 1)
		v = v2;
	else
		v = v3;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������" << m_speak[*it].m_name
			<< " �÷֣�" << m_speak[*it].m_score[m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	initMenu();
}

void Manage::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);  //������ķ�ʽ���ļ� --д�ļ�

	//��ÿ������д���ļ���
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << "," << m_speak[*it].m_score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "��¼�Ѿ�����\n";
	m_isEmpty = false;

}

void Manage::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���������� ��ȡ�ļ�
	if (!ifs.is_open())
	{
		m_isEmpty = true;
		cout << "�ļ�������!\n";
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�\n";
		m_isEmpty = true;
		ifs.close();
		return;
	}
	m_isEmpty = false;
	ifs.putback(ch); //��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start); // ��0��ʼ���� ','
			if (pos == -1)
				break;//�Ҳ���������break
			string tmp = data.substr(start, pos - start);//�ҵ���,���зָ� ����1 ��ʼλ�ã�����2 ��ȡ����
			v.push_back(tmp);
			start = pos + 1;
		}
		m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void Manage::showRecord()
{
	if (m_isEmpty)
		cout << "�ļ���¼Ϊ�ջ��߲�����\n";
	for (int i = 0; i < m_record.size(); i++)
	{
		cout << "��" << i + 1 << "�� "
			<< "�ھ���ţ�" << m_record[i][0] << " �÷֣�" << m_record[i][1]
			<< " �Ǿ���ţ�" << m_record[i][2] << " �÷֣�" << m_record[i][3]
			<< " ������ţ�" << m_record[i][4] << " �÷֣�" << m_record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void Manage::clearRecord()
{
	cout << "�Ƿ���գ�\n";
	cout << "1��ȷ��\n";
	cout << "2��ȡ��\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ��ios::trunc  ������ڣ�ɾ��
		ofstream ofs("specch.csv", ios::trunc);
		ofs.close();

		//��ʼ��
		initSpeaker();

		createSpeaker();
		loadRecord();

		cout << "��ճɹ�\n";
		system("pause");
		system("cls");

	}
}