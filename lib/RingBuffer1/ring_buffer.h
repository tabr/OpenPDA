#pragma once
// change to(is it use "new()"??!): https://github.com/KonstantinChizhov/Mcucpp/blob/master/mcucpp/ring_buffer.h
#include "static_assert.h"
#include "select_size.h"

template<int SIZE, class DATA_T=uint8_t>
class RingBuffer
{
public:
  typedef typename SelectSizeForLength<SIZE>::Result INDEX_T;// определ¤ем псевдоним дл¤ индексов 

//private:
  BOOST_STATIC_ASSERT((SIZE&(SIZE-1))==0);//SIZE must be a power of 2
  DATA_T _data[SIZE];                     // пам¤ть под буфер
//    volatile INDEX_T _readCount = 0;          // количество чтений
//    volatile INDEX_T _writeCount = 0;         // количество записей
    uint8_t _readCount = 0;          // количество чтений
    uint8_t _writeCount = 0;         // количество записей
  static const INDEX_T _mask = SIZE - 1;  // маска дл¤ индексов
public:
// запись в буфер, возвращает true если значение записано
  inline bool Write(DATA_T value)
  {
    if(IsFull())
      return false;
    _data[_writeCount++ & _mask] = value;
    return true;
  }
// чтение из буфера, возвращает true если значение прочитано
  inline bool Read(DATA_T &value)
  {
    if(IsEmpty())
      return false;
//    value = _data[_readCount++ & _mask];
    value = _data[_readCount & _mask];
    //_readCount++;
    return true;
  }
  inline bool IncrementRead(void)
  {
    _readCount++;
  }
// возвращает первый элемент из буфера, не удал¤¤ его
  inline DATA_T First()const
  {
    return operator[](0);
  }
// возвращает последний элемент из буфера, не удал¤¤ его
  inline DATA_T Last()const
    {
    return operator[](GetUsedSpace());
    }
// возвращает элемент по индексу
//  inline DATA_T& operator[] (INDEX_T i)
  inline DATA_T operator[] (INDEX_T i)
  {
    if(IsEmpty() || i > GetUsedSpace())
      return DATA_T();
    return _data[(_readCount + i) & _mask];
  }

  inline const DATA_T operator[] (INDEX_T i)const
  {
    if(IsEmpty()|| i > GetUsedSpace())
      return DATA_T();
    return _data[(_readCount + i) & _mask];
  }
// пуст ли буфер
  inline bool IsEmpty()const
  {
    return _writeCount == _readCount;
  }
  inline bool IsNotEmpty()const
  {
    return !(IsEmpty());
  }
// полон ли буфер
  inline bool IsFull()const
  {
    return ((_writeCount - _readCount) & (INDEX_T)~(_mask)) != 0;
  }
// количество элементов в буфере
  INDEX_T GetUsedSpace()const
  {
//    return ((_writeCount - _readCount) & _mask);
    return ((_writeCount - _readCount) & (_mask | SIZE));
  }
  inline INDEX_T GetFreeSpace()const
    {
    return (SIZE - GetUsedSpace());
    //return (GetUsedSpace());
    }
// очистить буфер
  inline void Clear()
    {
    _readCount  = 0;
    _writeCount = 0;
    }
// размер буфера
  inline unsigned GetMaxSize()
  {return SIZE;}
};
