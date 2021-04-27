// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef CLASS_STALKER_LAYER_0_CPP
#define CLASS_STALKER_LAYER_0_CPP
Class_StalkerLayer0::Class_StalkerLayer0(void)
  {
  memset(this->packetContainerRX, 0, this->STRUCTURE_SIZE);
  memset(this->packetContainerTX, 0, this->STRUCTURE_SIZE);

  this->isDataInsideRM    = false;
//  this->isGoodPacketReceivedValue  = false;
  this->isRMInit        = false;
  this->isRMReadyToWork    = false;
  this->RSSI          = 0;
  this->RSSIRaw        = 0;
  this->SignalPower      = 0;

//  PORTD  = 1<<4;
  }
void Class_StalkerLayer0::HardwareInitialization(void)
  {
//  RFM22B_ioinit();//Йобыныйтыврот - эта штука определена в конструкторе класса драйвера, но там, видимо, она не отрабатывается =(
  HAL.EnvironmentRarioModule.setPacketSize(this->STRUCTURE_SIZE);
  //      HAL.setTXBuffer(&this->txBuf[0]);
  HAL.EnvironmentRarioModule.setTXBuffer(this->packetContainerTX);
  HAL.EnvironmentRarioModule.setRXBuffer(this->packetContainerRX);
  if (HAL.EnvironmentRarioModule.HardwareInitialization() != Class_HAL::ERROR_NO_ERRORS)
    {
    this->isRMInit      = false;
    this->isRMReadyToWork  = false;
    return;
    }
  this->isRMInit      = true;
  this->isRMReadyToWork  = true;
  }
/*
bool Class_StalkerLayer0::isGoodPacketReceived1(void)
  {
  return this->isGoodPacketReceivedValue;
  }
void Class_StalkerLayer0::isGoodPacketReceived1(bool value)
  {
  this->isGoodPacketReceivedValue  = value;
  }
*/
bool Class_StalkerLayer0::isModuleReadyToWork(void)
  {
  return this->isRMReadyToWork;
  }
Class_StalkerLayer0::PACKET_TYPES Class_StalkerLayer0::GetRXPacketType(void)
  {
  return static_cast<Class_StalkerLayer0::PACKET_TYPES>(this->packetContainerRX[this->STRUCTURE_0X00_HEAD_H] & this->PACKET_TYPEMASK);
  }
uint8_t Class_StalkerLayer0::GetRXPacketSubType(void)
  {
  return ((this->packetContainerRX[this->STRUCTURE_0X00_HEAD_H] & this->PACKET_SUBTYPEMASK)>>3);
  }
void Class_StalkerLayer0::SetTXPacketType(PACKET_TYPES type)
  {
  //TODO нуу сделать по-нормальному, с обработкой битовых полей
//  type                          = (type & this->PACKET_TYPEMASK);
//  type                          = type;
//  this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H]  = (type & this->PACKET_TYPEMASK);
//  uint8_t newType  = (this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H] & (~(this->PACKET_TYPEMASK)));
  //uint8_t newType  = (this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H] & this->PACKET_SUBTYPEMASK);
  //newType      = newType | (type & this->PACKET_TYPEMASK);
  //this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H]  = newType;
  uint8_t newType  = (type & this->PACKET_TYPEMASK);
  this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H]  = ((this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H] & (~(this->PACKET_TYPEMASK))) | newType);
  }
void Class_StalkerLayer0::SetTXPacketSubType(uint8_t subType)
  {
  //uint8_t newSubType  = (this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H] & this->PACKET_TYPEMASK);
  //newSubType      = newSubType | (subType & this->PACKET_SUBTYPEMASK);
  uint8_t newSubType  = ((subType<<3) & this->PACKET_SUBTYPEMASK);
  this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H]  = ((this->packetContainerTX[this->STRUCTURE_0X00_HEAD_H] & (~(this->PACKET_SUBTYPEMASK))) | newSubType);
  }

/*void Class_StalkerLayer0::setID1(uint8_t id)
  {
  this->packetContainerTX[STRUCTURE_0X02_DATA_H]    = 0x00;
  this->packetContainerTX[STRUCTURE_0X03_DATA_L]    = id;
  }
*/
void Class_StalkerLayer0::prepareTimeUpdatePacket(void)
  {
  this->SetTXPacketType(PACKET_TYPE_TIMEUPDATE);
  this->prepareTXPacket();
  /*
#ifdef RFM69_HW_CRC
  return;
#else //software crc
  this->crc.value_int=CRC16_INIT_VALUE;
  for (uint8_t i=0;i<this->STRUCTURE_DATA_SIZE;i++)
    {
    crc.value_int=Crc16Update(crc.value_int,packetContainer[i]);
//    crc.value_int=_crc_xmodem_update(crc.value_int,packetContainer[i]);
    }
  this->applyCalculatedCRC16();
#endif
  */
  }
