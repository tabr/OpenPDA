/*
  *  RandomPseudo.h
  *
  *  Created:  2015-04-11  01:46:51
  *    Author:  tabr
  */  


#ifndef  RANDOMPSEUDO_H_
#define  RANDOMPSEUDO_H_

typedef  uint8_t  RP_SIZE;

class  RandomPseudoClass
  {
  public:
    const static uint8_t  RP_RAND_MAX  =  255;
    RP_SIZE  get(void)
      {
      //this->increment();
      //return  this->counter;
      return  (rand()%(this->RP_RAND_MAX));
      }
    uint8_t  getAsPercent(void)
      {
      //this->increment();
      //RAND_MAX;
      //return  ((100*this->counter)/this->RP_RAND_MAX);
      return  (rand()%(100  +  1));//[0..100]
      }
    void  increment(void)
      {
      //RAND_MAX;
      rand();
      //this->counter  =  rand()  %  this->RP_RAND_MAX;
      //this->counter++;
      }
    RandomPseudoClass  (void)
      {
      this->counter  =  0;
      }
    
    
  protected:
  private:
    RP_SIZE  counter;//TODO  private??!
    
  };


#endif  /*  RANDOMPSEUDO_H_  */
