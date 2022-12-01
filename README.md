# esp32_touchread
ESP32 lib to control intermittence when reading touch button state.
Tested with ESP-WROOM-32D

# Usage
```c++
//include touch lib
#include "touch_button.h"
//global vars
#define TOUCH_BUTTON_PIN 12 //GPIO pin
#define TOUCH_DEBOUNCE_THERESHOLD_INMILLIS 150  //you should adjust it for the best that addapt in your project, 150 worked fine for our project

//class initialization
TouchButton touchButton(TOUCH_BUTTON_PIN);

//we should call this methodo to handle bounce intermittence of touch sensor
touchButton.handleState(TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);

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

#define TOUCH_BUTTON_1_PIN 12
#define TOUCH_BUTTON_2_PIN 14
#define TOUCH_BUTTON_3_PIN 27
#define TOUCH_DEBOUNCE_THERESHOLD_INMILLIS 150  //you should adjust it for the best that addapt in your project, 150 worked fine for our project

TouchButton touchButton1(TOUCH_BUTTON_1_PIN);
TouchButton touchButton2(TOUCH_BUTTON_2_PIN);
TouchButton touchButton3(TOUCH_BUTTON_3_PIN);


void setup() {
  Serial.begin(115200);
  delay(1000);  // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void loop() {

  //we should call this methodo to handle bounce intermittence of touch sensor
  touchButton1.handleState(TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);
  touchButton2.handleState(TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);
  touchButton3.handleState(TOUCH_DEBOUNCE_THERESHOLD_INMILLIS);

  //here we use methods to verify if touch button is pressed or released
  //we can use:
  //  touchButton1.isPressed() //touch button is pressed
  //  !touchButton1.isPressed() //touch button is released
  //  touchButton1.getCurrentState() == TOUCH_STATE::PRESSED  //touch button is pressed
  //  touchButton1.getCurrentState() == TOUCH_STATE::RELEASED //touch button is released
  //  static_cast<uint32_t>(touchButton2.getCurrentState())   //0 is released | 1 is pressed

  //use serial plotter to see magic happening :)
  Serial.print("TOUCH_BUTTON_1:");
  Serial.print(touchButton1.isPressed());
  Serial.print(",");
  Serial.print("TOUCH_BUTTON_2:");
  Serial.print(touchButton2.isPressed());
  Serial.print(",");
  Serial.print("TOUCH_BUTTON_3:");
  Serial.print(touchButton3.isPressed());
  
  /*
  //uncomment here if you want to use serial monitor 
  //I have found 
  Serial.print(",");  
  Serial.print("TOUCH_BUTTON_1_AS_STRING:");
  Serial.print(touchButton1.getCurrentState() == TOUCH_STATE::PRESSED ? "PRESSED" : "RELEASED");
  Serial.print(",");
  Serial.print("TOUCH_BUTTON_2_AS_STRING:");
  Serial.print(touchButton2.getCurrentState() == TOUCH_STATE::PRESSED ? "PRESSED" : "RELEASED");
  Serial.print(",");
  Serial.print("TOUCH_BUTTON_3_AS_STRING:");
  Serial.print(touchButton3.getCurrentState() == TOUCH_STATE::PRESSED ? "PRESSED" : "RELEASED");
  */
  Serial.println("");
}

```
