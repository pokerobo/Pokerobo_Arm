#ifndef __PEDESTAL_COMMONS_H__
#define __PEDESTAL_COMMONS_H__

#include <Arduino.h>

#define __SERVO_DRIVER_NATIVE__         1
#define __SERVO_DRIVER_ADAFRUIT__       2
#define __SERVO_DRIVER_HCPCA9685__      4

#define __ACTIVE_SERVO_DRIVER__         __SERVO_DRIVER_ADAFRUIT__

#define __LOADING_LOG_ENABLED__         1
#define __RUNNING_LOG_ENABLED__         1

#define __DISPATCHER_RUNNING_LOG__      0
#define __PEDESTAL_RUNNING_LOG__        0

class WaitingCounter {
  public:
    WaitingCounter(uint16_t limit = 100); // 100ms
    void begin(uint16_t limit);
    void reset();
    bool check();
  private:
    uint16_t _delta = 0;
    uint16_t _limit = 0;
    uint32_t _milestone = 0;
};

class PedestalDebugLogger {
  public:
    void debug(char* s0,
        char* s1=NULL,
        char* s2=NULL,
        char* s3=NULL,
        char* s4=NULL,
        char* s5=NULL,
        char* s6=NULL,
        char* s7=NULL,
        char* s8=NULL,
        char* s9=NULL,
        char* s10=NULL,
        char* s11=NULL,
        char* s12=NULL,
        char* s13=NULL,
        char* s14=NULL,
        char* s15=NULL,
        char* s16=NULL,
        char* s17=NULL,
        char* s18=NULL,
        char* s19=NULL);
};
#endif//__PEDESTAL_COMMONS_H__
