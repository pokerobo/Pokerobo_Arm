#ifndef __PEDESTAL_GROUP_H__
#define __PEDESTAL_GROUP_H__

#include "Pedestal_Commons.h"
#include "Pedestal_Handler.h"

#define PEDESTALS_MAX                 8
#define PEDESTAL_DANCING_STEPS_MAX    32

#ifndef PEDESTAL_WAITING_MAX
#define PEDESTAL_WAITING_MAX          100
#endif//PEDESTAL_WAITING_MAX

class PedestalState {
  public:
    virtual int getCommonHorizontalPosition();
    virtual int getCommonVerticalPosition();
    virtual int getHorizontalPositionOf(uint8_t i);
    virtual int getVerticalPositionOf(uint8_t i);
    virtual uint8_t getTotal();
};

class PedestalGroup: public PedestalState {
  public:
    PedestalGroup(PedestalHandler* p1,
        PedestalHandler* p2=NULL,
        PedestalHandler* p3=NULL,
        PedestalHandler* p4=NULL,
        PedestalHandler* p5=NULL,
        PedestalHandler* p6=NULL,
        PedestalHandler* p7=NULL,
        PedestalHandler* p8=NULL);
    PedestalGroup(PedestalHandler* pedestalHandlers[]);
    void set(PedestalDebugLogger* logger);
    void begin();
    void reset();
    void verticalServoUp();
    void horizontalServoRight();
    void verticalServoDown();
    void horizontalServoLeft();
    void changeByJoystick(int nJoyX, int nJoyY);
    bool change(int hUnits, int vUnits);
    void setHorizontalPosition(int hPos);
    void setVerticalPosition(int vPos);
    int getCommonHorizontalPosition();
    int getCommonVerticalPosition();
    int getHorizontalPositionOf(uint8_t i);
    int getVerticalPositionOf(uint8_t i);
    uint8_t getTotal();
    void autoDance();
  protected:
    virtual bool isDebugEnabled();
  private:
    uint8_t _pedestalsTotal = 0;
    PedestalHandler* _pedestalHandlers[PEDESTALS_MAX] = {};
    void initialize_();
    void verticalServoUpFor(PedestalHandler *pedestalHandler);
    void horizontalServoRightFor(PedestalHandler *pedestalHandler);
    void verticalServoDownFor(PedestalHandler *pedestalHandler);
    void horizontalServoLeftFor(PedestalHandler *pedestalHandler);
    void changeByJoystickFor(PedestalHandler *pedestalHandler, int nJoyX, int nJoyY);
    WaitingCounter _waitingCounter;
    bool _sceneDirection = true;
    int _sceneStep = -1;
    int _sceneStepsTotal = 19;
    int8_t _sceneHPos[PEDESTAL_DANCING_STEPS_MAX] = {
      30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120
    };
    int8_t _sceneVPos[PEDESTAL_DANCING_STEPS_MAX] = {
      30, 35, 40, 45, 50, 45, 40, 35, 30, 30, 30, 35, 40, 45,  50,  45,  40,  33,  30
    };
    PedestalDebugLogger* _logger = NULL;
};

#endif
