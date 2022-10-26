#ifndef GAME_TAMPLE_INGAMEEVENTS_H
#define GAME_TAMPLE_INGAMEEVENTS_H

InGameEvents.registerNew(13,30,       13,59,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
InGameEvents.registerNew(13,25,       13,29,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
InGameEvents.registerNew(17,00,       17,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
InGameEvents.registerNew(16,55,       16,59,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
#ifndef MASTER_PDA
InGameEvents.registerNew(00,00,		  9,    59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+4),00,	  0xFF, 59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
#endif

#endif