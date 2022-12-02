# esp32_touchread
ESP32 lib to control intermittence when reading touch button state.
Tested with ESP-WROOM-32D

# Usage
```c++
//include touch lib
#include "touch_button.h"
//set gpio pin
#define TOUCH_BUTTON_PIN 12 //GPIO pin
//set behavior
#define TOUCH_THERESHOLD_SENSIBILITY 40         //you should adjust it for the best that addapt in your project, 40 worked fine in our project
#define TOUCH_DEBOUNCE_THERESHOLD_INMILLIS 150  //you should adjust it for the best that addapt in your project, 150 worked fine in our project

//class initialization
TouchButton touchButton(TOUCH_BUTTON_PIN, TOUCH_THERESHOLD_SENSIBILITY, TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);

//we should call this methodo to handle bounce intermittence of touch sensor
touchButton.handleState();

//if you want to use boolean - touch button is pressed
if (touchButton.isPressed()) {
  //do some magic
}

//if you want to use boolean - touch button is released
if (!touchButton.isPressed()) {
  //do some magic
}

//if you want to use enum - touch button is pressed
if (touchButton.getCurrentState() == TOUCH_STATE::PRESSED) {
  //do some magic
}

//if you want to use enum - touch button is released
if (touchButton.getCurrentState() == TOUCH_STATE::RELEASED{
  //do some magic
}

//if you want to use like and int - 0 is released | 1 is pressed
if (static_cast<uint32_t>(touchButton.getCurrentState()) == 1){
  //do some magic
}


```

# Demo
```c++
#include "touch_button.h"

//set gpio pins
#define TOUCH_BUTTON_1_PIN 12
#define TOUCH_BUTTON_2_PIN 14
#define TOUCH_BUTTON_3_PIN 27

//set behavior
#define TOUCH_THERESHOLD_SENSIBILITY 40         //you should adjust it for the best that addapt in your project, 40 worked fine in our project
#define TOUCH_DEBOUNCE_THERESHOLD_INMILLIS 150  //you should adjust it for the best that addapt in your project, 150 worked fine in our project

TouchButton touchButton1(TOUCH_BUTTON_1_PIN, TOUCH_THERESHOLD_SENSIBILITY, TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);
TouchButton touchButton2(TOUCH_BUTTON_2_PIN, TOUCH_THERESHOLD_SENSIBILITY, TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);
TouchButton touchButton3(TOUCH_BUTTON_3_PIN, TOUCH_THERESHOLD_SENSIBILITY, TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);

void setup() {
  Serial.begin(115200);
  delay(1000);  // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop() {
  //we should call this method to handle bounce intermittence of touch sensor
  touchButton1.handleState();
  touchButton2.handleState();
  touchButton3.handleState();
  //use serial plotter to see magic happening :)
  Serial.print("TOUCH_BUTTON_1:");
  Serial.print(touchButton1.isPressed());
  Serial.print(",");
  Serial.print("TOUCH_BUTTON_2:");
  Serial.print(touchButton2.isPressed());
  Serial.print(",");
  Serial.print("TOUCH_BUTTON_3:");
  Serial.print(touchButton3.isPressed());
  Serial.println("");
}

```
