/*
  *  CPUdefines.h
  *
  *  Created:  29.10.2015  3:24:47
  *    Author:  tabr
  */  


#ifndef  COMPILER_DEFINES_H_
#define  COMPILER_DEFINES_H_

#include  "my_defines.h"
#include "unionsByteOrder.h"

#define HARDWARE_REVISION     1
#define SELECTED_BYTE_ORDER   DEF_BYTE_ORDER_LITTLE_ENDIAN

#define  F_CPU            (32U*MHZ_1)
#define  ATMEL_STUDIO        6.2


#endif  /*  COMPILER_DEFINES_H_  */
