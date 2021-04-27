

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

//#include <stdint.h>
//#include <stddef.h>
//#include <avr/io.h>
//typedef unsigned char uint8_t;
//typedef unsigned int uint16_t;
#include "typedefs.h"
volatile MemoryPool_t MemoryManager_MemoryPool[MEMORYMANAGER_POOL_SIZE];
class MemoryManagerClass
  {
  public:
    static void* Allocate(size_t size);
    static void DeallocateFromTop(size_t size);
    static uint16_t GetAvailableBytes(void);
    //MemoryManagerClass(void);

    //const static uint16_t POOL_SIZE    = 4096;
//    uint8_t fail;//нафига оно?:!
  protected:
  private:
    const static uint16_t POOL_STARTS  = 0;
    static volatile uint16_t pointerTop;// = POOL_STARTS;

//    static volatile MemoryPool_t MemoryPool[MEMORYMANAGER_POOL_SIZE];
  };
//MemoryManagerClass MemoryManager;
volatile uint16_t MemoryManagerClass::pointerTop = MemoryManagerClass::POOL_STARTS;
//#define malloc #WARNING malloc is disabled

#endif /* MEMORYMANAGER_H_ */