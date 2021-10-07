/*
 * PDAMenu_AnomalyScanClass.hpp
 *
 * Created: 03.10.2021 12:21:45
 *  Author: tabr
 */ 


#ifndef PDAMENU_ANOMALYSCANCLASS_HPP_
#define PDAMENU_ANOMALYSCANCLASS_HPP_
class  PDAMenu_AnomalyScanClass : public PDAMenu_MainInterface
{
	public:
	void  Update(uint8_t  msPassed);
	void  JustSelected(void);
	PDAMenu_MainInterface::MENUIDS  getID(void);
	void  buttonPressed(ButtonsClass::BUTTONS  btn);
	bool  isSelectable(void){
		return  true;
	}
	bool  isUsable(void){
		return  false;
	}
	protected:
	private:
	uint8_t  position=0;
	uint8_t  PDANum=0;
	bool  txOn  =  false;
	bool  hackFirstTxPass  =  false;
	uint16_t  updateCounter=0;
	
};





#endif /* PDAMENU_ANOMALYSCANCLASS_HPP_ */