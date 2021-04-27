#ifndef GAME_ANORAD_DATA_H
#define GAME_ANORAD_DATA_H
//flash uint8_t anoradData[16][PACKET_SIZE]=

//#include "TemporaryClass.h"
#include "radiomark.h"

#define ANORAD_IDS_NUM						39
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

#ifdef ANORAD_IN_FLASH
const uint8_t anoradData[ANORAD_IDS_NUM][ANORAD_PARAMETERS] PROGMEM = 
#else
uint8_t anoradData[ANORAD_IDS_NUM][ANORAD_PARAMETERS]=
#endif // ANORAD_IN_FLASH
{
//												[PARAM0]                   
//ID	[TYPE]									[RADANO_RAD_MULTIPLIER]						[RADANO_ANO_TYPE]       				[RADANO_ANO_SKIP_LEVEL] [RADANO_ANO_KILL_LEVEL]
/*00*/{	RADIOMARK_TYPE_NONE,					0,											0,                      				0,						0}, //������ - �����?!
/*01*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*02*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*03*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*04*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*05*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*06*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*07*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*08*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*09*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*10*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*11*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*12*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*13*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*14*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*15*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*16*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*17*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*18*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,										0,						0},
/*19*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*20*/{	RADIOMARK_TYPE_RADIATION_ANOMALY,		1,											0,                      				0,						0},
/*21*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*22*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*23*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*24*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*25*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*26*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*27*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*28*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*29*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*30*/{	RADIOMARK_TYPE_PSY,						0,											0,                      				0,						0},
/*31*/{	RADIOMARK_TYPE_PSY,						0,											0,										0,						0},
/*32*/{	RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,										0,						0},
/*33*/{	RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,										0,						0},
/*34*/{	RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,										0,						0},
/*35*/{	RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,										0,						0},
/*36*/{	RADIOMARK_TYPE_SAFE_SHELTER,			0,											0,										0,						0},
/*37*/{	RADIOMARK_TYPE_REVIVE,					0,											0,										0,						0},
/*38*/{	RADIOMARK_TYPE_REVIVE,					0,											0,										0,						0},





};
#endif