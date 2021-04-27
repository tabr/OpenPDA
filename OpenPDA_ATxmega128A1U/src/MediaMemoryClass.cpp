// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * MediaMemoryClass.cpp
 *
 * Created: 10.12.2016 2:17:08
 *  Author: tabr
 */ 

#include "M25P05_instructions.h"

template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::EnterSleepMode(void)
  {
  FlashMemoryInstruction i  = this->GetDriver()->PowerDownInstruction();
  if (i != 0)
    {
    SPIDevice::Communicate(i);
    }
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::EnterNormalMode(void)
  {
  this->ReadJEDECIfNeed();
  FlashMemoryInstruction i  = this->GetDriver()->ReleasePowerDownInstruction();
  if (i != 0)
    {
    SPIDevice::Communicate(i);
    }
  this->GetDriver()->ReleasePowerDownDelay();
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::ReadJEDEC(void)//TODO: HACK!!!
  {
  //extern StalkerUI_Class StalkerUI;
  //extern LcdClass Lcd;
  TODO("this is hack");
  SPIDevice::Communicate(this->INSTRUCTION_RELEASE_PD);
  _delay_us(10);
  SPIDevice::Communicate(this->INSTRUCTION_JEDEC_ID, this->jedecArray, this->INSTRUCTION_JEDEC_LENGTH);
  
  //sprintf(Lcd.lcd_buf, "1 %03d %03d %03d", jedecArray[0], jedecArray[1], jedecArray[2]);
  //StalkerUI.DisplayString(StalkerUI_Class::UI_LCD_LINE_2);
  
  
  if (this->jedecArray[0] == 0 && this->jedecArray[1] == 0 && this->jedecArray[2] == 0)
    {
    //nothing found BUT...
    //NUMONYX M25P05 can be WITHOUT JEDEC
    //it reports 0x05 after RES instruction and 3dummy bytes
    TODO("this is hack");
    //while(1);
    SPIDevice::ActivateDevice();
    SPIDevice::Send(this->INSTRUCTION_RELEASE_PD);
    SPIDevice::Send(0);
    SPIDevice::Send(0);
    SPIDevice::Send(0);
    uint8_t response  = SPIDevice::Send(0);
    SPIDevice::DeactivateDevice();
    if (response == 0x05)
      {
      
      this->jedecArray[JEDECID_MANUFACTURER]  = FlashMemoryDriverContainerClass::FLASH_MEMORY_MENUFACTURERS::FLASH_MEMORY_MANUFACTURER_NUMONYX;
      this->jedecArray[JEDECID_MEMORY_TYPE]  = 0x20;
      this->jedecArray[JEDECID_CAPACITY]    = 0x10;
      }
    }

  this->jedec_device  = (this->jedecArray[JEDECID_MEMORY_TYPE]<<8) | (this->jedecArray[JEDECID_CAPACITY]<<0);
  
  //this->FMDC->SelectedDriver  = &this->FMDC->FlashMemoryDriverUnknown;
  //this->FMDC->SelectDriver(&this->FMDC->FlashMemoryDriverUnknown);
  this->FMDC->ResetSelectedDriver();
  if (this->FMDC->SelectDriverForJEDEC(this->jedecArray[JEDECID_MANUFACTURER], jedec_device))
    {
    //TODO
    }
  else
    {
    }
  }
template <class SPIDevice>
bool FlashMemoryClass<SPIDevice>::isJEDECReaded(void)
  {
  return (this->jedecArray[JEDECID_MANUFACTURER] != 0);
  }
template <class SPIDevice>
uint8_t FlashMemoryClass<SPIDevice>::GetManufacturerID(void)
  {
  this->ReadJEDECIfNeed();
  return this->jedecArray[JEDECID_MANUFACTURER];
  }
template <class SPIDevice>
uint8_t* FlashMemoryClass<SPIDevice>::GetCachedJDEC(void)
  {
  this->ReadJEDECIfNeed();
  return this->jedecArray;
  }
template <class SPIDevice>
FLASH_MEMORY_CAPACITY FlashMemoryClass<SPIDevice>::GetCapacity(void)
  {
  this->ReadJEDECIfNeed();
  return this->GetDriver()->GetCapacity(this->jedec_device);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::ReadJEDECIfNeed(void)
  {
  if (!this->isJEDECReaded())
    {
    this->ReadJEDEC();
    }
  }
template <class SPIDevice>
FlashMemoryDriverInterface* FlashMemoryClass<SPIDevice>::GetDriver(void)
  {
  this->ReadJEDECIfNeed();
  return this->FMDC->GetSelectedDriver();
  }
template <class SPIDevice>
FlashMemoryClass<SPIDevice>::FlashMemoryClass(void)
  {
  memset(this->jedecArray, 0, INSTRUCTION_JEDEC_LENGTH);
  }



template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::ReadData(uint8_t* data, uint8_t dataLength)
  {
  this->ReadData(0, 0, 0, data, (uint16_t)dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::ReadData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint8_t dataLength)
  {
  this->ReadData(AddressH, AddressM, AddressL, data, (uint16_t)dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::ReadData(uint8_t* data, uint16_t dataLength)
  {
  this->ReadData(0, 0, 0, data, dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::ReadData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint16_t dataLength)
  {
  this->ReadJEDECIfNeed();
  uint8_t request[4]  = {this->GetDriver()->GetReadInstrunction(), AddressH, AddressM, AddressL};
  SPIDevice::Communicate( request, 4, data, dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::EraseDevice(void)
  {
  
  //Player.GetArtefactPorts()->newActivatePort(0);
  //Player.GetArtefactPorts()->getHardware()->SPI_send(M25P05_INSTRUCTION_WRITE_ENABLE);
  //Player.GetArtefactPorts()->newDeactivatePort(0);
  //SPIDevice::Communicate(this->GetDriver()->InstructionWriteEnable());
  
  //_delay_us(15);
  //Player.GetArtefactPorts()->newActivatePort(0);
  //Player.GetArtefactPorts()->getHardware()->SPI_send(M25P05_INSTRUCTION_BULK_ERASE);
  //Player.GetArtefactPorts()->newDeactivatePort(0);
  //while((Player.GetArtefactPorts()->M25P05_Read_Status_Register(0) & 1) != 0);
  
  
  SPIDevice::Communicate(M25P05_INSTRUCTION_WRITE_ENABLE);
  _delay_us(15);//Вроде, по даташиту...
  SPIDevice::Communicate(this->GetDriver()->InstructionEraseDevice());
  _delay_ms(1000);//(tCE) W25X80 10 to 20 SECONDS!!!
  while ((this->ReadStatusRegister1()  & 1) != 0);//wait until busy
  //while ((this->ReadStatusRegister1() & (1<<1 | 1<<0)) != 0);//wait until WEL is set

  //while((this->M25P05_Read_Status_Register(pin) & 1) != 0);
  }
template <class SPIDevice>
uint8_t FlashMemoryClass<SPIDevice>::ReadStatusRegister1(void)
  {
  uint8_t answer[1]={0};
  SPIDevice::Communicate(this->GetDriver()->InstructionGetStatusRegister1(), answer, 1);
  return answer[0];
  }

template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::WriteData(uint8_t* data, uint8_t dataLength)
  {
  this->WriteData(0, 0, 0, data, dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::WriteData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint8_t dataLength)
  {
  this->WriteData(AddressH, AddressM, AddressL, data, (uint16_t)dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::WriteData(uint8_t* data, uint16_t dataLength)
  {
  this->WriteData(0, 0, 0, data, dataLength);
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>::WriteData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint16_t dataLength)
  {
  SPIDevice::Communicate(M25P05_INSTRUCTION_WRITE_ENABLE);
  _delay_us(15);//Вроде, по даташиту...
//  #warning "Ugly hack!"
  //uint8_t* request  = new uint8_t[dataLength+4];
  uint8_t request[4];
  request[0]  = this->GetDriver()->InstructionPageProgram();
  request[1]  = AddressH;
  request[2]  = AddressM;
  request[3]  = AddressL;
  //memcpy(&request[4], data, dataLength);//начиная с request[4] будут идти данные data[0]
  SPIDevice::ActivateDevice();
  SPIDevice::SendRequest(request, 4);//PP + addr
  _delay_ms(1);
  SPIDevice::SendRequest(data, dataLength);
//  SPIDevice::Communicate(request, dataLength+4);
  SPIDevice::DeactivateDevice();
  //MemoryManager.deallocateFromTop(dataLength+4);
  while ((this->ReadStatusRegister1()  & 1) != 0);//wait until busy
  }
template <class SPIDevice>
void FlashMemoryClass<SPIDevice>:: IOInit(void)
  {
  MediaFlashPinClk::SetDirOut();
  MediaFlashPinClk::SetOutHigh();

  MediaFlashPinMiso::SetDirIn();

  MediaFlashPinMosi::SetDirOut();
  MediaFlashPinMosi::SetOutHigh();

  MediaFlashPinSS::SetDirOut();
  MediaFlashPinSS::SetOutHigh();//deactivate
  }