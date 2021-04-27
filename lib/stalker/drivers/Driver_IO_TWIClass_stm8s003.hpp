#pragma once

#include "main.hpp"

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
/*
//template <uintptr_t twiAddr, TWI_Data deviceSlaveAddress, uint16_t interfaceSpeedKhz>
#warning "this function SOMEHOW make code smaller"
bool WaitForFlag(I2C_Flag_TypeDef flag, FlagStatus status, uint8_t usTime)
  {
  while(1)
    {
    if (I2C_GetFlagStatus(flag) == status)
      {
      break;
      }
    if (--usTime == 0)
      {
      //twi_stop();
      return false;
      }
    ONE_US_DELAY;
    }
  return true;
  }
*/
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
				if (++j == 64)//32 - ����� 48 - ����
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
			getTWI()->MASTER.DATA = data;
			while (!(getTWI()->MASTER.STATUS & TWI_MASTER_WIF_bm))
				{
				if (++j == 96)//64 - ����� 70 - ����
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
			/*
                        beginTransmission();
			sendByte(deviceAddress);
			for(uint8_t i=0;i<bytesToWrite;i++)
				{
				sendByte(writeData[i]);
				}
			twi_stop();
			return true;
                        */
                        uint8_t timeout=0;
                        I2C_Cmd(ENABLE);
                        //���� ������������ ���� I2C
                        //wait_event(I2C_SR3_BUSY, 10);
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY) == RESET)
                          
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 1;
                            }
                          ONE_US_DELAY;
                          }
                           
                        //��������� �����-�������
                        //I2C_CR2_START = 1;
                        I2C_GenerateSTART(ENABLE);
                        //���� ��������� ���� SB
                        //wait_event(!I2C_SR1_SB, 1);
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_STARTDETECTION) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 2;
                            }
                          ONE_US_DELAY;
                          }
                         
                         
                        //���������� � ������� ������ ����� �������� ����������
                        I2C->DR = deviceSlaveAddress  & 0xFE;
                        //���� ������������� �������� ������
                        //wait_event(!I2C_SR1_ADDR, 1);
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_ADDRESSSENTMATCHED) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 3;
                            }
                          ONE_US_DELAY;
                          }
                        //������� ���� ADDR ������� �������� SR3
                        //I2C_SR3;
                        I2C_GetFlagStatus(I2C_FLAG_GENERALCALL);
                         
                         
                        //���� ������������ �������� ������
                        //wait_event(!I2C_SR1_TXE, 1);
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 4;
                            }
                          ONE_US_DELAY;
                          }
                        //���������� ����� ��������
                        //I2C_DR = reg_addr;
                        I2C->DR = registerAddress;
                         
                        //�������� ������
                        while(bytesToWrite--)
                          {
                          //���� ������������ �������� ������
                          //wait_event(!I2C_SR1_TXE, 1);
                            timeout=100;
                            while(1)
                              {
                              if (I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == SET)
                                {
                                break;
                                }
                              if (--timeout == 0)
                                {
                                twi_stop();
                                return 5;
                                }
                              ONE_US_DELAY;
                              }
                          //���������� ����� ��������
                          I2C->DR = *writeData++;
                          }
                         
                        //����� ������, ����� DR ����������� � ������ ������ � ��������� �������
                        //wait_event(!(I2C_SR1_TXE && I2C_SR1_BTF), 1);
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == SET && I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 6;
                            }
                          ONE_US_DELAY;
                          }
                         
                        //�������� ����-�������
                        //I2C_CR2_STOP = 1;
                        I2C_GenerateSTOP(ENABLE);
                        //���� ���������� ������� ����
                        //wait_event(I2C_CR2_STOP, 1);
                        
                        timeout=100;
                        while(1)
                          {
                          if ((I2C->CR2 & I2C_CR2_STOP) == 0)
                          //if (I2C_GetFlagStatus(I2C_FLAG_STOPDETECTION) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            return 13;
                            }
                          ONE_US_DELAY;
                          }
                        
                        twi_stop();
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
			/*
                        beginTransmission();
			sendByte(registerAddress);
			requestRead();
			for(uint8_t i=0;i<bytesToRead;i++)
				{// read date and time
				readData[i]	= readByte();
				}
			twi_stop();
			return true;
			*/
                         
                        I2C_Cmd(ENABLE);
                        
                        //HardwareInitialization();
                        //uint8_t tmp=0;
                        uint8_t timeout=0;
                        //���� ������������ ���� I2C
                        //wait_event((I2C->SR3 & I2C_SR3_BUSY), (uint32_t)100);
                        
                        //WAIT_FOR_EVENT(I2C_GetFlagStatus( I2C_FLAG_BUSBUSY),100,{return 1;});
                        
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY) == RESET)
                          //if ((I2C->SR3 & I2C_SR3_BUSY) == 0)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 1;
                            }
                          ONE_US_DELAY;
                          }
                        


                        //��������� ������������� � ����� �������
                        //I2C_CR2_ACK = 1;
                        I2C_AcknowledgeConfig(I2C_ACK_CURR);
                        //I2C->SR2      |= I2C_CR2_ACK;
                         
                        //��������� �����-�������
                        //I2C_CR2_START = 1;
                        I2C_GenerateSTART(ENABLE);
                        //I2C->CR2 |= I2C_CR2_START;
                        
                        //���� ��������� ���� SB
                        //wait_event(!I2C_SR1_SB, 1);
                        //wait_event(!(I2C->SR1 & I2C_SR1_SB), 10);
                        //while ((I2C->SR1 & I2C_SR1_SB) == 0 );
                        //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_STARTDETECTION) == 0),100,{return 2;});
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_STARTDETECTION) == SET)
                          //if ((I2C->SR1 & I2C_SR1_SB))
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 2;
                            }
                          ONE_US_DELAY;
                          }
                         
                        //���������� � ������� ������ ����� �������� ����������
                        I2C->DR = deviceSlaveAddress & 0xFE;
                        //���� ������������� �������� ������
                        //wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 10);
                        //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == 0),100,{return 3;});
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_ADDRESSSENTMATCHED) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 3;
                            }
                          ONE_US_DELAY;
                          }
                        //������� ���� ADDR ������� �������� SR3
                        //tmp   = I2C->SR3;
                        I2C_GetFlagStatus(I2C_FLAG_GENERALCALL);
                         
                        //���� ������������ �������� ������ RD
                        //wait_event(!(I2C->SR1 & I2C_SR1_TXE), 10);
                        //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_TXEMPTY) == 0),100,{return 4;});
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 4;
                            }
                          ONE_US_DELAY;
                          }
                         
                        //�������� ����� �������� slave-����������, ������� ����� ���������
                        I2C->DR = registerAddress;
                        //����� ������, ����� DR ����������� � ������ ������ � ��������� �������
                        //wait_event(!((I2C->SR1 & I2C_SR1_TXE) && (I2C->SR1 & I2C_SR1_BTF)), 10);
                        //WAIT_FOR_EVENT(((I2C_GetFlagStatus( I2C_FLAG_TXEMPTY) == 0) && I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED)),100,{return 5;});
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == SET && I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 5;
                            }
                          ONE_US_DELAY;
                          }
                         
                        //��������� �����-������� (�������)
                        //I2C_CR2_START = 1;
                        I2C_GenerateSTART(ENABLE);
                        //���� ��������� ���� SB
                        //wait_event(!(I2C->SR1 & I2C_SR1_SB), 10);
                        //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_STARTDETECTION) == 0),100,{return 6;});
                        timeout=100;
                        while(1)
                          {
                          if (I2C_GetFlagStatus(I2C_FLAG_STARTDETECTION) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            twi_stop();
                            return 6;
                            }
                          ONE_US_DELAY;
                          }
                         
                        //���������� � ������� ������ ����� �������� ���������� � ���������
                        //� ����� ������ (���������� �������� ���� � 1)
                        I2C->DR = deviceSlaveAddress | BIT_READ;
                         
                        //������ �������� ������� �� ���������� ����������� ����
                        //N=1
                        /*
                        if(bytesToRead == 1){
                          //��������� ������������� � ����� �������
                          //I2C_CR2_ACK = 0;
                          I2C_AcknowledgeConfig(I2C_ACK_NONE);
                          //���� ������������� �������� ������
                          //wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 10);
                          //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == 0),100,{return 7;});
                          timeout=100;
                          while(1)
                            {
                            if (I2C_GetFlagStatus(I2C_FLAG_ADDRESSSENTMATCHED) == SET)
                              {
                              break;
                              }
                            if (--timeout == 0)
                              {
                              twi_stop();
                              return 7;
                              }
                            ONE_US_DELAY;
                            }
                           
                          //�������� �� Errata
                          __disable_interrupt();
                          //������� ���� ADDR ������� �������� SR3
                          tmp = I2C->SR3;
                           
                          //����������� ��� STOP
                          //I2C_CR2_STOP = 1;
                          I2C_GenerateSTOP(ENABLE);
                          //�������� �� Errata
                          __enable_interrupt();
                           
                          //���� ������� ������ � RD
                          //wait_event(!(I2C->SR1 & I2C_SR1_RXNE), 10);
                          //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_RXNOTEMPTY) == 0),100,{return 8;});
                          timeout=100;
                          while(1)
                            {
                            if (I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)
                              {
                              break;
                              }
                            if (--timeout == 0)
                              {
                              return 8;
                              }
                            ONE_US_DELAY;
                            }
                           
                          //������ �������� ����
                          *readData = I2C->DR;
                        } 
                        //N=2
                        else if(bytesToRead == 2){
                          //��� ������� ��������� NACK �� ��������� �������� �����
                          //I2C_CR2_POS = 1;
                          I2C_AcknowledgeConfig(I2C_ACK_NEXT);
                          //���� ������������� �������� ������
                          //wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 10);
                          WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == 0),100,{return 9;});
                          //�������� �� Errata
                          __disable_interrupt();
                          //������� ���� ADDR ������� �������� SR3
                          //I2C_SR3;
                          tmp = I2C->SR3;
                          //��������� ������������� � ����� �������
                          //I2C_CR2_ACK = 0;
                          I2C_AcknowledgeConfig(I2C_ACK_NONE);
                          //�������� �� Errata
                          __enable_interrupt();
                          //���� �������, ����� ������ ���� �������� � DR,
                          //� ������ � ��������� ��������
                          //wait_event(!(I2C->SR1 & I2C_SR1_BTF), 10);
                          WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == 0),100,{return 10;});

                           
                          //�������� �� Errata
                          __disable_interrupt();
                          //����������� ��� STOP
                          //I2C_CR2_STOP = 1;
                          I2C_GenerateSTART(ENABLE);
                          //������ �������� �����
                          *readData++ = I2C->DR;
                          //�������� �� Errata
                          __enable_interrupt();
                          *readData = I2C->DR;
                        } 
                        //N>2
                        else */ if(bytesToRead > 2)
                          {
                          //���� ������������� �������� ������
                          //wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 10);
                          //wait_event(((I2C->SR1 & I2C_SR1_ADDR) == 0), 10);
                          //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == 0),100,{return 11;});
                          //WAIT_FOR_EVENT(((I2C->SR1 & I2C_SR1_ADDR) == 0),100,{return 9;});
                          
                          timeout=100;
                          while(1)
                            {
                            if (I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == SET)
                            //tmp = I2C->SR1;
                            //if ((tmp & I2C_SR1_ADDR) != 0)
                              {
//                              tmp = I2C->SR1;
                              break;
                              }
                            if (--timeout == 0)
                              {
                              twi_stop();
                              return 11;
                              }
                            ONE_US_DELAY;
                            }
                          
                          //�������� �� Errata
                          __disable_interrupt();
                           
                          //������� ���� ADDR ������� �������� SR3
                          //I2C_SR3;
                          //tmp = I2C->SR3;
                          I2C_GetFlagStatus(I2C_FLAG_GENERALCALL);
                           
                          //�������� �� Errata
                          __enable_interrupt();
                           
//                          while(bytesToRead-- > 3 && tmo)
                          while(bytesToRead-- > 3)
                            {
                            //������� ��������� ������ � DR � ��������� ��������
                            //wait_event(!(I2C->SR1 & I2C_SR1_BTF), 10);
                            //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == 0),100,{return 12;});
                              timeout=100;
                              while(1)
                                {
                                if (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == SET)
                                  {
                                  break;
                                  }
                                if (--timeout == 0)
                                  {
                                  twi_stop();
                                  return 12;
                                  }
                                ONE_US_DELAY;
                                }
                            //������ �������� ���� �� DR
                            *readData++ = I2C->DR;
                            }
                          //����� �������� �����
                          /*
                          if(!tmo)
                            {
                            //return I2C_TIMEOUT;
                              return 13;
                            }
                           */
                          //�������� ������� 3 ��������� �����
                          //����, ����� � DR �������� N-2 ����, � � ��������� ��������
                          //�������� N-1 ����
                          //wait_event(!(I2C->SR1 & I2C_SR1_BTF), 10);
                          //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == 0),100,{return 13;});
                          timeout=100;
                          while(1)
                            {
                            if (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == SET)
                              {
                              break;
                              }
                            if (--timeout == 0)
                              {
                              twi_stop();
                              return 13;
                              }
                            ONE_US_DELAY;
                            }
                          //��������� ������������� � ����� �������
                          //I2C_CR2_ACK = 0;
                          I2C_AcknowledgeConfig(I2C_ACK_NONE);
                          //�������� �� Errata
                          __disable_interrupt();
                          //������ N-2 ���� �� RD, ��� ����� �������� ������� � ���������
                          //������� ���� N, �� ������ � ����� ������ ���������� ������� NACK
                          *readData++ = I2C->DR;
                          //������� STOP
                          //I2C_CR2_STOP = 1;
                          I2C_GenerateSTART(ENABLE);
                          //������ N-1 ����
                          *readData++ = I2C->DR;
                          //�������� �� Errata
                          __enable_interrupt();
                          //����, ����� N-� ���� ������� � DR �� ���������� ��������
                          //wait_event(!(I2C->SR1 & I2C_SR1_RXNE), 10);
                          timeout=100;
                          while(1)
                            {
                            if (I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == SET)
                              {
                              break;
                              }
                            if (--timeout == 0)
                              {
                              return 13;
                              }
                            ONE_US_DELAY;
                            }
                          //WAIT_FOR_EVENT((I2C_GetFlagStatus( I2C_FLAG_RXNOTEMPTY) == 0),100,{return 14;});
                          //������ N ����
                          *readData++ = I2C->DR;
                          }
                        else
                          {
                          while(1){nop();};
                          }
                        I2C_GenerateSTOP(ENABLE);
                        //���� �������� ���� �������
                        //wait_event((I2C->CR2 & I2C_CR2_STOP), 10);
                        /*
                        timeout=100;
                        while(1)
                          {
                          //if ((I2C->CR2 & I2C_CR2_STOP) == 0)
                          if (I2C_GetFlagStatus(I2C_FLAG_STOPDETECTION) == SET)
                            {
                            break;
                            }
                          if (--timeout == 0)
                            {
                            return 13;
                            }
                          ONE_US_DELAY;
                          }
                        */
                        //WAIT_FOR_EVENT((I2C->CR2 & I2C_CR2_STOP),100,{return 15;});
                        //���������� ��� POS, ���� ����� �� ��� ����������
                        //I2C_CR2_POS = 0;
                        //cbi(I2C->CR2, 3);// <- I2C_CR2_POS = 0;
                        //I2C_AcknowledgeConfig(I2C_ACK_NONE);//???
                        //I2C_Cmd(DISABLE);
                        //uint8_t tmp     = I2C->CR1;
                        //tmp             = I2C->CR2;
                        //tmp             = 0;
                        //I2C->CR1=0;
                        //I2C->CR2=0;
                        //I2C_SoftwareResetCmd(ENABLE);
                        //I2C_AcknowledgeConfig( I2C_ACK_CURR);
                        twi_stop();
                        return 255;
                        }
			
                        
                        
                        
                        
                        
                     /*
                    static uint8_t readFromDeviceExample(uint8_t registerAddress, uint8_t &bytesToRead, uint8_t *readData)
			{
                        uint16_t timeout=0;
                        //uint8_t tmp=0;
                        // While the bus is busy
                        timeout=200;
                        //wait_event((I2C->SR3 & I2C_SR3_BUSY), (uint32_t)100);
                        while(I2C_GetFlagStatus( I2C_FLAG_BUSBUSY))
                        //while (I2C->SR3 & I2C_SR3_BUSY)
                          {
                          if (--timeout == 0)
                            {
                            return 1;
                            }
                          ONE_US_DELAY;
                          }
                        
                        // Send START condition
                        I2C_GenerateSTART(ENABLE);
                        // Test on EV5 and clear it (cleared by reading SR1 then writing to DR)
                        timeout=200;
                        while(!I2C_CheckEvent( I2C_EVENT_MASTER_MODE_SELECT))
                          {
                          if((--timeout) == 0)
                            {
                            return 2;
                            }
                          ONE_US_DELAY;
                          }
                        // Send EEPROM address for write
                        I2C_Send7bitAddress( (uint8_t)deviceSlaveAddress, I2C_DIRECTION_TX);
                        // Test on EV6 and clear it
                        timeout=200;
                        while(!I2C_CheckEvent( I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
                          {
                          if((--timeout) == 0)
                            {
                            return 3;
                            }
                          ONE_US_DELAY;
                          }
                        // Send the EEPROM's internal address to read from: LSB of the address
                        I2C_SendData( registerAddress);
                        
                        // Test on EV8 and clear it
                        timeout=500;
                        while(I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == RESET)
//                        while(I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == SET)
                          {
                          if((--timeout) == 0)
                            {
                            return 4;
                            }
                          ONE_US_DELAY;
                          }
                        // Send START condition a second time
                        I2C_GenerateSTART( ENABLE);
                        // Test on EV5 and clear it (cleared by reading SR1 then writing to DR)
                        timeout=200;
                        while(!I2C_CheckEvent( I2C_EVENT_MASTER_MODE_SELECT))
                          {
                          if((--timeout) == 0)
                            {
                            return 5;
                            }
                          ONE_US_DELAY;
                          }
                        // Send EEPROM address for read
                        I2C_Send7bitAddress((uint8_t)deviceSlaveAddress, I2C_DIRECTION_RX);
                        // Read data from first byte until byte N-3
                        if (bytesToRead> 3)
                        //while (bytesToRead> 3)
                          {
                          // Poll on BTF
                          timeout=500;
                          //while (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == RESET)
//                          while (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == SET)
                          while(1)
                            {
                            if (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == RESET)
                              {
                              break;
                              }
                            if((--timeout) == 0)
                              {
                              return 6;
                              }
                            ONE_US_DELAY;
                            }
                          // Read a byte from the EEPROM
                          // *readData = I2C->DR;
                          *readData++ = I2C->DR;
                          // Point to the next location where the byte read will be saved
                          // *readData++
                          // Decrement the read bytes counter
                          bytesToRead--;
                          // Wait to make sure that STOP control bit has been cleared
                          timeout=200;
                          }
                        //  Remains three data for read: data N-2, data N-1, Data N
                        // Three Bytes Master Reception procedure (POLLING) ------------------------
                        if (bytesToRead == 3)
                          {
                          // Data N-2 in DR and data N -1 in shift register
                          // Poll on BTF
                          timeout=200;
                          while (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == RESET)
//                          while (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == SET)
                            {
                            if((--timeout) == 0)
                              {
                              return 7;
                              }
                            ONE_US_DELAY;
                            }
                          // Clear ACK
                          I2C_AcknowledgeConfig(I2C_ACK_NONE);
                          // Call User callback for critical section start (should typically disable interrupts)
                          sEE_EnterCriticalSection_UserCallback();
                          // Read Data N-2
                          *readData++ = I2C_ReceiveData();
                          // Program the STOP
                          I2C_GenerateSTOP(ENABLE);
                          // Read DataN-1
                          *readData++ = I2C_ReceiveData();
                          // Call User callback for critical section end (should typically re-enable interrupts)
                          sEE_ExitCriticalSection_UserCallback();
                          // Point to the next location where the byte read will be saved
                          // *pBuffer++;
                          // Poll on RxNE
                          timeout=500;
                          while (I2C_GetFlagStatus( I2C_FLAG_RXNOTEMPTY) == RESET)
                            {
                            if((--timeout) == 0)
                              {
                              return 8;
                              }
                            ONE_US_DELAY;
                            }
                          // Read DataN
                          *readData = I2C_ReceiveData();
                          //Reset the number of bytes to be read from the EEPROM
                          bytesToRead = 0;
                          }
                        // If number of data to be read is 2
                        // Tow Bytes Master Reception procedure (POLLING) ---------------------------
                        if (bytesToRead == 2)
                          {
                          // Enable acknowledgement on next byte (set POS and ACK bits)
                          I2C_AcknowledgeConfig(I2C_ACK_NEXT);
                          // Wait on ADDR flag to be set (ADDR is still not cleared at this level
                          timeout=200;
                          while(I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == RESET)
                            {
                            if((--timeout) == 0)
                              {
                              return 9;
                              }
                            ONE_US_DELAY;
                            }
                          // Clear ADDR register by reading SR1 then SR3 register (SR1 has already been read)
                          //tmp   = I2C->SR3;
                          I2C_GetFlagStatus(I2C_FLAG_GENERALCALL);
                          // Disable Acknowledgement
                          I2C_AcknowledgeConfig(I2C_ACK_NONE);
                          // Wait for BTF flag to be set
                          timeout=200;
                          while (I2C_GetFlagStatus( I2C_FLAG_TRANSFERFINISHED) == RESET)
                            {
                            if((--timeout) == 0)
                              {
                              return 10;
                              }
                            ONE_US_DELAY;
                            }
                          // Call User callback for critical section start (should typically disable interrupts)
                          sEE_EnterCriticalSection_UserCallback();
                          // Program the STOP
                          I2C_GenerateSTOP(ENABLE);
                          // Read Data N-1
                          *readData++ = I2C_ReceiveData();
                          // Call User callback for critical section end (should typically re-enable interrupts)
                          sEE_EnterCriticalSection_UserCallback();
                          // Read Data N
                          *readData = I2C_ReceiveData();
                          // Reset the number of bytes to be read from the EEPROM
                          bytesToRead = 0;  
                          }
                        if (bytesToRead < 2)
                          {
                          // Wait on ADDR flag to be set (ADDR is still not cleared at this level
                          timeout=200;
                          while(I2C_GetFlagStatus( I2C_FLAG_ADDRESSSENTMATCHED) == RESET)
                            {
                            if((--timeout) == 0)
                              {
                              return 11;
                              }
                            ONE_US_DELAY;
                            }
                          // Disable Acknowledgement
                          I2C_AcknowledgeConfig(I2C_ACK_NONE);   
                          // Call User callback for critical section start (should typically disable interrupts)
                          sEE_EnterCriticalSection_UserCallback();
                          // Clear ADDR register by reading SR1 then SR3 register (SR1 has already been read)
                          //tmp   = I2C->SR3;
                          I2C_GetFlagStatus(I2C_FLAG_GENERALCALL);
                          // Send STOP Condition
                          I2C_GenerateSTOP( ENABLE);
                          // Call User callback for critical section end (should typically re-enable interrupts)
                          sEE_ExitCriticalSection_UserCallback();
                          // Wait for the byte to be received
                          timeout=200;
                          while(I2C_GetFlagStatus( I2C_FLAG_RXNOTEMPTY) == RESET)
                            {
                            if((--timeout) == 0)
                              {
                              return 12;
                              }
                            ONE_US_DELAY;
                            }
                          // Read the byte received from the EEPROM
                          *readData = I2C_ReceiveData();
                          //bytesToRead--;
                          bytesToRead=0;
                          // Wait to make sure that STOP control bit has been cleared
                          timeout=200;
                          while(I2C->CR2 & I2C_CR2_STOP)
                            {
                            if((--timeout) == 0)
                              {
                              return 13;
                              }
                            ONE_US_DELAY;
                            }
                          // Re-Enable Acknowledgement to be ready for another reception
                          I2C_AcknowledgeConfig( I2C_ACK_CURR);
                          
                          }
                        return 14;
                        }
                */
