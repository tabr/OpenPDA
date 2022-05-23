#ifndef GAME_TAMPLE_INGAMEEVENTS_H
#define GAME_TAMPLE_INGAMEEVENTS_H

//InGameEvents.registerNew(16,00,       16,29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
//InGameEvents.registerNew(19,00,       19,29,      EVENT_PERIOD_ONE_SEC, RadStormEvent);
InGameEvents.registerNew((24+20),55,       (24+20),59,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
InGameEvents.registerNew((24+21),00,       (24+21),29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
InGameEvents.registerNew((48+0),55,        (48+0),59,       EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
InGameEvents.registerNew((48+1),00,        (24+1),29,       EVENT_PERIOD_ONE_SEC, BlowoutEvent);
//InGameEvents.registerNew((24+21),55,       (21+18),59,      EVENT_PERIOD_ONE_SEC, BlowoutPrepareEvent);
//InGameEvents.registerNew((24+22),00,       (22+19),29,      EVENT_PERIOD_ONE_SEC, BlowoutEvent);
#ifndef MASTER_PDA
InGameEvents.registerNew(00,00,				19,59,			EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+2),00,			9, 59,			EVENT_PERIOD_ONE_SEC, SleepEvent);
InGameEvents.registerNew((24+24+14),00,		0xFF, 59,		EVENT_PERIOD_ONE_SEC, SleepEvent);
#endif

#endif