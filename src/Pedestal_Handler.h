#ifndef __PEDESTAL_HANDLER_H__
#define __PEDESTAL_HANDLER_H__

#include "Pedestal_Commons.h"

#ifndef __PEDESTAL_LOADING_LOG__
#define __PEDESTAL_LOADING_LOG__  __LOADING_LOG_ENABLED__
#endif//__PEDESTAL_LOADING_LOG__

#ifndef __PEDESTAL_RUNNING_LOG__
#define __PEDESTAL_RUNNING_LOG__  __RUNNING_LOG_ENABLED__
#endif//__PEDESTAL_RUNNING_LOG__

#ifndef __ACTIVE_SERVO_DRIVER__
#define __ACTIVE_SERVO_DRIVER__  __SERVO_DRIVER_ADAFRUIT__
#endif

#if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
#include <Servo.h>
#endif

#if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_ADAFRUIT__
#include <Adafruit_PWMServoDriver.h>
#endif

#if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_HCPCA9685__
#include "HCPCA9685.h"
#endif

#if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_ADAFRUIT__
#define SERVOMIN              125
#define SERVOMAX              625
#endif

#ifndef HORIZONTAL_SERVO_PIN
#define HORIZONTAL_SERVO_PIN  4
#endif

#ifndef VERTICAL_SERVO_PIN
#define VERTICAL_SERVO_PIN    5
#endif

#ifndef HORIZONTAL_MIN_ANGLE
#define HORIZONTAL_MIN_ANGLE  30
#endif

#ifndef HORIZONTAL_MAX_ANGLE
#define HORIZONTAL_MAX_ANGLE  150
#endif

#ifndef VERTICAL_MIN_ANGLE
#define VERTICAL_MIN_ANGLE    30
#endif

#ifndef VERTICAL_MAX_ANGLE
#define VERTICAL_MAX_ANGLE    90
#endif

#ifndef MOVING_AMOUNT
#define MOVING_AMOUNT         1
#endif

class PedestalHandler {
  public:
    static void init();
    static bool initialized;

    PedestalHandler(byte hPin=HORIZONTAL_SERVO_PIN, byte vPin=VERTICAL_SERVO_PIN, bool debugEnabled=true);
    PedestalHandler* set(PedestalDebugLogger* logger);

    void begin(int hMinAngle=0, int hMaxAngle=180, int vMinAngle=0, int vMaxAngle=180);
    void reset();
    void test();

    bool verticalServoUp();
    bool verticalServoDown();
    bool horizontalServoLeft();
    bool horizontalServoRight();  

    int changeHorizontalServo(int hDelta);
    int changeVerticalServo(int vDelta);
    bool change(int hDelta, int vDelta);
    int getHorizontalMinAngle();
    int getHorizontalMaxAngle();
    int getHorizontalPosition();
    void setHorizontalPosition(int hPos);
    int updateHorizontalPosition(int hPos, int hCurrentPos = -1);
    int getVerticalMinAngle();
    int getVerticalMaxAngle();
    int getVerticalPosition();
    void setVerticalPosition(int vPos);
    int updateVerticalPosition(int vPos, int vCurrentPos = -1);
    bool syncWith(PedestalHandler master);

  protected:
    virtual bool isDebugEnabled();

  private:
    int count;
    #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
    Servo horizontalServo;
    #endif
    byte horizontalServoPin;
    int horizontalServoPos;
    int horizontalMinAngle;
    int horizontalMaxAngle;
    #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
    Servo verticalServo;
    #endif
    byte verticalServoPin;
    int verticalServoPos;
    int verticalMinAngle;
    int verticalMaxAngle;
    bool _debugEnabled;
    PedestalDebugLogger* _logger = NULL;
};

#endif
