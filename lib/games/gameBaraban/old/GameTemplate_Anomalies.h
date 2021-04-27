#ifndef GAME_ANOMALIES_H
#define GAME_ANOMALIES_H
	#ifdef DEBUG_BUILD
		LcdStringUpdate(1,LCD_LINE_2, (char*)"Anomalies     ");
	#endif
	Anomaly.setAnomaliesNum(6);
	//	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_NONE,		(char*)"(���)",			DamageClass::DAMAGE_SOURCE_NONE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_JARKA,		(char*)"�����",			DamageClass::DAMAGE_SOURCE_FIRE);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_ELECTRA,	(char*)"�������",		DamageClass::DAMAGE_SOURCE_ELECTRICITY);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_HOLODEC,	(char*)"�������",		DamageClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_KISEL,		(char*)"������",		DamageClass::DAMAGE_SOURCE_CHEMICAL);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_KARUSEL,	(char*)"��������",		DamageClass::DAMAGE_SOURCE_GRAVY);
	Anomaly.registerNew(TemporaryClass::ANOMALY_TYPE_TRAMPLIN,	(char*)"��������",		DamageClass::DAMAGE_SOURCE_GRAVY);
#endif
