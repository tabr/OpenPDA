#pragma once

#include "main.hpp"
#include "stdint.h"
#include "stm32f0xx_i2c.h"

#ifdef USING_HACKS_US_MS
  #define USING_HACK_US
#endif //USING_HACKS_US_MS


#ifdef USING_HACK_US
  #if (F_CPU==16000000UL)
    #define ONE_US_DELAY {nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();}
  #elif (F_CPU==48000000UL)
    #define ONE_US_DELAY {nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop(); nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop(); nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();}
  #else
    #error "ERROR"
  #endif
#else //USING_HACK_US
  #define ONE_US_DELAY _delay_us(1);
#endif //USING_HACK_US
//#define ONE_US_DELAY {for(uint8_t iter=12;iter>0;iter--);}
//#define ONE_US_DELAY {uint8_t iter=12; for(uint8_t iter=12;iter>0;iter--){nop();};}
//static inline void _delay_loop_2(uint16_t __count) __attribute__((always_inline));

/*
#define ONE_US_DELAY one_us_delay_f(12)
#pragma optimize=none
#pragma inline=forced
static inline void one_us_delay_f(uint8_t iter)
{
  //uint8_t iter=12;
  while(--iter);
}*/
/*
#define ONE_US_DELAY f(12)
#pragma inline=forced
static inline void f(uint8_t i)
{ 
while(--i) 
asm("");
}
*/
#include "typedefs.h"

//http://forum.easyelectronics.ru/viewtopic.php?f=35&t=22482
template <TWI_Data_t deviceSlaveAddress, uint16_t interfaceSpeedKhz>
class Driver_IO_TWIClass
	{
	public:
		const static uint8_t BIT_READ		= 0x01;
/*
		static bool beginTransmission(void)
			{
			uint8_t j=0;
			getTWI()->MASTER.ADDR = deviceSlaveAddress;// & ~0x01;
			while (!(getTWI()->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 64)//32 - малоб 48 - норм
					{
					twi_stop();
					return false;
					}
				//_delay_us(1);
                                ONE_US;
				}
			return true;
			}

		static bool sendByte(TWI_Data data)
			{
			uint8_t j=0;
                        //Send the address of the register you wish to read
                        I2C_SendData(I2C1, (uint8_t)registerAddress);
                
                        //Wait until transfer is complete!
			while (I2C_GetFlagStatus(I2C1, I2C_FLAG_TC) == RESET)
				{
				if (++j == 96)//64 - малоб 70 - норм
					{
					twi_stop();
					return false;
					}
				//_delay_us(1);
                                ONE_US;
				}
//			twi_stop();
			return true;
			}

		static void requestRead(void)
			{
			getTWI()->MASTER.ADDR		= deviceSlaveAddress | BIT_READ;
			getTWI()->MASTER.STATUS		|= TWI_MASTER_RIF_bm;
			getTWI()->MASTER.CTRLC		= TWI_MASTER_CMD_RECVTRANS_gc;
			}
*/
		static uint8_t writeToDevice(uint8_t registerAddress, uint8_t bytesToWrite, uint8_t *writeData)
			{
                        uint8_t j=0;
                        //Wait until I2C isn't busy
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET)
                          {
                          if (++j == 96)//64 - малоб 70 - норм
                            {
                            return 1;
                            }
                          ONE_US_DELAY;
                          }
                        
                        //"Handle" a transfer - The STM32F0 series has a shocking
                        //I2C interface... Regardless! Send the address of the HMC
                        //sensor down the I2C Bus and generate a start saying we're
                        //going to write one byte. I'll be completely honest,
                        //the I2C peripheral doesn't make too much sense to me
                        //and a lot of the code is from the Std peripheral library
                        I2C_TransferHandling(I2C1, deviceSlaveAddress, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
                
                        //Ensure the transmit interrupted flag is set
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET)
                          {
                          if (++j == 96)//64 - малоб 70 - норм
                            {
                            return 2;
                            }
                          ONE_US_DELAY;
                          }
                
                        //Send the address of the register we wish to write to
                        I2C_SendData(I2C1, registerAddress);
                
                        //Ensure that the transfer complete reload flag is
                        //set, essentially a standard TC flag
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TCR) == RESET)
                          {
                          if (++j == 96)//64 - малоб 70 - норм
                            {
                            return 3;
                            }
                          ONE_US_DELAY;
                          }

                        //Now that the HMC5883L knows which register
                        //we want to write to, send the address again
                        //and ensure the I2C peripheral doesn't add
                        //any start or stop conditions
                        I2C_TransferHandling(I2C1, deviceSlaveAddress, bytesToWrite, I2C_AutoEnd_Mode, I2C_No_StartStop);
/*
                        //Again, wait until the transmit interrupted flag is set
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET)
                          {
                          if (++j == 96)//64 - малоб 70 - норм
                            {
                            return 4;
                            }
                          ONE_US_DELAY;
                          }
*/                
                        for(uint8_t i=0;i<bytesToWrite;i++)
                          {
                          //Again, wait until the transmit interrupted flag is set
                          j=0;
                          while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET)
                            {
                            if (++j == 96)//64 - малоб 70 - норм
                              {
                              return 100+i;
                              }
                            ONE_US_DELAY;
                            }

                          //Send the value you wish you write to the register
                          I2C_SendData(I2C1, writeData[i]);
                          }
                        //Wait for the stop flag to be set indicating
                        //a stop condition has been sent
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET)
                          {
                          if (++j == 96)//64 - малоб 70 - норм
                            {
                            //return 6;
                            }
                          ONE_US_DELAY;
                          }
                
                        //Clear the stop flag for the next potential transfer
                        I2C_ClearFlag(I2C1, I2C_FLAG_STOPF);
                        return 0xFF;
			}
