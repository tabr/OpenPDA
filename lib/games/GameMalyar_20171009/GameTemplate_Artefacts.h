#ifndef GAME_TAMPLE_H
#define GAME_SUITS_H

#ifdef DEBUG_BUILD
	LcdStringUpdate(1,LCD_LINE_2, (char*)"Artefacts     ");
#endif
GameCFG.ArtefactsContainer.setContainerSize(10);
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MEDUSA,			(char*)"медуза");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KAM_CVETOK,		(char*)"кам.цветок");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_VSPYSHKA,		(char*)"вспышка");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_OGN_SHAR,		(char*)"огн.шар");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_PLENKA,			(char*)"пленка");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_PUSTIWKA,		(char*)"пустышка");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_LUN_SVET,		(char*)"лун.свет");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_KRYSTAL,		(char*)"кристалл");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_MORSKOI_EZH,	(char*)"морской еж");
GameCFG.ArtefactsContainer.setProperties(TemporaryClass::ARTEFACTID_DUWA,			(char*)"душа");
#endif