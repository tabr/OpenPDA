#ifndef GAMETEMPLATE_QUESTS_H_
#define GAMETEMPLATE_QUESTS_H_
	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Quests        ");
	#endif
	Quest.RegisterNew(1,				(char*)"���������� � ������ ���������",	2);
	Quest.RegisterNew(2,				(char*)"���������� �������� �����",		3);
	Quest.RegisterNew(3,				(char*)"����� ������������",			4);
	Quest.RegisterNew(4,				(char*)"�������� ������������",			5);
	Quest.RegisterNew(5,				(char*)"�������� ������ �����",			0);
#endif //GAMETEMPLATE_QUESTS_H_