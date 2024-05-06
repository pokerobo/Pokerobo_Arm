#include "Pedestal_Controller.h"

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalGroup pedestalGroup(&pedestalHandler1,
    &pedestalHandler3);

void setup() {
  Serial.begin(57600);
  pedestalGroup.begin();
}

void loop() {
  uint32_t begin = millis();

  pedestalGroup.autoDance();

  uint32_t exectime = millis() - begin;

  delay(max(50 - exectime, 0));
}
