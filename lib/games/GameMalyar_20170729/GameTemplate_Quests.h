#ifndef GAMETEMPLATE_QUESTS_H_
#define GAMETEMPLATE_QUESTS_H_
	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Quests        ");
	#endif
	Quest.RegisterNew(1,				(char*)"Проникнуть в старую котельную",	2);
	Quest.RegisterNew(2,				(char*)"Уничтожить главного зомби",		3);
	Quest.RegisterNew(3,				(char*)"найти бензоколонки",			4);
	Quest.RegisterNew(4,				(char*)"Взорвать бензоколонки",			5);
	Quest.RegisterNew(5,				(char*)"Взорвать логово зомби",			0);
#endif //GAMETEMPLATE_QUESTS_H_