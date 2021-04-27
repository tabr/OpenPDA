#ifndef MY_DEFINES_H
#define MY_DEFINES_H

#include <stddef.h>

#define cbi(port,bit)               port&=~(1<<(bit)) //clear bit
#define sbi(port,bit)               port|=(1<<(bit))  //set bit
#define ibi(port,bit)               port^=(1<<(bit))  //invert bit
#define isBitSet(reg,bit)           ((reg)&(1<<(bit)))
//#define array_length(array)         (sizeof(array)/sizeof(array[0]))
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
#define array_length(array)         (sizeof(ArraySizeHelper(array)))

#define cbi_mask(port,mask)         port&=~(mask)
#define sbi_mask(port,mask)         port|=(mask)
#define ibi_mask(port,mask)         port^=(mask)
//#define SetOutput(port,bit)        port|=(1<<bit)
//#define SetInput(port,bit)        port&=~(1<<bit)
#define GetBit(value, place)        (((value) >> (place)) & 1)
#define GetMSB(value, datatype)     GetBit(value, (sizeof(datatype) * 4 - 1))
#define GetLSB(value)               GetBit(value, 0)

#define MHZ_1                       1000000
#define ONE_MHZ                      MHZ_1

#endif