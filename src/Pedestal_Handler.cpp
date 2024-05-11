#include "Pedestal_Handler.h"

#if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_HCPCA9685__
/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40 */
#define  I2C_ADDR             0x40

/* Create an instance of the library */
HCPCA9685 hcpca9685(I2C_ADDR);
#endif

#if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_ADAFRUIT__
Adafruit_PWMServoDriver pwmServoDriver = Adafruit_PWMServoDriver(0x40);
#endif

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

static bool PedestalHandler::initialized = false;

static void PedestalHandler::init() {
  if (initialized) return;
  initialized = true;

  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_HCPCA9685__
  /* Initialise the library and set it to 'servo mode' */ 
  hcpca9685.Init(SERVO_MODE);

  /* Wake the device up */
  hcpca9685.Sleep(false);
  #endif

  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_ADAFRUIT__
  pwmServoDriver.begin();
  pwmServoDriver.setPWMFreq(60);
  #endif
}

PedestalHandler::PedestalHandler(byte hPin, byte vPin, bool debugEnabled) {
  count = 0;
  horizontalServoPin = (hPin >= 0) ? hPin : HORIZONTAL_SERVO_PIN;
  horizontalServoPos = 0;
  verticalServoPin = (vPin >= 0) ? vPin : VERTICAL_SERVO_PIN;
  verticalServoPos = 0;
  _debugEnabled = debugEnabled;
  #if __PEDESTAL_LOADING_LOG__
  if (isDebugEnabled()) {
    char p_[5], sp_[5];
    _logger->debug("PedestalHandler", "::", "PedestalHandler", "()", " - ",
        "h", "Pin", ": ", itoa(hPin, p_, 10), " => ", itoa(horizontalServoPin, sp_, 10));
    _logger->debug("PedestalHandler", "::", "PedestalHandler", "()", " - ",
        "v", "Pin", ": ", itoa(vPin, p_, 10), " => ", itoa(verticalServoPin, sp_, 10));
  }
  #endif
}

PedestalHandler* PedestalHandler::set(PedestalDebugLogger* logger) {
  _logger = logger;
  return this;
}

bool PedestalHandler::isDebugEnabled() {
  return _logger != NULL && _debugEnabled;
}

void PedestalHandler::begin(int hMinAngle, int hMaxAngle, int vMinAngle, int vMaxAngle) {
  #if __PEDESTAL_LOADING_LOG__
  if (isDebugEnabled()) {
    char num_[7];
    _logger->debug("PedestalHandler", "::", "begin", "()", ": ");
    _logger->debug(" - ", "h", "Min", "Angle", ": ", itoa(hMinAngle, num_, 10));
    _logger->debug(" - ", "h", "Max", "Angle", ": ", itoa(hMaxAngle, num_, 10));
    _logger->debug(" - ", "v", "Min", "Angle", ": ", itoa(vMinAngle, num_, 10));
    _logger->debug(" - ", "v", "Max", "Angle", ": ", itoa(vMaxAngle, num_, 10));
  }
  #endif
  //
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
  horizontalServo.attach(horizontalServoPin);
  #endif
  horizontalMinAngle = (hMinAngle < 0) ? 0 : hMinAngle;
  horizontalMaxAngle = (hMaxAngle > 180) ? 180 : hMaxAngle;
  //
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
  verticalServo.attach(verticalServoPin);
  #endif
  verticalMinAngle = (vMinAngle < 0) ? 0 : vMinAngle;
  verticalMaxAngle = (vMaxAngle > 180) ? 180 : vMaxAngle;
  //
  reset();
}

void PedestalHandler::reset() {
  setHorizontalPosition( (horizontalMaxAngle + horizontalMinAngle) / 2);
  setVerticalPosition(verticalMinAngle);
}

int PedestalHandler::getHorizontalPosition() {
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
  return horizontalServo.read();
  #else
  #if __PEDESTAL_RUNNING_LOG__
  char num_[7];
  _logger->debug("old ", "Horizontal", "Servo", "Pos", ": ", itoa(horizontalServoPos, num_, 10));
  #endif
  return horizontalServoPos;
  #endif
}

void PedestalHandler::setHorizontalPosition(int hPos) {
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
  horizontalServo.write(hPos);
  #else

  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_HCPCA9685__
  horizontalServoPos = hPos;
  int horizontalHcpcaPos = map(horizontalServoPos, 0, 180, 10, 450);
  #if __PEDESTAL_RUNNING_LOG__
  char n1_[7], n2_[7];
  _logger->debug("new ", "Horizontal", "Servo", "Pos", ": ", itoa(horizontalServoPos, n1_, 10),
      "; ", "Horizontal", "Hcpca", "Pos", ": ", itoa(horizontalHcpcaPos, n2_, 10));
  #endif
  hcpca9685.Servo(horizontalServoPin, horizontalHcpcaPos);
  #endif//__SERVO_DRIVER_HCPCA9685__

  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_ADAFRUIT__
  horizontalServoPos = hPos;
  pwmServoDriver.setPWM(horizontalServoPin, 0, angleToPulse(horizontalServoPos));
  #endif//__SERVO_DRIVER_ADAFRUIT__

  #endif//__SERVO_DRIVER_NATIVE__
}

int PedestalHandler::updateHorizontalPosition(int hPos, int hCurrentPos) {
  if (hPos < horizontalMinAngle) {
    hPos = horizontalMinAngle;
  }
  if (hPos > horizontalMaxAngle) {
    hPos = horizontalMaxAngle;
  }
  //
  if (hCurrentPos < 0) {
    hCurrentPos = getHorizontalPosition();
  }
  if (hPos != hCurrentPos) {
    setHorizontalPosition(hPos);
  }
  //
  return hPos - hCurrentPos;
}