void Class_StalkerLayer0::prepareMultyBytePacket(uint8_t TransferID, uint8_t MID)
  {
  this->SetTXPacketSubType(TransferID);
  this->SetTXPacketVar(MID);
  this->SetTXPacketType(PACKET_TYPE_250BYTES);
  this->prepareTXPacket();
  }
void Class_StalkerLayer0::prepareEnvironmentPacket(void)
  {
  this->SetTXPacketType(PACKET_TYPE_ENVIRONMENT);
  this->prepareTXPacket();
/*
#ifdef RFM69_HW_CRC
  return;
#else //software crc
  this->crc.value_int=CRC16_INIT_VALUE;
  for (uint8_t i=0;i<this->STRUCTURE_DATA_SIZE;i++)
    {
    crc.value_int=Crc16Update(crc.value_int,packetContainerTX[i]);
//    crc.value_int=_crc_xmodem_update(crc.value_int,packetContainer[i]);
    }
  this->applyCalculatedCRC16();
#endif
*/
  }
void Class_StalkerLayer0::prepareTXPacket(void)
  {
#ifdef RFM69_HW_CRC
  return;
#else //software crc
  this->crc.value_int=CRC16_INIT_VALUE;
  for (uint8_t i=0;i<this->STRUCTURE_DATA_SIZE;i++)
    {
    crc.value_int=Crc16Update(crc.value_int,packetContainerTX[i]);
//    crc.value_int=_crc_xmodem_update(crc.value_int,packetContainer[i]);
    }
  this->applyCalculatedCRC16();
#endif
  }
void Class_StalkerLayer0::applyCalculatedCRC16(void)
  {
#ifdef RFM69_HW_CRC
  return;
#else
  this->packetContainerTX[STRUCTURE_0X04_CRC16_H]  = this->crc.byte_field.h;
  this->packetContainerTX[STRUCTURE_0X05_CRC16_L]  = this->crc.byte_field.l;
#endif
  }

void Class_StalkerLayer0::receiveBegin (void)
  {
  this->isRSSIReceived  = false;
  HAL.EnvironmentRarioModule.receiveBegin();
  }
void Class_StalkerLayer0::packetChanged (void)
  {
  this->isDataInsideRM  = false;
  }
void Class_StalkerLayer0::sendPacket(void)
  {
  if (!this->isDataInsideRM)
    {
    HAL.EnvironmentRarioModule.sendBufferToRM();
    this->isDataInsideRM  = true;
    }
  
  HAL.EnvironmentRarioModule.startTX();
  
  //HAL.AnoRadRarioModule.RFM22B_txMode();
  }
bool Class_StalkerLayer0::checkEnvironmentPacketAcception (void)
  {
  LogClass::Log(LogClass::MESSAGES::MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__ENTER);
//  if (this->isGoodPacketReceivedValue == false && HAL.EnvironmentRarioModule.isPacketReceived())
  if (HAL.EnvironmentRarioModule.isPacketReceived())
    {
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__SOME_PACKET_RECEIVED);
    //TODO("может выйти так, что пакет будет не обработан, но будет висеть внутри радиомодуля, пока isGoodPacketReceivedValue == true");
    //    radio.receivePacket();
    //    radio.receiveBegin();
    this->getEnvPacketAndRSSI();
    this->receiveBegin();
//    #ifdef RM69_HW_
//don't need beacuse checks will return true
//      {
//      this->isGoodPacketReceivedValue  = true;
//      return true;
//      }
//    #endif // RFM69_HW_CRC
    #ifdef DEBUG_ENV_PACKETS_L0
      #ifdef RFM69_HW_CRC
        sprintf (USARTBuffer,"packet received %02u  %03d %03d %03d %03d --- --- \r\n", TimeRTC.second, this->packetContainer[0], this->packetContainer[1], this->packetContainer[2], this->packetContainer[3]);
      #else
        sprintf (USARTBuffer,"packet received %02u  %03d %03d %03d %03d %03d %03d \r\n", TimeRTC.second, this->packetContainer[0], this->packetContainer[1], this->packetContainer[2], this->packetContainer[3], this->packetContainer[4], this->packetContainer[5]);
      #endif
      sendString(USARTBuffer);
    #endif // DEBUG_ENV_PACKETS
    if (this->checkReceivedPacketCRC())
      {
      LogClass::Log(LogClass::MESSAGES::MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCOK);
      return true;
      }
#ifdef RFM69_HW_CRC
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCFAIL, this->packetContainerRX[0], this->packetContainerRX[1], this->packetContainerRX[2], this->packetContainerRX[3]);
#else //software crc
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCFAIL, this->packetContainerRX[0], this->packetContainerRX[1], this->packetContainerRX[2], this->packetContainerRX[3], this->packetContainerRX[4], this->packetContainerRX[5]);
#endif //RFM69_HW_CRC
    }
