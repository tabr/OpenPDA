#ifndef DRIVER_ANORAD_RADIOMODULE_CLASS_H
#define DRIVER_ANORAD_RADIOMODULE_CLASS_H

#include "RFM69registers.h"
#include "stalker/Driver_AnoRadRarioModuleInterfaceClass.h"



class Driver_AnoRadRarioModule : public Driver_AnoRadRarioModuleInterfaceClass
	{
	public:
	
		const static uint8_t TX_POWER_MAX																			= 31;
		const static bool CFG_RSSI_INVERTED																		= true;
	
		const static uint8_t RFM69_REGISTER_00_FIFO																	= 0x00;
		const static uint8_t RFM69_REGISTER_01_OPMODE																= 0x01;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL	  														= 0x02;
		const static uint8_t RFM69_REGISTER_03_BITRATEMSB															= 0x03;
		const static uint8_t RFM69_REGISTER_04_BITRATELSB															= 0x04;
		const static uint8_t RFM69_REGISTER_05_FDEVMSB																= 0x05;
		const static uint8_t RFM69_REGISTER_06_FDEVLSB		  														= 0x06;
		const static uint8_t RFM69_REGISTER_07_FRFMSB	  															= 0x07;
		const static uint8_t RFM69_REGISTER_08_FRFMID																= 0x08;
		const static uint8_t RFM69_REGISTER_09_FRFLSB			  													= 0x09;
		const static uint8_t RFM69_REGISTER_0A_OSC1			  														= 0x0A;
		const static uint8_t RFM69_REGISTER_0B_OSC2	  																= 0x0B;
		const static uint8_t RFM69_REGISTER_0C_LOWBAT																= 0x0C;
		const static uint8_t RFM69_REGISTER_0D_LISTEN1																= 0x0D;
		const static uint8_t RFM69_REGISTER_0E_LISTEN2																= 0x0E;
		const static uint8_t RFM69_REGISTER_0F_LISTEN3																= 0x0F;
		const static uint8_t RFM69_REGISTER_10_VERSION																= 0x10;
		const static uint8_t RFM69_REGISTER_11_PALEVEL																= 0x11;
		/*
		Output power setting, with 1 dB steps
		Pout = -18 + OutputPower [dBm] , with PA0
		Pout = -18 + OutputPower [dBm] , with PA1**
		Pout = -14+ OutputPower [dBm] , with PA1 and PA2**
		Pout = -11 + OutputPower [dBm] , with PA1 and PA2, and
		high Power PA settings (refer to section 3.3.7)**
		*/
		const static uint8_t RFM69_REGISTER_11_PALEVEL_7_PA_0_ON													= 7;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_7_PA_0_ON_SETON												= 1<<7;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_7_PA_0_ON_SETOFF												= 0<<7;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_6_PA_1_ON													= 6;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_6_PA_1_ON_SETON												= 1<<6;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_6_PA_1_ON_SETOFF												= 0<<6;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_5_PA_2_ON													= 5;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_5_PA_2_ON_SETON												= 1<<5;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_5_PA_2_ON_SETOFF												= 0<<5;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_40_OUTPUT_POWER												= 0;
		const static uint8_t RFM69_REGISTER_11_PALEVEL_40_OUTPUT_POWER_MASK											= 0b11111;

		const static uint8_t RFM69_REGISTER_12_PARAMP																= 0x12;
		const static uint8_t RFM69_REGISTER_13_OCP				    												= 0x13;
		const static uint8_t RFM69_REGISTER_13_OCP_75_RESERVED														= 5;
		const static uint8_t RFM69_REGISTER_13_OCP_4_OCP_ON															= 4;
		const static uint8_t RFM69_REGISTER_13_OCP_4_OCP_ON_OCP_DISABLED											= 0<<4;
		const static uint8_t RFM69_REGISTER_13_OCP_4_OCP_ON_OCP_ENABLED												= 1<<4;
		const static uint8_t RFM69_REGISTER_13_OCP_30_OCP_TRIM														= 0;
		const static uint8_t RFM69_REGISTER_13_OCP_30_OCP_TRIM_DEFAULT												= (0b1010)<<0;
		const static uint8_t RFM69_REGISTER_14_AGCREF																= 0x14;
		const static uint8_t RFM69_REGISTER_15_AGCTHRESH1															= 0x15;
		const static uint8_t RFM69_REGISTER_16_AGCTHRESH2															= 0x16;
		const static uint8_t RFM69_REGISTER_17_AGCTHRESH3															= 0x17;
		const static uint8_t RFM69_REGISTER_18_LNA			  														= 0x18;
		const static uint8_t RFM69_REGISTER_19_RXBW		    														= 0x19;
		const static uint8_t RFM69_REGISTER_1A_AFCBW		    													= 0x1A;
		const static uint8_t RFM69_REGISTER_1B_OOKPEAK	  															= 0x1B;
		const static uint8_t RFM69_REGISTER_1C_OOKAVG  																= 0x1C;
		const static uint8_t RFM69_REGISTER_1D_OOKFIX	  															= 0x1D;
		const static uint8_t RFM69_REGISTER_1E_AFCFEI		  														= 0x1E;
		const static uint8_t RFM69_REGISTER_1F_AFCMSB																= 0x1F;
		const static uint8_t RFM69_REGISTER_20_AFCLSB																= 0x20;
		const static uint8_t RFM69_REGISTER_21_FEIMSB																= 0x21;
		const static uint8_t RFM69_REGISTER_22_FEILSB																= 0x22;
		const static uint8_t RFM69_REGISTER_23_RSSICONFIG															= 0x23;
		const static uint8_t RFM69_REGISTER_24_RSSIVALUE															= 0x24;

		const static uint8_t RFM69_REGISTER_25_DIOMAPPING1															= 0x25; //See Table 21(22) for mapping in Continuous(Packet) mode
		const static uint8_t RFM69_REGISTER_25_DIOMAPPING1_DIO0														= 6;
		const static uint8_t RFM69_REGISTER_25_DIOMAPPING1_DIO1														= 4;
		const static uint8_t RFM69_REGISTER_25_DIOMAPPING1_DIO2														= 2;
		const static uint8_t RFM69_REGISTER_25_DIOMAPPING1_DIO3														= 0;

		//const static uint8_t RFM69_DIO_MAPPING_CONTINUOUS_MODE_


		const static uint8_t RFM69_REGISTER_26_DIOMAPPING2															= 0x26;
		const static uint8_t RFM69_REGISTER_26_DIOMAPPING2_DIO4														= 6;
		const static uint8_t RFM69_REGISTER_26_DIOMAPPING2_DIO5														= 4;
		const static uint8_t RFM69_REGISTER_26_DIOMAPPING2_3_UNUSED													= 3;
		const static uint8_t RFM69_REGISTER_26_DIOMAPPING2_20_CLK_OUT												= 0;


		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1															= 0x27;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_7_MODE_READY												= 7;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_7_MODE_READY_SET											= 1<<7;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_7_MODE_READY_UNSET											= 0<<7;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_6_RX_READY													= 6;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_6_RX_READY_SET												= 1<<6;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_6_RX_READY_UNSET											= 0<<6;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_5_TX_READY													= 5;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_5_TX_READY_SET												= 1<<5;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_5_TX_READY_UNSET											= 0<<5;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_4_PLL_LOCK													= 4;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_4_PLL_LOCK_SET												= 1<<4;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_4_PLL_LOCK_UNSET											= 0<<4;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_3_RSSI														= 3;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_3_RSSI_SET													= 1<<3;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_3_RSSI_UNSET												= 0<<3;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_2_TIMEOUT													= 2;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_2_TIMEOUT_SET												= 1<<2;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_2_TIMEOUT_UNSET											= 0<<2;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_1_AUTO_MODE												= 1;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_1_AUTO_MODE_SET											= 1<<1;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_1_AUTO_MODE_UNSET											= 0<<1;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_0_SYNC_ADDRESS_MATCH										= 0;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_0_SYNC_ADDRESS_SET											= 1<<0;
		const static uint8_t RFM69_REGISTER_27_IRQFLAGS1_0_SYNC_ADDRESS_UNSET										= 0<<0;

		const static uint8_t RFM69_REGISTER_28_IRQFLAGS2															= 0x28;
		const static uint8_t RFM69_REGISTER_29_RSSITHRESH															= 0x29;
		const static uint8_t RFM69_REGISTER_2A_RXTIMEOUT1															= 0x2A;
		const static uint8_t RFM69_REGISTER_2B_RXTIMEOUT2															= 0x2B;
		const static uint8_t RFM69_REGISTER_2C_PREAMBLEMSB															= 0x2C;
		const static uint8_t RFM69_REGISTER_2D_PREAMBLELSB															= 0x2D;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG															= 0x2E;
		const static uint8_t RFM69_REGISTER_2F_SYNCVALUE1															= 0x2F;
		const static uint8_t RFM69_REGISTER_30_SYNCVALUE2															= 0x30;
		const static uint8_t RFM69_REGISTER_31_SYNCVALUE3															= 0x31;
		const static uint8_t RFM69_REGISTER_32_SYNCVALUE4															= 0x32;
		const static uint8_t RFM69_REGISTER_33_SYNCVALUE5															= 0x33;
		const static uint8_t RFM69_REGISTER_34_SYNCVALUE6															= 0x34;
		const static uint8_t RFM69_REGISTER_35_SYNCVALUE7															= 0x35;
		const static uint8_t RFM69_REGISTER_36_SYNCVALUE8															= 0x36;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1														= 0x37;
		const static uint8_t RFM69_REGISTER_38_PAYLOADLENGTH														= 0x38;
		const static uint8_t RFM69_REGISTER_39_NODEADRS																= 0x39;
		const static uint8_t RFM69_REGISTER_3A_BROADCASTADRS														= 0x3A;
		const static uint8_t RFM69_REGISTER_3B_AUTOMODES															= 0x3B;
		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH															= 0x3C;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2														= 0x3D;
		const static uint8_t RFM69_REGISTER_3E_AESKEY1																= 0x3E;
		const static uint8_t RFM69_REGISTER_3F_AESKEY2 																= 0x3F;
		const static uint8_t RFM69_REGISTER_40_AESKEY3	  															= 0x40;
		const static uint8_t RFM69_REGISTER_41_AESKEY4		  														= 0x41;
		const static uint8_t RFM69_REGISTER_42_AESKEY5																= 0x42;
		const static uint8_t RFM69_REGISTER_43_AESKEY6 																= 0x43;
		const static uint8_t RFM69_REGISTER_44_AESKEY7	  															= 0x44;
		const static uint8_t RFM69_REGISTER_45_AESKEY8		  														= 0x45;
		const static uint8_t RFM69_REGISTER_46_AESKEY9																= 0x46;
		const static uint8_t RFM69_REGISTER_47_AESKEY10  															= 0x47;
		const static uint8_t RFM69_REGISTER_48_AESKEY11	  															= 0x48;
		const static uint8_t RFM69_REGISTER_49_AESKEY12																= 0x49;
		const static uint8_t RFM69_REGISTER_4A_AESKEY13  															= 0x4A;
		const static uint8_t RFM69_REGISTER_4B_AESKEY14	  															= 0x4B;
		const static uint8_t RFM69_REGISTER_4C_AESKEY15																= 0x4C;
		const static uint8_t RFM69_REGISTER_4D_AESKEY16																= 0x4D;
		const static uint8_t RFM69_REGISTER_4E_TEMP1																= 0x4E;
		const static uint8_t RFM69_REGISTER_4F_TEMP2																= 0x4F;

		const static uint8_t RFM69_REGISTER_58_TESTLNA																= 0x58; //only present on ???
		const static uint8_t RFM69_REGISTER_5A_TESTPA1																= 0x5A; //only present on RFM69HW/SX1231H
		const static uint8_t RFM69_REGISTER_5C_TESTPA2																= 0x5C; //only present on RFM69HW/SX1231H
		const static uint8_t RFM69_REGISTER_6F_TESTDAGC																= 0x6F;
		const static uint8_t RFM69_REGISTER_71_TESTAFC																= 0x71;//??

		const static uint8_t RFM69_OPMODE_SLEEP																		= 0b000<<2;
		const static uint8_t RFM69_OPMODE_STANDBY																	= 0b001<<2;
		const static uint8_t RFM69_OPMODE_SYNTHESIZER																= 0b010<<2; //frequency synthesizer
		const static uint8_t RFM69_OPMODE_TRANSMITTER																= 0b011<<2;
		const static uint8_t RFM69_OPMODE_RECEIVER																	= 0b100<<2;



		const static uint8_t RFM69_REGISTER_01_OPMODE_7_SEQUENCER_OFF												= 7;
		const static uint8_t RFM69_REGISTER_01_OPMODE_6_LISTEN_ON													= 6;
		const static uint8_t RFM69_REGISTER_01_OPMODE_5_LISTEN_ABORT												= 5;
		const static uint8_t RFM69_REGISTER_01_OPMODE_42_MODE														= 2;//4-2
		const static uint8_t RFM69_REGISTER_01_OPMODE_42_MODE_SLEEP													= 0b000<<2;
		const static uint8_t RFM69_REGISTER_01_OPMODE_42_MODE_STANDBY												= 0b001<<2;
		const static uint8_t RFM69_REGISTER_01_OPMODE_42_MODE_FREQUENCY_SYNTHESIZER									= 0b010<<2;
		const static uint8_t RFM69_REGISTER_01_OPMODE_42_MODE_TRANSMITTER											= 0b011<<2;
		const static uint8_t RFM69_REGISTER_01_OPMODE_42_MODE_RECEIVER												= 0b100<<2;

		const static uint8_t RFM69_REGISTER_02_DATAMODUL_65_DATAMODE												= 5;//6-5
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_65_DATAMODE_PACKET											= 0b00<<5;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_65_DATAMODE_CONT_WITH_SYNTH								= 0b10<<5;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_65_DATAMODE_CONT_NO_SYNTH									= 0b11<<5;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_43_MODULATION_TYPE											= 3;//4-3
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_43_MODULATION_TYPE_FCK										= 0b00<<3;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_43_MODULATION_TYPE_OOK										= 0b01<<3;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING										= 0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_FCK_NO_SHAPING						= 0b00<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_FCK_GF_10							= 0b01<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_FCK_GF_05							= 0b10<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_FCK_GF_03							= 0b11<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_OOK_NO_SHAPING						= 0b00<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_OOK_F_BR								= 0b01<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_OOK_F_2BR							= 0b10<<0;
		const static uint8_t RFM69_REGISTER_02_DATAMODUL_10_MODULATION_SHAPING_OOK_RESERVED							= 0b11<<0;
		//bitrate: 32MHZ/(REG_03.REG_04)
		//FXO = 32MHZ
		//FSTEP (Frequency synthesizer step) = 61Hz
		const static uint8_t RFM69_REGISTER_19_RXBW_75_DCC_FREQ														= 5;
		const static uint8_t RFM69_REGISTER_19_RXBW_75_DCC_FREQ_DEFAULT_4PERCENT									= 0b010<<5;
		const static uint8_t RFM69_REGISTER_19_RXBW_43_RX_BW_MANT													= 3;
		const static uint8_t RFM69_REGISTER_19_RXBW_43_RX_BW_MANT_16												= 0b00<<3;
		const static uint8_t RFM69_REGISTER_19_RXBW_43_RX_BW_MANT_24												= 0b01<<3;
		const static uint8_t RFM69_REGISTER_19_RXBW_43_RX_BW_MANT_20												= 0b10<<3;
		const static uint8_t RFM69_REGISTER_19_RXBW_43_RX_BW_MANT_RESERVED											= 0b11<<3;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP													= 0;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_0039KHZ									= 7;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_0078KHZ									= 6;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_0156KHZ									= 5;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_0313KHZ									= 4;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_0625KHZ									= 3;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_1250KHZ									= 2;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_2500KHZ									= 1;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT16_5000KHZ									= 0;

		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_0031KHZ									= 7;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_0063KHZ									= 6;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_0125KHZ									= 5;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_0250KHZ									= 4;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_0500KHZ									= 3;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_1000KHZ									= 2;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_2000KHZ									= 1;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT20_4000KHZ									= 0;

		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_0026KHZ									= 7;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_0052KHZ									= 6;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_0104KHZ									= 5;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_0208KHZ									= 4;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_0417KHZ									= 3;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_0833KHZ									= 2;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_1667KHZ									= 1;
		const static uint8_t RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_FCK_MANT24_3333KHZ									= 0;
		//TODO:  RFM69_REGISTER_19_RXBW_20_RX_BW_EXP_OOK_...

		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_7_SYNC_ON													= 7;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_7_SYNC_ON_TURN_ON											= 1<<7;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_7_SYNC_ON_TURN_OFF										= 0<<7;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_6_FIFO_FILL_CONDITION										= 6;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_6_FIFO_FILL_CONDITION_INTERRUPT							= 0<<6;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_6_FIFO_FILL_CONDITION_AS_FFC_SET							= 1<<6;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_53_SYNC_SIZE_PLUS_1										= 3;
		const static uint8_t RFM69_REGISTER_2E_SYNCCONFIG_20_SYNC_TOL												= 0;

		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_7_PACKET_FORMAT										= 7;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_7_PACKET_FORMAT_FIXED									= 0<<7;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_7_PACKET_FORMAT_VARIABLE								= 1<<7;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_65_PACKET_FORMAT_DC_FREE								= 5;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_65_PACKET_FORMAT_DC_FREE_NONE							= 0b00<<5;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_65_PACKET_FORMAT_DC_FREE_MANCHESTER					= 0b01<<5;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_65_PACKET_FORMAT_DC_FREE_WHITENING						= 0b10<<5;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_65_PACKET_FORMAT_DC_FREE_RESERVED						= 0b11<<5;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_4_CRC_ON												= 4;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_4_CRC_ON_TURN_ON										= 1<<4;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_4_CRC_ON_TURN_OFF										= 0<<4;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_3_CRC_AUTO_CREAR_OFF									= 3;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_3_CRC_AUTO_CREAR_OFF_CLEAR_FIFO_RESTART_PRCV			= 0<<3;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_3_CRC_AUTO_CREAR_OFF_NO_NOT_CLEAR_FIFO					= 1<<3;
//		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_3_CRC_AUTO_CREAR_OFF									= 3;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING									= 1;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING_NONE								= 0b00<<1;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING_MATCH_NODE_ADDRESS				= 0b01<<1;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING_MATCH_NODE_ADDRESS_OR_BROADCAST	= 0b10<<1;
		const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING_RESERVED							= 0b11<<1;
		//const static uint8_t RFM69_REGISTER_37_PACKETCONFIG1_21_ADDRESS_FILTERING_RESERVED							0b11<<1

		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH_7_TX_START_CONDITION										= 7;
		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH_7_TX_START_CONDITION_FIFO_LOW_LEVEL						= 0<<7;
		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH_7_TX_START_CONDITION_FIFO_NOT_EMPTY						= 1<<7;
		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH_60_FIFO_THRESHOLD											= 0;
		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH_60_FIFO_THRESHOLD_MASK									= 127;
		const static uint8_t RFM69_REGISTER_3C_FIFOTHRESH_60_FIFO_THRESHOLD_DEFAULT									= 0b000111;

		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_74_INTER_PACKET_RX_DELAY								= 4;//???????????? ??????? ??????, ?.?. ???? 1, ????? 2, 2=4, ...
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_74_INTER_PACKET_RX_DELAY_1_BIT							= 0<<4;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_74_INTER_PACKET_RX_DELAY_2_BIT							= 1<<4;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_3_RESERVED												= 3; //unused
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_2_RESTART_RX											= 2; //Forces the Receiver in WAIT mode, in Continuous Rx mode. Always reads 0.
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_1_AUTO_RESTART_RX_ON									= 1;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_1_AUTO_RESTART_RX_ON_SETON								= 1<<1;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_1_AUTO_RESTART_RX_ON_SETOFF							= 0<<1;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_0_AES_ON												= 0;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_0_AES_ON_SETON											= 1<<0;
		const static uint8_t RFM69_REGISTER_3D_PACKETCONFIG2_0_AES_ON_SETOFF										= 0<<0;

		const static uint8_t RFM69_REGISTER_6F_TESTDAGC_70_CONTINUOUS_DAGC											= 0; //Fading Margin Improvement, refer to 3.4.4
		const static uint8_t RFM69_REGISTER_6F_TESTDAGC_70_CONTINUOUS_DAGC_NORMAL_MODE								= 0x00; //Normal mode
		const static uint8_t RFM69_REGISTER_6F_TESTDAGC_70_CONTINUOUS_DAGC_IMPROVED_ALBO1							= 0x20; //Improved margin, use if AfcLowBetaOn=1
		const static uint8_t RFM69_REGISTER_6F_TESTDAGC_70_CONTINUOUS_DAGC_IMPROVED_ALBO0							= 0x30; //Improved margin, use if AfcLowBetaOn=0

		void setTXBuffer(uint8_t* buf);						//����� �������� ����� �������������� �����������
		void setRXBuffer(uint8_t* buf);						//����� �������� ����� �������������� ��������
		void setPacketSize(uint8_t size);					//����� �������� ����� ��������������
		void writeRegister(uint8_t addr, uint8_t value);
		uint8_t readRegister(uint8_t addr);
		void TXMode(void);									//��������� � ����� ��������
		void getPacket(void);
		uint8_t getRSSIRaw(void);
    uint8_t GetRSSIMax(void)
      {
      return 127;
      }
		bool isPacketReceived(void);

		void IOInit(void);
		uint8_t HardwareInitialization(void);
		void setTXPower(uint8_t pwr);
		void deviceEnable(void);
		void deviceDisable(void);

		void waitModeReady(void);
		void ClearFifo(void);
		//TODO:
		void sendBufferToRM(void);
		bool switchMode(TRX_STATE mode);//TODO: return not only true
		uint8_t startTX(void);//TODO: return not only "OK"
		void receiveBegin(void);
		Driver_AnoRadRarioModule(void)
			{
			
			this->isRMInit				= false;
			this->isRXBufInit			= false;
			this->isTXBufInit			= false;
			this->packetSize			= 0;
			this->txPower				= 0;
            this->rxBuffer              = nullptr;
            this->txBuffer              = nullptr;
			//this->IOInit();//moved to runlevels
			
			}
	protected:
	private:
		uint8_t packetSize;
		uint8_t txPower;
		bool isRMInit;
		bool isRXBufInit;
		bool isTXBufInit;
		uint8_t* rxBuffer;
		uint8_t* txBuffer;
		
	};
#endif