/*
		static bool readFromDevice(uint8_t registerAddressH, uint8_t registerAddressL, uint16_t bytesToRead, uint8_t *readData)
			{
			if (!(beginTransmission()))
				{
				return false;
				}
			sendByte(registerAddressH);
			sendByte(registerAddressL);
			requestRead();
			for(uint16_t i=0;i<bytesToRead;i++)
				{// read date and time
				readData[i]	= readByte();
				}
			twi_stop();
			return true;
			
			}
		static uint8_t readByte(void)
			{
			uint8_t j=0;
			while(!(getTWI()->MASTER.STATUS&TWI_MASTER_RIF_bm))
				{
				if (++j == 96)//64 - ����� 70 - ����
					{
					twi_stop();
					return 0;
					}
				//_delay_us(1);
                                
				}
			return getTWI()->MASTER.DATA;
			}

*/
		static void twi_stop(void)
			{
			//getTWI()->MASTER.CTRLC = (TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc);
                        I2C_SoftwareResetCmd(ENABLE);
                        HardwareInitialization();
                        //I2C->CR1=0;
                        //I2C->CR2=0;
                        //���������� ��� POS, ���� ����� �� ��� ����������
                        //I2C_CR2_POS = 0;
                        //cbi(I2C->CR2, 3);// <- I2C_CR2_POS = 0;
                        //I2C_Cmd(DISABLE);
			}
                static void IOInit(void)
                  {
                        
                        I2C_SCL_Pin::SetDirInFloating();//I2C
                        I2C_SDA_Pin::SetDirInFloating();//
                        I2C_SCL_Pin::SetOutLow();
                        I2C_SDA_Pin::SetOutLow();
                        //TODO cbi(GPIOB->CR2,5);??!
                        
                        //cbi(GPIOB->DDR,4);
                        //cbi(GPIOB->DDR,5);
                        //sbi(GPIOB->ODR,4);
                        //sbi(GPIOB->ODR,5);
                        //cbi(GPIOB->CR1,4);
                        //cbi(GPIOB->CR1,5);
                        //cbi(GPIOB->CR2,4);
                        //cbi(GPIOB->CR2,5);
                        /*
                        PB_DDR_bit.DDR4 = 0;
                        PB_DDR_bit.DDR5 = 0;
                        PB_ODR_bit.ODR5 = 1;  //SDA
                        PB_ODR_bit.ODR4 = 1;  //SCL
                         
                        PB_CR1_bit.C14 = 0;
                        PB_CR1_bit.C15 = 0;
                         
                        PB_CR2_bit.C24 = 0;
                        PB_CR2_bit.C25 = 0;
                        */
                  }
		static void HardwareInitialization(void)
			{
			I2C_DeInit();
                        /* Initialize the I2C */
                        //I2C_Init(100000, 0xA2,I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
                        I2C_Init(400000, 0xBC,I2C_DUTYCYCLE_16_9, I2C_ACK_CURR, I2C_ADDMODE_7BIT, 16);
                        /* Configuration of interrupts only */
                        I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_EVT | I2C_IT_BUF) , DISABLE);
                        I2C_Cmd(DISABLE); //// ���� �� ������. � SPL � ������ ���
                        /*
                         
                        //������� ������������ ��������� MHz
                        I2C_FREQR_FREQ = 12;
                        //��������� I2C
                        I2C_CR1_PE = 0;
                        //� ����������� ������ �������� I2C max = 100 ����/�
                        //�������� ����������� ����� 
                        I2C_CCRH_F_S = 0;
                        //CCR = Fmaster/2*Fiic= 12MHz/2*100kHz
                        ccr = f_master_hz/(2*f_i2c_hz);
                        //Set Maximum Rise Time: 1000ns max in Standard Mode
                        //= [1000ns/(1/InputClockFrequencyMHz.10e6)]+1
                        //= InputClockFrequencyMHz+1
                        I2C_TRISER_TRISE = 12+1;
                        I2C_CCRL = ccr & 0xFF;
                        I2C_CCRH_CCR = (ccr >> 8) & 0x0F;
                        //�������� I2C
                        I2C_CR1_PE = 1;
                        //��������� ������������� � ����� �������
                        I2C_CR2_ACK = 1;
                        
  */

			}
	protected:
	private:
		static I2C_TypeDef* getTWI()
			{
			//return (I2C_TypeDef*)twiAddr;
                        return I2C;
			}
	};
