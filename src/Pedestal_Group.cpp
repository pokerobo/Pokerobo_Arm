#include "Pedestal_Group.h"

PedestalGroup::PedestalGroup(PedestalHandler* p1,
    PedestalHandler* p2,
    PedestalHandler* p3,
    PedestalHandler* p4,
    PedestalHandler* p5,
    PedestalHandler* p6,
    PedestalHandler* p7,
    PedestalHandler* p8) {
  if (p1 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p1;
    _pedestalsTotal += 1;
  }
  if (p2 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p2;
    _pedestalsTotal += 1;
  }
  if (p3 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p3;
    _pedestalsTotal += 1;
  }
  if (p4 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p4;
    _pedestalsTotal += 1;
  }
  if (p5 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p5;
    _pedestalsTotal += 1;
  }
  if (p6 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p6;
    _pedestalsTotal += 1;
  }
  if (p7 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p7;
    _pedestalsTotal += 1;
  }
  if (p8 != NULL) {
    _pedestalHandlers[_pedestalsTotal] = p8;
    _pedestalsTotal += 1;
  }
  initialize_();
}

PedestalGroup::PedestalGroup(PedestalHandler* pedestalHandlers[]) {
  for (int i=0; i<PEDESTALS_MAX; i++) {
    if (pedestalHandlers[i] != NULL) {
      _pedestalHandlers[_pedestalsTotal] = pedestalHandlers[i];
      _pedestalsTotal += 1;
    }
  }
  initialize_();
}

void PedestalGroup::initialize_() {
#if __PEDESTAL_LOADING_LOG__
  if (isDebugEnabled()) {
    char _pedestalsTotal_[7];
    _logger->debug("PedestalGroup", "()", " - ", "total", ": ", itoa(_pedestalsTotal, _pedestalsTotal_, 10));
  }
#endif
  _sceneDirection = true;
  _sceneStep = -1;
}

void PedestalGroup::set(PedestalDebugLogger* logger) {
  _logger = logger;
  // return this;
}

bool PedestalGroup::isDebugEnabled() {
  return _logger != NULL;
}

void PedestalGroup::begin() {
  PedestalHandler::init();
  for (int i=0; i<_pedestalsTotal; i++) {
    if (_pedestalHandlers[i] == NULL) continue;
    _pedestalHandlers[i]->begin(
        HORIZONTAL_MIN_ANGLE,
        HORIZONTAL_MAX_ANGLE,
        VERTICAL_MIN_ANGLE,
        VERTICAL_MAX_ANGLE);
  }
  _waitingCounter.begin(PEDESTAL_WAITING_MAX);
}

bool PedestalGroup::change(int hDelta, int vDelta) {
  for (int i=0; i<_pedestalsTotal; i++) {
    _pedestalHandlers[i]->change(hDelta, vDelta);
  }
}

void PedestalGroup::setHorizontalPosition(int hPos) {
  for (int i=0; i<_pedestalsTotal; i++) {
    _pedestalHandlers[i]->setHorizontalPosition(hPos);
  }
}

void PedestalGroup::setVerticalPosition(int vPos) {
  for (int i=0; i<_pedestalsTotal; i++) {
    _pedestalHandlers[i]->setVerticalPosition(vPos);
  }
}

int PedestalGroup::getCommonHorizontalPosition() {
  return getHorizontalPositionOf(0);
}

int PedestalGroup::getCommonVerticalPosition() {
  return getVerticalPositionOf(0);
}

int PedestalGroup::getHorizontalMinAngleOf(uint8_t i) {
  if (i >= _pedestalsTotal) {
    return -1;
  }
  return _pedestalHandlers[i]->getHorizontalMinAngle();
}

int PedestalGroup::getHorizontalMaxAngleOf(uint8_t i) {
  if (i >= _pedestalsTotal) {
    return -1;
  }
  return _pedestalHandlers[i]->getHorizontalMaxAngle();
}

int PedestalGroup::getHorizontalPositionOf(uint8_t i) {
  if (i >= _pedestalsTotal) {
    return -1;
  }
  return _pedestalHandlers[i]->getHorizontalPosition();
}

int PedestalGroup::getVerticalMinAngleOf(uint8_t i) {
  if (i >= _pedestalsTotal) {
    return -1;
  }
  return _pedestalHandlers[i]->getVerticalMinAngle();
}

