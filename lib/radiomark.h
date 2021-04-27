#ifndef RADIOMARK_H
#define RADIOMARK_H
#define PACKET_RADIOMARK_TYPE                           0
#define PACKET_RADIOMARK_TYPE_PARAM0                    1
#define PACKET_RADIOMARK_TYPE_PARAM1                    2
#define PACKET_RADIOMARK_TYPE_PARAM2                    3
#define PACKET_RADIOMARK_TYPE_PARAM3                    4
#define PACKET_RADIOMARK_TYPE_PARAM4                    5


#define RADIOMARK_PACKET_STRUCT_RADANO_RAD_MULTIPLIER   PACKET_RADIOMARK_TYPE_PARAM0
#define RADIOMARK_PACKET_STRUCT_RADANO_ANO_TYPE         PACKET_RADIOMARK_TYPE_PARAM1
#define RADIOMARK_PACKET_STRUCT_RADANO_ANO_SKIP_LEVEL   PACKET_RADIOMARK_TYPE_PARAM2
#define RADIOMARK_PACKET_STRUCT_RADANO_ANO_KILL_LEVEL   PACKET_RADIOMARK_TYPE_PARAM3

#define RADIOMARK_PACKET_STRUCT_QUEST_ACTION            PACKET_RADIOMARK_TYPE_PARAM0
#define RADIOMARK_PACKET_STRUCT_QUEST_ID                PACKET_RADIOMARK_TYPE_PARAM1

#define RADIOMARK_TYPE_QUEST_ACTION_GIVE                0
#define RADIOMARK_TYPE_QUEST_ACTION_COMPLETE            1
#define RADIOMARK_TYPE_QUEST_ACTION_FAIL                2
#define RADIOMARK_TYPE_QUEST_ACTION_REMOVE              3
#define RADIOMARK_PACKET_STRUCT_QUEST_QID               PACKET_RADIOMARK_TYPE_PARAM0

/////////////////////////////ADM//////////////////////////////

//#define RADIOMARK_TYPE_ADM_GET_PARAMETER				128
//#define RADIOMARK_TYPE_ADM_SET_PARAMETER				129
//#define RADIOMARK_TYPE_ADM_ACTION						130

//????#define RADIOMARK_ADM_PARAMETER_HP				0
//????#define RADIOMARK_ADM_PARAMETER_RAD_DOSE			0
//????#define RADIOMARK_ADM_PARAMETER_					0
//#define RADIOMARK_ADM_PARAMETER_						0
//#define RADIOMARK_ADM_PARAMETER_						0

//PACKET[PACKET_RADIOMARK_TYPE]							RADIOMARK_TYPE_ADM_ACTION
//PACKET[PACKET_RADIOMARK_TYPE_PARAM0]					ADDRESS[UNIQUE_ID] 0-none,255 - all(broadcast)
//PACKET[PACKET_RADIOMARK_TYPE_PARAM1]					ACTION
enum RADIOMARK_ADM_ACTIONS
	{
	RADIOMARK_ADM_ACTION_NONE,
	RADIOMARK_ADM_ACTION_REMOVE_ADDICION,
	RADIOMARK_ADM_ACTION_SET_HP,
	RADIOMARK_ADM_ACTION_SET_ITEM_NUM,
	RADIOMARK_ADM_ACTION_REVIVE,
	RADIOMARK_ADM_ACTION_HALF_DEATH_TIME,
	RADIOMARK_ADM_ACTION_SET_DEFENCE_RAD,
	RADIOMARK_ADM_ACTION_SET_RESISTANCE_RAD,
	RADIOMARK_ADM_ACTION_SET_REGEN_HP,
	RADIOMARK_ADM_ACTION_INIT_DEFAULT,
	RADIOMARK_ADM_ACTION_CLEAR_ADDICION,
	RADIOMARK_ADM_ACTION_KILL,
	RADIOMARK_ADM_ACTION_RESET,
	RADIOMARK_ADM_ACTION_SET_LEVEL,
	RADIOMARK_ADM_ACTION_SET_KARMA,
	RADIOMARK_ADM_ACTION_ADD_KARMA,
	RADIOMARK_ADM_ACTION_REM_KARMA,
	RADIOMARK_ADM_ACTION_SET_DEFENCE_FIRE,
	RADIOMARK_ADM_ACTION_SET_DEFENCE_ELECTRO,
	RADIOMARK_ADM_ACTION_SET_DEFENCE_CHEMICAL,
	RADIOMARK_ADM_ACTION_SET_DEFENCE_PSY,
	RADIOMARK_ADM_ACTION_SET_PDA_ADVANCED,
	RADIOMARK_ADM_ACTION_SET_PDA_BROKEN,
	RADIOMARK_ADM_ACTION_SET_PDA_NORMAL,
	RADIOMARK_ADM_ACTION_TEST,
	RADIOMARK_ADM_ACTION_SET_CONTAINER_NUM,
	RADIOMARK_ADM_ACTION_SET_ADDRESS,
	RADIOMARK_ADM_ACTION_SET_STATISTICS,
	RADIOMARK_ADM_ACTION_STATISTICS_CLEAR,
	RADIOMARK_ADM_ACTION_SET_NOTRIPPER,
	RADIOMARK_ADM_ACTIONS_NUM
	};

#endif