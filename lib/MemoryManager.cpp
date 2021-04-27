// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * MemoryManager.cpp
 *
 * Created: 2015-08-03 19:04:08
 *  Author: tabr
 */ 
#include "MemoryManager.hpp"
/*
MemoryManagerClass::MemoryManagerClass(void)
  {
  this->pointerTop  = this->POOL_STARTS;
//  this->fail      = 0;
  }*/
uint16_t MemoryManagerClass::GetAvailableBytes(void)
  {
  return (MEMORYMANAGER_POOL_SIZE - pointerTop);
  }
void* MemoryManagerClass::Allocate(size_t size)
  {
  //return malloc(size);
  
  if (size > GetAvailableBytes())
    {
//    this->fail  = 1;
    //return (void*)&this->MemoryPool[0];
    StatusLedPin::SetDirOut();
    while(1)
      {
      StatusLedPin::SetOutToggle();
      _delay_ms(100);
      }
    return NULL;
    }
  void* ptr  = (void*)&(MemoryManager_MemoryPool[pointerTop]);
  pointerTop+=size;
  return ptr;
  }
void MemoryManagerClass::DeallocateFromTop(size_t size)
  {
  if (size > pointerTop + POOL_STARTS)
    {
    return;//TODO: מרטבךא ךאדב‎
    }
  pointerTop-=size;
  }