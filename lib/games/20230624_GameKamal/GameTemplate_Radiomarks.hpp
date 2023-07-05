#ifndef GAMETEMPLATE_RADIOMARKS_H_
#define GAMETEMPLATE_RADIOMARKS_H_
//flash uint8_t anoradData[16][PACKET_SIZE]=

#include "GameTemplate_TemporaryClass.hpp"
//#include "./../../../x128_test2/src/RadiomarkClass.h"
/*
//#define ANORAD_IDS_NUM						32
#define ANORAD_PARAMETERS					5
#define ANORAD_PARAMETER_TYPE				0x00
#define ANORAD_PARAMETER_RAD_MULTIPLIER		0x01
#define ANORAD_PARAMETER_ANO_TYPE			0x02
#define ANORAD_PARAMETER_ANO_SKIP			0x03
#define ANORAD_PARAMETER_ANO_KILL			0x04
#define ANORAD_PARAMETER_0					0x01
#define ANORAD_PARAMETER_1					0x02
#define ANORAD_PARAMETER_2					0x03
#define ANORAD_PARAMETER_3					0x04
*/
//GameCFG.Radiomarks.SetRadiomarksNum(TemporaryClass::ANORAD_IDS_NUM);
//GameCFG.Radiomarks.SetRadiomarksNum(30);
//									[PARAM0]
//								ID	[TYPE]																					[RADANO_RAD_MULTIPLIER]					[RADANO_ANO_TYPE]      					    [RADANO_ANO_SKIP_LEVEL] [RADANO_ANO_KILL_LEVEL]

GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(1,  RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_ELECTRA,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(2,  RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_ELECTRA,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(3,  RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_ELECTRA,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(4,  RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_ELECTRA,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(5,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_HOLODEC,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(6,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_HOLODEC,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(7,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_HOLODEC,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(8,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_HOLODEC,			75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(9,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_TRAMPLIN,		75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(10,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_TRAMPLIN,		75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(11,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_TRAMPLIN,		75,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(12,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,										TemporaryClass::ANOMALY_ID_TRAMPLIN,		75,			0));

GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(13,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(14,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(15,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(16,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(17,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(18,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(19,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,										0,											0,			0));

GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(20,	RadiomarkInstanceClass::RADIOMARK_TYPE_GRAVEYARD,				0,										0,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(21,	RadiomarkInstanceClass::RADIOMARK_TYPE_GRAVEYARD,				0,										0,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(22,	RadiomarkInstanceClass::RADIOMARK_TYPE_GRAVEYARD,				0,										0,											0,          0));

GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(23,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						1,										0,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(24,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						1,										0,											0,          0));

GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(25,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,										0,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(26,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,										0,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(27,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,										0,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(28,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,										0,											0,          0));

GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(29,	RadiomarkInstanceClass::RADIOMARK_TYPE_QUEST,					RADIOMARK_TYPE_QUEST_ACTION_GIVE,		1,											0,          0));
GameCFG.RegisterNewRadiomark(new RadiomarkInstanceClass(30,	RadiomarkInstanceClass::RADIOMARK_TYPE_QUEST,					RADIOMARK_TYPE_QUEST_ACTION_COMPLETE,	1,											0,          0));

#endif //GAMETEMPLATE_RADIOMARKS_H_