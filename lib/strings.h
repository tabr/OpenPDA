/*
 * strings.h
 *
 * Created: 2015-03-29 15:59:13
 *  Author: tabr
 */ 


#ifndef STRINGS_H_
#define STRINGS_H_

//std::string str = "";

char RAM_STR_UNDEFINED[]                           = "[undefined]";
//char RAM_STR_None[]                           = "[None]";
//char RAM_STR_Unknown[]                        = " [неизвестно] ";
//char RAM_STR_NAME_UNNAMED[]                   = "без имени     ";
//char RAM_STR_FACTION_NO_FACTION[]             = "без фракции   ";
const static uint8_t TIME_FORMAT_LENGTH              = 8;


#ifdef LOAD_SOUNDS

const PROGMEM char STR_None[]                                 = "[None]";
const PROGMEM char STR_Unknown[]                              = " [неизвестно] ";
const PROGMEM char STR_NAME_UNNAMED[]                         = "без имени     ";
const PROGMEM char STR_FACTION_NO_FACTION[]                   = "без фракции   ";
const PROGMEM char STR_ItemTypeEmptyName[]                    = "(пусто)";
const PROGMEM char STR_ItemTypeMedicamentsName[]              = "медикаменты";
const PROGMEM char STR_ItemTypeResourcesName[]                = "ресурсы";
const PROGMEM char STR_ItemTypeSuiteName[]                    = "костюм";
const PROGMEM char STR_ItemTypeInformationName[]              = "информация";
const PROGMEM char STR_ItemTypeQuestName[]                    = "квест";
const PROGMEM char STR_ItemTypeElseName[]                     = "другое";
const PROGMEM char STR_ItemTypeComputerName[]                 = "компьютер";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_TYPE[]            = "тип           ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_SUBTYPE[]         = "субтип        ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_ID[]              = "ИД            ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_STATUS[]          = "статус        ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_EX0[]             = "EX0           ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_EX1[]             = "EX1           ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_EX2[]             = "EX2           ";
const PROGMEM char STR_CONNECTED_ITEM_STUCT_EX3[]             = "EX3           ";
const PROGMEM char STR_ARTEFACT[]                             = "Артефакт      ";
const PROGMEM char STR_ERROR[]                                = "ERROR         ";
const PROGMEM char STR_PDAMENU_LAST_MEET_ANOMALY[]            = "посл.аномалия:";
const PROGMEM char STR_PDAMENU_PLAYER[]                       = "игрок:        ";
const PROGMEM char STR_PDAMENU_SUITE[]                        = "костюм:       ";
const PROGMEM char STR_PDAMENU_ARTEFACTS_FORMAT[]             = "подкл.арт.(%01u):";
const PROGMEM char STR_PDAMENU_STATS[]                        = "статы:        ";
const PROGMEM char STR_PDAMENU_SETTINGS[]                     = "настройки:    ";
const PROGMEM char STR_PDAMENU_CONNECTED_ITEMS[]              = "подкл.предмет:";
const PROGMEM char STR_PDAMENU_QUESTS[]                       = "квесты:       ";
const PROGMEM char STR_PDAMENU_ACTIONS[]                      = "действия:     ";
const PROGMEM char STR_PDAMENU_ACTION_SUICIDE[]               = "суицид        ";
const PROGMEM char STR_PDAMENU_COMPUTER[]                     = "компьютер:    ";
const PROGMEM char STR_PDAMENU_EFFECTS[]                      = "эффекты:      ";
const PROGMEM char STR_PDAMENU_DEBUG[]                        = "DEBUG:)       ";
const PROGMEM char STR_PDAMENU_SKILLS[]                       = "умения:       ";
const PROGMEM char STR_PDAMENU_GAMES[]                        = "игры:         ";
const PROGMEM char STR_PDAMENU_SETTINGS_NIGHT_MODE[]          = "   ночн.режим ";
const PROGMEM char STR_PDAMENU_SETTINGS_SWITH_ART[]           = "   перекл.арт.";
const PROGMEM char STR_PDAMENU_SETTINGS_SWITH_ITEM[]          = "   перекл.итем";
const PROGMEM char STR_PDAMENU_SETTINGS_VIBRO[]               = "   вибро      ";
const PROGMEM char STR_PDAMENU_SETTINGS_RADIO[]               = "   радио      ";
const PROGMEM char STR_PDAMENU_SETTINGS_BACKLIGHT[]           = "   подсветка  ";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_LED[]             = "   свет арта  ";
const PROGMEM char STR_PDAMENU_QUESTS_STATUS_INCOMPLETE[]     = "[не выполнено]";
const PROGMEM char STR_PDAMENU_QUESTS_STATUS_COMPLETE[]       = "[выполнено]   ";
const PROGMEM char STR_PDAMENU_QUESTS_STATUS_FAILED[]         = "[провалено]   ";
const PROGMEM char STR_PDAMENU_QUESTS_STATUS_UNKNOWN[]        = "[не понятно]  ";
const PROGMEM char STR_PDAMENU_ADM_HALF_DEATH_TIME[]          = "Сокр.врем.смер";
const PROGMEM char STR_PDAMENU_ADM_REVIVE[]                   = "Воскрешалка   ";
const PROGMEM char STR_PDAMENU_ADM_TIME_TRANSMITTER[]         = "Синхр.времени ";
const PROGMEM char STR_PDAMENU_CONNECTED_ITEM_EMPTY[]         = "пусто         ";
const PROGMEM char STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_1[]   = "включать подс ";
const PROGMEM char STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_2[]   = "ветку при нажа";
const PROGMEM char STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_3[]   = "тии на кнопку ";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_INFO_1[]          = "переключаться ";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_INFO_2[]          = "к подключенном";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_INFO_3[]          = "у артефакту   ";
const PROGMEM char STR_PDAMENU_SETTINGS_ITEM_INFO_1[]         = "переключаться ";
const PROGMEM char STR_PDAMENU_SETTINGS_ITEM_INFO_2[]         = "к подключенным";
const PROGMEM char STR_PDAMENU_SETTINGS_ITEM_INFO_3[]         = "предметам     ";
const PROGMEM char STR_PDAMENU_SETTINGS_VIBRO_INFO_1[]        = "включает вибро";
const PROGMEM char STR_PDAMENU_SETTINGS_RADIO_INFO_1[]        = "включает радио";
const PROGMEM char STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_1[]    = "включает подсв";
const PROGMEM char STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_2[]    = "етку дисплея  ";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_LED_INFO_1[]      = "включает подсв";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_LED_INFO_2[]      = "етку артефакта";
const PROGMEM char STR_PDAMENU_SETTINGS_ART_LED_INFO_3[]      = "при подключени";
const PROGMEM char STR_PDAMENU_SETTINGS_SUICIDE_INFO_2[]      = "чтобы отменить";
const PROGMEM char STR_PDAMENU_SETTINGS_SUICIDE_INFO_3[]      = "нажми любую   ";
const PROGMEM char STR_PDAMENU_CONNECTED_ITEM_HELP_USE[]      = "исп - центр.кн";
const PROGMEM char STR_PDAMENU_GAMES_GAME_SNAKE[]             = " змейка";
const PROGMEM char STR_PDAMENU_GAMES_GAME_GTAVI[]             = " GTA VI";
const PROGMEM char STR_POINTER[]                              = ">";
const PROGMEM char STR_STAR[]                                 = "*";
const PROGMEM char STR_EFFECTS_SAFE_SHELTER[]                 = "убежище       ";
const PROGMEM char STR_EFFECTS_UNKNOWN[]                      = "неизвестный   ";
const PROGMEM char STR_EFFECTS_NONE[]                         = "    (нет)     ";
const PROGMEM char STR_Q_SWITH[]                              = "переключить?  ";
const PROGMEM char STR_PLUS_BRACKED[]                         = "[+]";
const PROGMEM char STR_MINUS_BRACKED[]                        = "[-]";
const PROGMEM char STR_COMP_ACCESS_DENIED[]                   = "ACCESS DENIED ";
const PROGMEM char STR_COMP_ACCESS_GRANTED[]                  = "ACCESS GRANTED";
const PROGMEM char STR_COMP_DISCONNECTED[]                    = "[DISCONNECTED]";
const PROGMEM char STR_COMP_Q_DO_HACK[]                       = "взломать?";
const PROGMEM char STR_COMP_TRYING[]                          = "trying...";
const PROGMEM char STR_PDAMENU_6ROW_STR_USE[]                 = "цнтр";
const PROGMEM char STR_NEXT_QUEST[]                           = "nextQuest";
const PROGMEM char STR_PDAMENU_6ROW_DOWN[]                    = "вниз";
const PROGMEM char STR_GO_GRAVEYARD_1[]                       = " следуйте на  ";
const PROGMEM char STR_GO_GRAVEYARD_2[]                       = " кладбище :)  ";
const PROGMEM char STR_QUEST_NUMS_FORMAT[]                    = "квест %03d(%03u)";
const PROGMEM char STR_QUEST_ID_FORMAT[]                      = "QID %03u";
const PROGMEM char STR_DEATH_TIME_REMAIN_FORMAT[]             = "%04uс";
const PROGMEM char STR_CONTAINERS_NUM_FORMAT[]                = "%d: ";
const PROGMEM char STR_MENU_CHARGES_FORMAT[]                  = "зарядов: %03u  ";
const PROGMEM char STR_MENU_PCS_FORMAT[]                      = "ед: %03u       ";
const PROGMEM char STR_MENU_DURABILITY_FORMAT[]               = "прочн:   %05u";
const PROGMEM char STR_MENU_QUEST_STATUS_FORMAT[]             = "статус: %s";
const PROGMEM char STR_SUICIDE_AFTER_FORMAT[]                 = "через %02d сек";
const PROGMEM char STR_MENU_DURABILITY_MAX_FORMAT[]           = "макс:    %05u";
const PROGMEM char STR_MENU_DURABILITY_PERCENT_FORMAT[]       = "   %s:      %03u";
const PROGMEM char STR_ID_FORMAT[]                            = "ID: %03d";
const PROGMEM char STR_DEVID_FORMAT[]                         = "DevID: %03d";
const PROGMEM char STR_TIME_FORMAT[]                          = "%02u:%02u:%02u";
const PROGMEM char STR_STAT_MAX_HP_FORMAT[]                   = "макс  ХП   %03u";
const PROGMEM char STR_STAT_REGEN_HP_FORMAT[]                 = "реген ХП   %03u";
const PROGMEM char STR_STAT_RAD_RESIST_FORMAT[]               = "сопр. рад  %03u";
const PROGMEM char STR_STAT_DEF_RAD_FORMAT[]                  = "защ. рад   %03u";
const PROGMEM char STR_STAT_DEF_FIRE_FORMAT[]                 = "защ. огонь %03u";
const PROGMEM char STR_STAT_DEF_CHEMICAL_FORMAT[]             = "защ. хим   %03u";
const PROGMEM char STR_STAT_DEF_BIO_FORMAT[]                  = "защ. био   %03u";
const PROGMEM char STR_STAT_DEF_ELECTRO_FORMAT[]              = "защ.электро%03u";
const PROGMEM char STR_STAT_DEF_GRAVY_FORMAT[]                = "защ. грави %03u";
const PROGMEM char STR_STAT_DEF_PSY_FORMAT[]                  = "защ. пси   %03u";
const PROGMEM char STR_SKILL_STRING_FORMAT[]                  = "%s%03u";
const PROGMEM char STR_LEVEL_FORMAT[]                         = "Level:  %03u";
const PROGMEM char STR_SECONDS_5_DIGITS_FORMAT[]              = "%05u сек";
const PROGMEM char STR_1_OF_2_FORMAT[]                        = "%03u/%03u";
const PROGMEM char STR_TIME_SYNC_AWAITING[]                   = "Синхр.время...";
const PROGMEM char STR_NON_PLAYABLE_TIME[]                    = "НеигровоеВремя";
const PROGMEM char STR_DEBUG_MEMFREE_FORMAT[]                 = "mem free:%04d";
const PROGMEM char STR_DEBUG_BATTERY_VOLTAGE_FORMAT[]         = "%04umv";
const PROGMEM char STR_DEBUG_3D_FORMAT[]                      = "%03d";
const PROGMEM char STR_DATE_DAY_FORMAT[]                      = "День:%u";
const PROGMEM char STR_DEBUG_4D_3D_FORMAT[]                   = "%04d %03d";
const PROGMEM char STR_OFF[]                                  = "OFF";
const PROGMEM char STR_ON[]                                   = "ON";
const PROGMEM char STR_GAMEOVER[]                             = "     GameOver";
const PROGMEM char STR_MASTER_TX_PLUS_FORMAT[]                = "%03u tx:+";
const PROGMEM char STR_MASTER_TX_MINUS_FORMAT[]               = "%03u tx:-";
const PROGMEM char STR_FORMAT_01U[]                           = "%01u";
const PROGMEM char STR_FORMAT_01D[]                           = "%01d";
const PROGMEM char STR_FORMAT_02U[]                           = "%02u";
const PROGMEM char STR_FORMAT_02D[]                           = "%02d";
const PROGMEM char STR_FORMAT_03U[]                           = "%03u";
const PROGMEM char STR_FORMAT_03D[]                           = "%03d";
const PROGMEM char STR_FORMAT_4x_03D[]                        = "%03d%03d %03d%03d";
const PROGMEM char STR_ERROR_RM0[]                            = "Error in RM0";
const PROGMEM char STR_MENU_SUIT_FORMAT[]                     = "%s(%01d)";





