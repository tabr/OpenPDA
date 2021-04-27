/*
 * USART_Codes.h
 *
 * Created: 21.09.2016 22:36:52
 *  Author: tabr
 */ 


#ifndef USART_CODES_H_
#define USART_CODES_H_


#ifdef DEBUG_USART_CODES

enum DEBUG_USART_LOGLEVELS
{
	DEBUG_USART_LOGLEVEL_NONE,
	DEBUG_USART_LOGLEVEL_MINIMAL,
	DEBUG_USART_LOGLEVEL_NORMAL,
	DEBUG_USART_LOGLEVEL_DEBUG,
};

//#define DEBUG_USART_CURRENT_LOGLEVEL	DEBUG_USART_LOGLEVEL_NORMAL

enum USART_DEBUG_CODES
	{
	USART_DEBUG_CODE_DATA_0			                                  = 0,//48 - 0 //USART_DEBUG_CODES::USART_DEBUG_CODE_DATA_0+this->L0.getReceivedPacketType(
	USART_DEBUG_CODE_NONE			                                    = 65,//65 - A
	USART_DEBUG_CODE_SYSTEM_STARTED                               = 66,//66 - B
	USART_DEBUG_CODE_SYSTEM_ALIVE                                 = 0,//67 - C
	USART_DEBUG_CODE_PLAYER_REVIVED                               = 68,//68 - D
	USART_DEBUG_CODE_PLAYER_DAMAGE_TAKEN                          = 69,//69 - E
	USART_DEBUG_CODE_L0_SOME_PACKET_RECEIVED                      = 0,//60 - F
	USART_DEBUG_CODE_ANORAD_RM_STRANGTE_ERROR                     = 71,//71 - G --not used?
	USART_DEBUG_CODE_L0_CRC_FAIL                                  = 72,//72 - H
	USART_DEBUG_CODE_L0_CRC_OK                                    = 0,//73 - I
	USART_DEBUG_CODE_L1_VALID_PACKET_RECEIVED                     = 0,//74 - J
	USART_DEBUG_CODE_ERROR_RSSI_ALREADY_RECEIVED                  = 75,//75 - K
	USART_DEBUG_CODE_ISR_RSSI_RECEIVED_ENTERING                   = 0,//76 - L
	USART_DEBUG_CODE_ISR_RSSI_WAIT_ERROR                          = 0,//77 - M
	USART_DEBUG_CODE_ISR_RSSI_GOOD_PACKET_RECEIVED                = 0,//78 - N
	USART_DEBUG_CODE_ISR_RSSI_WAIT_TICK                           = 0,//79 - O
	USART_DEBUG_CODE_ISR_RSSI_CRC_FAIL                            = 70,//70 - P
	USART_DEBUG_CODE_ISR_RSSI_CRC_OK                              = 0,//81 - Q
	USART_DEBUG_CODE_TIME_NOT_SYNC                                = 0,//82 - R
	USART_DEBUG_CODE_TIME_ISR                                     = 0,//83 - S
	USART_DEBUG_CODE_TIME_PACKET_RECEIVED                         = 84,//84 - T
	USART_DEBUG_CODE_L0_ENTER_CHECK_ENV_PA                        = 0,//85 - U
	USART_DEBUG_CODE_TIME_UPDATED                                 = 0,//86 - V
	USART_DEBUG_CODE_L0_RCV_ADM_ACTION                            = 87,//87 - W
	USART_DEBUG_CODE_L2_RADIOMARK_TYPE_REVIVE                     = 88,//88 - X
	USART_DEBUG_CODE_KIILED_BY_SLEEP_EVT                          = 89,//89 - Y
	USART_DEBUG_CODE_SLEEP_REVIVE                                 = 80,//80 - Z
	USART_DEBUG_CODE_REVIVE_BY_DEATH_TIMER                        = 91,//91 - "["
	USART_DEBUG_CODE_INITIAL_REVIVE                               = 92,//92 - "\"
	USART_DEBUG_CODE_RCV_RESTARTED_BY_HACK                        = 93,//93 - "]"
	USART_DEBUG_CODE_ENTER_PLAYER_KILL                            = 94,//94 - "^"
	USART_DEBUG_CODE_ANORAD_RM_RECEIVE_BEGIN                      = 0,//95 - "_"
	USART_DEBUG_CODE_REVIVED_BY_SLEEP_EVT                         = 96,//96 - "`"
	USART_DEBUG_CODE_KIILED_BY_SLEEP_EVT1                         = 97,//97 - "a"
	USART_DEBUG_CODE_PROCESSING_DEATH_SOUND                       = 98,//98 - "b"
	USART_DEBUG_CODE_PLAYER_IS_ZOMBIE                             = 99,//99 - "c"
	USART_DEBUG_CODE_PLAYER_REVIVE_10_SEC                         = 100,//90 - "d"
  USART_DEBUG_CODE_SYSTEM_STARING                               = 101,//101 - e
  USART_DEBUG_CODE_ENTER_PLAYER_KILL_PLAYER_ALIVE_SETTING_HP_0  = 102,//102 - f
  USART_DEBUG_CODE_ENTER_PLAYER_DIE                             = 103,//103 - g
  USART_DEBUG_CODE_ENTER_PLAYER_DIE_SET_GO_GRAVEYARD            = 104,//104 - h
  USART_DEBUG_CODE_ENTER_PLAYER_DIE_RENEW_DEATH_TIMER           = 105,//105 - i
  USART_DEBUG_CODE_KILLING_PLAYER_BY_ANOMALY_KILL_LEVEL         = 106,//106 - j
  USART_DEBUG_CODE_KILLING_PLAYER_BY_ADM                        = 107,//107 - k
  USART_DEBUG_CODE_BLOWOUT_DAMAGE                               = 108,//108 - l
  USART_DEBUG_CODE_DEAL_DAMAGE_DMG_HIGH_KILLING                 = 109,//109 - m
  USART_DEBUG_CODE_ENTER_PLAYER_SETHEALTH                       = 110,//110 - n
  USART_DEBUG_CODE_ENTER_PLAYER_SETHEALTH_CALLING_DIE           = 111,//111 - o
	};

volatile bool USART_TX_Complete=true;
// USART Transmitter interrupt service routine
ISR(USART_TXC_vect)// void usart_tx_isr(void)
	{
	USART_TX_Complete	= true;
	}

//void USART_SendCode(USART_DEBUG_CODES code, DEBUG_USART_LOGLEVELS L	= DEBUG_USART_LOGLEVEL_NORMAL)
void USART_SendCode(uint8_t code, DEBUG_USART_LOGLEVELS L	= DEBUG_USART_LOGLEVEL_NORMAL)
	{
  if (code == 0)
    {
    return;
    }
	if ( DEBUG_USART_CURRENT_LOGLEVEL >= L )
		{
		USART_TX_Complete	= false;
		UDR=code;
		while ((UCSRA & DATA_REGISTER_EMPTY)==0);//wait for TX complete
		}
	//while (USART_TX_Complete == false);
	}

#endif //DEBUG_USART_CODES



#endif /* USART_CODES_H_ */