//https://github.com/KonstantinChizhov/AvrProjects/blob/master/mcucpp/HD44780.h
#ifndef N3310_LCD_CLASS_H
#define N3310_LCD_CLASS_H

#include "n3310_new.h"


//char emptyCharArray[]={0x00};

//template<class BUS>


template <uint8_t b7, uint8_t b6, uint8_t b5, uint8_t b4, uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0>
struct BinaryConst
  {
  enum {get      =  (((b7&1)<<7) | ((b6&1)<<6) | ((b5&1)<<5) | ((b4&1)<<4) | ((b3&1)<<3) | ((b2&1)<<2) | ((b1&1)<<1) | ((b0&1)<<0))};
  };

class n3310LcdClass //: public LcdBase
	{
	const static uint8_t COMMAND_FUNCTION_SET_INSTRUCTION					= BinaryConst<0,0,1,0,0,0,0,0>::get;
	const static uint8_t COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION				= BinaryConst<0,0,0,0,1,0,0,0>::get;
	const static uint8_t COMMAND_H0_SET_VOP_RANGE_INSTRUCTION				= BinaryConst<0,0,0,1,0,0,0,0>::get;
	const static uint8_t COMMAND_H0_SET_Y_ADDRESS_RAM_INSTRUCTION				= BinaryConst<0,1,0,0,0,0,0,0>::get;
	const static uint8_t COMMAND_H0_SET_X_ADDRESS_RAM_INSTRUCTION				= BinaryConst<1,0,0,0,0,0,0,0>::get;
	const static uint8_t Y_ADDRESS_MASK							= BinaryConst<0,0,0,0,1,1,1,1>::get;//[0..8]
	const static uint8_t X_ADDRESS_MASK							= BinaryConst<0,1,1,1,1,1,1,1>::get;//[0..101]

	const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION				= BinaryConst<0,0,0,0,0,1,0,0>::get;
//	const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION	        = BinaryConst<0,0,0,1,0,0,0,0>::get;
	const static uint8_t COMMAND_H1_BIAS_SYSTEM_INSTRUCTION					= BinaryConst<0,0,0,1,0,0,0,0>::get;
	const static uint8_t COMMAND_H1_SET_VOP_INSTRUCTION					= BinaryConst<1,0,0,0,0,0,0,0>::get;

	const static uint8_t COMMAND_FUNCTION_SET__BASIC_INSTRUCTION_SET			= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
	const static uint8_t COMMAND_FUNCTION_SET__EXTENDED_INSTRUCTION_SET			= BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
	const static uint8_t COMMAND_FUNCTION_SET__HORIZONTAL_ADDRESSING			= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
	const static uint8_t COMMAND_FUNCTION_SET__VERTICAL_ADDRESSING				= BinaryConst<0,0,0,0,0,0,1,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
	const static uint8_t COMMAND_FUNCTION_SET__POWER_DOWN_DEACTIVATE			= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
	const static uint8_t COMMAND_FUNCTION_SET__POWER_DOWN_ACTIVATE				= BinaryConst<0,0,0,0,0,1,0,0>::get | COMMAND_FUNCTION_SET_INSTRUCTION;
	const static uint8_t COMMAND_H0_DISPLAY_CONTROL__DISPLAY_BLANK				= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H0_DISPLAY_CONTROL__NORMAL_MODE				= BinaryConst<0,0,0,0,0,1,0,0>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H0_DISPLAY_CONTROL__ALL_DISPLAY_SEGMENTS_ON	        = BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H0_DISPLAY_CONTROL__INVERSE_VIDEO_MODE			= BinaryConst<0,0,0,0,0,1,0,1>::get | COMMAND_H0_DISPLAY_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H0_SET_VOP_RANGE__HI					= BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H0_SET_VOP_RANGE_INSTRUCTION;
	const static uint8_t COMMAND_H0_SET_VOP_RANGE__LOW					= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H0_SET_VOP_RANGE_INSTRUCTION;
	const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_0			= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_1			= BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_2			= BinaryConst<0,0,0,0,0,0,1,0>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
	const static uint8_t COMMAND_H1_TEMPERATURE_CONTROL__COEFFICIENT_3			= BinaryConst<0,0,0,0,0,0,1,1>::get | COMMAND_H1_TEMPERATURE_CONTROL_INSTRUCTION;
//	const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_2				= BinaryConst<0,0,0,0,0,0,0,0>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
//	const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_3				= BinaryConst<0,0,0,0,0,0,0,1>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
//	const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_4				= BinaryConst<0,0,0,0,0,0,1,0>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
//	const static uint8_t COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_5				= BinaryConst<0,0,0,0,0,0,1,1>::get | COMMAND_H1_SET_VOLTAGE_MULTIPLIER_FACTOR_INSTRUCTION;
	const static uint8_t COMMAND_H1_BIAS_SYSTEM_MASK					= BinaryConst<0,0,0,0,0,1,1,1>::get;
	const static uint8_t COMMAND_H1_SET_VOP_MASK						= BinaryConst<0,1,1,1,1,1,1,1>::get;
/*
//	enum{SclkBit = 0, SdinBit = 1, D_CBit = 2, BusBits = 3};
	enum{SclkBit = 0, SdinBit = 1, D_CBit = 2, SceBit = 3, ResBit = 4};
//	enum{SclkBit = 0, SdinBit = 1, SdoutBit = 2, D_CBit = 3, SceBit = 4, ResBit = 5};
	typedef typename BUS::template Pin<SclkBit>		PIN_SCLK;//Clock
	typedef typename BUS::template Pin<SdinBit>		PIN_SDIN;//MOSI
//	typedef typename BUS::template Pin<SdoutBit>	PIN_SDOUT;//MISO - must be set IN!!! NO, SS must be OUT
	typedef typename BUS::template Pin<D_CBit>		PIN_DATA_COMMAND;//DC
	typedef typename BUS::template Pin<SceBit>		PIN_CHIP_SELECT;//SCE
	typedef typename BUS::template Pin<ResBit>		PIN_RESET;
*/
//	typedef typename BUS::template Pin<SclkBit> SCLK;
//	typedef typename BUS::template Pin<SdinBit> MOSI;
//	typedef typename BUS::template Pin<D_CBit> D_C;
//	typedef typename BUS::template Pin<SceBit> SS;
//	typedef typename BUS::template Pin<ResBit> RES;

//	typedef typename BUS::template Slice<BusBits, 4> DATA_BUS;
	public:
		//static uint8_t LcdCache[LCD_CACHE_SIZE];
		static void ActivateDisplay(void);
		static void DeactivateDisplay(void);
		static void IOInit(void);
		static void DMA_Initialization(void);
		static void HardwareInitialization(void);
		static void StopDMATransaction(void);
		static void TryStartDMATransaction(void);//calling from interrupt
		static void RequestUpdate(void);
		static void ResetHardwareBufferPointer(void);
		static void SetData(void);
		static void Reset20MS(void);
		static void SetCommand(void);
		static void SPI_TXData(uint8_t data);
//		static void RequestHardwareBufferReset(void);
		static void LcdSendCommandPacket(uint16_t length, uint8_t* packet);	//transmitting withoud DMA
		static bool isDMAActivated(void);
		static bool isDMANotActivated(void);
		static void DMAActivate(void);
		static void DMADeactivate(void);

		/*
		static void LcdSendCommand (uint8_t command)
			{
			ActivateDisplay();
			LcdPinDC::SetOutLow();//command
			USARTE1.DATA	= command;
			while (!(USARTE1.STATUS & USART_TXCIF_bm));
			USARTE1.STATUS |= USART_TXCIF_bm;
			DeactivateDisplay();
			}*/
		/*
		static void LcdSendCachePacket(uint16_t length, uint8_t* packet)
			{
			ActivateDisplay();
			LcdPinDC::SetOutLow();//command
			for (uint16_t i=0;i<length;i++)
				{
				if (i==2)
					{
					LcdPinDC::SetOutHigh();//data
					}
				SPI_TXData(packet[i]);
				}
			DeactivateDisplay();
			}*/
		/*
//		static void LcdSendData (uint8_t data, uint8_t dataOrCommand)    //Sends data to display controller
		static void LcdSendData (uint8_t data)    //Sends data to display controller
			{
			#ifdef SOFT_SPI
				uint8_t i, mask = 128;
			#endif
			ActivateDisplay();

//			if (dataOrCommand)//выбираем команда или данные
//				{
//				LcdPinDC::SetOutHigh();
//				}
//			else
//				{
//				LcdPinDC::SetOutLow();
//				}
			LcdPinDC::SetOutHigh();//data
			#ifdef SOFT_SPI
				for (i=0;i<8;i++)
					{
					if ((data&mask)!=0)
						{
						LcdPinSDIN::SetOutHigh();
						}
					else
						{
						LcdPinSDIN::SetOutLow();
						}
					mask = mask>>1;
					LcdPinCLK::SetOutHigh();
					_delay_us(1);
					LcdPinCLK::SetOutLow();
					}
			#else
				#ifdef ATMEL_STUDIO
					
					USARTE1.DATA	= data;
					//while (!(USARTE1.STATUS & USART_TXCIF_bm));
					//if(!(USARTE1.STATUS & USART_DREIF_bm))
						{
						//while(!(USARTE1.STATUS & USART_TXCIF_bm)); // wait for TX complete
						}
					//while( ( USARTE1.STATUS & USART_DREIF_bm ) == 0 );
					while (!(USARTE1.STATUS & USART_TXCIF_bm));

					USARTE1.STATUS |= USART_TXCIF_bm;
					
					
					
//					LCD_SPI.DATA	= data;
//					while (!(LCD_SPI.STATUS & SPI_IF_bm))
//						{
//						}        //Wait Interrupt
//				#else
//					SPDR = data;                            //Send data to display controller
//					while ( (SPSR & 0x80) != 0x80 );        //Wait until Tx register empty
				#endif
			#endif
			DeactivateDisplay();
			}*/
	};
#endif