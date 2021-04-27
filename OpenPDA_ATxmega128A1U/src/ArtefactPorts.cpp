// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "ArtefactPorts.hpp"
/*
void ArtefactPortsClass::ArtefactPortsClassTask1::Task(void)
	{
	((ArtefactPortsClass*)this->GetLinkedObject())->scanForConnected();
	//ArtefactPorts.scanForConnected();
	}
void ArtefactPortsClass::ArtefactPortsClassTask2::Task(void)
	{
	//ArtefactPorts.ledFlashProcess();
	((ArtefactPortsClass*)this->GetLinkedObject())->ledFlashProcess();
	}*/
void ArtefactPortsClass::IOInit(void)
	{
	this->m_Hardware.IOInit();
	}
void ArtefactPortsClass::TimerUpdateEvent (uint8_t msPassed)
	{
	static uint16_t scanForConnected_msCounter=0;
	static uint16_t ledFlashProcess_msCounter=0;
	
	scanForConnected_msCounter+=msPassed;
	ledFlashProcess_msCounter+=msPassed;
	
	if (scanForConnected_msCounter >= 40)
		{
		scanForConnected_msCounter	-=40;
		this->scanForConnected();
		}
	if (ledFlashProcess_msCounter >= 100)
		{
		ledFlashProcess_msCounter	-=100;
		this->ledFlashProcess();
		}
	}
ArtefactPortsClass::ArtefactPortsClass(void)
	{
	for (uint8_t i=0;i<ArtefactsPortsHardwareClass::MAX_SLOTS;i++)
		{
		/*
		HAL.IO.SetDirOut(HW_SLOT_ARTEFACT_LEDS_PIN_START + i);	//выход
		HAL.IO.SetOutLow(HW_SLOT_ARTEFACT_LEDS_PIN_START + i);	//нуль на выходе
		HAL.IO.SetDirIn(HW_SLOT_CHIPS_SELECT_PIN_START + i);	//вход
		HAL.IO.SetOutLow(HW_SLOT_CHIPS_SELECT_PIN_START + i);	//нуль на выходе
		HAL.IO.SetPullDown(HW_SLOT_CHIPS_SELECT_PIN_START + i);//подтяжка к низу
		*/
		this->m_ledFlashCounters[i]				= 0;
		this->m_artefactsConnected[i].disconnect();
		}
	//this->TaskScanForConnected.SetLinkedObject(this);
	//this->TaskLedFlashProcess.SetLinkedObject(this);
	
//	memset(this->ledFlashCounters,0, this->MAX_SLOTS);
//	this->m_settingsSelected	= 0;
//	this->SPI_init();
	this->ArtefactHardware[A_PORT_0]	= &Artefact00;
	this->ArtefactHardware[A_PORT_1]	= &Artefact01;
	this->ArtefactHardware[A_PORT_2]	= &Artefact02;
	this->ArtefactHardware[A_PORT_3]	= &Artefact03;
	this->ArtefactHardware[A_PORT_4]	= &Artefact04;
  memset(this->m_lastArtefact, 0, sizeof(this->m_lastArtefact));
	}
