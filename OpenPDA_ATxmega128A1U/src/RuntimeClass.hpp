/*
 * RuntimeClass.h
 *
 * Created: 09.10.2017 15:16:01
 *  Author: tabr
 */ 


#ifndef RUNTIMECLASS_H_
#define RUNTIMECLASS_H_

class RuntimeClass
  {
  public:
    enum RUNLEVELS
      {
      RUNLEVEL_JUST_STARTED,
      RUNLEVEL_0,
#ifndef LOAD_SOUNDS
      RUNLEVEL_1,
      RUNLEVEL_2,
      RUNLEVEL_3,
      RUNLEVEL_4,
      RUNLEVEL_5,
      RUNLEVEL_6,
      RUNLEVEL_PROGRAM_STARTED,
#endif //LOAD_SOUNDS
      RUNLEVELS_NUM,
      };

    static void Run(void);
    static void Level0(void);//XTAL
  protected:
  private:
#ifndef LOAD_SOUNDS
    static void Level1(void);//IO
    static void Level2(void);//Hardware
    static void Level3(void);//Tasks
    static void Level4(void);//Game load
    static void Level5(void);//GAME configure
    static void Level6(void);
    static void Level7(void);//main loop
#endif //LOAD_SOUNDS
    static void SetLevel(RUNLEVELS lvl);

    static RUNLEVELS CurrentLevel;
  };
RuntimeClass::RUNLEVELS RuntimeClass::CurrentLevel  = RuntimeClass::RUNLEVELS::RUNLEVEL_JUST_STARTED;


#endif /* RUNTIMECLASS_H_ */