const static char* pos_array[]=
  {
  STR_None,
  STR_Unknown,
  STR_NAME_UNNAMED,
  STR_FACTION_NO_FACTION,
  STR_ItemTypeEmptyName,
  STR_ItemTypeMedicamentsName,
  STR_ItemTypeResourcesName,
  STR_ItemTypeSuiteName,
  STR_ItemTypeInformationName,
  STR_ItemTypeQuestName,
  STR_ItemTypeElseName,
  STR_ItemTypeComputerName,
  STR_CONNECTED_ITEM_STUCT_TYPE,
  STR_CONNECTED_ITEM_STUCT_SUBTYPE,
  STR_CONNECTED_ITEM_STUCT_ID,
  STR_CONNECTED_ITEM_STUCT_STATUS,
  STR_CONNECTED_ITEM_STUCT_EX0,
  STR_CONNECTED_ITEM_STUCT_EX1,
  STR_CONNECTED_ITEM_STUCT_EX2,
  STR_CONNECTED_ITEM_STUCT_EX3,
  STR_ARTEFACT,
  STR_ERROR,
  STR_PDAMENU_LAST_MEET_ANOMALY,
  STR_PDAMENU_PLAYER,
  STR_PDAMENU_SUITE,
  STR_PDAMENU_ARTEFACTS_FORMAT,
  STR_PDAMENU_STATS,
  STR_PDAMENU_SETTINGS,
  STR_PDAMENU_CONNECTED_ITEMS,
  STR_PDAMENU_QUESTS,
  STR_PDAMENU_ACTIONS,
  STR_PDAMENU_ACTION_SUICIDE,
  STR_PDAMENU_COMPUTER,
  STR_PDAMENU_EFFECTS,
  STR_PDAMENU_DEBUG,
  STR_PDAMENU_SKILLS,
  STR_PDAMENU_GAMES,
  STR_PDAMENU_SETTINGS_NIGHT_MODE,
  STR_PDAMENU_SETTINGS_SWITH_ART,
  STR_PDAMENU_SETTINGS_SWITH_ITEM,
  STR_PDAMENU_SETTINGS_VIBRO,
  STR_PDAMENU_SETTINGS_RADIO,
  STR_PDAMENU_SETTINGS_BACKLIGHT,
  STR_PDAMENU_SETTINGS_ART_LED,
  STR_PDAMENU_QUESTS_STATUS_INCOMPLETE,
  STR_PDAMENU_QUESTS_STATUS_COMPLETE,
  STR_PDAMENU_QUESTS_STATUS_FAILED,
  STR_PDAMENU_QUESTS_STATUS_UNKNOWN,
  STR_PDAMENU_ADM_HALF_DEATH_TIME,
  STR_PDAMENU_ADM_REVIVE,
  STR_PDAMENU_ADM_TIME_TRANSMITTER,
  STR_PDAMENU_CONNECTED_ITEM_EMPTY,
  STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_1,
  STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_2,
  STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_3,
  STR_PDAMENU_SETTINGS_ART_INFO_1,
  STR_PDAMENU_SETTINGS_ART_INFO_2,
  STR_PDAMENU_SETTINGS_ART_INFO_3,
  STR_PDAMENU_SETTINGS_ITEM_INFO_1,
  STR_PDAMENU_SETTINGS_ITEM_INFO_2,
  STR_PDAMENU_SETTINGS_ITEM_INFO_3,
  STR_PDAMENU_SETTINGS_VIBRO_INFO_1,
  STR_PDAMENU_SETTINGS_RADIO_INFO_1,
  STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_1,
  STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_2,
  STR_PDAMENU_SETTINGS_ART_LED_INFO_1,
  STR_PDAMENU_SETTINGS_ART_LED_INFO_2,
  STR_PDAMENU_SETTINGS_ART_LED_INFO_3,
  STR_PDAMENU_SETTINGS_SUICIDE_INFO_2,
  STR_PDAMENU_SETTINGS_SUICIDE_INFO_3,
  STR_PDAMENU_CONNECTED_ITEM_HELP_USE,
  STR_PDAMENU_GAMES_GAME_SNAKE,
  STR_PDAMENU_GAMES_GAME_GTAVI,
  STR_POINTER,
  STR_STAR,
  STR_EFFECTS_SAFE_SHELTER,
  STR_EFFECTS_UNKNOWN,
  STR_EFFECTS_NONE,
  STR_Q_SWITH,
  STR_PLUS_BRACKED,
  STR_MINUS_BRACKED,
  STR_COMP_ACCESS_DENIED,
  STR_COMP_ACCESS_GRANTED,
  STR_COMP_DISCONNECTED,
  STR_COMP_Q_DO_HACK,
  STR_COMP_TRYING,
  STR_PDAMENU_6ROW_STR_USE,
  STR_NEXT_QUEST,
  STR_PDAMENU_6ROW_DOWN,
  STR_GO_GRAVEYARD_1,
  STR_GO_GRAVEYARD_2,
  STR_QUEST_NUMS_FORMAT,
  STR_QUEST_ID_FORMAT,
  STR_DEATH_TIME_REMAIN_FORMAT,
  STR_CONTAINERS_NUM_FORMAT,
  STR_MENU_CHARGES_FORMAT,
  STR_MENU_PCS_FORMAT,
  STR_MENU_DURABILITY_FORMAT,
  STR_MENU_QUEST_STATUS_FORMAT,
  STR_SUICIDE_AFTER_FORMAT,
  STR_MENU_DURABILITY_MAX_FORMAT,
  STR_MENU_DURABILITY_PERCENT_FORMAT,
  STR_ID_FORMAT,
  STR_DEVID_FORMAT,
  STR_TIME_FORMAT,
  STR_STAT_MAX_HP_FORMAT,
  STR_STAT_REGEN_HP_FORMAT,
  STR_STAT_RAD_RESIST_FORMAT,
  STR_STAT_DEF_RAD_FORMAT,
  STR_STAT_DEF_FIRE_FORMAT,
  STR_STAT_DEF_CHEMICAL_FORMAT,
  STR_STAT_DEF_BIO_FORMAT,
  STR_STAT_DEF_ELECTRO_FORMAT,
  STR_STAT_DEF_GRAVY_FORMAT,
  STR_STAT_DEF_PSY_FORMAT,
  STR_SKILL_STRING_FORMAT,
  STR_LEVEL_FORMAT,
  STR_SECONDS_5_DIGITS_FORMAT,
  STR_1_OF_2_FORMAT,
  STR_TIME_SYNC_AWAITING,
  STR_NON_PLAYABLE_TIME,
  STR_DEBUG_MEMFREE_FORMAT,
  STR_DEBUG_BATTERY_VOLTAGE_FORMAT,
  STR_DATE_DAY_FORMAT,
  STR_DEBUG_4D_3D_FORMAT,
  STR_OFF,
  STR_ON,
  STR_GAMEOVER,
  STR_MASTER_TX_PLUS_FORMAT,
  STR_MASTER_TX_MINUS_FORMAT,
  STR_FORMAT_01U,
  STR_FORMAT_01D,
  STR_FORMAT_02U,
  STR_FORMAT_02D,
  STR_FORMAT_03U,
  STR_FORMAT_03D,
  STR_FORMAT_4x_03D,
  STR_ERROR_RM0,
  STR_MENU_SUIT_FORMAT
  };
