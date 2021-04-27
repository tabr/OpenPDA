// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

PlayerEffectsStoragableClass::PlayerEffectsStoragableClass()
  {

  }
PlayerEffectsStoragableClass::PlayerEffectsStoragableClass(PE_CFG_t tmpCFG,TimeSecond_t repeatPeriodSec, PE_RepeatTimes_t repeatTimes, PlayerEffectGUID_t EGUID, EffectName_t tmpName)
  {
  this->m_CFG               = tmpCFG;
  this->m_repeatTimes       = repeatTimes;
  this->m_repeatPeriodSec   = repeatPeriodSec;
  this->EGUID               = EGUID;
  if (tmpName == NULL)
    {
    tmpName = RAM_STR_UNDEFINED;
    }
  this->Name                = LcdStringCopy.CopyFrom(tmpName);
  }
void PlayerEffectsStoragableClass::Clean(void)
  {
  this->m_CFG               = 0;
  this->m_repeatPeriodSec   = 0;
  this->m_repeatTimes       = 0;
  this->EGUID               = 0;
  this->Name                = NULL;
  }