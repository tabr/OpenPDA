/*
 * DataStorageClass.h
 *
 * Created: 10/26/2022 4:26:00 PM
 *  Author: tabr
 */ 


#ifndef DATASTORAGECLASS_H_
#define DATASTORAGECLASS_H_
#include "DataStorage_InternalEEPROMClass.hpp"
#include "DataStorage_ExternalEEPROMClass.hpp"
#include "DataStorage_ExternalFlashClass.hpp"

class DataStorageClass
{
public:
	const static DataStorage_InternalEEPROMClass InternalEEPROM;
	const static DataStorage_ExternalEEPROMClass ExternalEEPROM;
	const static DataStorage_ExternalFlashClass ExternalFlash;
protected:
private:
};



#endif /* DATASTORAGECLASS_H_ */