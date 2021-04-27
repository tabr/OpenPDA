#ifndef  EVENT_SYSTEM_CLASS_H
#define  EVENT_SYSTEM_CLASS_H

namespace EventSystemSpace
  {
    enum  EVIDS
      {
      EVID_UNKNOWN,
      EVID_ANY,
      EVID_DAMAGE_TAKEN,                          //DOESN'T WORK!!!
      EVID_USABLE_ITEM_CONNECTED_DISCONNECTED,
      EVID_CHGARGE_STATE_CHANGED_TO,
//      EVID_ENVIRONMENT_PROCESSED,
      EVIDS_NUM
      };
  };
class  EventArrivedInterface
  {
  public:
    virtual void EventArrived(EventSystemSpace::EVIDS evID, void* parameters)   = 0;
  protected:
  private:
  };

class  EventSystemClass//TODO
  {
  public:

    const static uint8_t  EVID_BUFFER_SIZE            =  16;

//    void  registerUserEvent(void  (*pf)(void*),  EventSystemSpace::EVIDS  evID);
    void  RegisterUserEvent(EventSystemSpace::EVIDS  evID, EventArrivedInterface* EListener);
    void  ExternalEventArrived(EventSystemSpace::EVIDS  evID,  void*  E_Parameters);
    EventSystemClass(void);
  protected:
  private:
//    void  (*programms[EVID_BUFFER_SIZE])(void*);
    EventArrivedInterface*  programms[EVID_BUFFER_SIZE];
    uint8_t  parameters[EVID_BUFFER_SIZE];
    uint8_t  counter;
  };
#endif