int PedestalGroup::getVerticalMaxAngleOf(uint8_t i) {
  if (i >= _pedestalsTotal) {
    return -1;
  }
  return _pedestalHandlers[i]->getVerticalMaxAngle();
}

int PedestalGroup::getVerticalPositionOf(uint8_t i) {
  if (i >= _pedestalsTotal) {
    return -1;
  }
  return _pedestalHandlers[i]->getVerticalPosition();
}

uint8_t PedestalGroup::getTotal() {
  return _pedestalsTotal;
}

void PedestalGroup::reset() {
  for (int i=0; i<_pedestalsTotal; i++) {
    if (_pedestalHandlers[i] == NULL) {
      continue;
    }
    _pedestalHandlers[i]->reset();
  }
  _waitingCounter.reset();
}

void PedestalGroup::verticalServoUp() {
  for (int i=0; i<_pedestalsTotal; i++) {
    verticalServoUpFor(_pedestalHandlers[i]);
  }
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    _logger->debug("main", "()", " - ", "UP", " is pushed");
  }
  #endif
}

void PedestalGroup::verticalServoUpFor(PedestalHandler *pedestalHandler) {
  if (pedestalHandler == NULL) return;
  pedestalHandler->verticalServoUp();
}

void PedestalGroup::horizontalServoRight() {
  for (int i=0; i<_pedestalsTotal; i++) {
    horizontalServoRightFor(_pedestalHandlers[i]);
  }
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    _logger->debug("main", "()", " - ", "RIGHT", " is pushed");
  }
  #endif
}

void PedestalGroup::horizontalServoRightFor(PedestalHandler *pedestalHandler) {
  if (pedestalHandler == NULL) return;
  pedestalHandler->horizontalServoRight();
}

void PedestalGroup::verticalServoDown() {
  for (int i=0; i<_pedestalsTotal; i++) {
    verticalServoDownFor(_pedestalHandlers[i]);
  }
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    _logger->debug("main", "()", " - ", "DOWN", " is pushed");
  }
  #endif
}

void PedestalGroup::verticalServoDownFor(PedestalHandler *pedestalHandler) {
  if (pedestalHandler == NULL) return;
  pedestalHandler->verticalServoDown();
}

void PedestalGroup::horizontalServoLeft() {
  for (int i=0; i<_pedestalsTotal; i++) {
    horizontalServoLeftFor(_pedestalHandlers[i]);
  }
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    _logger->debug("main", "()", " - ", "LEFT", " is pushed");
  }
  #endif
}

void PedestalGroup::horizontalServoLeftFor(PedestalHandler *pedestalHandler) {
  if (pedestalHandler == NULL) return;
  pedestalHandler->horizontalServoLeft();
}

void PedestalGroup::changeByJoystick(int nJoyX, int nJoyY) {
  for (int i=0; i<_pedestalsTotal; i++) {
    changeByJoystickFor(_pedestalHandlers[i], nJoyX, nJoyY);
  }
}

void PedestalGroup::changeByJoystickFor(PedestalHandler *pedestalHandler, int nJoyX, int nJoyY) {
  if (pedestalHandler == NULL) return;
  bool changed = pedestalHandler->change(nJoyX, nJoyY);
  if (changed) {
    #if __PEDESTAL_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debug("main", "()", " - ", "process", "Left", "JoystickChange", "Event", "()", " is called");
    }
    #endif
  }
}

void PedestalGroup::autoDance() {
  // special case: getting started the autoDance() procedure
  if (_sceneStep < 0) {
    _sceneStep = 0;
    reset();
    #if __PEDESTAL_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debug("PedestalGroup", "::", "autoDance", "()", " - ", "Starting");
    }
    #endif
    return;
  }
  // check the waitingCount reach the limit
  if (!_waitingCounter.check()) {
    return;
  }
  // move the next step
  if (_sceneStep == 0) {
    _sceneDirection = true;
  }
  if (_sceneStep == _sceneStepsTotal - 1) {
    _sceneDirection = false;
  }
  if (_sceneDirection) {
    _sceneStep += 1;
  } else {
    _sceneStep -= 1;
  }
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    char _step_[7];
    _logger->debug("PedestalGroup", "::", "autoDance", "()", " - ", "step", ": ", itoa(_sceneStep, _step_, 10));
  }
  #endif
  setHorizontalPosition(_sceneHPos[_sceneStep]);
  setVerticalPosition(_sceneVPos[_sceneStep]);
}
