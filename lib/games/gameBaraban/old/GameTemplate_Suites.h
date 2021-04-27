#ifndef GAME_SUITES_H
#define GAME_SUITES_H
	#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suites        ");
	#endif
	//!!!!!!!!!!!������!!! ������ ����������� ������ ������������� �� 0�00
	//	GameCFG.load();
	//														���														[����.���������]		[���.���]	[���.���]	[���.�������]	[���.�����]	[���.���]	[���.����]	[����.�����������]
	GameCFG.SuitsContainer.setContainerSize(TemporaryClass::SUITE_ID_SIZE);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_NONE].setProperties((char*)("(�����)"),				1,						0,			0,			0,				0,			0,			0,			1);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ZARYA].setProperties((char*)("����"),					100,					5,			0,			0,				0,			50,			0,			4);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_MONOLIT].setProperties((char*)("������.�������"),		100,					50,			0,			0,				0,			50,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_KOZH].setProperties((char*)("�������"),				100,					5,			0,			0,				0,			5,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BANDOS].setProperties((char*)("����.������"),			100,					0,			0,			0,				0,			5,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ECOLOG].setProperties((char*)("���-99 ������"),		100,					50,			0,			0,				0,			90,			0,			5);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_BERYL].setProperties((char*)("������-5�"),				100,					10,			0,			0,				0,			30,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_ARM_BRONE].setProperties((char*)("���.����������"),	100,					5,			0,			0,				0,			10,			0,			2);
	GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_EXO].setProperties((char*)("����������"),				100,					50,			0,			0,				0,			70,			0,			4);
	

#endif