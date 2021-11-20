#pragma once
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__RECEIVED_PACKET[]                   = "L2: received packet: RID:[%03u] power:\r\n";
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__PROCESSING_BUFFER[]                     = "L2[EnvironmentProcess] bufPointer[%03u] rariomarkID[%03u] SignalPower[%03u] type[%03u]\r\n";
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__ENTER[]                                 = "L2[EnvironmentProcess] enter. bufPointer[%03u]\r\n";
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_REVIVE[]                 = "L2[EnvironmentProcess] Receive RM Revive\r\n";
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__ENTER[]                             = "L2[EnvironmentLookAround] Enter\r\n";
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__FOUND_DUPLICATE_PACKET[]            = "L2[EnvironmentLookAround] found duplicate packet\r\n";
const PROGMEM char STR_MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_RADIATION_ANOMALY[]      = "L2[EnvironmentProcess] Packet is RADANO\r\n";
const PROGMEM char STR_MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__VALID_PACKET_RECEIVED[]               = "L1[isEnvironmentActive]: ValidPacked Received, type: %03u\r\n";
const PROGMEM char STR_MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__ENTER[]                               = "L1[isEnvironmentActive]: enter isEnvironmentActive\r\n";
const PROGMEM char STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__ENTER[]                  = "L0[checkEnvironmentPacketAcception]: enter checkEnvironmentPacketAcception()\r\n";
const PROGMEM char STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__SOME_PACKET_RECEIVED[]   = "L0[checkEnvironmentPacketAcception]: Some packed received\r\n";
const PROGMEM char STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCOK[]                  = "L0[checkEnvironmentPacketAcception]: CRC ok\r\n";
const PROGMEM char STR_MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCFAIL[]                = "L0[checkEnvironmentPacketAcception]: CRC Fail\r\n";
const PROGMEM char STR_MESSAGE_SL0_GET_RSSI__ERROR_RSSI_ALREADY_RECEIVED[]                      = "L0[checkEnvironmentPacketAcception]: ERROR! RSSI already received!\r\n";
const PROGMEM char STR_MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ENTER[]                        = "[RadiomarkRadiationAnomayClass::ProcessSignal] Entering... signalPower: %03d\r\n";
const PROGMEM char STR_MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__RAD_MUL[]                      = "[RadiomarkRadiationAnomayClass::ProcessSignal] RadiationMultiplier: [%03d]\r\n";
const PROGMEM char STR_MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ITMP[]                         = "[RadiomarkRadiationAnomayClass::ProcessSignal] itmp: [%03d]\r\n";
//const PROGMEM char STR_

class LogClass
  {
  public:
  enum MESSAGES
    {
    MESSAGE_NONE                                                            = 0 , //0,
    MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__ENTER                   = 0 , //1,
    MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__SOME_PACKET_RECEIVED    = 2 , //2,
    MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCOK                   = 3 , //3,
    MESSAGE_SL0_CHECK_ENVIRONMENT_PACKET_ACCEPTION__CRCFAIL                 = 4 , //4,
    MESSAGE_SL0_GET_RSSI__ERROR_RSSI_ALREADY_RECEIVED                       = 5 , //5,
    MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__ENTER                                = 0 , //6,
    MESSAGE_SL1_IS_ENVIRONMENT_ACTIVE__VALID_PACKET_RECEIVED                = 7 , //7,
    MESSAGE_SL2_ENVIRONMENT_PROCESS__ENTER                                  = 0 , //8,
    MESSAGE_SL2_ENVIRONMENT_PROCESS__PROCESSING_BUFFER                      = 9 , //9,
    MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_REVIVE                  = 10, //10,
    MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__ENTER                              = 0 , //12,
    MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__RECEIVED_PACKET                    = 13, //13,
    MESSAGE_SL2_ENVIRONMENT_LOOK_AROUND__FOUND_DUPLICATE_PACKET             = 14, //14,
    MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_RADIATION_ANOMALY       = 15, //15,
    MESSAGE_SL2_ENVIRONMENT_PROCESS__RADIOMARK_TYPE_RADIATION_NEUTRON_FLUX  = 19, //19,
    MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ENTER                         = 16, //16,
    MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__RAD_MUL                       = 17, //17,
    MESSAGE_RADIOMARK_RADANO__PROCESS_SIGNAL__ITMP                          = 18, //18,
    };
  static void Log(MESSAGES msg, uint8_t p1=0, uint8_t p2=0, uint8_t p3=0, uint8_t p4=0, uint8_t p5=0, uint8_t p6=0);
  protected:
  private:
  };