#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

void setup() {
  Keyboard.begin();
  USB.begin();
  
  delay(2000);
  // Win+R
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(500);
  Keyboard.releaseAll();
  delay(500);
  // notepad + Enter
  Keyboard.print("notepad");
  delay(500);
  Keyboard.write('\n');
  delay(1000); // allow Notepad to open
  // type message
  Keyboard.print("Hello Notepad");
  Keyboard.write('\n');
}

void loop() {
}
