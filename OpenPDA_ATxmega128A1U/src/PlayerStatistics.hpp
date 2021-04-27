/*
  *  playerStatistics.h
  *
  *  Created:  2015-04-12  20:15:22
  *    Author:  tabr
  */  


#ifndef  PLAYERSTATISTICS_H_
#define  PLAYERSTATISTICS_H_


class  PlayerStatisticsClass
  {
  public:
    PlayerStatisticsClass(void);
    void  playerDeathIncrement(void);
    void  playerMedicamentUseIncrement(uint8_t  medicament);
    void  EEPROM_init(void);
  protected:
  private:
    uint8_t*  playerDeathNum = nullptr;
    uint8_t*  itemsUsed = nullptr;
  };


#endif  /*  PLAYERSTATISTICS_H_  */
