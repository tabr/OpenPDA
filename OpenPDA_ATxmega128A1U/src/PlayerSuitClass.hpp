#ifndef  PLAYER_SUIT_CLASS_H
#define  PLAYER_SUIT_CLASS_H

#include  "GameTemplate_TemporaryClass.hpp"
#include  "DamageClass.hpp"
//#include  "Suits.h"
#include  "typedefs.h"
#include  "GameCharacteristicsClass.hpp"


class  SuitTemplateInstance;  //in  "Suits.h"
class  ConnectedItemSuitClass;
class  UsableItemClass;

class  PlayerSuitInstanceClass : public GameCharacteristicsInterface
  {
  public:
    void  CloneFrom  (SuitID_t  suitId,  SuitDurabiluty_t  durability);
    void  CloneFrom  (PlayerSuitInstanceClass*  src);
    void  CloneFrom  (ConnectedItemSuitClass*  connectedSuit);
//    GameCharacteristicsClass*  GetCharacteristics(void);
    SuitID_t  GetID(void);
    SuitDurabiluty_t  GetDurability(void);
    SuitTemplateInstance*  GetTemplate(void);
    DamageSourceContainerClass*  GetDefences(void);
    bool  WriteTo(UsableItemClass*  UI);
    //PlayerSuitInstanceClass(void) : SID(0),  SuitTemplate(NULL)  {};
  protected:
  private:
//    GameCharacteristicsClass  GameCharacteristics;
    SuitID_t  SID=0;
    SuitTemplateInstance*  SuitTemplate=NULL;
  };

class  PlayerSuitClass
  {
  public:
//    const static uint8_t  PARAMETER_SUIT_ID      =  0;
//    const static uint8_t  PARAMETER_DURABITITY_H    =  1;
//    const static uint8_t  PARAMETER_DURABITITY_L    =  2;

    const  static  SuitDurabiluty_t  DURABILITY_FULL  =  0xFFFF;
    
//    const  static  char  NAMES[PlayerSuitClass::SUITS_NUM][11];//����
    
//    uint8_t  previousSuit[TemporaryClass::SUITE_PARAMETERS_NUM];//������������  �����
//    uint8_t  currentDurable;//TODO:  ��������  ��  �����������
    
    PlayerSuitClass  (void);
//    void  wear(uint8_t  *suitData);//����  �������,  ������  �������
//    void  wear(uint8_t  suitId,  uint8_t  durability,  uint8_t  containers);
    void  Wear  (SuitID_t  suitId,  SuitDurabiluty_t  durability);    //����  �������,  ������  �������
    bool  Wear  (ConnectedItemSuitClass*  connectedSuit);
    bool  Wear  (UsableItemClass*  UI);
    bool  isValidSuitID(SuitID_t  SID);
//    DamageDefenceValue_t  getDefenceFrom(DamageSource_t  dmgSrc);
    DamageDefenceValue_t  GetDefenceFrom(DamageClass  damage);
    SuitContainersNum_t  getContainersNum(void);
    Percent_t  getDurabilityPercent(void);            //32  bit  calculations
    SuitDurabiluty_t  getDurability(void);
//    void  setSuitID(SuitID  SID);
    SuitID_t  getSuitID(void);
    SuitID_t  GetID(void);
    SuitName_t  getSuitName(void);
    SuitDurabiluty_t  getMaxDurability(void);            //������������  ���������  ���  �������  =  ��,  ���  ������  �  ������  ����  +  ������������
    void  damageTaken(DamageClass  *damage);        //����������  �����,  ������������,  �������,  ���  ������  ���������
    void  setDurability(SuitDurabiluty_t  durability);
    void  loseDurability(SuitDurabiluty_t  durability);
    void  repair(SuitDurabiluty_t  value);              //��������  ���������  (���������������)
//    SuitTemplateInstance*  GetCurrentSuitTemplate(void);
    PlayerSuitInstanceClass*  GetCurrentSuit(void);
    PlayerSuitInstanceClass*  GetPreviousSuit(void);
    void  EEPROM_init(void);
  protected:
  private:
    //uint8_t  currentSuite[PARAMETERS_NUM];
    //uint8_t  *currentSuite;
    //SuiteTemplateInstance  currentSuit;
    PlayerSuitInstanceClass  currentSuit;
    PlayerSuitInstanceClass  previousSuit;
  };

#endif