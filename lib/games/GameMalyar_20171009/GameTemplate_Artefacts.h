#ifndef GAME_TAMPLE_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Artefacts     ");
#endif
GameCFG.ArtefactsContainer.setContainerSize(10);
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MEDUSA,			(char*)"������");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KAM_CVETOK,		(char*)"���.������");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_VSPYSHKA,		(char*)"�������");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_OGN_SHAR,		(char*)"���.���");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_PLENKA,			(char*)"������");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_PUSTIWKA,		(char*)"��������");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_LUN_SVET,		(char*)"���.����");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KRYSTAL,		(char*)"��������");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MORSKOI_EZH,	(char*)"������� ��");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_DUWA,			(char*)"����");
#endif