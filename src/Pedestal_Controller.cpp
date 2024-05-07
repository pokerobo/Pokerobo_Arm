#include "Pedestal_Controller.h"

#define PEDESTAL_RANGE_X          20
#define PEDESTAL_RANGE_Y          20

#define ARM_JOYSTICK_RANGE_X      255
#define ARM_JOYSTICK_RANGE_Y      255

#define ARM_JOYSTICK_DEADZONE_X   32
#define ARM_JOYSTICK_DEADZONE_Y   32

#ifndef MASK_UP_BUTTON
#define MASK_UP_BUTTON     1U << 0
#endif

#ifndef MASK_RIGHT_BUTTON
#define MASK_RIGHT_BUTTON  1U << 1
#endif

#ifndef MASK_DOWN_BUTTON
#define MASK_DOWN_BUTTON   1U << 2
#endif

#ifndef MASK_LEFT_BUTTON
#define MASK_LEFT_BUTTON   1U << 3
#endif

#ifndef MASK_START_BUTTON
#define MASK_START_BUTTON  1U << 4
#endif

#ifndef MASK_SELECT_BUTTON
#define MASK_SELECT_BUTTON 1U << 5
#endif

#ifndef MASK_ANALOG_BUTTON
#define MASK_ANALOG_BUTTON 1U << 6
#endif

PedestalController::PedestalController(PedestalGroup* pedestalGroup) {
  _pedestalGroup = pedestalGroup;
}

PedestalController* PedestalController::set(PedestalDebugLogger* logger) {
  _logger = logger;
  return this;
}

bool PedestalController::isDebugEnabled() {
  return _logger != NULL;
}

void PedestalController::begin() {}

void PedestalController::play(uint16_t toggleFlags, uint16_t joystickX, uint16_t joystickY) {
  uint16_t pressed = processButtonPress(toggleFlags);
  if (pressed) {
    return;
  }

  processJoystickChange(joystickX, joystickY, 'L');
}

//-------------------------------------------------------------------------------------------------

bool PedestalController::checkButtonPress(uint16_t pressed, uint16_t mask) {
  return pressed & mask;
}

uint16_t PedestalController::processButtonPress(uint16_t pressed) {
  uint16_t checked = 0;

  if(checkButtonPress(pressed, MASK_START_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "START", " is pushed");
    }
    #endif
    processStartButtonPressedEvent();
    checked |= MASK_START_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_SELECT_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "SELECT", " is pushed");
    }
    #endif
    processSelectButtonPressedEvent();
    checked |= MASK_SELECT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_ANALOG_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "ANALOG", " is pushed");
    }
    #endif
    processAnalogButtonPressedEvent();
    checked |= MASK_ANALOG_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_UP_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "PAD", "_", "UP", " is pushed");
    }
    #endif
    processDPadUpButtonPressedEvent();
    checked |= MASK_UP_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_RIGHT_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "PAD", "_", "RIGHT", " is pushed");
    }
    #endif
    processDPadRightButtonPressedEvent();
    checked |= MASK_RIGHT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_DOWN_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "PAD", "_", "DOWN", " is pushed");
    }
    #endif
    processDPadDownButtonPressedEvent();
    checked |= MASK_DOWN_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_LEFT_BUTTON)) {
    #if __DISPATCHER_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debugLog("JOY", "_", "PAD", "_", "LEFT", " is pushed");
    }
    #endif
    processDPadLeftButtonPressedEvent();
    checked |= MASK_LEFT_BUTTON;
  }

  return checked;
}

int PedestalController::processJoystickChange(int nJoyX, int nJoyY, char label) {
  nJoyX = map(nJoyX, 0, 1024, -ARM_JOYSTICK_RANGE_X, ARM_JOYSTICK_RANGE_X);
  nJoyY = map(nJoyY, 0, 1024, -ARM_JOYSTICK_RANGE_Y, ARM_JOYSTICK_RANGE_Y);

  #if __DISPATCHER_RUNNING_LOG__
  if (isDebugEnabled()) {
    char l_[2] = { 'L', '\0' };
    _logger->debugLog("Event", "Trigger", "::", "process", "JoystickChange", "()", " - ", l_, ": ");
    char x_[7], y_[7];
    _logger->debugLog(" - ", "X", ": ", itoa(nJoyX, x_, 10));
    _logger->debugLog(" - ", "Y", ": ", itoa(nJoyY, y_, 10));
  }
  #endif

  if (isJoystickInDeadzone(nJoyX, nJoyY)) {
    return 0;
  }

  if (label == 'L') {
    processLeftJoystickChangeEvent(nJoyX, nJoyY);
    return 1;
  }

  if (label == 'R') {
    processRightJoystickChangeEvent(nJoyX, nJoyY);
    return 1;
  }

  #if __DISPATCHER_RUNNING_LOG__
  if (isDebugEnabled()) {
    char l_[2] = { 'L', '\0' };
    _logger->debugLog("Event", "Trigger", "::", "process", "JoystickChange", "()", " - ", l_, ": ", "not registered");
  }
  #endif

  return -1;
}

bool PedestalController::isJoystickInDeadzone(int nJoyX, int nJoyY) {
  return nJoyX <= ARM_JOYSTICK_DEADZONE_X && nJoyX >= -ARM_JOYSTICK_DEADZONE_X &&
      nJoyY <= ARM_JOYSTICK_DEADZONE_Y && nJoyY >= -ARM_JOYSTICK_DEADZONE_Y;
}

//-------------------------------------------------------------------------------------------------

void PedestalController::processStartButtonPressedEvent() {
}

void PedestalController::processSelectButtonPressedEvent() {
}

void PedestalController::processAnalogButtonPressedEvent() {
}

void PedestalController::processDPadUpButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->verticalServoUp();
  }
}

void PedestalController::processDPadRightButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->horizontalServoRight();
  }
}

void PedestalController::processDPadDownButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->verticalServoDown();
  }
}

void PedestalController::processDPadLeftButtonPressedEvent() {
  if (_pedestalGroup != NULL) {
    _pedestalGroup->horizontalServoLeft();
  }
}

void PedestalController::processLeftJoystickChangeEvent(int nJoyX, int nJoyY) {
  if (_pedestalGroup != NULL) {
    nJoyX = map(nJoyX, -ARM_JOYSTICK_RANGE_X, ARM_JOYSTICK_RANGE_X, PEDESTAL_RANGE_X, -PEDESTAL_RANGE_X);
    nJoyY = map(nJoyY, -ARM_JOYSTICK_RANGE_Y, ARM_JOYSTICK_RANGE_Y, -PEDESTAL_RANGE_Y, PEDESTAL_RANGE_Y);
    _pedestalGroup->changeByJoystick(nJoyX, nJoyY);
  }
}

void PedestalController::processRightJoystickChangeEvent(int nJoyX, int nJoyY) {
}
