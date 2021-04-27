#ifndef GAME_SUITS_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Suites        ");
#endif
//!!!!!!!!!!!������!!! ������ ����������� ������ ������������� �� 0�00
//	GameCFG.load();
//														���														[����.���������]	[���.���]	[���.���]	[���.�������]	[���.�����]	[���.���]	[���.����]	[����.�����������]
GameCFG.SuitsContainer.setContainerSize(TemporaryClass::SUITE_ID_SIZE);
//GameCFG.SuitsContainer.container[TemporaryClass::SUITE_ID_NONE].setProperties((char*)("(�����)"),				0,					0,			0,			0,				0,			0,			0,			1);
GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_NONE)->setProperties((char*)("(�����)"),				0,					0,			0,			0,				0,			0,			0,			1);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_ZARYA)->setProperties((char*)("����"),					1000,				5,			50,			50,				50,			50,			25,			4);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_SEVA)->setProperties((char*)("����"),					2000,				10,			70,			90,				80,			90,			50,			5);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_MONOLIT).setProperties((char*)("������.�������"),		1250,				10,			50,			60,				50,			50,			25,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_KOZH).setProperties((char*)("�������"),				1000,				0,			10,			10,				10,			5,			0,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_KOZH1).setProperties((char*)("�������*"),				1500,				5,			30,			30,				30,			30,			10,			3);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BANDOS).setProperties((char*)("����.������"),			900,				0,			10,			10,				10,			5,			0,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BANDOS1).setProperties((char*)("����.������*"),		1250,				5,			40,			40,				40,			40,			15,			3);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_ECOLOG).setProperties((char*)("���-99 ������"),		1000,				10,			90,			90,				90,			90,			50,			5);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BERYL).setProperties((char*)("������-5�"),			2000,				10,			30,			30,				30,			30,			20,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_BRONE).setProperties((char*)("���.����������"),		1500,				0,			10,			10,				10,			10,			0,			2);
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_HALAT).setProperties((char*)("�����.�����"),			400,				5,			30,			30,				30,			30,			5,			2);
//DamageListStruct dmg	= {.DamageRadiation=0, .DamageElectromagnetic=0,};
//GameCFG.SuitsContainer.getSuiteInstance(TemporaryClass::SUITE_ID_NONE).setProperties((char*)("(�����)"),				0,					0, dmg);

#endif
