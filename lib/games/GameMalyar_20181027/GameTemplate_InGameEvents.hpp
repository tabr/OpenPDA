#ifndef GAME_TAMPLE_INGAMEEVENTS_H
#define GAME_TAMPLE_INGAMEEVENTS_H

//InGameEvents.registerNew(16,00,       16,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
//InGameEvents.registerNew(19,00,       19,29,      EVENT_PERIOD_ONE_SEC, RadStormEvent);
InGameEvents.registerNew(16,00,       16,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
InGameEvents.registerNew(20,00,       20,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
#ifndef MASTER_PDA
InGameEvents.registerNew(00,00,       11,59,      EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+0),00,   (24+9),59,  EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+14),00,  0xFF, 59,   EVENT_PERIOD_ONE_SEC, SleepEvent);
#endif

#endif