int PedestalHandler::getVerticalPosition() {
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
  return verticalServo.read();
  #else
  return verticalServoPos;
  #endif
}

void PedestalHandler::setVerticalPosition(int vPos) {
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_NATIVE__
  verticalServo.write(vPos);
  #else
  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_HCPCA9685__
  verticalServoPos = vPos;
  int verticalHcpcaPos = map(verticalServoPos, 0, 180, 10, 450);
  hcpca9685.Servo(verticalServoPin, verticalHcpcaPos);
  #endif//__SERVO_DRIVER_HCPCA9685__

  #if __ACTIVE_SERVO_DRIVER__ == __SERVO_DRIVER_ADAFRUIT__
  verticalServoPos = vPos;
  pwmServoDriver.setPWM(verticalServoPin, 0, angleToPulse(verticalServoPos));
  #endif//__SERVO_DRIVER_ADAFRUIT__

  #endif//__SERVO_DRIVER_NATIVE__
}

int PedestalHandler::updateVerticalPosition(int vPos, int vCurrentPos) {
  if (vPos < verticalMinAngle) {
    vPos = verticalMinAngle;
  }
  if (vPos > verticalMaxAngle) {
    vPos = verticalMaxAngle;
  }
  //
  if (vCurrentPos < 0) {
    vCurrentPos = getVerticalPosition();
  }
  if (vPos != vCurrentPos) {
    setVerticalPosition(vPos);
  }
  //
  return vPos - vCurrentPos;
}

bool PedestalHandler::syncWith(PedestalHandler master) {
  int hDelta = updateHorizontalPosition(master.getHorizontalPosition());
  int vDelta = updateVerticalPosition(master.getVerticalPosition());
  return (hDelta != 0) || (vDelta != 0);
}

void PedestalHandler::test() {
  char n_[7];
  if (count >= 3) {
    _logger->debug(itoa(count, n_, 10), " rounds are done!");
    return;
  }
  count++;
  //
  for (int pos = 0; pos <= 180; pos += 5) {
    setHorizontalPosition(pos);
    setVerticalPosition(pos);
    _logger->debug("h", "Pos", ": ", itoa(pos, n_, 10));
    delay(100);
  }
  //
  for (int pos = 180; pos >= 0; pos -= 5) {
    setHorizontalPosition(pos);
    setVerticalPosition(pos);
    _logger->debug("h", "Pos", ": ", itoa(pos, n_, 10));
    delay(100);
  }
}

bool PedestalHandler::verticalServoUp() {
  return changeVerticalServo(MOVING_AMOUNT);
}

bool PedestalHandler::verticalServoDown() {
  return changeVerticalServo(-MOVING_AMOUNT);
}

bool PedestalHandler::horizontalServoLeft() {
  return changeHorizontalServo(MOVING_AMOUNT);
}

bool PedestalHandler::horizontalServoRight() {
  return changeHorizontalServo(-MOVING_AMOUNT);
}

int PedestalHandler::changeHorizontalServo(int hDelta) {
  if (hDelta == 0) {
    #if __PEDESTAL_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debug("PedestalHandler", "::", "change", "Horizontal", "Servo", "()", " - ",
          "h", "Delta", ": ", "0, do nothing");
    }
    #endif
    return false;
  }
  int hCurrentPos = getHorizontalPosition();
  int hPos = hCurrentPos;
  //
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    char hDelta_[7], hPos_[7];
    _logger->debug("PedestalHandler", "::", "change", "Horizontal", "Servo", "()", " - ",
        "h", "Delta", ": ", itoa(hDelta, hDelta_, 10), "; ",
        "h", "Pos", ": ", itoa(hPos, hPos_, 10));
  }
  #endif
  //
  if (hDelta < 0 && hPos <= horizontalMinAngle) {
    return false;
  }
  if (hDelta > 0 && hPos >= horizontalMaxAngle) {
    return false;
  }
  hPos += hDelta;
  //
  return updateHorizontalPosition(hPos, hCurrentPos);
}

int PedestalHandler::changeVerticalServo(int vDelta) {
  if (vDelta == 0) {
    #if __PEDESTAL_RUNNING_LOG__
    if (isDebugEnabled()) {
      _logger->debug("PedestalHandler", "::", "change", "Vertical", "Servo", "()", " - ",
          "v", "Delta", ": ", "0, do nothing");
    }
    #endif
    return false;
  }
  int vCurrentPos = getVerticalPosition();
  int vPos = vCurrentPos;
  //
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    char vDelta_[7], vPos_[7];
    _logger->debug("PedestalHandler", "::", "change", "Vertical", "Servo", "()", " - ",
        "v", "Delta", ": ", itoa(vDelta, vDelta_, 10), "; ",
        "v", "Pos", ": ", itoa(vPos, vPos_, 10));
  }
  #endif
  //
  if (vDelta < 0 && vPos <= verticalMinAngle) {
    return false;
  }
  if (vDelta > 0 && vPos >= verticalMaxAngle) {
    return false;
  }
  vPos += vDelta;
  //
  return updateVerticalPosition(vPos, vCurrentPos);
}

bool PedestalHandler::change(int hDelta, int vDelta) {
  #if __PEDESTAL_RUNNING_LOG__
  if (isDebugEnabled()) {
    char h_[7], v_[7];
    _logger->debug("PedestalHandler", "::", "change", "()", " - ",
        "h", "Delta", ": ", itoa(hDelta, h_, 10), "; ",
        "v", "Delta", ": ", itoa(vDelta, v_, 10));
  }
  #endif
  int hChanged = changeHorizontalServo(hDelta);
  int vChanged = changeVerticalServo(vDelta);
  return (hChanged != 0) || (vChanged != 0);
}
