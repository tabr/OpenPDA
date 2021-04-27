/*
  *  hackableComputer.h
  *
  *  Created:  2015-08-10  19:59:27
  *    Author:  tabr
  */  


#ifndef  HACKABLECOMPUTER_H_
#define  HACKABLECOMPUTER_H_

#include  <avr/io.h>

#include  "boards/compiler_defines.h"
#include  <util/delay.h>

#include  "PlayerClass.hpp"
#include  "crc16.h"
#include  "unionsFixed.h"
#include  "protocols/protocolComputerHack.h"
#include  "ArtefactPorts.hpp"

//extern  ArtefactPortsClass  ArtefactPorts;

class  HackableComputerClass
  { //-V802
  public:
    void  updateStatus();
//    void  tryToHack(uint8_t  skillLevel);
    void  tryToHack(PlayerClass*  pPlayer);
    //uint8_t*  readItem(ArtefactsPortsHardwareClass*  hardware);
    void  setConnected(ArtefactsPortsHardwareClass*  hardware);
    void  setDisconnected(void);
    bool  isConnected(void);
    bool  isDisconnected(void);
    bool  haveAccess(void);
    uint8_t  getLevel(void);
    void  toggleSwitch(void);
    bool  getSwitch(void);

  protected:
  private:
    void  sendRequest(uint8_t  isHead,  HACK_COMMANDS  command,  uint8_t  dataH,  uint8_t  dataL);

    //this order is smaller size
    uint8_t  data[PROTO_HACK_SIZE];
    ArtefactsPortsHardwareClass*  m_hardware=NULL;
    uint8_t  status=0;
    uint8_t  level=0;
  };



#endif  /*  HACKABLECOMPUTER_H_  */