/*

void ArtefactPortsClass::M25P05_wholeItemWrite(uint8_t pin, uint8_t *item)
	{
	this->newActivatePort(pin);
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_WRITE_ENABLE);
	this->newDeactivatePort(pin);
	//нужна ли задержка? по даташиту до 15 мс, но без этого, вроде, работает...
	_delay_us(15);
	this->newActivatePort(pin);
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_PAGE_PROGRAM);
	this->m_Hardware.SPI_send(this->ADDRESS_HEAD_H);
	this->m_Hardware.SPI_send(this->ADDRESS_HEAD_M);
	this->m_Hardware.SPI_send(this->ADDRESS_HEAD_L);
	this->m_Hardware.SPI_send(item[0]);
	this->m_Hardware.SPI_send(item[1]);
	this->m_Hardware.SPI_send(item[2]);
	this->m_Hardware.SPI_send(item[3]);
	this->m_Hardware.SPI_send(item[4]);
	this->m_Hardware.SPI_send(item[5]);
	this->m_Hardware.SPI_send(item[6]);
	this->m_Hardware.SPI_send(item[7]);
	this->newDeactivatePort(pin);
	}
uint8_t ArtefactPortsClass::M25P05_Read_DataByteNoActivate(uint8_t H,uint8_t M, uint8_t L)
	{
	uint8_t tmp;
	//			M25P05_ACTIVATE;
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_READ_DATA_BYTES);
	this->m_Hardware.SPI_send(H);
	this->m_Hardware.SPI_send(M);
	this->m_Hardware.SPI_send(L);
	tmp	= this->m_Hardware.SPI_send(0);
	//			M25P05_DEACTIVATE;
	return tmp;
	}
uint8_t ArtefactPortsClass::M25P05_Read_Status_Register(uint8_t pin)
	{
	uint8_t tmp;
	this->newActivatePort(pin);
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_READ_STATUS_REGISTER);
	tmp	= this->m_Hardware.SPI_send(0);
	this->newDeactivatePort(pin);
	return tmp;
	}
bool ArtefactPortsClass::M25P05_isWriteInProgress (uint8_t pin)
	{
	return (this->M25P05_Read_Status_Register(pin) & 1);
	}
void ArtefactPortsClass::M25P05_BulkErase(uint8_t pin)
	{
	this->newActivatePort(pin);
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_WRITE_ENABLE);
	this->newDeactivatePort(pin);
	_delay_us(15);
	this->newActivatePort(pin);
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_BULK_ERASE);
	this->newDeactivatePort(pin);
	while((this->M25P05_Read_Status_Register(pin) & 1) != 0);
	}
*/
void ArtefactPortsClass::readActivatedItem(void)
	{
	//			M25P05_ACTIVATE;
	this->m_Hardware.SPI_send(M25P05_INSTRUCTION_READ_DATA_BYTES);
	_delay_us(5);
	this->m_Hardware.SPI_send(this->ADDRESS_HEAD_H);
	_delay_us(5);
	this->m_Hardware.SPI_send(this->ADDRESS_HEAD_M);
	_delay_us(5);
	this->m_Hardware.SPI_send(this->ADDRESS_HEAD_L);
	_delay_us(5);
	this->m_lastArtefact[0]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[1]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[2]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[3]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[4]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[5]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[6]			= this->m_Hardware.SPI_send(0);
	this->m_lastArtefact[7]			= this->m_Hardware.SPI_send(0);
	//			M25P05_DEACTIVATE;
	}

void ArtefactPortsClass::ledFlashProcess(void)
	{
	for (uint8_t currentLedPin=0;currentLedPin<ArtefactsPortsHardwareClass::MAX_SLOTS;currentLedPin++)
		{
		if (this->m_ledFlashCounters[currentLedPin] > 0)
			{
			//HAL.IO.SetOutToggle(HW_SLOT_ARTEFACT_LEDS_PIN_START + currentLedPin);
			this->newLEDToggle(static_cast<A_PORTS>(currentLedPin));
			if (--this->m_ledFlashCounters[currentLedPin] == 0)
				{
				if (PDASettings.isParameterSet(ConfigClass::SETTINGS_ARTEFACTS_LEDS_ON))
					{
					//HAL.IO.SetOutHigh(HW_SLOT_ARTEFACT_LEDS_PIN_START + currentLedPin);
					this->newLEDOn(static_cast<A_PORTS>(currentLedPin));
					}
				else
					{
					//HAL.IO.SetOutLow(HW_SLOT_ARTEFACT_LEDS_PIN_START + currentLedPin);
					this->newLEDOff(static_cast<A_PORTS>(currentLedPin));
					}
				}
			}
		}
	}
