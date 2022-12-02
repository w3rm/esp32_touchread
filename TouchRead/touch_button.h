#include "esp32-hal-touch.h"
enum class TOUCH_STATE : byte {
  RELEASED = 0,
  PRESSED = 1
};
class TouchButton {
private:
  byte pin;
  TOUCH_STATE currentEvent = TOUCH_STATE::RELEASED;
  TOUCH_STATE currentState = TOUCH_STATE::RELEASED;
  unsigned long lastChangedStateTime = 0;
  unsigned short touchThresholdSensibility;
  unsigned short debounceThresholdInMillis;  
public:
  TouchButton(byte pin, unsigned short touchThresholdSensibility, unsigned short debounceThresholdInMillis) {
    this->pin = pin;
    this->touchThresholdSensibility = touchThresholdSensibility;
    this->debounceThresholdInMillis = debounceThresholdInMillis;    
  }
  void handleState() {
    if (touchRead(pin) < touchThresholdSensibility) {
      currentEvent = TOUCH_STATE::PRESSED;
    } else {
      currentEvent = TOUCH_STATE::RELEASED;
    }
    //cause we are having a lot of intermittence, I have to put this line of code to get first touch state
    if (currentEvent == TOUCH_STATE::PRESSED && currentState == TOUCH_STATE::RELEASED) {
      currentState = TOUCH_STATE::PRESSED;
      lastChangedStateTime = millis();
    } else if (currentEvent != currentState) {
      if (millis() - lastChangedStateTime > debounceThresholdInMillis) {
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