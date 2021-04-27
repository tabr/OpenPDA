/*
  *  FactionsClass.h
  *
  *  Created:  30.06.2017  23:13:53
  *    Author:  tabr
  */  


#ifndef  FACTIONSCLASS_H_
#define  FACTIONSCLASS_H_
#include  "Node.hpp"


class  FactionsClass : public NodeExtended
  {
  public:
    FactionsClass  (void);
    FactionsClass  (FactionID_t  FID,  FactionName_t  FName);
    FactionName_t  GetName(void);
    FactionID_t  GetID(void);
    FactionsClass*  GetNextNode(void);


//    FactionsClass*  PrevItem=NULL;
  protected:
  private:
    FactionID_t  ID=0;
    FactionName_t  Name=NULL;
  };


#endif  /*  FACTIONSCLASS_H_  */