/*
t_i2c_status i2c_rd_reg(unsigned char address, unsigned char reg_addr, char * data, unsigned char length)
{
   uint8_t tmp=0;
  //���� ������������ ���� I2C
  wait_event((I2C->SR3 & I2C_SR3_BUSY), (uint32_t)10);
     
  //��������� ������������� � ����� �������
  //I2C_CR2_ACK = 1;
  //I2C_AcknowledgeConfig(I2C_ACK_CURR);
  I2C->SR2      |= I2C_CR2_ACK;
   
  //��������� �����-�������
  //I2C_CR2_START = 1;
  //I2C_GenerateSTART(ENABLE);
  I2C->CR2 |= I2C_CR2_START;
  
  //���� ��������� ���� SB
  //wait_event(!I2C_SR1_SB, 1);
  wait_event(!(I2C->SR1 & I2C_SR1_SB), 1);
  //while ((I2C->SR1 & I2C_SR1_SB) == 0 );
   
  //���������� � ������� ������ ����� �������� ����������
  I2C->DR = address & 0xFE;
  //���� ������������� �������� ������
  wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 1);
  //������� ���� ADDR ������� �������� SR3
  tmp   = I2C->SR3;
   
  //���� ������������ �������� ������ RD
  wait_event(!(I2C->SR1 & I2C_SR1_TXE), 1);
   
  //�������� ����� �������� slave-����������, ������� ����� ���������
  I2C->DR = reg_addr;
  //����� ������, ����� DR ����������� � ������ ������ � ��������� �������
  wait_event(!((I2C->SR1 & I2C_SR1_TXE) && (I2C->SR1 & I2C_SR1_BTF)), 1);
   
  //��������� �����-������� (�������)
  //I2C_CR2_START = 1;
  I2C_GenerateSTART(ENABLE);
  //���� ��������� ���� SB
  wait_event(!(I2C->SR1 & I2C_SR1_SB), 1);
   
  //���������� � ������� ������ ����� �������� ���������� � ���������
  //� ����� ������ (���������� �������� ���� � 1)
  I2C->DR = address | 0x01;
   
  //������ �������� ������� �� ���������� ����������� ����
  //N=1
  if(length == 1){
    //��������� ������������� � ����� �������
    //I2C_CR2_ACK = 0;
    I2C_AcknowledgeConfig(I2C_ACK_NONE);
    //���� ������������� �������� ������
    wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 1);
     
    //�������� �� Errata
    __disable_interrupt();
    //������� ���� ADDR ������� �������� SR3
    tmp = I2C->SR3;
     
    //����������� ��� STOP
    //I2C_CR2_STOP = 1;
    I2C_GenerateSTOP(ENABLE);
    //�������� �� Errata
    __enable_interrupt();
     
    //���� ������� ������ � RD
    wait_event(!(I2C->SR1 & I2C_SR1_RXNE), 1);
     
    //������ �������� ����
    *data = I2C->DR;
  } 
  //N=2
  else if(length == 2){
    //��� ������� ��������� NACK �� ��������� �������� �����
    //I2C_CR2_POS = 1;
    I2C_AcknowledgeConfig(I2C_ACK_NEXT);
    //���� ������������� �������� ������
    wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 1);
    //�������� �� Errata
    __disable_interrupt();
    //������� ���� ADDR ������� �������� SR3
    //I2C_SR3;
    tmp = I2C->SR3;
    //��������� ������������� � ����� �������
    //I2C_CR2_ACK = 0;
    I2C_AcknowledgeConfig(I2C_ACK_NONE);
    //�������� �� Errata
    __enable_interrupt();
    //���� �������, ����� ������ ���� �������� � DR,
    //� ������ � ��������� ��������
    wait_event(!(I2C->SR1 & I2C_SR1_BTF), 1);
     
    //�������� �� Errata
    __disable_interrupt();
    //����������� ��� STOP
    //I2C_CR2_STOP = 1;
    I2C_GenerateSTART(ENABLE);
    //������ �������� �����
    *data++ = I2C->DR;
    //�������� �� Errata
    __enable_interrupt();
    *data = I2C->DR;
  } 
  //N>2
  else if(length > 2){
    //���� ������������� �������� ������
    wait_event(!(I2C->SR1 & I2C_SR1_ADDR), 1);
     
    //�������� �� Errata
    __disable_interrupt();
     
    //������� ���� ADDR ������� �������� SR3
    //I2C_SR3;
    tmp = I2C->SR3;
     
    //�������� �� Errata
    __enable_interrupt();
     
    while(length-- > 3 && tmo){
      //������� ��������� ������ � DR � ��������� ��������
      wait_event(!(I2C->SR1 & I2C_SR1_BTF), 1);
      //������ �������� ���� �� DR
      *data++ = I2C->DR;
    }
    //����� �������� �����
    if(!tmo) return I2C_TIMEOUT;
     
    //�������� ������� 3 ��������� �����
    //����, ����� � DR �������� N-2 ����, � � ��������� ��������
    //�������� N-1 ����
    wait_event(!(I2C->SR1 & I2C_SR1_BTF), 1);
    //��������� ������������� � ����� �������
    //I2C_CR2_ACK = 0;
    I2C_AcknowledgeConfig(I2C_ACK_NONE);
    //�������� �� Errata
    __disable_interrupt();
    //������ N-2 ���� �� RD, ��� ����� �������� ������� � ���������
    //������� ���� N, �� ������ � ����� ������ ���������� ������� NACK
    *data++ = I2C->DR;
    //������� STOP
    //I2C_CR2_STOP = 1;
    I2C_GenerateSTART(ENABLE);
    //������ N-1 ����
    *data++ = I2C->DR;
    //�������� �� Errata
    __enable_interrupt();
    //����, ����� N-� ���� ������� � DR �� ���������� ��������
    wait_event(!(I2C->SR1 & I2C_SR1_RXNE), 1);
    //������ N ����
    *data++ = I2C->DR;
  }
   
  //���� �������� ���� �������
  wait_event((I2C->CR2 & I2C_CR2_STOP), 1);
  //���������� ��� POS, ���� ����� �� ��� ����������
  //I2C_CR2_POS = 0;
  cbi(I2C->CR2, 3);// <- I2C_CR2_POS = 0;
  //I2C_AcknowledgeConfig(I2C_ACK_NONE);//???
   
  return I2C_SUCCESS;
}
*/