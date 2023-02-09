#pragma once
#include "Speecher.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Manage
{
private:
	vector<int> v1;  //比赛选手容器 12人

	vector<int> v2;  //第一轮晋级容器  6人

	vector<int> v3;  //胜利前三人容器  3人

	int m_index;  //比赛轮数
public:
	Manage();
	~Manage();
	void initMenu();  //菜单初始化

	void exitSystem();  //退出功能

	void initSpeaker();
	void createSpeaker();

	map<int, speaker> m_speak;  //存放编号选手姓名的容器

	void gameStart();

	void drawLots();//抽签

	void Competition(); //比赛

	void showScore();  //显示结果

	void saveRecord();  //保存结果

	void loadRecord();  //读取往届记录

	bool m_isEmpty;  //判断文件是否为空

	//往届记录的容器m_Record 中的key代表第几届,value记录具体的信息
	map<int, vector<string>> m_record;

	void showRecord();  //显示往届记录

	void clearRecord(); //清空记录





};