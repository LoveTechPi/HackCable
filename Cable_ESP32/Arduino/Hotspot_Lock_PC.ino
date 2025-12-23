#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "USB.h"
#include "USBHIDKeyboard.h"

// ===== CONFIG =====
const char* ap_ssid     = "HACKCABLE";
const char* ap_password = "12345678"; // >=8 chars for WPA2

#define LED_PIN    10      // WS2812 data pin
#define LED_COUNT  1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);
WebServer server(80);

// USB HID
USBHIDKeyboard Keyboard;
USBHID HID;
bool hidReady = false;

// ===== HTML page (includes button for sending 1 to lock the PC) =====
String htmlPage() {
  String html = "<!doctype html><html><head><meta charset='utf-8'>"
                "<meta name='viewport' content='width=device-width,initial-scale=1'>"
                "<title>HACKCABLE</title>"
                "<style>body{font-family:Arial;background:#111;color:#eee;text-align:center} .card{background:#222;padding:18px;border-radius:10px;display:inline-block;margin:18px}</style>"
                "</head><body>"
                "<h2>HACKCABLE WiFi Demo</h2>"
                "<div class='card'>"
                "<form action='/lock' method='POST'>"
                "<button type='submit' name='action' value='1'>Lock PC</button>"
                "</form></div>"
                "<div class='card'>"
                "<p><b>HID ready:</b> " + String(hidReady ? "YES" : "NO") + "</p>"
                "</div>"
                "</body></html>";
  return html;
}

// ===== LED helpers =====
void setColorHex(String hex) {
  if (hex.startsWith("#")) hex = hex.substring(1);
  long val = strtol(hex.c_str(), NULL, 16);
  uint8_t r = (val >> 16) & 0xFF;
  uint8_t g = (val >> 8) & 0xFF;
  uint8_t b = val & 0xFF;
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}

void flash(uint8_t r, uint8_t g, uint8_t b, int ms = 200) {
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
  delay(ms);
  strip.setPixelColor(0, 0);
  strip.show();
}

// ===== HID helpers =====
void lockWorkstation() {
  // Win+L to lock the PC
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('l');
  delay(100);
  Keyboard.releaseAll();
}

// ===== Web handlers =====
void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void handleLock() {
  // Check if the "action" POST data is "1"
  if (server.hasArg("action") && server.arg("action") == "1") {
    if (hidReady) {
      flash(255, 100, 0, 120); // orange flash
      lockWorkstation();
      flash(0, 0, 0, 50);
    } else {
      flash(150, 0, 0, 200); // red = not ready
    }
  }
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

// ===== Setup =====
void setup() {
  Serial.begin(115200);
  delay(100);

  strip.begin();
  strip.show();
  strip.setPixelColor(0, 0);
  strip.show();

  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAP(ap_ssid, ap_password);
  IPAddress ip = WiFi.softAPIP();
  Serial.println("AP started: " + String(ap_ssid));
  Serial.print("Visit http://");
  Serial.println(ip);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/lock", HTTP_POST, handleLock);
  server.onNotFound(handleNotFound);
  server.begin();

  delay(2000);
  HID.begin();
  Keyboard.begin();
  USB.begin();
  hidReady = true;
  Serial.println("USB HID ready.");
}

// ===== Loop =====
void loop() {
  server.handleClient();
}
