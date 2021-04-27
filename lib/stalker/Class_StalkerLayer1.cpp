// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

void Class_StalkerLayer1::programmStart(void)
  {
  this->L0.receiveBegin();
  }
void Class_StalkerLayer1::HardwareInitialization(void)
  {
  this->L0.HardwareInitialization();
  }
bool Class_StalkerLayer1::isEnvironmentActive(void)
  {
  LogClass::Log(LogClass::MESSAGES::MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__ENTER);
  if (this->L0.checkEnvironmentPacketAcception())
    {
    LogClass::Log(LogClass::MESSAGES::MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__VALID_PACKET_RECEIVED, this->L0.getReceivedPacketType());
    
    switch (this->L0.getReceivedPacketType())
      {
      case Class_StalkerLayer0::PACKET_TYPE_ENVIRONMENT:
        {
        return true;
        }
      break;

      case Class_StalkerLayer0::PACKET_TYPE_TIMEUPDATE:
        {
        #ifdef DEBUG_USART_CODES
          USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_TIME_PACKET_RECEIVED);
        #endif // DEBUG_USART_CODES
        TimeUpdate.RequestUpdate(this->L0.packetContainerRX[PACKET_RADIOMARK_TYPE_PARAM0], this->L0.packetContainerRX[PACKET_RADIOMARK_TYPE_PARAM1], this->L0.packetContainerRX[PACKET_RADIOMARK_TYPE_PARAM2]);
        this->L0.packetProcessed();
        return false;
        }
      break;
      
      case Class_StalkerLayer0::PACKET_TYPE_ADM_ACTION:
        {
        #ifdef DEBUG_USART_CODES
          USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_L0_RCV_ADM_ACTION);
        #endif // DEBUG_USART_CODES
        uint8_t action    = this->L0.packetContainerRX[PACKET_RADIOMARK_TYPE_PARAM0];
        uint8_t addressedTo  = this->L0.packetContainerRX[PACKET_RADIOMARK_TYPE_PARAM1];
//        uint8_t parameter2  = this->L0.packetContainer[PACKET_RADIOMARK_TYPE_PARAM2];
        switch (action)
          {
          case RADIOMARK_ADM_ACTIONS::RADIOMARK_ADM_ACTION_REVIVE:
            {
            if (DeviceConfig.IsAddressedToMe(addressedTo))
              {
              Player.Revive();
              }
            }
          break;
          
          case RADIOMARK_ADM_ACTIONS::RADIOMARK_ADM_ACTION_KILL:
            {
            if (DeviceConfig.IsAddressedToMe(addressedTo))
              {
              #ifdef DEBUG_USART_CODES
                USART_SendCode(USART_DEBUG_CODES::USART_DEBUG_CODE_KILLING_PLAYER_BY_ADM);
              #endif // DEBUG_USART_CODES
              Player.Kill(TemporaryClass::DAMAGE_SOURCE_MASTER);
              }
            }
          break;
          
          case RADIOMARK_ADM_ACTIONS::RADIOMARK_ADM_ACTION_HALF_DEATH_TIME:
            {
            if (DeviceConfig.IsAddressedToMe(addressedTo))
              {
              if (Player.IsDead())
                {
                PlayerDeathTimer_t halfTime  = (GameCFG.GetPlayerDeathTime() / 2);
                if (halfTime > 2)
                  {
                  halfTime--;
                  }
                if (Player.GetDeathTimeRemain() > halfTime)
                  {
                  Player.SetDeathTimeRemain(halfTime);
                  }
                }

              }
            }
          break;

          case RADIOMARK_ADM_ACTIONS::RADIOMARK_ADM_ACTION_RESET          :
            {
            if (DeviceConfig.IsAddressedToMe(addressedTo))
              {
              while(1);//wait 4 watchdog
              }
            }
          break;

          }
        return false;
        }
      break;
      
      case Class_StalkerLayer0::PACKET_TYPE_250BYTES:
        {
        uint8_t TransferID    = this->L0.GetRXPacketSubType();//[0..248]
        uint8_t MultyPacketID  = this->L0.GetRXPacketVar();
        if (MultyPacketID > MAX_MULTI_PACKET_ID)
          {
          Errors.SetError(ErrorClass::CODES::ERROR_MULTIBYTE_ID_BIGGER_THAN_MAX);
          return false;
          break;
          }

        #ifdef DEBUG_USART_MULTY_PACKETS
          sprintf (USARTBuffer,"[multy] received! TID %03u MID %03u [%03d %03d %03d %03d %03d %03d %03d %03d %03d %03d %03d %03d %03d %03d %03d %03d]\r\n", TransferID, MultyPacketID, this->rcv_ids[0], this->rcv_ids[1], this->rcv_ids[2], this->rcv_ids[3], this->rcv_ids[4], this->rcv_ids[5], this->rcv_ids[6], this->rcv_ids[7], this->rcv_ids[8], this->rcv_ids[9], this->rcv_ids[10], this->rcv_ids[11], this->rcv_ids[12], this->rcv_ids[13], this->rcv_ids[14], this->rcv_ids[15]);
          sendString(USARTBuffer);
          uint8_t* packet  = this->L0.GetReceivedPacket();
          sprintf (USARTBuffer,"[multy] Data received: %03d %03d %03d %03d %03d %03d\r\n", packet[0], packet[1], packet[2], packet[3], packet[4], packet[5]);
          sendString(USARTBuffer);
        #endif // DEBUG_USART_MULTY_PACKETS

        if (this->multiByteCache[MULTIBYTE_STRUCTURE_TRANSFERID] != TransferID)
          {
          #ifdef DEBUG_USART_MULTY_PACKETS
            sprintf (USARTBuffer,"[multy] TransferID differs have[%03u] arrived[%03u]\r\n", this->multiByteCache[MULTIBYTE_STRUCTURE_TRANSFERID], TransferID);
            sendString(USARTBuffer);
          #endif // DEBUG_USART_MULTY_PACKETS
          this->CleanCache();
          this->multiByteCache[MULTIBYTE_STRUCTURE_TRANSFERID]  = TransferID;
          }
        //uint8_t* packet  = this->L0.GetReceivedPacket();
        //this->cache[TransferID]
        memcpy(&this->multiByteCache[MultyPacketID*2], this->L0.GetReceivedPacketData(), this->BYTES_IN_PACKET);
        sbi((this->rcv_ids[MultyPacketID/8]), (MultyPacketID%8));
        if (this->CheckMultibytePacketReceived())
          {
          #ifdef DEBUG_USART_MULTY_PACKETS
            sprintf (USARTBuffer,"[multy] full packet received.\r\n");
            sendString(USARTBuffer);
          #endif // DEBUG_USART_MULTY_PACKETS
          //check CRC
          return true;
          }
        return false;
        }
      break;
      
      default:
      case Class_StalkerLayer0::PACKET_TYPE_NONE:
        {
        this->L0.packetProcessed();
        return false;
        }
      break;
      }
    }
  else
    {
    #ifdef DEBUG_ENV_PACKETS
      sprintf (USARTBuffer,"L1: there is no packet\r\n");
      sendString(USARTBuffer);
    #endif // DEBUG_ENV_PACKETS
    return false;
    }
  return false;
  }
bool Class_StalkerLayer1::CheckMultibytePacketReceived(void)
  {
  for (uint8_t i=0; i < (this->RCV_IDS_BUFFER_SIZE);i++)
    {
    if (this->rcv_ids[i] != 255)
      {
      return false;
      }
    }
  return true;
  }
void Class_StalkerLayer1::CleanCache(void)
  {
  memset(this->multiByteCache, 0, this->CACHE_SIZE);
  memset(this->rcv_ids, 0, (this->RCV_IDS_BUFFER_SIZE));
  }
uint8_t Class_StalkerLayer1::getReceivedEnvPacketID(void)
  {
  return this->L0.packetContainerRX[Class_StalkerLayer0::STRUCTURE_0X03_DATA_L];
  }
uint8_t Class_StalkerLayer1::getReceivedEnvPacketSignalPower(void)
  {
  return this->L0.SignalPower;
  }
Class_StalkerLayer1::Class_StalkerLayer1(void)
  {
  this->CleanCache();
  }