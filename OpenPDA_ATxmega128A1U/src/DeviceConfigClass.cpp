// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * DeviceConfigClass.cpp
 *
 * Created: 28.04.2017 15:03:52
 *  Author: tabr
 */ 
DeviceID_t DeviceConfigClass::GetID(void)
	{
	if (this->DeviceID == 0xFF)
		{
		//uint8_t tmp[]={}
		ExternalEEPROMTWI::readFromDevice(0,0, 1, &this->DeviceID);
		}
	return this->DeviceID;
	}
void DeviceConfigClass::WriteNewDevID(DeviceID_t DID)
  {
  ExternalEEPROMTWI::writeToDevice(0,0,1,&DID);
  _delay_ms(10);
  }

bool DeviceConfigClass::IsAddressedToMe(DeviceID_t DID)
	{
	if (this->GetID() == DID || DID == ADDRESS_BROADCAST)
		{
		return true;
		}
	return false;
	}