/*
		static bool writeToDevice(uint8_t deviceAddressH,uint8_t deviceAddressL, uint16_t bytesToWrite, uint8_t *writeData)
			{
			beginTransmission();
			sendByte(deviceAddressH);
			sendByte(deviceAddressL);
			for(uint16_t i=0;i<bytesToWrite;i++)
				{
				sendByte(writeData[i]);
				}
			twi_stop();
			return true;
			}
*/
		static uint8_t readFromDevice(uint8_t registerAddress, uint8_t bytesToRead, uint8_t *readData)
			{
                        //As per, ensure the I2C peripheral isn't busy!
                        uint8_t j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) == SET)
                          {
                          if (++j == 200)//96
                            {
                            return 1;
                            }
                          ONE_US_DELAY;
                          }
                
                        
                
                        //Again, start another tranfer using the "transfer handling"
                        //function, the end bit being set in software this time
                        //round, generate a start condition and indicate you will
                        //be writing data to the HMC device.
                        I2C_TransferHandling(I2C1, deviceSlaveAddress, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);
                        //void I2C_TransferHandling(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Number_Bytes, uint32_t ReloadEndMode, uint32_t StartStopMode);
                
                        //Wait until the transmit interrupt status is set
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXIS) == RESET)
                          {
                          if (++j == 200)//96
                            {
                            return 2;
                            }
                          ONE_US_DELAY;
                          }
                
                        //Send the address of the register you wish to read
                        //sendByte(registerAddress);
                        I2C_SendData(I2C1, (uint8_t)registerAddress);
                
                        //Wait until transfer is complete!
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TC) == RESET)
                          {
                          if (++j == 200)//96
                            {
                            return 3;
                            }
                          ONE_US_DELAY;
                          }

//                        return 0;

                        //As per, start another transfer, we want to read DCnt
                        //amount of bytes. Generate a start condition and
                        //indicate that we want to read.
                        I2C_TransferHandling(I2C1, deviceSlaveAddress, bytesToRead, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
                
                        //Read in DCnt pieces of data
                        for(uint8_t i = 0; i<bytesToRead; i++)
                          {
                          //Wait until the RX register is full of luscious data!
                          j=0;
                          while(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET)
                            {
                            if (++j == 200)//96
                              {
                              return 100+i;
                              }
                            ONE_US_DELAY;
                            }
                          readData[i]   = I2C_ReceiveData(I2C1);
                          }
                  
                        //Wait for the stop condition to be sent
                        j=0;
                        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF) == RESET)
                          {
                          if (++j == 200)//96
                            {
                            return 4;
                            }
                          ONE_US_DELAY;
                          }
                      
                        //Clear the stop flag for next transfers
                        I2C_ClearFlag(I2C1, I2C_FLAG_STOPF);
                        return 0xFF;
                        }
			
		static void twi_stop(void)
			{
			}
                static void IOInit(void)
                  {
                        
                        I2C_SCL_Pin::SetDirInFloating();//I2C
                        I2C_SDA_Pin::SetDirInFloating();//
                  }
		static void HardwareInitialization(void)
                          {
                          GPIO_InitTypeDef GPIO_InitStructure;
    
                          GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_4);  // SCL
                          GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4);  // SDA
                          
                          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
                          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
                          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//                          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
                          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
                          GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
                          GPIO_Init(GPIOA, &GPIO_InitStructure);
                          
                          RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
                          
                          
                          I2C_InitTypeDef  I2C_InitStructure;
                          
                          // I2C1 Reset

                          RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
                          RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
                      
                      
                          //I2C_DeInit(I2C1);
                      
                          // Configure I2C1
                      
//                          I2C_StructInit(&I2C_InitStructure);
                      
                          I2C_InitStructure.I2C_Ack                     = I2C_Ack_Enable;
                          I2C_InitStructure.I2C_AcknowledgedAddress     = I2C_AcknowledgedAddress_7bit;
                          I2C_InitStructure.I2C_AnalogFilter            = I2C_AnalogFilter_Enable;
                          I2C_InitStructure.I2C_DigitalFilter           = 0x00;
                          I2C_InitStructure.I2C_Mode                    = I2C_Mode_I2C;
                          I2C_InitStructure.I2C_OwnAddress1             = 0x00;
//                          I2C_InitStructure.I2C_Timing                  = (uint32_t)0x00B01A4B; //Timing register value is computed with the AN4235 xls file, fast Mode @400kHz with I2CCLK = 48MHz, rise time = 140ns, fall time = 40ns
                          //I2C_InitStructure.I2C_Timing = 0x00201D2B;//100khz, standard
//                          I2C_InitStructure.I2C_Timing                  = 0x00B0184C; //48mhz 400khz 100/100
                          I2C_InitStructure.I2C_Timing                  = 0x0010020A;//I2C clock 8MHz 400KHz 100/10
                      
                          I2C_Init(I2C1, &I2C_InitStructure);
                          I2C_Cmd(I2C1, ENABLE);
                          }
	protected:
	private:
		static I2C_TypeDef* getTWI()
			{
			//return (I2C_TypeDef*)twiAddr;
                        return I2C1;
			}
	};
