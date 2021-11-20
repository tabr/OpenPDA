#ifndef  GAME_CONFIG_CLASS_H
#define  GAME_CONFIG_CLASS_H
//WARNING!!!
//IT  USES  IN  PHP
#include  "SuitsContainerClass.hpp"
#include  "Suits.hpp"
#include  "RadiomarkClass.hpp"
#include  "Items.hpp"
#include  "ArtefactClass.hpp"
#include  "FactionsClass.hpp"
//#include  "TWI.h"

//template<char*  srcCharArray>


class  GameConfig //: public  NodeProcessor
  {
  public:
    enum  CFG_CONFIGURATION_BITS
      {
      CFG_CONFIGURATION_BITS_GAME_USE_SUIT_DURABILITY,
      CFG_CONFIGURATION_BITS_DEATH_COUNTER_STARTS_ONLY_AT_GRAVEYARD,
      CFG_CONFIGURATION_BITS_REGEN_X3_IN_SAFE_ZONE,
      CFG_CONFIGURATION_BITS_SUTE_USE_PU,
      };
    enum  CFG_SECTIONS
      {
      CFG_SECTION_HEAD_SIZE_H,
      CFG_SECTION_HEAD_SIZE_L,
      CFG_SECTION_HEAD,
      CFG_SECTION_GAME_CONSTANTS,
      CFG_SECTION_ANOMALIES,
      CFG_SECTION_ARTEFACTS,
      CFG_SECTION_FACTIONS,
      CFG_SECTION_IN_GAME_EVENTS,
      CFG_SECTION_ITEMS,
      CFG_SECTION_PDA_MENU,
      CFG_SECTION_QUESTS,
      CFG_SECTION_RADIOMARKS,
      CFG_SECTION_SUITES,
      CFG_SECTION_NUM
      };
/*
    const static uint16_t  PLAYER_DEATH_TIME          =  2700;  //002  Время  в  секундах  отсидки  в  мертвяке  -  45мин
    const static uint8_t  DEFAULT_REGEN_VALUE        =  30;  //004  кол-во  секунд  для  регена  (меньше  -  быстрее)
    const static uint8_t  MAXIMUM_PLAYER_HEALTH        =  100;  //005  максимальное  ХП,  которое  игрок  может  накопить
    const static uint8_t  START_PLAYER_HEALTH        =  90;  //005  максимальное  ХП,  которое  игрок  может  накопить
    const static uint8_t  MAXIMUM_PLAYER_RAD_DOSE      =  100;  //007  максимальная  радиационная  доза,  которую  может  накопить  игрок
    const static uint8_t  RAD_DOSE_DOUBLE_DAMAGE_VALUE    =  85;  //008  уровень,  при  котором  наносится  двойной  урон  радиацией
    const static uint8_t  RAD_DOSE_DAMAGE          =  1;  //009  множитель  урона  от  радиации
    const static uint16_t  PLAYER_ZOMBIE_TIME        =  600;  //010  Время  в  секундах  на  отыгрыш  зомби
//    const static uint8_t  MAX_SUITS              =  16;  //010  кол-во  разных  костюмов  на  Игре
*/
    PlayerDeathTimer_t  GetPlayerDeathTime(void)
      {
      return  ((this->cfg[this->PLAYER_DEATH_TIME_H]<<8  )  |  this->cfg[this->PLAYER_DEATH_TIME_L]);
      }                                                    //ok  -  загрузка  ЕДИНОЖДЫ
    uint8_t  GetMaxumumPlayerRadDose(void)
      {
      return  this->cfg[this->MAXIMUM_PLAYER_RAD_DOSE];                            //ok  -  загрузка  ЕДИНОЖДЫ
      }
    uint8_t  GetRadDoseDoubleDamage(void)
      {
      return  this->cfg[this->RAD_DOSE_DOUBLE_DAMAGE_VALUE];                          //ok  -  загрузка  ЕДИНОЖДЫ
      }
    uint8_t  GetRadDoseDamage(void)
      {
      return  this->cfg[this->RAD_DOSE_DAMAGE];                                //ok  -  загрузка  ЕДИНОЖДЫ
      }
    uint16_t  GetPlayerZombieTime(void)
      {
      return  ((this->cfg[this->PLAYER_ZOMBIE_TIME_H]<<8)  |  (this->cfg[this->PLAYER_ZOMBIE_TIME_L]<<0));    //ok  -  загрузка  ЕДИНОЖДЫ
      }



    const static uint8_t  CFG_MEMORY_START          =  1;

    SuitsContainerClass  SuitsContainer;
    GameTemplate_ArtefactsContainerClass  ArtefactsContainer;
    bool  load(void);
    GameConfig(void);
    bool  SetDamageSourcesNum(DamageSourcesNum_t  num);
    DamageSourcesNum_t  GetDamageSourceNum(void);
    bool  IsGameUseParameter(CFG_CONFIGURATION_BITS  parameter)
      {
      return  (this->cfg[SOME_CONFIGURATION]  &  (1<<parameter));
      }
//    NodeExtended*  GetContainer(void);

//    bool RegisterNewEmission(EmissionInstanceClass* NewEmission)
//    bool RegisterNewEmission(RadiomarkInstanceClass::RADIOMARK_TYPE NewERID)
//      {
//      return this->EmissionStorage.RegisterNew(new EmissionInstanceClass(NewERID));
//      }
//    EmissionInstanceClass* GetEmission(RadiomarkID_t ERID)
//      {
//      return this->EmissionStorage.GetNode(ERID);
//      }
    bool RegisterNewFaction(FactionsClass* NewFaction)
      {
      return this->FactionsClassStorage.RegisterNew(NewFaction);
      }
    FactionsClass* GetFaction(FactionID_t FGUID)
      {
      return this->FactionsClassStorage.GetNode(FGUID);
      }
    bool RegisterNewPlayerEffect(PlayerEffectsStoragableClass* NewEffect)
      {
      return this->PlayerEffectsStorage.RegisterNew(NewEffect);
      }
/*
    PlayerEffectsStoragableClass* GetPlayerEffect(PlayerEffectGUID_t EGUID)
      {
      return this->PlayerEffectsStorage.GetNode(EGUID);
      }
*/
    bool RegisterNewRadiomark(RadiomarkInstanceClass* NewRadiomark)
      {
      return this->RadiomarkInstanceStorage.RegisterNew(NewRadiomark);
      }
    RadiomarkInstanceClass* GetRadiomark(RadiomarkID_t RMGUID)
      {
      return this->RadiomarkInstanceStorage.GetNode(RMGUID);
      }


    ItemTemplateClass  ItemTemplate;

  protected:
  private:
//    NodeProcessorT<EmissionInstanceClass> EmissionStorage;
    NodeProcessorT<PlayerEffectsStoragableClass> PlayerEffectsStorage;
    NodeProcessorT<FactionsClass> FactionsClassStorage;
    NodeProcessorT<RadiomarkInstanceClass> RadiomarkInstanceStorage;
    /*uint16_t  PLAYER_DEATH_TIME;                    //ok
    uint8_t  DEFAULT_REGEN_VALUE;                  //много  переделывать
    uint8_t  MAXIMUM_PLAYER_HEALTH;                  //fixed
    uint8_t  START_PLAYER_HEALTH;
    uint8_t  MAXIMUM_PLAYER_RAD_DOSE;                //ok
    uint8_t  RAD_DOSE_DOUBLE_DAMAGE_VALUE;              //ok
    uint8_t  RAD_DOSE_DAMAGE;                    //ok
    uint16_t  PLAYER_ZOMBIE_TIME;                  //ok*/
    
//    const static uint8_t  CFG_PLAYER_DEATH_TIME_H;
    enum  CFG_PARAMETERS
      {
      PLAYER_DEATH_TIME_H,
      PLAYER_DEATH_TIME_L,
//      DEFAULT_REGEN_VALUE,      //сомнительная  необходимость
//      MAXIMUM_PLAYER_HEALTH,
//      START_PLAYER_HEALTH,      //сомнительная  необходимость
      MAXIMUM_PLAYER_RAD_DOSE,
      RAD_DOSE_DOUBLE_DAMAGE_VALUE,
      RAD_DOSE_DAMAGE,
      PLAYER_ZOMBIE_TIME_H,
      PLAYER_ZOMBIE_TIME_L,
      SOME_CONFIGURATION,
//      DAMAGE_TYPE_NUM,//except  "0",  includes  build-in  types
//      ADDRESS_SUITE_STARTS,  //нахуя  оно??!
//      ADDRESS_ANOMALY_STARTS,
//      ADDRESS_ITEMS_STARTS,
//      ADDRESS_QUESTS_STARTS,
      CFG_BYTE_SIZE,
      };
    
    
    //const static uint8_t  CFG_BYTE_SIZE          =  10;
    uint8_t  cfg[CFG_BYTE_SIZE];
    enum  GAME_PARAMETERS
      {
      GAME_PARAMETER_DAMAGE_SOURCE_NUM,
      GAME_PARAMETERS_NUM,
      };
    uint8_t  GameParameters[GAME_PARAMETERS::GAME_PARAMETERS_NUM];
  };

/*
const  SuitExample  GameConfig::suits[3]  =
  {
  //      имя        [макс.прочность]  [защ.пси]  [защ.хим]  [защ.электро]  [защ.огонь]  [защ.рад]  [защ.грав]  [макс.контейнеров]
  SuitExample("(пусто)",    0,          0,      0,      0,        0,      0,      0,      1),
  SuitExample("к.сталкера",  100,        0,      25,      25,        25,      25,      25,      3),
  SuitExample("сева",      150,        10,      70,      90,        80,      90,      50,      5),
  };
*/
/*SuitExample    qwe  =  {
  .name    =  "(пусто)"
};
twi_package_t  packet  =  {
  .addr_length  =  0,
  .chip                =  TWI_SLAVE_ADDR,
  .buffer            =  (void  *)data,
  .length            =  DATA_LENGTH,
  .no_wait          =  false
};*/
#endif