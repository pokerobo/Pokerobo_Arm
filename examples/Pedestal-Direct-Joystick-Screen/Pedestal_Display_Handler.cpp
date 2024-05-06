#include "Pedestal_Display_Handler.h"
#include <U8g2lib.h>

void PedestalDisplayHandler::render(JoystickAction *action) {
  this->firstPage();
  do {
    this->renderInternal(action);
  } while (this->nextPage());
}

void PedestalDisplayHandler::renderInternal(JoystickAction *action) {
  if (action == NULL) {
    return action;
  }
  this->renderJoystickAction_(0, 0, action);
}
