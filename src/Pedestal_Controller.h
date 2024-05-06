#ifndef __PEDESTAL_CONTROLLER_H__
#define __PEDESTAL_CONTROLLER_H__

#include "Pedestal_Group.h"

class PedestalController {
  public:
    PedestalController(PedestalGroup* pedestalGroup);
    void begin();
    void play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY);
  protected:
    virtual uint16_t processButtonPress(uint16_t buttons);
    virtual int processJoystickChange(int joystickX, int joystickY, char label);
  private:
    void processStartButtonPressedEvent();
    void processSelectButtonPressedEvent();
    void processAnalogButtonPressedEvent();
    void processDPadUpButtonPressedEvent();
    void processDPadRightButtonPressedEvent();
    void processDPadDownButtonPressedEvent();
    void processDPadLeftButtonPressedEvent();
    void processLeftJoystickChangeEvent(int nJoyX, int nJoyY);
    void processRightJoystickChangeEvent(int nJoyX, int nJoyY);
    bool checkButtonPress(uint16_t pressed, uint16_t mask);
    bool isJoystickInDeadzone(int nJoyX, int nJoyY);
    PedestalGroup* _pedestalGroup = NULL;
};

#endif
