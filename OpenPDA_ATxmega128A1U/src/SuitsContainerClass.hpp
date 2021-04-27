/*
  *  SuitsContainerClass.h
  *
  *  Created:  06.05.2017  20:32:24
  *    Author:  tabr
  */  


#ifndef  SUITSCONTAINERCLASS_H_
#define  SUITSCONTAINERCLASS_H_

#include  "Suits.hpp"

class  SuitsContainerClass : public NodeProcessor
  {
  public:
//    void  setContainerSize(SuitsContainerSize_t  size);
    void  RegisterNew(SuitTemplateInstance*  s);
    SuitID_t  getRegisteredSuitsNum(void);
    SuitName_t  GetSuitName(SuitID_t  SID);
    SuitTemplateInstance*  getSuiteInstance(const  SuitID_t  SID);
    SuitTemplateInstance*  GetContainer(void);
    //SuitsContainerClass(void);

    //SuitExample  *container[DeviceConfigClass::MAX_SUITS];//массив  ссылок  на  объекты  "костюмы"
    //SuiteInstance  container[12];
  protected:
  private:  
    SuitTemplateInstance  *container = nullptr;
//    uint8_t  counter=0;
    uint8_t  containerSize=0;
    
  };



#endif  /*  SUITSCONTAINERCLASS_H_  */
