#include "Pokerobo_Car.h"

DisplayAdapter displayAdapter;

const uint64_t address = 0x18580901LL;
RF24Controller rf24Controller(address);
HangingDetector hangingDetector;

RoboCarHandler roboCarHandler;
MovingResolver movingResolver;

PedestalHandler pedestalHandler1(4, 5);
PedestalHandler pedestalHandler3(8, 9);

PedestalHandler* pedestalHandlers[PEDESTALS_MAX] = {
  &pedestalHandler1,
  &pedestalHandler3,
};
PedestalGroup pedestalGroup(pedestalHandlers);

RemoteControlCar remoteControlCar(" Remote Control Car");

EventListener eventListener;

void setup() {
  while (!Serial) delay(100); // Wait for the serial connection to be establised.
  Serial.begin(57600);

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Starting");
  #endif

  displayAdapter.begin();

  roboCarHandler.set(&movingResolver);
  roboCarHandler.begin();

  remoteControlCar.set(&displayAdapter);
  remoteControlCar.set(&roboCarHandler);
  remoteControlCar.set(&pedestalGroup);
  remoteControlCar.begin();

  hangingDetector.begin([] (void ()) {
    displayAdapter.clear();
    displayAdapter.render(0, 0, "Suspending...");
    roboCarHandler.stop();
  }, 100);

  rf24Controller.set(&hangingDetector);
  rf24Controller.begin();

  eventListener.set(&displayAdapter);
  eventListener.set(&rf24Controller);
  eventListener.add(&remoteControlCar);
  eventListener.begin();

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Done!");
  #endif
}

void loop() {
  uint32_t begin = millis();
  eventListener.check();
  delay(max(100 - (millis() - begin), 0));
}
