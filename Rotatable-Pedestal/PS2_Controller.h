// PS2 Tank by Igor Fonseca @2019
// Controls a robotic tank using a PS2 joystick, using D-pad buttons
// based on an example using the PS2X library by Bill Porter 2011
// All text above must be included in any redistribution.

// include libraries
#include <PS2X_lib.h>

#ifndef __PS2_CONTROLLER_H__
#define __PS2_CONTROLLER_H__

#define MIN_BOUND_X      5
#define MIN_BOUND_Y      5

#define NUM_RANGE_X      10
#define NUM_RANGE_Y      10

#define DEBUG_DEFAULT       true

#define GAMEPAD_ATTENTION   10
#define GAMEPAD_COMMAND     11
#define GAMEPAD_DATA        12
#define GAMEPAD_CLOCK       13

static void (*user_onDPadButtonPressed)(uint16_t);
static void (*user_onLeftJoystickChanged)(int, int);

class PS2Controller {
  public:
    PS2Controller();
    void begin();
    int loop();
    bool hasError();
    void showError();
    void reload();
    void onDPadButtonPressed(void (*function)(uint16_t));
    void onLeftJoystickChanged(void (*function)(int, int));
    int check();
  private:
    PS2X ps2x;
    bool debugEnabled;
    int errorCode;
    bool errorDisplayed;
    byte ps2Type;
    byte vibrate;
};

#endif
