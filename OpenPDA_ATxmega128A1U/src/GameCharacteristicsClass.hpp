/*
  *  GameCharacteristicsClass.h
  *
  *  Created:  27.01.2016  1:00:32
  *    Author:  tabr
  */  


#ifndef  GAMECHARACTERISTICSCLASS_H_
#define  GAMECHARACTERISTICSCLASS_H_

#include  "typedefs.h"
class  GameCharacteristicsInterface;

class  GameCharacteristicsClass
  {
  public:
    enum  CHARACTERISTICS
      {
      CHARACTERISTIC_NONE,
      CHARACTERISTIC_HIT_POINTS,
      CHARACTERISTIC_RADIATION,
      CHARACTERISTIC_DURABILITY,
      CHARACTERISTIC_CONTAINERS,
      CHARACTERISTICS_NUM
      };
    void  CloneFrom  (GameCharacteristicsClass*  src);
    CharacteristicsValue_t  Get(GameCharacteristicsClass::CHARACTERISTICS  c);
    void  Set(GameCharacteristicsClass::CHARACTERISTICS  c,  CharacteristicsValue_t  value);  //also  calls  SetUsingCharacteristic
    void  MaxValuesSetObject(GameCharacteristicsInterface*  max);
    GameCharacteristicsClass*  MaxValuesGet(void);
    bool  IsUsingCharacteristic1(GameCharacteristicsClass::CHARACTERISTICS  c);
    void  SetUsingCharacteristic(GameCharacteristicsClass::CHARACTERISTICS  c);
    /*void  Select(GameCharacteristicsClass::CHARACTERISTICS  c)
      {
      sbi(this->characteristicsSelected,  c);
      }*/
    /*CharacteristicsValue_t  GetMax(GameCharacteristicsClass::CHARACTERISTICS  c)
      {
      return  this->storageMax[c];
      }*/
    /*void  SetMax(GameCharacteristicsClass::CHARACTERISTICS  c,  CharacteristicsValue_t  value)
      {
      this->storageMax[c]  =  value;
      }*/
    GameCharacteristicsClass(CharacteristicsBitLength_t  select=0);
  protected:
  private:
    GameCharacteristicsInterface*  max=NULL;
    CharacteristicsBitLength_t  characteristicsUsing=0;
    CharacteristicsValue_t  storage[CHARACTERISTICS_NUM];
    //CharacteristicsValue_t  storageMax[CHARACTERISTICS::CHARACTERISTICS_NUM];//MAX  value  should  be  get  from  template
    //CharacteristicsValue_t*  translationTable;
    TODO("Use  translation  table  to  minimize  RAM  load");//memleak  may  cause  on  dynamic  allocation!  beacuse  new  in  runlevels
  };
class  GameCharacteristicsInterface
  {
  public:
    GameCharacteristicsClass*  GetCharacteristics()
      {
      return  this->GameCharacteristics;
      }
    void  SetCharacteristics(GameCharacteristicsClass*  c)
      {
      this->GameCharacteristics  =  c;
      }
  protected:
    GameCharacteristicsClass*  GameCharacteristics=NULL;
  private:
  };
/*
class  GameCharacteristicsContainerClass
  {
  public:
  protected:
  private:
  };
*/



#endif  /*  GAMECHARACTERISTICSCLASS_H_  */
