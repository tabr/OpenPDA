#ifndef GAMETEMPLATE_ANOMALIES_H_
#define GAMETEMPLATE_ANOMALIES_H_
	
	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Anomalies     ");
	#endif
	Anomaly.setAnomaliesNum(6);
	//	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_NONE,		(char*)"(нет)",			DamageClass::DAMAGE_SOURCE_NONE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_ID_JARKA,		(char*)"жарка",			TemporaryClass::DAMAGE_SOURCE_FIRE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_ID_ELECTRA,		(char*)"электра",		TemporaryClass::DAMAGE_SOURCE_ELECTRICITY);
	Anomaly.registerNew(TemporaryClass::ANOMALY_ID_HOLODEC,		(char*)"холодец",		TemporaryClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_ID_KISEL,		(char*)"кисель",		TemporaryClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_ID_KARUSEL,		(char*)"карусель",		TemporaryClass::DAMAGE_SOURCE_GRAVY);
	Anomaly.registerNew(TemporaryClass::ANOMALY_ID_TRAMPLIN,	(char*)"трамплин",		TemporaryClass::DAMAGE_SOURCE_GRAVY);
#endif //GAMETEMPLATE_ANOMALIES_H_