void ArtefactPortsClass::scanForConnectedIfNeed(void)
{
	//TODO
}
void ArtefactPortsClass::scanForConnected(void)
	{

//	uint8_t selectPortLocal;
//	uint8_t currentLedPin;
//	uint8_t tmp;

	if (Player.IsDead())//мёртвые не используют артефакты
		{
		//while(1);
		return;
		}
	
	for (uint8_t selectedPort=0;selectedPort<Player.GetSuit()->getContainersNum();selectedPort++)
		{
		if (this->newIsSomethingConnectedTo(selectedPort))
			{
			if (this->m_artefactsConnected[selectedPort].isEmpty())//не было, подключили
				{
				this->SetPortOut(selectedPort);
//				if (selectedPort == 0)
//					{
//					ArtefactsPinSS00::SetOutLow();
//					_delay_ms(1);
//					}
				//while(1)
//					{BackLight.turnON();_delay_ms(100);BackLight.turnOFF();_delay_ms(100);};
				//this->readActivatedItem();
				this->ArtefactHardware[selectedPort]->ReadData(m_lastArtefact, this->ARTEFACT_FLASH_DATA_LENGTH);
//				if (selectedPort == 0)
//					{
//					ArtefactsPinSS00::SetOutHigh();
//					}
						
				this->SetPortIn(selectedPort);
						
				if (this->m_lastArtefact[this->FLASHDATA_ARTEFACT_TYPE] == this->ITEM_TYPE_ARTEFACT)//кагбэ и не нужен этот if
					{
					if (PDASettings.isParameterSet(ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ARTEFACT))
						{
						PDAMenu.SelectMenu(PDAMenu_MainInterface::MENUID_ARTEFACTS_CONNECTED);
						}
					ArtefactID_t AID	= this->m_lastArtefact[this->FLASHDATA_ARTEFACT_ID];
					if (Artefact.isArtefactValid(AID))
						{
						this->m_ledFlashCounters[selectedPort]	= this->LED_FLASH_COUNTER;												//начинаю мигание
						this->m_artefactsConnected[selectedPort].setArtefactRAW(AID);	//задаю артефакт
						this->m_artefactsConnected[selectedPort].connect();
						//Player.GetEffects()->applyEffect(AID, static_cast<PlayerEffectsOldClass::EFFECT_SOURCE>(selectedPort));					//применяю эффект
						}
					}
				else if (this->m_lastArtefact[this->FLASHDATA_ARTEFACT_TYPE] == UsableItemClass::ITEM_TYPE_COMPUTER)
					{
					//this->m_artefactsConnected[currentLedPin].setArtefactRAW(UsableItemClass::ITEM_TYPE_COMPUTER);	//задаю артефакт
					//this->m_artefactsConnected[currentLedPin].connect();
					HackableComputer.setConnected(&this->m_Hardware);
					if (PDASettings.isParameterSet(ConfigClass::SETTINGS_SWITCH_TO_CONNECTED_ARTEFACT))
						{
						PDAMenu.SelectMenu(PDAMenu_MainInterface::MENUID_COMPUTER_HACK);
						}
					}
				}
			}
		else //низкий уровень - флешка отсуствует
			{
			if (this->m_artefactsConnected[selectedPort].isNotEmpty())//был подключен, отключили
				{
				//Player.GetEffects()->removeFromPool(selectedPort);
				this->newLEDOff(static_cast<A_PORTS>(selectedPort));
				this->m_artefactsConnected[selectedPort].disconnect();
				this->m_ledFlashCounters[selectedPort]	= 0;
				}
			}
		}
	}
void ArtefactPortsClass::HardwareInitialization(void)
	{
	this->m_Hardware.HardwareInitialization();
	}
ArtefactsPortsHardwareClass* ArtefactPortsClass::GetHardware(void)
	{
	return &this->m_Hardware;
	}
ArtefactClass* ArtefactPortsClass::GetConnectedArtefact(uint8_t pos)
	{
	if (pos >= ArtefactsPortsHardwareClass::MAX_SLOTS)
		{
		pos	= (ArtefactsPortsHardwareClass::MAX_SLOTS - 1);
		}
	return &this->m_artefactsConnected[pos];
	}
void ArtefactPortsClass::newLEDOff(A_PORTS a_port)
	{
	switch (a_port)
		{
		case A_PORT_0:
			{
			ArtefactsPinLED00::SetOutLow();
			}
		break;
		case A_PORT_1:
			{
			ArtefactsPinLED01::SetOutLow();
			}
		break;
		case A_PORT_2:
			{
			ArtefactsPinLED02::SetOutLow();
			}
		break;
		case A_PORT_3:
			{
			ArtefactsPinLED03::SetOutLow();
			}
		break;
		case A_PORT_4:
			{
			ArtefactsPinLED04::SetOutLow();
			}
		break;
		case A_PORTS_NUM://hack
		default:
			{
			
			}
		break;
		}
	}
void ArtefactPortsClass::newLEDOn(A_PORTS a_port)
	{
	switch (a_port)
		{
		case A_PORT_0:
			{
			ArtefactsPinLED00::SetOutHigh();
			}
		break;
		case A_PORT_1:
			{
			ArtefactsPinLED01::SetOutHigh();
			}
		break;
		case A_PORT_2:
			{
			ArtefactsPinLED02::SetOutHigh();
			}
		break;
		case A_PORT_3:
			{
			ArtefactsPinLED03::SetOutHigh();
			}
		break;
		case A_PORT_4:
			{
			ArtefactsPinLED04::SetOutHigh();
			}
		break;
		case A_PORTS_NUM://hack
		default:
			{
			
			}
		break;
		}
	}
void ArtefactPortsClass::newLEDToggle(A_PORTS a_port)
	{
	switch (a_port)
		{
		case A_PORT_0:
			{
			ArtefactsPinLED00::SetOutToggle();
			}
		break;
		case A_PORT_1:
			{
			ArtefactsPinLED01::SetOutToggle();
			}
		break;
		case A_PORT_2:
			{
			ArtefactsPinLED02::SetOutToggle();
			}
		break;
		case A_PORT_3:
			{
			ArtefactsPinLED03::SetOutToggle();
			}
		break;
		case A_PORT_4:
			{
			ArtefactsPinLED04::SetOutToggle();
			}
		break;
		case A_PORTS_NUM://hack
		default:
			{
			
			}
		break;
		}
	}