#endif //LOAD_SOUNDS
enum STR_POS
  {
  STRPOS_STR_None,
  STRPOS_STR_Unknown,
  STRPOS_STR_NAME_UNNAMED,
  STRPOS_STR_FACTION_NO_FACTION,
  STRPOS_STR_ItemTypeEmptyName,
  STRPOS_STR_ItemTypeMedicamentsName,
  STRPOS_STR_ItemTypeResourcesName,
  STRPOS_STR_ItemTypeSuiteName,
  STRPOS_STR_ItemTypeInformationName,
  STRPOS_STR_ItemTypeQuestName,
  STRPOS_STR_ItemTypeElseName,
  STRPOS_STR_ItemTypeComputerName,
  STRPOS_STR_CONNECTED_ITEM_STUCT_TYPE,
  STRPOS_STR_CONNECTED_ITEM_STUCT_SUBTYPE,
  STRPOS_STR_CONNECTED_ITEM_STUCT_ID,
  STRPOS_STR_CONNECTED_ITEM_STUCT_STATUS,
  STRPOS_STR_CONNECTED_ITEM_STUCT_EX0,
  STRPOS_STR_CONNECTED_ITEM_STUCT_EX1,
  STRPOS_STR_CONNECTED_ITEM_STUCT_EX2,
  STRPOS_STR_CONNECTED_ITEM_STUCT_EX3,
  STRPOS_STR_ARTEFACT,
  STRPOS_STR_ERROR,
  STRPOS_STR_PDAMENU_LAST_MEET_ANOMALY,
  STRPOS_STR_PDAMENU_PLAYER,
  STRPOS_STR_PDAMENU_SUITE,
  STRPOS_STR_PDAMENU_ARTEFACTS_FORMAT,
  STRPOS_STR_PDAMENU_STATS,
  STRPOS_STR_PDAMENU_SETTINGS,
  STRPOS_STR_PDAMENU_CONNECTED_ITEMS,
  STRPOS_STR_PDAMENU_QUESTS,
  STRPOS_STR_PDAMENU_ACTIONS,
  STRPOS_STR_PDAMENU_ACTION_SUICIDE,
  STRPOS_STR_PDAMENU_COMPUTER,
  STRPOS_STR_PDAMENU_EFFECTS,
  STRPOS_STR_PDAMENU_DEBUG,
  STRPOS_STR_PDAMENU_SKILLS,
  STRPOS_STR_PDAMENU_GAMES,
  STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE,
  STRPOS_STR_PDAMENU_SETTINGS_SWITH_ART,
  STRPOS_STR_PDAMENU_SETTINGS_SWITH_ITEM,
  STRPOS_STR_PDAMENU_SETTINGS_VIBRO,
  STRPOS_STR_PDAMENU_SETTINGS_RADIO,
  STRPOS_STR_PDAMENU_SETTINGS_BACKLIGHT,
  STRPOS_STR_PDAMENU_SETTINGS_ART_LED,
  STRPOS_STR_PDAMENU_QUESTS_STATUS_INCOMPLETE,
  STRPOS_STR_PDAMENU_QUESTS_STATUS_COMPLETE,
  STRPOS_STR_PDAMENU_QUESTS_STATUS_FAILED,
  STRPOS_STR_PDAMENU_QUESTS_STATUS_UNKNOWN,
  STRPOS_STR_PDAMENU_ADM_HALF_DEATH_TIME,
  STRPOS_STR_PDAMENU_ADM_REVIVE,
  STRPOS_STR_PDAMENU_ADM_TIME_TRANSMITTER,
  STRPOS_STR_PDAMENU_CONNECTED_ITEM_EMPTY,
  STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_2,
  STRPOS_STR_PDAMENU_SETTINGS_NIGHT_MODE_INFO_3,
  STRPOS_STR_PDAMENU_SETTINGS_ART_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_ART_INFO_2,
  STRPOS_STR_PDAMENU_SETTINGS_ART_INFO_3,
  STRPOS_STR_PDAMENU_SETTINGS_ITEM_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_ITEM_INFO_2,
  STRPOS_STR_PDAMENU_SETTINGS_ITEM_INFO_3,
  STRPOS_STR_PDAMENU_SETTINGS_VIBRO_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_RADIO_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_BACKLIGHT_INFO_2,
  STRPOS_STR_PDAMENU_SETTINGS_ART_LED_INFO_1,
  STRPOS_STR_PDAMENU_SETTINGS_ART_LED_INFO_2,
  STRPOS_STR_PDAMENU_SETTINGS_ART_LED_INFO_3,
  STRPOS_STR_PDAMENU_SETTINGS_SUICIDE_INFO_2,
  STRPOS_STR_PDAMENU_SETTINGS_SUICIDE_INFO_3,
  STRPOS_STR_PDAMENU_CONNECTED_ITEM_HELP_USE,
  STRPOS_STR_PDAMENU_GAMES_GAME_SNAKE,
  STRPOS_STR_PDAMENU_GAMES_GAME_GTAVI,
  STRPOS_STR_POINTER,
  STRPOS_STR_STAR,
  STRPOS_STR_EFFECTS_SAFE_SHELTER,
  STRPOS_STR_EFFECTS_UNKNOWN,
  STRPOS_STR_EFFECTS_NONE,
  STRPOS_STR_Q_SWITH,
  STRPOS_STR_PLUS_BRACKED,
  STRPOS_STR_MINUS_BRACKED,
  STRPOS_STR_COMP_ACCESS_DENIED,
  STRPOS_STR_COMP_ACCESS_GRANTED,
  STRPOS_STR_COMP_DISCONNECTED,
  STRPOS_STR_COMP_Q_DO_HACK,
  STRPOS_STR_COMP_TRYING,
  STRPOS_STR_PDAMENU_6ROW_STR_USE,
  STRPOS_STR_NEXT_QUEST,
  STRPOS_STR_PDAMENU_6ROW_DOWN,
  STRPOS_STR_GO_GRAVEYARD_1,
  STRPOS_STR_GO_GRAVEYARD_2,
  STRPOS_STR_QUEST_NUMS_FORMAT,
  STRPOS_STR_QUEST_ID_FORMAT,
  STRPOS_STR_DEATH_TIME_REMAIN_FORMAT,
  STRPOS_STR_CONTAINERS_NUM_FORMAT,
  STRPOS_STR_MENU_CHARGES_FORMAT,
  STRPOS_STR_MENU_PCS_FORMAT,
  STRPOS_STR_MENU_DURABILITY_FORMAT,
  STRPOS_STR_MENU_QUEST_STATUS_FORMAT,
  STRPOS_STR_SUICIDE_AFTER_FORMAT,
  STRPOS_STR_MENU_DURABILITY_MAX_FORMAT,
  STRPOS_STR_MENU_DURABILITY_PERCENT_FORMAT,
  STRPOS_STR_ID_FORMAT,
  STRPOS_STR_DEVID_FORMAT,
  STRPOS_STR_TIME_FORMAT,
  STRPOS_STR_STAT_MAX_HP_FORMAT,
  STRPOS_STR_STAT_REGEN_HP_FORMAT,
  STRPOS_STR_STAT_RAD_RESIST_FORMAT,
  STRPOS_STR_STAT_DEF_RAD_FORMAT,
  STRPOS_STR_STAT_DEF_FIRE_FORMAT,
  STRPOS_STR_STAT_DEF_CHEMICAL_FORMAT,
  STRPOS_STR_STAT_DEF_BIO_FORMAT,
  STRPOS_STR_STAT_DEF_ELECTRO_FORMAT,
  STRPOS_STR_STAT_DEF_GRAVY_FORMAT,
  STRPOS_STR_STAT_DEF_PSY_FORMAT,
  STRPOS_STR_SKILL_STRING_FORMAT,
  STRPOS_STR_LEVEL_FORMAT,
  STRPOS_STR_SECONDS_5_DIGITS_FORMAT,
  STRPOS_STR_1_OF_2_FORMAT,
  STRPOS_STR_TIME_SYNC_AWAITING,
  STRPOS_STR_NON_PLAYABLE_TIME,
  STRPOS_STR_DEBUG_MEMFREE_FORMAT,
  STRPOS_STR_DEBUG_BATTERY_VOLTAGE_FORMAT,
  STRPOS_STR_DATE_DAY_FORMAT,
  STRPOS_STR_DEBUG_4D_3D_FORMAT,
  STRPOS_STR_OFF,
  STRPOS_STR_ON,
  STRPOS_STR_GAMEOVER,
  STRPOS_STR_MASTER_TX_PLUS_FORMAT,
  STRPOS_STR_MASTER_TX_MINUS_FORMAT,
  STRPOS_STR_FORMAT_01U,
  STRPOS_STR_FORMAT_01D,
  STRPOS_STR_FORMAT_02U,
  STRPOS_STR_FORMAT_02D,
  STRPOS_STR_FORMAT_03U,
  STRPOS_STR_FORMAT_03D,
  STRPOS_STR_FORMAT_4x_03D,
  STRPOS_STR_ERROR_RM0,
  STRPOS_STR_MENU_SUIT_FORMAT,
  STRPOS_SIZE
  };



