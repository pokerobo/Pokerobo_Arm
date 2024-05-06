#include "Pedestal_Commons.h"

WaitingCounter::WaitingCounter(uint16_t limit) {
  begin(limit);
}

void WaitingCounter::begin(uint16_t limit) {
  if (limit > 0) {
    _limit = limit;
  }
  reset();
}

void WaitingCounter::reset() {
  _delta = 0;
  _milestone = millis();
}

bool WaitingCounter::check() {
  uint32_t current = millis();
  if (current > _milestone) {
    _delta += (current - _milestone);
    _milestone = current;
    if (_delta >= _limit) {
      _delta = 0;
      return true;
    }
  }
  return false;
}

void PedestalDebugLogger::debugLog(char* s0) {
  debugLog(s0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1) {
  debugLog(s0, s1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2) {
  debugLog(s0, s1, s2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3) {
  debugLog(s0, s1, s2, s3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4) {
  debugLog(s0, s1, s2, s3, s4, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5) {
  debugLog(s0, s1, s2, s3, s4, s5, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, NULL, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
    char* s10) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, NULL, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
    char* s10, char* s11) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
    char* s10, char* s11, char* s12, char* s13) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
    char* s10, char* s11, char* s12, char* s13, char* s14) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
    char* s10, char* s11, char* s12, char* s13, char* s14, char* s15) {
  debugLog(s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, NULL, NULL, NULL, NULL);
}

void PedestalDebugLogger::debugLog(char* s0, char* s1, char* s2, char* s3, char* s4, char* s5, char* s6, char* s7, char* s8, char* s9,
    char* s10, char* s11, char* s12, char* s13, char* s14, char* s15, char* s16, char* s17, char* s18, char* s19) {
  Serial.print(s0);
  while(1) {
    if (s1 != NULL) Serial.print(s1); else break;
    if (s2 != NULL) Serial.print(s2); else break;
    if (s3 != NULL) Serial.print(s3); else break;
    if (s4 != NULL) Serial.print(s4); else break;
    if (s5 != NULL) Serial.print(s5); else break;
    if (s6 != NULL) Serial.print(s6); else break;
    if (s7 != NULL) Serial.print(s7); else break;
    if (s8 != NULL) Serial.print(s8); else break;
    if (s9 != NULL) Serial.print(s9); else break;
    if (s10 != NULL) Serial.print(s10); else break;
    if (s11 != NULL) Serial.print(s11); else break;
    if (s12 != NULL) Serial.print(s12); else break;
    if (s13 != NULL) Serial.print(s13); else break;
    if (s14 != NULL) Serial.print(s14); else break;
    if (s15 != NULL) Serial.print(s15); else break;
    if (s16 != NULL) Serial.print(s16); else break;
    if (s17 != NULL) Serial.print(s17); else break;
    if (s18 != NULL) Serial.print(s18); else break;
    if (s19 != NULL) Serial.print(s19); else break;
    break;
  }
  Serial.println();
}
