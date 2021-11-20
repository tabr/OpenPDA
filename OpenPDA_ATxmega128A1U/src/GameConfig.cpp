// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * GameConfig.cpp
 *
 * Created: 28.01.2016 0:57:27
 *  Author: tabr
 */ 
GameConfig::GameConfig(void)
  {
  //this->Wire  = new TWI(&GAME_CONFIG_TWI, AT24C02_SLAVE_ADDRESS, 400);
  this->load();
  //this->SuitsContainer.container  = (SuitExample*)malloc(sizeof(SuitExample) * GameConfig::MAX_SUITS);
  memset(this->GameParameters, 0, this->GAME_PARAMETERS::GAME_PARAMETERS_NUM);
  }
bool GameConfig::load(void)
  {
  //bool result;
  //this->PLAYER_DEATH_TIME  = 2700;
  //uint16_t test=0x00ff;
//  UNION_UINT16_FIXED a;
  //a.value_int=2700;
  //uint8_t tmp[10];

//    30,                          //002 кол-во секунд для регена (меньше - быстрее)
//    100,                        //003 максимальное ХП, которое игрок может накопить
//    90,                          //004 кол-во ХП, с которым стартует Игрок
  uint8_t tmp[GameConfig::CFG_PARAMETERS::CFG_BYTE_SIZE]={
    (((5)>>8) & 0xFF), (((5)>>0) & 0xFF),    //1+2 Время в секундах отсидки в мертвяке - 45мин [0-65535]
    100,                        //003 максимальная радиационная доза, которую может накопить игрок
    85,                          //003 уровень, при котором наносится двойной урон радиацией
    1,                          //004 множитель урона от радиации
    (((15*60)>>8) & 0xFF), (((15*60)>>0) & 0xFF),      //5+6 Время в секундах на отыгрыш зомби [0-65535]
//    (((30*60)>>8) & 0xFF), (((30*60)>>0) & 0xFF),      //5+6 Время в секундах на отыгрыш зомби [0-65535]
    (
    1<<CFG_CONFIGURATION_BITS_GAME_USE_SUIT_DURABILITY |  //костюмы не ломаются. ВНИМАНИЕ! Если не включен, некоторый урон может вообще не проходить, т.к. костюмы работают в режиме ПределУрона!
    1<<CFG_CONFIGURATION_BITS_DEATH_COUNTER_STARTS_ONLY_AT_GRAVEYARD |
    1<<CFG_CONFIGURATION_BITS_REGEN_X3_IN_SAFE_ZONE | 
	0<<CFG_CONFIGURATION_BITS_SUTE_USE_PU //not tested
    ),
//    TemporaryClass::DAMAGE_SOURCE_NUM,          //010
//    this->getDamageSourceNum(),          //010
    };
  /*
//  this->Wire->writeToDevice(CFG_MEMORY_START, 10, tmp);
  this->Wire->writeToDevice(0, CFG_MEMORY_START, 10, tmp);
  _delay_ms(500);*/
  memcpy(this->cfg, tmp, GameConfig::CFG_PARAMETERS::CFG_BYTE_SIZE);
  return true;
  //return this->Wire->readFromDevice(0, this->CFG_MEMORY_START, CFG_BYTE_SIZE, this->cfg);
  /*
  this->PLAYER_DEATH_TIME        = (tmp[0]<<8) | (tmp[1]&0xFF);
  this->DEFAULT_REGEN_VALUE      = tmp[2];
  this->MAXIMUM_PLAYER_HEALTH      = tmp[3];
  this->START_PLAYER_HEALTH      = tmp[4];
  this->MAXIMUM_PLAYER_RAD_DOSE    = tmp[5];
  this->RAD_DOSE_DOUBLE_DAMAGE_VALUE  = tmp[6];
  this->RAD_DOSE_DAMAGE        = tmp[7];
  this->PLAYER_ZOMBIE_TIME      = (tmp[8]<<8) | (tmp[9]&0xFF);*/
  //return result;
  /*LcdClearCache();
  sprintf (lcd_buf, "%03d%03d %03d%03d",tmp[0], tmp[1], tmp[2], tmp[3]);
  LcdString(1,LCD_LINE_1);
  sprintf (lcd_buf, "%01d %03d", result, this->PLAYER_DEATH_TIME);
  LcdString(1,LCD_LINE_2);
  LcdUpdate();
  while(1);*/
  }
/*
bool GameConfig::registerFaction(FactionID_t FID, FactionName_t FName)
  {
  this->FContainer.AddNode(new FactionsClass (FID, FName));
  this->FCnt++;
  return true;
  }
FactionsClass* GameConfig::GetFaction(FactionID_t FID)
  {
  return static_cast<FactionsClass*>(this->GetNode(FID));
  }
*/
bool GameConfig::SetDamageSourcesNum(DamageSourcesNum_t num)
  {
  if (this->GetDamageSourceNum() != 0)
    {
    Errors.SetError(ErrorClass::CODES::ERROR_DAMAGE_SOURCE_ALREADY_SET);
    return false;
    }
  if (num > 255) //-V547
    {
    #warning "[T] bad code style!"
    Errors.SetError(ErrorClass::CODES::ERROR_DAMAGE_SOURCE_OVF);
    return false;
    }
  this->GameParameters[this->GAME_PARAMETER_DAMAGE_SOURCE_NUM]  = num;
  return true;
  }
DamageSourcesNum_t GameConfig::GetDamageSourceNum(void)
  {
  return this->GameParameters[this->GAME_PARAMETERS::GAME_PARAMETER_DAMAGE_SOURCE_NUM];
  }
