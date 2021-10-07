#ifndef GAME_TAMPLE_INGAMEEVENTS_H
#define GAME_TAMPLE_INGAMEEVENTS_H

//InGameEvents.registerNew(16,00,       16,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
//InGameEvents.registerNew(19,00,       19,29,      EVENT_PERIOD_ONE_SEC, RadStormEvent);
InGameEvents.registerNew(16,55,       16,59,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
InGameEvents.registerNew(17,00,       17,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
InGameEvents.registerNew(21,55,       21,59,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
InGameEvents.registerNew(22,00,       22,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
#ifndef MASTER_PDA
InGameEvents.registerNew(00,00,       9,59,      EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+2),00,  9, 59,   EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+15),00,  0xFF, 59,   EVENT_PERIOD_ONE_SEC, SleepEvent);
#endif

#endif