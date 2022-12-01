#include "esp32-hal-touch.h"
enum class TOUCH_STATE {
  RELEASED = 0,
  PRESSED = 1
};
class TouchButton {
private:
  byte pin;
  TOUCH_STATE currentEvent = TOUCH_STATE::RELEASED;
  TOUCH_STATE currentState = TOUCH_STATE::RELEASED;
  unsigned long lastChangedStateTime = 0;
public:
  TouchButton(byte pin) {
    this->pin = pin;
  }
  void handleState(unsigned int debounceThreshold = 100) {
    if (touchRead(pin) < 40) {
      currentEvent = TOUCH_STATE::PRESSED;
    } else {
      currentEvent = TOUCH_STATE::RELEASED;
    }
    //cause we are having a lot of intermittence, I have to put this line of code to get first touch state
    if (currentEvent == TOUCH_STATE::PRESSED && currentState == TOUCH_STATE::RELEASED) {
      currentState = TOUCH_STATE::PRESSED;
      lastChangedStateTime = millis();
    }else if (currentEvent != currentState) {
      if (millis() - lastChangedStateTime > debounceThreshold) {
        currentState = currentEvent;
        lastChangedStateTime = millis();
      }
    } else {
      lastChangedStateTime = millis();
    }
  }
  bool isPressed() {
    return (this->currentState == TOUCH_STATE::PRESSED);
  }
  TOUCH_STATE getCurrentState() {
    return this->currentState;
  }
};  // don't forget the semicolon at the end of the class