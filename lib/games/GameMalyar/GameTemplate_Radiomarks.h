#ifndef GAMETEMPLATE_RADIOMARKS_H_
#define GAMETEMPLATE_RADIOMARKS_H_
//BARABAN
//flash uint8_t anoradData[16][PACKET_SIZE]=

#include "GameTemplate_TemporaryClass.h"
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
GameCFG.Radiomarks.SetRadiomarksNum(24);
//									[PARAM0]
//								ID	[TYPE]															[RADANO_RAD_MULTIPLIER]						[RADANO_ANO_TYPE]      					[RADANO_ANO_SKIP_LEVEL] [RADANO_ANO_KILL_LEVEL]
GameCFG.Radiomarks.RegisterNew(1,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(2,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0);
//GameCFG.Radiomarks.RegisterNew(2,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_KISEL,		30,						255);
GameCFG.Radiomarks.RegisterNew(3,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(4,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(5,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(6,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0);
GameCFG.Radiomarks.RegisterNew(7,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		3,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(8,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		3,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(9,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(10,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(11,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(12,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(13,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(14,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(15,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(16,	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(17,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(18,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(19,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(20,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(21,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(22,	RadiomarkInstanceClass::RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(23,	RadiomarkInstanceClass::RADIOMARK_TYPE_REVIVE,					0,											0,                      				0,						0);
GameCFG.Radiomarks.RegisterNew(24,	RadiomarkInstanceClass::RADIOMARK_TYPE_REVIVE,					0,											0,                      				0,						0);
//GameCFG.Radiomarks.RegisterNew(25,	RadiomarkInstanceClass::RADIOMARK_TYPE_ARTEFACT,				0,											0,                      				0,						0);
//GameCFG.Radiomarks.RegisterNew(26,	RadiomarkInstanceClass::RADIOMARK_TYPE_ARTEFACT,				0,											0,                      				0,						0);

//GameCFG.Radiomarks.RegisterNew(9,	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0);
//GameCFG.Radiomarks.RegisterNew(,	);
//#ifdef ANORAD_IN_FLASH
//const uint8_t anoradData[ANORAD_IDS_NUM][ANORAD_PARAMETERS] PROGMEM = 
//#else
//uint8_t anoradData[ANORAD_IDS_NUM][ANORAD_PARAMETERS]=
//#endif // ANORAD_IN_FLASH
//{
////																		[PARAM0]                   
////ID		[TYPE]															[RADANO_RAD_MULTIPLIER]						[RADANO_ANO_TYPE]       				[RADANO_ANO_SKIP_LEVEL] [RADANO_ANO_KILL_LEVEL]
///*00*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_NONE,					0,											0,                      				0,                      0}, //пустой - нахуа?!
///*01*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,                      0}, //рад зомби
///*02*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,                      0},
///*03*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,                      0},
///*04*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,                      0},
///*05*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		2,											0,                      				0,                      0},
///*06*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		2,											0,                      				0,                      0},
///*07*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,                      0},
///*08*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		3,											0,										0,                      0},
///*09*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
///*10*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_KISEL,		30,                     255},
///*11*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_KISEL,		30,                     255},
///*12*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											TemporaryClass::ANOMALY_TYPE_KISEL,		30,                     255},
///*13*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_JARKA,		30,                     80},
///*14*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_JARKA,		30,                     80},
///*15*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_QUEST,					RADIOMARK_TYPE_QUEST_ACTION_COMPLETE,		TemporaryClass::QID_FIND_KEY,		0,							0},
///*16*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											TemporaryClass::ANOMALY_TYPE_ELECTRA,	20,						80},
///*17*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_ELECTRA,	20,						80},
///*18*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_KARUSEL,	20,						80},
///*19*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,                      0},
///*20*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		5,											0,                      				0,                      0},
///*21*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		5,											0,                      				0,                      0},
///*22*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		5,											0,                      				0,                      0},
///*23*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//контроллёр
///*24*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//бюррер
///*25*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//1
///*26*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//2
///*27*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//3
///*28*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//4
///*29*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//5
///*30*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_PSY,						0,											0,                      				0,                      0},//лаба
///*31*/{	RadiomarkInstanceClass::RADIOMARK_TYPE_RADIATION_ANOMALY,		0,											TemporaryClass::ANOMALY_TYPE_ELECTRA,	20,						80},
//};
#endif //GAMETEMPLATE_RADIOMARKS_H_