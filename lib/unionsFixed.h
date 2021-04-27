#ifndef UNIONS_H
#define UNIONS_H

//https://habr.com/post/121811/
//http://codepad.org/2ycmkz2y

//#define DISABLE_UNIONS_FOR_TEST
#ifndef DISABLE_UNIONS_FOR_TEST

#include "unionsByteOrder.h"
#ifndef SELECTED_BYTE_ORDER
#error "Please define SELECTED_BYTE_ORDER"
#endif

//При программирование под сеть для ББ используются макросы ntol, ntos и т.д. и появление их обусловлено разным порядком на разных архетиктурах. Добавьте подобные макросы себе и используйте их для доступа к полям структуры.
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

uint32_t hton(uint32_t hostlong)
  {
  return htonl(hostlong);
  }
uint16_t hton(uint16_t hostshort)
  {
  return htons(hostshort);
  }
uint8_t hton(uint8_t hostshort)
  {
  return hostshort;
  }

uint32_t ntoh(uint32_t netlong)
  {
  return htonl(netlong);
  }
uint16_t ntoh(uint16_t netshort)
  {
  return htons(netshort);
  }
uint8_t ntoh(uint8_t netshort)
  {
  return netshort;
  }


BYTE_ORDER GetByteOrderRuntime(void)
  {
  uint32_t a  = 0x01020304;
  uint8_t* ptr  = reinterpret_cast<uint8_t*>(&a);
  if (*(ptr+0) == 0x04 && *(ptr+1) == 0x03 && *(ptr+2) == 0x02 && *(ptr+3) == 0x01)
    {
    return BYTE_ORDER_LITTLE_ENDIAN;
    }
  else if (*(ptr+0) == 0x01 && *(ptr+1) == 0x02 && *(ptr+2) == 0x03 && *(ptr+3) == 0x04)
    {
    return BYTE_ORDER_BIG_ENDIAN;
    }
  return BYTE_ORDER_UNKNOWN;
  };
//some checks
#ifdef __BYTE_ORDER__
  #if (SELECTED_BYTE_ORDER == (DEF_BYTE_ORDER_UNKNOWN))
    #error "USE DEF_ not Enum"
  #elif (SELECTED_BYTE_ORDER == (DEF_BYTE_ORDER_UNKNOWN))
    #if (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
      #error "Error while select byteorder"
    #endif
  #elif (SELECTED_BYTE_ORDER == DEF_BYTE_ORDER_BIG_ENDIAN)
    #if (__BYTE_ORDER__ != __ORDER_BIG_ENDIAN__)
      #error "Error while select byteorder"
    #endif
  #endif
#endif




  
typedef union 
	{
    uint16_t value_int;
    struct 
		{
	    unsigned char l;
	    unsigned char h;
		} byte_field;
	} UNION_UINT16_LITTLE_ENDIAN;
typedef union 
	{
    uint32_t value_int;
    struct 
		{
	    unsigned char l;
	    unsigned char ml;
	    unsigned char mh;
	    unsigned char h;
		} byte_field;
	} UNION_UINT32_LITTLE_ENDIAN;
typedef union 
	{
    uint32_t value_int;
    struct 
		{
	    uint16_t l;
	    uint16_t h;
		} data_field;
	} UNION_UINT32_16_LITTLE_ENDIAN;
typedef union 
	{
    uint32_t value_int;
    struct 
		{
	    UNION_UINT16_LITTLE_ENDIAN l;
	    UNION_UINT16_LITTLE_ENDIAN h;
		} data_field;
	} UNION_UINT32_16_8_LITTLE_ENDIAN;
typedef union 
	{
    uint16_t value_int;
    struct 
		{
	    unsigned char h;
	    unsigned char l;
		} byte_field;
	} UNION_UINT16_BIG_ENDIAN;
typedef union 
	{
    uint32_t value_int;
    struct 
		{
	    unsigned char h;
	    unsigned char mh;
	    unsigned char ml;
	    unsigned char l;
		} byte_field;
	} UNION_UINT32_BIG_ENDIAN;
typedef union 
	{
    uint32_t value_int;
    struct 
		{
	    uint16_t h;
	    uint16_t l;
		} data_field;
	} UNION_UINT32_16_BIG_ENDIAN;
typedef union 
	{
    uint32_t value_int;
    struct 
		{
	    UNION_UINT16_BIG_ENDIAN h;
	    UNION_UINT16_BIG_ENDIAN l;
		} data_field;
	} UNION_UINT32_16_8_BIG_ENDIAN;
#endif


#if (SELECTED_BYTE_ORDER == DEF_BYTE_ORDER_LITTLE_ENDIAN)
  #define UNION_UINT16        UNION_UINT16_LITTLE_ENDIAN
  #define UNION_UINT32        UNION_UINT32_LITTLE_ENDIAN
  #define UNION_UINT32_16     UNION_UINT32_16_LITTLE_ENDIAN
  #define UNION_UINT32_1_86   UNION_UINT32_16_8_LITTLE_ENDIAN
  uint32_t htonl(uint32_t hostlong)//host-to-network
    {
    UNION_UINT32_BIG_ENDIAN host;
    UNION_UINT32_LITTLE_ENDIAN network;
    host.value_int        = hostlong;

    network.byte_field.h  = host.byte_field.h;
    network.byte_field.mh = host.byte_field.mh;
    network.byte_field.ml = host.byte_field.ml;
    network.byte_field.l  = host.byte_field.l;

    return network.value_int;
    }
  uint16_t htons(uint16_t hostshort)
    {
    UNION_UINT16_BIG_ENDIAN host;
    UNION_UINT16_LITTLE_ENDIAN network;
    host.value_int    = hostshort;

    network.byte_field.h  = host.byte_field.h;
    network.byte_field.l  = host.byte_field.l;

    return network.value_int;
    }
  uint32_t ntohl(uint32_t netlong)
    {
    UNION_UINT32_BIG_ENDIAN host;
    UNION_UINT32_LITTLE_ENDIAN network;
    network.value_int    = netlong;

    host.byte_field.h  = network.byte_field.h;
    host.byte_field.mh = network.byte_field.mh;
    host.byte_field.ml = network.byte_field.ml;
    host.byte_field.l  = network.byte_field.l;

    return host.value_int;
    }
  
  uint16_t ntohs(uint16_t netshort)
    {
    UNION_UINT16_BIG_ENDIAN host;
    UNION_UINT16_LITTLE_ENDIAN network;
    network.value_int    = netshort;

    host.byte_field.h  = network.byte_field.h;
    host.byte_field.l  = network.byte_field.l;

    return host.value_int;
    }

#elif (SELECTED_BYTE_ORDER == DEF_BYTE_ORDER_BIG_ENDIAN)
  #define UNION_UINT16        UNION_UINT16_BIG_ENDIAN
  #define UNION_UINT32        UNION_UINT32_BIG_ENDIAN
  #define UNION_UINT32_16     UNION_UINT32_16_BIG_ENDIAN
  #define UNION_UINT32_1_86   UNION_UINT32_16_8_BIG_ENDIAN
  uint32_t htonl(uint32_t hostlong)
    {
    return hostlong;
    }
  uint16_t htons(uint16_t hostshort)
    {
    return hostshort;
    }
  uint32_t ntohl(uint32_t netlong)
    {
    return netlong;
    }
  
  uint16_t ntohs(uint16_t netshort)
    {
    return netshort;
    }
#else
  #error "Unimplemented"
#endif

#endif
