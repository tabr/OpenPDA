// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * hackableComputer.cpp
 *
 * Created: 2015-08-10 20:15:21
 *  Author: tabr
 */ 
#include "hackableComputer.hpp"
void HackableComputerClass::updateStatus(void)
	{
	this->sendRequest(1, HACK_COMMAND_GET_STATUS, 0, 0);
	if (isCRCMatch(this->data, PROTO_HACK_SIZE))
		{
		//return &this->data[PROTO_HACK_DATA_H];
		this->level		= this->data[PROTO_HACK_DATA_H];
		this->status	= this->data[PROTO_HACK_DATA_L];
		}
	else
		{
		//this->level
		this->setDisconnected();
		}
	//return NULL;
	}
/*void HackableComputerClass::tryToHack(uint8_t skillLevel)
	{
	this->sendRequest(1, HACK_COMMAND_TRY_TO_HACK, skillLevel, 0);
	//this->data[PROTO_HACK_DATA_H];
	_delay_ms(100);//ÕÀÊ ÁËßÄÜ!!!
	this->updateStatus();
	}*/
void HackableComputerClass::tryToHack(PlayerClass* pPlayer)
	{
	//this->tryToHack(pPlayer->getSkills()->getValue(PlayerSkillsClass::SKILL_COMPUTER));
	this->sendRequest(1, HACK_COMMAND_TRY_TO_HACK, pPlayer->GetSkills()->getValue(PlayerSkillsClass::SKILL_COMPUTER), 0);
	_delay_ms(100);//ÕÀÊ ÁËßÄÜ!!!
	this->updateStatus();
	}
void HackableComputerClass::sendRequest(uint8_t isHead, HACK_COMMANDS command, uint8_t dataH, uint8_t dataL)
	{
	//ArtefactsPortsHardwareClass* hardware	= ArtefactPorts.getHardware();
	this->data[PROTO_HACK_IS_HEAD]		= isHead;
	this->data[PROTO_HACK_COMMAND]		= command;
	this->data[PROTO_HACK_DATA_H]		= dataH;
	this->data[PROTO_HACK_DATA_L]		= dataL;
	updatePacketCRC(this->data, PROTO_HACK_SIZE);
	Player.GetArtefactPorts()->SetPortOut(ArtefactPortsClass::A_PORTS::A_PORT_0);
	for (uint8_t dataIDX=0;dataIDX<PROTO_HACK_SIZE;dataIDX++)
		{
		this->m_hardware->SPI_send(this->data[dataIDX]);
		_delay_us(10);
		}
	_delay_us(100);
	for (uint8_t dataIDX=0;dataIDX<PROTO_HACK_SIZE;dataIDX++)
		{
		this->data[dataIDX]	= this->m_hardware->SPI_send(0);
		_delay_us(10);
		}
	//#warning dirty hack!
	//_delay_ms(100);//ÁËßÄÜ!!!
	Player.GetArtefactPorts()->SetPortIn(ArtefactPortsClass::A_PORTS::A_PORT_0);
	}
void HackableComputerClass::setConnected(ArtefactsPortsHardwareClass* hardware)
	{
	this->m_hardware	= hardware;
	_delay_ms(100);//ÕÀÊ ÁËßÄÜ!!!
	this->updateStatus();
	}
void HackableComputerClass::setDisconnected(void)
	{
	this->m_hardware	= NULL;
	}
bool HackableComputerClass::isConnected(void)
	{
	return !(this->isDisconnected());
	}
bool HackableComputerClass::isDisconnected(void)
	{
	return (this->m_hardware == NULL);
	}
bool HackableComputerClass::haveAccess(void)
	{
	return (this->status & 1<<COMPUTER_STATUS_HACKED);
	}
uint8_t HackableComputerClass::getLevel(void)
	{
	return this->level;
	}
void HackableComputerClass::toggleSwitch(void)
	{
	if (this->isDisconnected())
		{
		return;
		}
	if (!(this->haveAccess()))
		{
		return;
		}
	this->sendRequest(1, HACK_COMMAND_TOGGLE_SWITCH, 0, 0);
	_delay_ms(100);//ÕÀÊ ÁËßÄÜ!!!
	this->updateStatus();
	}
bool HackableComputerClass::getSwitch(void)
	{
	return (this->status & 1<<COMPUTER_STATUS_SWITCH_ON);
	}

/*
uint8_t* HackableComputerClass::readItem(ArtefactsPortsHardwareClass* hardware)
	{
	//this->data[PROTO_HACK_IS_HEAD]		= M25P05_INSTRUCTION_READ_DATA_BYTES;
	hardware->SPI_send(M25P05_INSTRUCTION_READ_DATA_BYTES);
	_delay_us(5);
	hardware->SPI_send(0);
	_delay_us(5);
	hardware->SPI_send(0);
	_delay_us(5);
	hardware->SPI_send(0);
	_delay_us(5);
	
	this->data[PROTO_HACK_DATA_H]	= hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	//_delay_ms(1);
	hardware->SPI_send(0);
	
	return &this->data[PROTO_HACK_DATA_H];
	}
*/