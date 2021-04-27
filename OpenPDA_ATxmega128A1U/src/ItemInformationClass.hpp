#ifndef  ITEM_INFORMATION_CLASS_H
#define  ITEM_INFORMATION_CLASS_H

#include  <avr/io.h>
#include  "UsableItemClass.hpp"

//extern  UsableItemClass  UsableItem;


class  ItemInformationClass//TODO:  реализовано  ХАКом  -  переделать
  {
  public:
    const static uint8_t  ID_NONE      =  0;
    const static uint8_t  ID_FOUND_SEVA    =  1;
    const static uint8_t  ID_CODE      =  2;
    const static uint8_t  ID_GOOUT      =  3;

    void  getHead(uint8_t  id,  char  *data);
    void  getBody(uint8_t  id,  uint8_t  LCDLine,  char  *data);
  protected:
  private:
  };
#endif