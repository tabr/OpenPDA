#ifndef  DAMAGE_CLASS_H
#define  DAMAGE_CLASS_H

#include  "typedefs.h"
#include  "Node.hpp"
/*
class  DamageSourceNewInstanceClass : public NodeExtended
  {
  public:
    DamageSourceNewID_t  GetID(void)
      {
      return  this->ID;
      }
    DamageSourceName_t  GetName(void)
      {
      return  this->Name;
      }
    DamageSourceNewInstanceClass*  GetNextNode(void)
      {
      return  static_cast<DamageSourceNewInstanceClass*>(Node::GetNextNode());
      }
    DamageSourceNewInstanceClass(void)
      {
      this->ID  =  0;
      this->Name  =  STR_None;
      }
  protected:
  private:
    DamageSourceNewID_t  ID=0;
    DamageSourceName_t  Name;
  };
class  DamageSourceNewClass : public NodeProcessor
  {
  public:
    NodeExtended*  GetContainer(void)
      {
      return  this->container;
      }
  protected:
  private:
    NodeExtended*  container;
  };
*/


class  DamageSourceContainerClass
  {
  public:
    DamageSourceContainerClass(void);
    DamageSourceContainerClass(DamageSourceCounter_t  num);
    DamageDefenceValue_t  GetDefenceFrom(DamageSource_t  src);
    void  SetDefenceFrom(DamageSource_t  src,  DamageDefenceValue_t  value);
    DamageDefenceValue_t*  container  =  NULL;
  protected:
  private:
    uint8_t  containerSize      =  0;
    void  Constructor(DamageSourceCounter_t  num);
  };

class  DamageSourceClass
  {
  public:
    void Set (DamageSource_t  value)
      {
      this->selected  =  value;
      }
    TemporaryClass::DamageSource  Get  (void)
      {
      return  this->selected;
      }
    DamageSourceClass  (TemporaryClass::DamageSource  initValue  =  TemporaryClass::DAMAGE_SOURCE_NONE)
      {
      this->Set(initValue);
      }
  protected:
  private:
    DamageSource_t  selected;
  };

class  DamageClass//TODO
  {
  public:

    enum  AGGRESSOR_SOURCE
      {
      AGGRESSOR_SOURCE_INTERNAL,
      AGGRESSOR_SOURCE_EXTERNAL
      };
    AGGRESSOR_SOURCE  GetAggressorSource(void)
      {
      return  this->aggressorSource;
      }
    void  SetValue(DamageValue_t  dmgValue)//Also  sets  final  value
      {
      this->value        =  dmgValue;
      }
    void  SetNewDamage(AGGRESSOR_SOURCE  aSrc,  DamageSource_t  dmgSrc,  DamageValue_t  damageValue)
      {
      this->CleanDamage();  //Зачем  оно,  если  всё  равно  переопределяется  -  не  удалять  напоминание
      this->SetAggressorSource(aSrc);
      this->GetSource()->Set(dmgSrc);
//      this->setAggressorType(agressorType);
//      this->setAggressorSubType(agressorSubType);
      this->SetValue(damageValue);
      }
    void  CleanDamage(void)//may  be  called  after  damage  applied
      {
      this->SetAggressorSource(DamageClass::AGGRESSOR_SOURCE_INTERNAL);
      this->GetSource()->Set(TemporaryClass::DAMAGE_SOURCE_NONE);
//      this->setAggressorType(0);
//      this->setAggressorSubType(0);
      this->SetValue(0);
      }
    void  SetAggressorSource(AGGRESSOR_SOURCE  aSrc)
      {
      this->aggressorSource  =  aSrc;
      }
/*
    DamageSource_t  getDamageSource(void)
      {
      return  this->m_damageSource.Get();
      }
    void  setDamageSource(DamageSource_t  dmgSrc)
      {
      this->m_damageSource.Set(dmgSrc);
      }
*/
    DamageSourceClass*  GetSource(void)
      {
      return  &this->damageSource;
      }
    DamageValue_t  GetValue(void)
      {
      return  this->value;
      }
    bool  isDamageSourceValid(DamageSource_t  value);

    DamageValue_t  value=0;
    DamageSourceClass  damageSource=DamageSource_t::DAMAGE_SOURCE_GENERIC;
    AGGRESSOR_SOURCE  aggressorSource=AGGRESSOR_SOURCE::AGGRESSOR_SOURCE_EXTERNAL;
  protected:
  private:
  };
struct DamageValueStruct
  {
  DamageValue_t value=0;
  DamageSource_t src=DamageSource_t::DAMAGE_SOURCE_GENERIC;

  };

#endif