//  sendString ((char*)"packet not received\r\n");
  return false;
  }
bool Class_StalkerLayer0::checkReceivedPacketCRC(void)
  {
#ifdef RFM69_HW_CRC
  return true;
#else //software crc
  UNION_UINT16_LITTLE_ENDIAN crc_local;
  //crc.value_int  = 0xFFFF;CRC16_INIT_VALUE
  crc_local.value_int  = CRC16_INIT_VALUE;
  for (uint8_t i=0;i<STRUCTURE_DATA_SIZE;i++)
    {
    crc_local.value_int  = Crc16Update(crc_local.value_int, this->packetContainerRX[i]);
    }
  if (crc_local.byte_field.h == this->packetContainerRX[STRUCTURE_0X04_CRC16_H] && crc_local.byte_field.l == this->packetContainerRX[STRUCTURE_0X05_CRC16_L])
    {
    return true;
    }
  return false;
#endif
  }
bool Class_StalkerLayer0::isNewEnvPacketReceived(void)
  {
  //return RFM69_DIO0_HIGH;
  return HAL.EnvironmentRarioModule.isPacketReceived();
  }
void Class_StalkerLayer0::getEnvPacketAndRSSI(void)
  {
  HAL.EnvironmentRarioModule.getPacket();
//  HAL.EnvironmentRarioModule.globalRSSI      = HAL.EnvironmentRarioModule.fetchRSSIRaw();
  this->getRSSI();
  //      this->i++;
  }
Class_StalkerLayer0::PACKET_TYPES Class_StalkerLayer0::getReceivedPacketType(void)
  {
  return static_cast<Class_StalkerLayer0::PACKET_TYPES>(this->packetContainerRX[STRUCTURE_0X00_HEAD_H] & PACKET_TYPEMASK);
  }

void Class_StalkerLayer0::getRSSI(void)
  {
  if (this->isRSSIReceived)
    {
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL0_GET_RSSI__ERROR_RSSI_ALREADY_RECEIVED);
    return;
    }
  this->RSSIRaw  = HAL.EnvironmentRarioModule.getRSSIRaw();
  //      this->RSSIRaw  = 85;
  TODO("move this calculations to drivers!");
  if (HAL.EnvironmentRarioModule.CFG_RSSI_INVERTED)
    {
    this->RSSI    = ~this->RSSIRaw;
    }
  else
    {
    this->RSSI    = this->RSSIRaw;
    }
  if (this->RSSI > 64)//removing [0..64]
    {
    this->RSSI-=64;
    }
  else
    {
    this->RSSI=0;
    }

  if (this->RSSI >127)
    {
    this->RSSI  = 127;
    }
  this->SignalPower  = this->SignalPower + this->RSSI;//filter [(a1+a2)/2]

  if (this->SignalPower > 0)
    {
    this->SignalPower = (this->SignalPower)/2;
    }
  this->isRSSIReceived  = true;
  }
void Class_StalkerLayer0::packetProcessed(void)
  {
//  this->isGoodPacketReceivedValue  = false;
  //HAL.EnvironmentRarioModule.PacketProcessed();
  }
uint8_t* Class_StalkerLayer0::GetReceivedPacketData(void)
  {
  return &(this->packetContainerRX[STRUCTURE_0X02_DATA_H]);
  }
uint8_t* Class_StalkerLayer0::GetReceivedPacket(void)
  {
  return &(this->packetContainerRX[STRUCTURE_0X00_HEAD_H]);
  }
uint8_t Class_StalkerLayer0::GetRXPacketVar(void)
  {
  return this->packetContainerRX[STRUCTURE_0X01_VAR];
  }
void Class_StalkerLayer0::SetTXPacketVar(uint8_t packetVar)
  {
  this->packetContainerTX[STRUCTURE_0X01_VAR]  = packetVar;
  }
void Class_StalkerLayer0::ClearFifo(void)
  {
  HAL.EnvironmentRarioModule.ClearFifo();
  this->isDataInsideRM  = false;
  }
#endif