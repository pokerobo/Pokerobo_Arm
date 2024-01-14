#include "Pokerobo_Car.h"

DisplayAdapter displayAdapter;

const uint64_t address = 0x18580901LL;
RF24Listener rf24Listener(address);
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

DancingPuppetCar dancingPuppetCar(" Remote Control Car");

ProgramManager programManager;

void setup() {
  while (!Serial) delay(100); // Wait for the serial connection to be establised.
  Serial.begin(57600);

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Starting");
  #endif

  displayAdapter.begin();

  roboCarHandler.set(&movingResolver);
  roboCarHandler.begin();

  dancingPuppetCar.set(&displayAdapter);
  dancingPuppetCar.set(&roboCarHandler);
  dancingPuppetCar.set(&pedestalGroup);
  dancingPuppetCar.begin();

  hangingDetector.begin([] (void ()) {
    displayAdapter.clear();
    displayAdapter.render(0, 0, "Suspending...");
    roboCarHandler.stop();
  }, 100);

  rf24Listener.set(&hangingDetector);
  rf24Listener.begin();

  programManager.set(&displayAdapter);
  programManager.set(&rf24Listener);
  programManager.add(&dancingPuppetCar);
  programManager.begin();

  #if __LOADING_LOG_ENABLED__
  debugLog("main", "()", " - ", "Done!");
  #endif
}

void loop() {
  uint32_t begin = millis();
  programManager.check();
  delay(max(100 - (millis() - begin), 0));
}
