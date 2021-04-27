#ifndef USABLE_ITEM_CLASS_H
#define USABLE_ITEM_CLASS_H

#include "ConnectedItemClass.hpp"
#include "stalker/TimerClass.hpp"
#include "typedefs.h"

class UsableItemClass : public ITimerListener
  {
  public:
    /*struct EepromItem_t 
      {
      uint8_t type;
      uint8_t subtype;
      uint8_t ID;
      uint8_t status;
      uint8_t ex0;
      uint8_t ex1;
      uint8_t ex2;
      uint8_t ex3;
      };*/
/*
    const static uint8_t FLASHDATA_ITEM_TYPE            = 0;
    const static uint8_t FLASHDATA_ITEM_SUBTYPE            = 1;
    const static uint8_t FLASHDATA_ITEM_ID              = 2;
    const static uint8_t FLASHDATA_ITEM_STATUS            = 3;//нужно ли...

    const static uint8_t FLASHDATA_ITEM_EX0              = 4;
    const static uint8_t FLASHDATA_ITEM_EX1              = 5;
    const static uint8_t FLASHDATA_ITEM_EX2              = 6;
    const static uint8_t FLASHDATA_ITEM_EX3              = 7;
    const static uint8_t FLASHDATA_ITEM_PARAMETERS_NUM        = 8;
*/
    const static uint8_t PAGE_SIZE                  = 8;
    const static uint8_t ITEM_PAGE_ADDRESS              = 1;//адрес страницы. [0-7] - reserved, например, под версию...
//    const static uint8_t ADDRESS_HEAD                = 8;//адрес [0] - reserved, например, под версию...
//    const static uint8_t ADDRESS_ADDITIONAL_START          = ADDRESS_HEAD + FLASHDATA_ITEM_PARAMETERS_NUM;

    enum ITEM_TYPE
      {
      ITEM_TYPE_EMPTY,//это еепром, поэтому можно и так=)
      ITEM_TYPE_MEDICAMENTS,
      ITEM_TYPE_SUIT,
      ITEM_TYPE_INFORMATION,
      ITEM_TYPE_REPAIR_KITS,//repair kit, ...
      ITEM_TYPE_ELSE,
      ITEM_TYPE_COMPUTER,
      ITEM_TYPE_RESOURCE,
      ITEM_TYPE_QUEST,
      ITEM_TYPES_NUM
      };

    const static uint8_t ITEM_SUBTYPE_NONE              = 0;
    
//    const static uint8_t ITEM_INFORMATION_PAGE_SIZE          = 14;
//    const static uint8_t ITEM_INFORMATION_HEAD_SIZE          = 8;
    const static uint8_t ITEM_INFORMATION_HEAD_PAGE          = 2;
    const static uint8_t ITEM_INFORMATION_HEAD_SIZE          = 2;//в страницах
    const static uint8_t ITEM_INFORMATION_DATA_PAGE          = 4;
    const static uint8_t ITEM_INFORMATION_HEAD_ADDRESS        = ITEM_INFORMATION_HEAD_PAGE * PAGE_SIZE;
    const static uint8_t ITEM_INFORMATION_DATA_ADDRESS        = ITEM_INFORMATION_DATA_PAGE * PAGE_SIZE;
    const static uint8_t ITEM_INFORMATION_MAXIMUM_DATA_LENGTH_PAGES  = 224/PAGE_SIZE;//28 страниц
//    const static uint8_t ITEM_INFORMATION_ADDRESS_DATA        = ITEM_INFORMATION_ADDRESS_HEAD + ITEM_INFORMATION_HEAD_SIZE;
    
    const static uint8_t DEVICE_STATUS_OK              = 1;
    const static uint8_t DEVICE_STATUS_EMPTY            = 0;
    
/*
FLASHDATA_ITEM_TYPE == 1  предмет из инвентаря (съедобное) - используется (к-во бит FLASHDATA_PARAMETER_0) раз
FLASHDATA_ITEM_SUBTYPE    -
FLASHDATA_ITEM_ID      ID предмета
FLASHDATA_ITEM_STATUS:    255-ok
FLASHDATA_PARAMETER_0    к-во зарядов (до 8ми - по 1 на бит)
FLASHDATA_PARAMETER_1    к-во хп, восстанавливаемого за заряд
FLASHDATA_PARAMETER_2    задержка до следующего заряда

FLASHDATA_ITEM_TYPE == 2  Костюм
FLASHDATA_ITEM_SUBTYPE    -
FLASHDATA_ITEM_ID      ID костюма
FLASHDATA_ITEM_STATUS:    255-ok
FLASHDATA_PARAMETER_0    прочность костюма
FLASHDATA_PARAMETER_1    кол-во контейнеров

FLASHDATA_ITEM_TYPE == 3  Информация
FLASHDATA_ITEM_SUBTYPE    -ТУДУ
FLASHDATA_ITEM_ID      -
FLASHDATA_ITEM_STATUS:    255-ok
FLASHDATA_PARAMETER_0    кол-во страниц (без учё)
FLASHDATA_PARAMETER_1    -

*/
    enum CONNECTION_STATE
      {
      CONNECTION_STATE_CONNECTED,
      CONNECTION_STATE_DISCONNECTED
      };
//    const static uint8_t CONNECTED_ITEM_SIZE  = FLASHDATA_ITEM_PARAMETERS_NUM;
    const static uint8_t ITEMLED_TIMER_SUCCESS  = 6;
    const static uint8_t ITEMLED_TIMER_ERROR  = 1;
  
    //uint8_t connectedItemArray[CONNECTED_ITEM_SIZE];
    //ConnectedItemClass2* connectedItem2;
  
    void TimerUpdateEvent (uint8_t msPassed);
  
    void ledOnTick();
    void turnOffItemLed(void);
    void turnOnItemLed(uint8_t delay);
    void itemLedStatusSuccess(void);
    void itemLedStatusError(void);
    
    void scanForConnected(void);
    void scanForConnectedIfNeed(void);
    void itemJustConnected(void);            //типа Event
    void itemJustDisconnected(void);          //типа Event
    void itemJustConnectedOrDisconnected(CONNECTION_STATE state);      //типа Event
    void SetConnectedItem(uint8_t type, uint8_t subtype, uint8_t id, uint8_t status, uint8_t ex0, uint8_t ex1, uint8_t ex2, uint8_t ex3);
    void SetConnectedItem(uint8_t type, uint8_t subtype, uint8_t id, uint8_t status, uint16_t ex01, uint8_t ex2, uint8_t ex3);
    bool WriteConnectedItem(void);            //записать currentItem в подключенный слот
    bool ReadConnectedItem(void);            //прочитать подключенный слот в currentItem
    bool use(void);
    bool ProcessMedicaments(void);
    void CleanConnectedItem(void);
    //void twi_stop(void);
    //bool twi_write_page(uint8_t page, uint8_t *writeData);
    //void twi_write_byte(uint8_t eepromAddress, uint8_t writeData);
    //bool at24c02_readConnectedItem1();
//    bool at24c02_read_pages(uint8_t page, uint8_t pagesToRead, uint8_t *readData);
//    bool at24c02_read_bytes(uint8_t addressStart, uint8_t bytesToRead, uint8_t *readData);
//    bool at24c02_readCustomlPage(uint8_t address, uint8_t pageSize, uint8_t pageNum, uint8_t *data);
//    bool at24c02_readCustomlPage(uint8_t address, uint8_t pageSize, uint8_t pageNum, char *data);
    ItemType_t getConnectedItemType(void);
    ItemTypeName_t getItemTypeName(ItemType_t type);
    STR_POS getConnectedItemTypeNamePOS(ItemType_t type);
    STR_POS getConnectedItemTypeNamePOS(void);
    ItemTypeName_t getConnectedItemTypeName(void);
    ItemName_t getItemName(ItemType_t type, ItemID_t id);    //ВНИМАНИЕ!!! Нельзя получить HEAD неподключенной флешки информации!!!
    ItemName_t getConnectedItemName(void);
    ItemID_t getConnectedItemID(void);
    UsableItemClass (void);
//    TWI* GetHardware(void);
    ConnectedItemClass* GetConnectedItem(void);
//    ConnectedItemArray_t* GetConnectedItemArray(void);


    bool isItemConnected(void);              //hardware read and set as "itemConnected" class
    bool isItemIsNotConnected(void);

  protected:
  private:
    bool DecrementChargesWrite(void);          //декрементировать кол-во "итемов в стаке" и записать на устройство - используется изнутри
    bool IncrementChargesWrite(void);          //инкрементировать кол-во "итемов в стаке" и записать на устройство - используется изнутри

    bool isSomeHardwareConnected(void);          //some hardware connected
    bool isSomeHardwareDisconnected(void);
    void SetSomeHardwareConnected(bool value);
//    TWI* hardware;

    bool m_isSomethingConnected;//  = false;
    //bool isItemPresents;
    uint8_t ledOnTimer;
    char itemInformationHead[PAGE_SIZE * ITEM_INFORMATION_HEAD_SIZE];
    //ConnectedItemArray_t connectedItemArray[UsableItemClass::CONNECTED_ITEM_SIZE];
    //EepromItem_t EepromItem;
    ConnectedItemClass connectedItem;
  };
#endif