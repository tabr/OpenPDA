#ifndef ARTEFACT_PORT_CLASS_H
#define ARTEFACT_PORT_CLASS_H


#include <avr/io.h>

#include "boards/compiler_defines.h"
#include <util/delay.h>
#include <string.h>

#include "ArtefactsPortsHardware.hpp"
#include "ArtefactClass.hpp"
#include "Runnable.hpp"
#include "UsableItemClass.hpp"
#include "PlayerSuitClass.hpp"
#include "PlayerClass.hpp"
#include "ConfigClass.hpp"
#include "M25P05_instructions.h"
#include "stalker/HAL.hpp"


class ArtefactHardwareInterface
  {
  public:
    virtual void ReadData(uint8_t* data, uint8_t dataLength) = 0;
    virtual void ReadData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint8_t dataLength) = 0;
    virtual void ReadData(uint8_t* data, uint16_t dataLength) = 0;
    virtual void ReadData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint16_t dataLength) = 0;
    virtual void EraseDevice(void) = 0;
    virtual void WriteData(uint8_t* data, uint8_t dataLength) = 0;
    virtual void WriteData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint8_t dataLength) = 0;
    virtual void WriteData(uint8_t* data, uint16_t dataLength) = 0;
    virtual void WriteData(uint8_t AddressH, uint8_t AddressM, uint8_t AddressL, uint8_t* data, uint16_t dataLength) = 0;
  protected:
  private:
  };

class ArtefactPortsClass : public ITimerListener
  {
  public:

    const static uint8_t LED_FLASH_COUNTER            = 6;//умноженное в 2 раза кол-во миганий

    const static uint8_t ADDRESS_HEAD_H               = 0;
    const static uint8_t ADDRESS_HEAD_M               = 0;
    const static uint8_t ADDRESS_HEAD_L               = 0;

    const static uint8_t ADDRESS_PARAMETERS_H         = 0;//не исползуется
    const static uint8_t ADDRESS_PARAMETERS_M         = 0;
    const static uint8_t ADDRESS_PARAMETERS_L         = 4;
/*
    const static uint8_t ADDRESS_ITEM_TYPE_H          = 0;
    const static uint8_t ADDRESS_ITEM_TYPE_M          = 0;
    const static uint8_t ADDRESS_ITEM_TYPE_L          = 0;

    const static uint8_t ADDRESS_ITEM_SUBTYPE_H       = 0;
    const static uint8_t ADDRESS_ITEM_SUBTYPE_M       = 0;
    const static uint8_t ADDRESS_ITEM_SUBTYPE_L       = 1;

    const static uint8_t ADDRESS_ITEM_STATUS_H        = 0;
    const static uint8_t ADDRESS_ITEM_STATUS_M        = 0;
    const static uint8_t ADDRESS_ITEM_STATUS_L        = 2;
*/
    const static uint8_t ITEM_TYPE_EMPTY              = 0b11111111;
    const static uint8_t ITEM_TYPE_CORRUPTED          = 0;
    const static uint8_t ITEM_TYPE_ARTEFACT           = 1;
    const static uint8_t ITEM_TYPE_MEDICAMENTS        = 2;
    const static uint8_t ITEM_TYPE_SUIT               = 3;
    //const static uint8_t  ITEM_TYPE_COMPUTER

//    const static uint8_t  ITEM_SUBTYPE_NONE          = 0;
    
    const static uint8_t  FLASHDATA_ARTEFACT_TYPE     = 0;
//    const static uint8_t  FLASHDATA_ITEM_SUBTYPE    = 1;
    const static uint8_t  FLASHDATA_ARTEFACT_ID       = 2;
//    const static uint8_t  FLASHDATA_ITEM_STATUS     = 3;
/*
      const static uint8_t  FLASHDATA_PARAMETER_0     = 0;
      const static uint8_t  FLASHDATA_PARAMETER_1     = 1;
      const static uint8_t  FLASHDATA_PARAMETER_2     = 2;
      const static uint8_t  FLASHDATA_PARAMETER_3     = 3;
*/
/*
type 0 - ???

FLASHDATA_ITEM_TYPE == 1 артефакт
FLASHDATA_ITEM_ID      ID артефакта

*/
    const static uint8_t DEVICE_STATUS_OK             = 255;
    const static uint8_t DEVICE_STATUS_EMPTY          = 0;
    const static uint8_t ARTEFACT_FLASH_DATA_LENGTH   = 8;
    enum A_PORTS
      {
      A_PORT_0,
      A_PORT_1,
      A_PORT_2,
      A_PORT_3,
      A_PORT_4,
      A_PORTS_NUM
      };
    
    uint8_t m_ledFlashCounters[ArtefactsPortsHardwareClass::MAX_SLOTS];
    uint8_t m_lastArtefact[8];

    ArtefactPortsClass(void);
    
    void TimerUpdateEvent (uint8_t msPassed);

    void ledFlashProcess(void);                            //должна вызываться извне (в прерывании, например) для отработки мигания светодиода
//    void deactivateFlashChip(uint8_t pin);
//    void activateFlashChip(uint8_t pin);
    void scanForConnected(void);                          //сканирует подключенные арты и применяет их
//    void scanForConnectedOld(void);                          //сканирует подключенные арты и применяет их
    void scanForConnectedIfNeed(void);                        //TODO

//    void M25P05_wholeItemWrite(uint8_t pin, uint8_t *item);
//    uint8_t M25P05_Read_DataByteNoActivate(uint8_t H,uint8_t M, uint8_t L);
//    uint8_t M25P05_Read_Status_Register(uint8_t pin);
//    bool M25P05_isWriteInProgress (uint8_t pin);
//    void M25P05_BulkErase(uint8_t pin);
    void readActivatedItem(void);                          //пин SS должен быть уже выставлен
    void IOInit(void);
    void HardwareInitialization(void);
    ArtefactsPortsHardwareClass* GetHardware(void);
    ArtefactClass* GetConnectedArtefact(uint8_t pos);
    void newLEDOff(A_PORTS a_port);
    void newLEDOn(A_PORTS a_port);
    void newLEDToggle(A_PORTS a_port);
    void SetPortOut(A_PORTS a_port);
    void SetPortIn(A_PORTS a_port);
    void SetPortOut(uint8_t portNum);
    void SetPortIn(uint8_t portNum);
    bool newIsSomethingConnectedTo(uint8_t portNum);
  protected:
    //void SPI_init(void);
    //uint8_t SPI_send(uint8_t data);

    ArtefactsPortsHardwareClass m_Hardware;
    ArtefactClass m_artefactsConnected[ArtefactsPortsHardwareClass::MAX_SLOTS];
    ArtefactHardwareInterface* ArtefactHardware[ArtefactsPortsHardwareClass::MAX_SLOTS];
  private:
  };
#endif