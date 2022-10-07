// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * DeviceConfigClass.cpp
 *
 * Created: 28.04.2017 15:03:52
 *  Author: tabr
 */ 
bool DeviceConfigClass::GetDevFlags(void){
	if (this->dev_flag == 0xFF){
		//uint8_t tmp[]={}
		ExternalEEPROMTWI::readFromDevice(0,1, 1, &this->dev_flag);
		if (this->dev_flag == 0xFF){
			this->dev_flag = 0x00;
			this->WriteDevFlags();
		}
	}
	return this->dev_flag;
}
void DeviceConfigClass::WriteDevFlags(void){
  ExternalEEPROMTWI::writeToDevice(0,1, 1,&this->dev_flag);
  _delay_ms(10);
}
void DeviceConfigClass::WriteDevFlags(uint8_t f){
  this->dev_flag = f;
  this->WriteDevFlags();
}

bool DeviceConfigClass::GetBL(void){
	return (this->GetDevFlags() & (1<<DEV_FLAG_BL_IVERTED));
}
void DeviceConfigClass::WriteNewBL(bool BL_STATUS){
	if (BL_STATUS == true){
		sbi(this->dev_flag, DEV_FLAG_BL_IVERTED);
	} else {
		cbi(this->dev_flag, DEV_FLAG_BL_IVERTED);
	}
	this->WriteDevFlags();
	BackLight.DefaultState();
}

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
  this->DeviceID = DID;
  ExternalEEPROMTWI::writeToDevice(0,0,1,&this->DeviceID);
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