#include "stdarg.h"
class STRClass
  {
  public:
    enum STR_LOCATION
      {
      STR_LOCATION_OUTSIDE_BUFFER,
      STR_LOCATION_INSIDE_BUFFER,
      };
    const static uint8_t MAX_STR_LENGTH=30;
    const static uint8_t STORAGE_DATA_WIDTH=32;
    STRClass(char* ext_str)//should not call any Write.. methods
      {
      this->Clean();
      this->SetExternalBuffer(ext_str);
      this->str_loc     = STR_LOCATION_INSIDE_BUFFER;
      }
    STRClass(STR_POS pos)
      {
      this->Clean();
      this->SetPos(pos);
      }
    STRClass(void)
      {
      this->Clean();
      }
    void SetPos(STR_POS pos)
      {
      this->current_pos = pos;
      this->str_loc     = STR_LOCATION_OUTSIDE_BUFFER;
      }
    void WriteTo(char* buffer);
    void WritePgmTo(char* buffer);
    void WriteFormat(char* buffer, ...)
      {
      if (this->str_loc == STR_LOCATION_INSIDE_BUFFER)
        {
        return;
        }
      //this->SetExternalBuffer(buffer);
      //STRClass Str(format_pos);
      char format[STORAGE_DATA_WIDTH];
      memset(format, 0, sizeof(format));
      this->WriteTo(format);
      va_list ap;

      va_start(ap, buffer);
      //это вместо fprintf
      vsprintf(buffer, format, ap);
      //vsprintf(buffer, "%03u", ap);
      va_end(ap);
      this->SetExternalBuffer(buffer);
      this->str_loc     = STR_LOCATION_INSIDE_BUFFER;
      }
    void SetExternalBuffer(char* buffer)
      {
      this->external_buffer = buffer;
      this->str_loc     = STR_LOCATION_OUTSIDE_BUFFER;
      }
    char* Get(void)
      {
      return this->external_buffer;
      }
  protected:
  private:
    void Clean(void);
    STR_POS current_pos;
    char* external_buffer;
    STR_LOCATION str_loc;
  };
typedef STRClass ItemTypeName_t;
#endif /* STRINGS_H_ */