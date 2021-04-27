#ifndef GAME_TAMPLE_ARTEFACTS_H
#define GAME_TAMPLE_ARTEFACTS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Artefacts     ");
#endif
GameTemplate_ArtefactsContainer.setContainerSize(2);
GameTemplate_ArtefactsContainer.setProperties(0,										(char*)"          ");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MEDUSA,		(char*)"медуза");
/*
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KAM_CVETOK,	(char*)"кам.цветок");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_VSPYSHKA,		(char*)"вспышка");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_OGN_SHAR,		(char*)"огн.шар");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_PLENKA,		(char*)"пленка");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_VSPYSHKA,		(char*)"пустышка");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_LUN_SVET,		(char*)"лун.свет");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KRYSTAL,		(char*)"кристалл");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MORSKOI_EZH,	(char*)"морской еж");
GameTemplate_ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_DUWA,			(char*)"душа");
*/
#endif