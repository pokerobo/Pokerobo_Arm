#ifndef __PEDESTAL_COMMONS_H__
#define __PEDESTAL_COMMONS_H__

#include <Arduino.h>

#define __HCPCA9685_ENABLED__           1

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
    void debugLog(char* s0);
    void debugLog(char* s0, char* s1);
    void debugLog(char* s0, char* s1, char* s2);
    void debugLog(char* s0, char* s1, char* s2, char* s3);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10, char* s11);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10, char* s11, char* s12, char* s13);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10, char* s11, char* s12, char* s13, char* s14);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10, char* s11, char* s12, char* s13, char* s14, char* s15);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10, char* s11, char* s12, char* s13, char* s14, char* s15, char* s16, char* s17, char* s18);
    void debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
        char* s10, char* s11, char* s12, char* s13, char* s14, char* s15, char* s16, char* s17, char* s18, char* s19);
};
#endif//__PEDESTAL_COMMONS_H__
