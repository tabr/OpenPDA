#ifndef GAME_TAMPLE_INGAMEEVENTS_H
#define GAME_TAMPLE_INGAMEEVENTS_H
//do not sleep!
//InGameEvents.registerNew(13,30,       13,59,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
//InGameEvents.registerNew(13,25,       13,29,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);

InGameEvents.registerNew(16,20,       16,29,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
InGameEvents.registerNew(16,30,       19,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
//#ifndef MASTER_PDA
InGameEvents.registerNew(00,00,		  8,    59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+2),30,	(24+7), 59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+12),00,  0xFF, 59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
//#endif

#endif