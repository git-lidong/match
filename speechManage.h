#pragma once
#include "Speecher.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

class Manage
{
private:
	vector<int> v1;  //����ѡ������ 12��

	vector<int> v2;  //��һ�ֽ�������  6��

	vector<int> v3;  //ʤ��ǰ��������  3��

	int m_index;  //��������
public:
	Manage();
	~Manage();
	void initMenu();  //�˵���ʼ��

	void exitSystem();  //�˳�����

	void initSpeaker();
	void createSpeaker();

	map<int, speaker> m_speak;  //��ű��ѡ������������

	void gameStart();

	void drawLots();//��ǩ

	void Competition(); //����

	void showScore();  //��ʾ���

	void saveRecord();  //������

	void loadRecord();  //��ȡ�����¼

	bool m_isEmpty;  //�ж��ļ��Ƿ�Ϊ��

	//�����¼������m_Record �е�key����ڼ���,value��¼�������Ϣ
	map<int, vector<string>> m_record;

	void showRecord();  //��ʾ�����¼

	void clearRecord(); //��ռ�¼





};