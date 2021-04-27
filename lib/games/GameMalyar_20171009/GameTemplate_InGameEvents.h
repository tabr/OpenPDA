#ifndef GAME_TAMPLE_INGAMEEVENTS_H
#define GAME_TAMPLE_INGAMEEVENTS_H

InGameEvents.registerNew(20,00,			20,59,			EVENT_PERIOD_ONE_SEC, BlowoutEvent);
#ifndef MASTER_PDA
InGameEvents.registerNew(00,00,			13,59,			EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+1),00,		(24+8),59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+13),00,	0xFF, 59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
#endif
#endif