void ArtefactPortsClass::SetPortOut(A_PORTS a_port)
	{
	switch (a_port)
		{
		case A_PORT_0:
			{
			ArtefactsPinSS00::SetDirOut();
//			ArtefactsPinSS00::SetOutLow();
			}
		break;
		case A_PORT_1:
			{
			ArtefactsPinSS01::SetDirOut();
//			ArtefactsPinSS01::SetOutLow();
			}
		break;
		case A_PORT_2:
			{
			ArtefactsPinSS02::SetDirOut();
//			ArtefactsPinSS02::SetOutLow();
			}
		break;
		case A_PORT_3:
			{
			ArtefactsPinSS03::SetDirOut();
//			ArtefactsPinSS03::SetOutLow();
			}
		break;
		case A_PORT_4:
			{
			ArtefactsPinSS04::SetDirOut();
//			ArtefactsPinSS04::SetOutLow();
			}
		break;
		case A_PORTS_NUM://hack
		default:
			{
			
			}
		break;
		}
	}
void ArtefactPortsClass::SetPortIn(A_PORTS a_port)
	{
	switch (a_port)
		{
		case A_PORT_0:
			{
//			ArtefactsPinSS00::SetOutHigh();
			ArtefactsPinSS00::SetDirIn();
			}
		break;
		case A_PORT_1:
			{
//			ArtefactsPinSS01::SetOutHigh();
			ArtefactsPinSS01::SetDirIn();
			}
		break;
		case A_PORT_2:
			{
//			ArtefactsPinSS02::SetOutHigh();
			ArtefactsPinSS02::SetDirIn();
			}
		break;
		case A_PORT_3:
			{
//			ArtefactsPinSS03::SetOutHigh();
			ArtefactsPinSS03::SetDirIn();
			}
		break;
		case A_PORT_4:
			{
//			ArtefactsPinSS04::SetOutHigh();
			ArtefactsPinSS04::SetDirIn();
			}
		break;
		case A_PORTS_NUM://hack
		default:
			{
			
			}
		break;
		}
	}
void ArtefactPortsClass::SetPortOut(uint8_t portNum)
	{
	this->SetPortOut(static_cast<A_PORTS>(portNum));
	}
void ArtefactPortsClass::SetPortIn(uint8_t portNum)
	{
	this->SetPortIn(static_cast<A_PORTS>(portNum));
	}
bool ArtefactPortsClass::newIsSomethingConnectedTo(uint8_t portNum)
	{
	switch (portNum)
		{
		case A_PORT_0:
			{
			return ArtefactsPinSS00::IsPinHigh();
			}
		break;
		case A_PORT_1:
			{
			return ArtefactsPinSS01::IsPinHigh();
			}
		break;
		case A_PORT_2:
			{
			return ArtefactsPinSS02::IsPinHigh();
			}
		break;
		case A_PORT_3:
			{
			return ArtefactsPinSS03::IsPinHigh();
			}
		break;
		case A_PORT_4:
			{
			return ArtefactsPinSS04::IsPinHigh();
			}
		break;
		}
	return false;
	}





/////////////////////////////////////////////////////////////////////////////

#ifdef HUINYA_STARAYA
void ArtefactPortsClass::activateFlashChip(uint8_t pin)
	{
	//sbi(HW_SLOT_CHIPS_SELECT_PORT.DIR,		pin);//выход
	//HW_SLOT_CHIPS_SELECT_PORT.DIRSET		= 1<<pin;
	HAL.IO.SetDirOut(HW_SLOT_CHIPS_SELECT_PIN_START + pin);
	//_delay_us(1);
	//asm ("nop");
	//cbi(HW_SLOT_CHIPS_SELECT_PORT.OUT, pin);//активирую...
	//HW_SLOT_CHIPS_SELECT_PORT.OUTCLR		= 1<<pin;
	HAL.IO.SetOutLow(HW_SLOT_CHIPS_SELECT_PIN_START + pin);
	}
void ArtefactPortsClass::deactivateFlashChip(uint8_t pin)
	{
	//sbi(HW_SLOT_CHIPS_SELECT_PORT.OUT,		pin);
	//HW_SLOT_CHIPS_SELECT_PORT.OUTSET		= 1<<pin;
	HAL.IO.SetOutHigh(HW_SLOT_CHIPS_SELECT_PIN_START + pin);
	//						cbi(HW_SLOT_CHIPS_SELECT_PORT.OUT,		currentLedPin);//к земле
	//cbi(HW_SLOT_CHIPS_SELECT_PORT.DIR,		pin);//вход
	//HW_SLOT_CHIPS_SELECT_PORT.DIRCLR		= 1<<pin;
	HAL.IO.SetDirIn(HW_SLOT_CHIPS_SELECT_PIN_START + pin);
	//			_delay_us(1);//в общем-то не нужна...
	}
#endif
