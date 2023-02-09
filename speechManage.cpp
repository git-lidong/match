#include "speechManage.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <deque>
#include <fstream>
#include <windows.h> 


Manage::Manage() {
	//初始化属性
	initSpeaker();

	//创建选手
	createSpeaker();

	//调取往届记录
	loadRecord();

}

Manage::~Manage()
{

}
void Manage::initMenu()
{
	cout << "**********************************************\n";
	cout << "**************** 欢迎参加演讲比赛 ************\n";
	cout << "**************** 1、参加演讲比赛 *************\n";
	cout << "**************** 2、查看往届记录 *************\n";
	cout << "**************** 3、清空比赛记录 *************\n";
	cout << "**************** 0、退出比赛程序 *************\n";
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
	//保证容器为空
	v1.clear();
	v2.clear();
	v3.clear();
	m_speak.clear();
	//初始化比赛轮数
	m_index = 1;

	m_record.clear();
}

void Manage::createSpeaker()
{
	string named = "ABCDEFGHIJKL";
	for (int i = 0; i < named.size(); i++)
	{
		//初始化选手姓名
		string name = "选手";
		name += named[i];
		speaker sp;
		sp.m_name = name;

		//初始化分数
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}

		//初始化选手编号
		v1.push_back(i + 10001);

		//编号，姓名放在map容器中
		m_speak.insert(make_pair(i + 10001, sp));
	}
}

void Manage::gameStart()
{
	//第一轮比赛
	//1、抽签
	drawLots();
	Sleep(2000);
	//2、比赛
	Competition();
	Sleep(2000);
	//3、显示晋级结果
	showScore();
	//第二轮比赛流程同第一轮，只是比赛的轮是+1，其余流程不变
	m_index++;
	//1、抽签
	drawLots();
	Sleep(2000);
	//2、比赛
	Competition();
	Sleep(2000);
	//3、显示最终结果
	showScore();
	//4、保存分数
	saveRecord();
	cout << "本届比赛结束，谢谢参与\n";
	//重置比赛
	//初始化属性
	initSpeaker();
	//创建选手
	createSpeaker();
	//调取往届记录
	loadRecord();
	system("pause");
	system("cls");
}

void Manage::drawLots()
{
	cout << "第" << m_index << "轮比赛选手抽签\n";
	cout << "-------------------------------------\n";
	cout << "抽签后顺序如下：\n";
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
	cout << "-----------第" << m_index << "轮比赛正式开始-------------\n";
	multimap<double, int, greater<int>> groupScore;//临时容器，保存分数(key)，选手编号(value)
	int num = 0;//记录人员数，6人一组
	vector<int> v_Src;  //参加比赛的人员容器
	if (m_index == 1)
		v_Src = v1;
	else
		v_Src = v2;
	//遍历参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)//10个评委
		{
			double score = (rand() % 401 + 600) / 10.f;  //600~1000
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());  //排序
		d.pop_front();//去掉最高分
		d.pop_back();//去掉最低分
		double sum = accumulate(d.begin(), d.end(),0.0f);//获取总分
		double avg = sum / (double)d.size();//获得平均分
		//每个人的平均分
		//cout << "编号: " << *it << " 选手：" << m_speak[*it].m_name << "获取的平均分为：" << avg << endl;//打印平均分
		m_speak[*it].m_score[m_index - 1] = avg;
		//6个人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); 
				it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << " 姓名：" << m_speak[it->second].m_name
					<< " 成绩：" << m_speak[it->second].m_score[m_index - 1] << endl;
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
	cout << "--------------第" << m_index << "轮比赛结束--------------------\n";
	system("pause");
}

void Manage::showScore()
{
	cout << "-------第" << m_index << "轮晋级名单如下：-----------------------\n";
	vector<int>v;
	if (m_index == 1)
		v = v2;
	else
		v = v3;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名：" << m_speak[*it].m_name
			<< " 得分：" << m_speak[*it].m_score[m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	initMenu();
}

void Manage::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);  //用输出的方式打开文件 --写文件

	//将每个数据写入文件中
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << "," << m_speak[*it].m_score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "记录已经保存\n";
	m_isEmpty = false;

}

void Manage::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//输入流对象 读取文件
	if (!ifs.is_open())
	{
		m_isEmpty = true;
		cout << "文件不存在!\n";
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！\n";
		m_isEmpty = true;
		ifs.close();
		return;
	}
	m_isEmpty = false;
	ifs.putback(ch); //读取的单个字符放回去

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
			pos = data.find(",", start); // 从0开始查找 ','
			if (pos == -1)
				break;//找不到，所以break
			string tmp = data.substr(start, pos - start);//找到了,进行分割 参数1 起始位置，参数2 截取长度
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
		cout << "文件记录为空或者不存在\n";
	for (int i = 0; i < m_record.size(); i++)
	{
		cout << "第" << i + 1 << "届 "
			<< "冠军编号：" << m_record[i][0] << " 得分：" << m_record[i][1]
			<< " 亚军编号：" << m_record[i][2] << " 得分：" << m_record[i][3]
			<< " 季军编号：" << m_record[i][4] << " 得分：" << m_record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void Manage::clearRecord()
{
	cout << "是否清空：\n";
	cout << "1、确定\n";
	cout << "2、取消\n";
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式，ios::trunc  如果存在，删除
		ofstream ofs("specch.csv", ios::trunc);
		ofs.close();

		//初始化
		initSpeaker();

		createSpeaker();
		loadRecord();

		cout << "清空成功\n";
		system("pause");
		system("cls");

	}
}