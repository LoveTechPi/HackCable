#include <Adafruit_NeoPixel.h>

#define LED_PIN    25     // GPIO pin connected to DIN
#define LED_COUNT  1     // Number of WS2812 LEDs

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();          // Turn off all LEDs
}

void loop() {
  // Red ON
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  delay(500);

  // OFF
  strip.clear();
  strip.show();
  delay(500);

  // Green ON
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
  delay(500);

  // OFF
  strip.clear();
  strip.show();
  delay(500);

  // Blue ON
  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.show();
  delay(500);

  // OFF
  strip.clear();
  strip.show();
  delay(500);
}
