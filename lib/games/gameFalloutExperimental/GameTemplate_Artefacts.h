#ifndef GAME_TAMPLE_ARTEFACTS_H
#define GAME_TAMPLE_ARTEFACTS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Artefacts     ");
#endif
GameTemplate_ArtefactsContainer.setContainerSize(2);
GameTemplate_ArtefactsContainer.setProperties(0,										(char*)"          ");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MEDUSA,		(char*)"������");
/*
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KAM_CVETOK,	(char*)"���.������");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_VSPYSHKA,		(char*)"�������");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_OGN_SHAR,		(char*)"���.���");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_PLENKA,		(char*)"������");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_VSPYSHKA,		(char*)"��������");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_LUN_SVET,		(char*)"���.����");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KRYSTAL,		(char*)"��������");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MORSKOI_EZH,	(char*)"������� ��");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_DUWA,			(char*)"����");
*/
#endif