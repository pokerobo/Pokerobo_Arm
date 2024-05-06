#ifndef __PEDESTAL_DISPLAY_HANDLER_H__
#define __PEDESTAL_DISPLAY_HANDLER_H__

#include <Pokerobo_RCB_master.h>

class PedestalDisplayHandler: public DisplayHandler {
  public:
    using DisplayHandler::DisplayHandler;
    void render(JoystickAction *action);
  protected:
    virtual void renderInternal(JoystickAction *action);
};

#endif
