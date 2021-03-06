// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


void LogClass::Log(MESSAGES msg, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6)
  {
  #ifdef DEBUG_USAR
  USARTBuffer[0]=0;
  if ( msg == MESSAGE_NONE)
    {
    //none & disabled
    }
  else if ( msg == MESSAGE_SL2_ENVIRONMENT_PROCESS__ENTER)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__ENTER,p1);
  else if (msg == MESSAGE_SL2_ENVIRONMENT_PROCESS__PROCESSING_BUFFER)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__PROCESSING_BUFFER,p1, p2, p3, p4);
  else if (msg == MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__VALID_PACKET_RECEIVED)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__VALID_PACKET_RECEIVED, p1);
  else if (msg == MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__ENTER)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__ENTER);
  else if (msg == MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__ENTER)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__ENTER);
  else if (msg == MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_REVIVE)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_REVIVE);
  else if (msg == MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__SOME_PACKET_RECEIVED)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__SOME_PACKET_RECEIVED);
  else if (msg == MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCOK)
    sprintf (USARTBuffer,STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCOK);
  else if (msg == MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCFAIL)
    sprintf (USARTBuffer,STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCFAIL);
  else if (msg == MESSAGE_SL0_GET_RSSI__ERROR_RSSI_ALREADY_RECEIVED)
    sprintf (USARTBuffer,STR_MESSAGE_SL0_GET_RSSI__ERROR_RSSI_ALREADY_RECEIVED);
  else if (msg == MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__ENTER)
    sprintf (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__ENTER);
  else if (msg == MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__RECEIVED_PACKET)
  sprintf_P (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__RECEIVED_PACKET, p1, p2);
  else if (msg == MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__FOUND_DUPLICATE_PACKET)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__FOUND_DUPLICATE_PACKET);
  else if (msg == MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_RADIATION_ANOMALY)
    sprintf_P (USARTBuffer,STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_RADIATION_ANOMALY);
  else if (msg == MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ENTER)
    sprintf_P (USARTBuffer,STR_MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ENTER, p1);
  else if (msg == MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__RAD_MUL)
    sprintf_P (USARTBuffer,STR_MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__RAD_MUL, (int8_t)p1);
  else if (msg == MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ITMP)
    sprintf_P (USARTBuffer,STR_MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ITMP, p1);

  

  if (USARTBuffer[0] != 0)
    {
    sendString(USARTBuffer);
    }
  #endif
  };