#ifndef GAMETEMPLATE_QUESTS_H_
#define GAMETEMPLATE_QUESTS_H_
//BARABAN
	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Quests        ");
	#endif
	Quest.setQuestsNum(TemporaryClass::QUESTS_NUM - 1);
	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				(char*)"����� �� ����");
	//	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				tmp);
	Quest.registerNew(TemporaryClass::QID_FIND_KEY,				(char*)"����� ���� �� ����");
	//	Quest.registerNew(TemporaryClass::QID_FIND_BARMAN,			(char*)"����� ���������� �������");
	//	sprintf(tmp,"����� ���������� �������");
	//	Quest.registerNew(TemporaryClass::QID_FIND_BAR,				tmp);
#endif //GAMETEMPLATE_QUESTS_H_