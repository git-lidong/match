#include "speechManage.h"
#include <iostream>

int main()
{
	srand((unsigned int)time(NULL));
	Manage m;
	
	/*for (map<int, speaker>::iterator it = m.m_speak.begin(); it != m.m_speak.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first
			<< " ������" << it->second.m_name
			<< " �ɼ���" << it->second.m_score[0] << endl;
	}*/

	int select;
	while (true)
	{
		m.initMenu();
		cout << "����������ѡ��: \n";
		cin >> select;
		switch (select)
		{
		case 1:   //��ʼ����
			m.gameStart();
			break;
		case 2:
			m.showRecord();
			break;
		case 3:
			m.clearRecord();
			break;
		case 0:
			m.exitSystem();
			break;
		}
	}

	system("pause");
	return 0;
}
