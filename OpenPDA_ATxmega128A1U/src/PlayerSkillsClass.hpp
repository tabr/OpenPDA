/*
  *  PlayerSkillsClass.h
  *
  *  Created:  2015-07-17  20:05:31
  *    Author:  tabr
  */  


#ifndef  PLAYERSKILLSCLASS_H_
#define  PLAYERSKILLSCLASS_H_

#include  <stdint.h>
#include  <stddef.h>
#include  <avr/io.h>

#include  "typedefs.h"
//#include  "EEPROM_StructPlayer.h"  //<-  cross-link


class  PlayerSkillsClass
  {
  public:
    enum  SKILLS
      {
      SKILL_FIRST_AID,
      SKILL_BREAKING,
      SKILL_COMPUTER,
      SKILL_CHEMICAL,
      SKILL_TECH,
      SKILL_FARMER,
      SKILL_MELE_WEAPON,
      SKILL_RANGE_WEAPON,
      SKILL_ENERGY_WEAPON,
      SKILL_DOCTOR,
      SKILLS_NUM
      };
    
    const static uint8_t  MAX_VALUE  =  100;
    const static uint8_t  MAX_SKILLS  =  3;
    
    bool  increaseValue(SkillID_t  SID,  uint8_t  value);
    bool  setValue(SkillID_t  SID,  uint8_t  value);
    bool  isMaxSkillsReached(void);
    bool  isSkillKnown(SkillID_t  SID);
    bool  isSkillUnknown(SkillID_t  SID);
    bool  setSkillKnown(SkillID_t  SID);
    uint8_t  getSkills(uint8_t*  data);//returns  number  of  skills
    uint8_t  getValue(SkillID_t  SID);
    char*  getName(SkillID_t  SID);
    void  EEPROM_init(void);
  protected:
  private:
    uint8_t*  container = nullptr;
  };


#endif  /*  PLAYERSKILLSCLASS_H_  */
