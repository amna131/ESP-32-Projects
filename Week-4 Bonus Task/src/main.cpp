//EMOJI
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Smiley Face Bitmap (16x16 pixels)
const unsigned char smiley_bmp[] PROGMEM = {
  0b00000000, 0b00000000,
  0b00000011, 0b11000000,
  0b00001100, 0b00110000,
  0b00010000, 0b00001000,
  0b00100000, 0b00000100,
  0b01000011, 0b11000010,
  0b01000100, 0b00100010,
  0b10001000, 0b00010001,
  0b10001000, 0b00010001,
  0b01000100, 0b00100010,
  0b01000011, 0b11000010,
  0b00100000, 0b00000100,
  0b00010000, 0b00001000,
  0b00001100, 0b00110000,
  0b00000011, 0b11000000,
  0b00000000, 0b00000000
};

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();

  // Draw bitmap (emoji/logo)
  display.drawBitmap(
    56, 24,           // X, Y position
    smiley_bmp,       // Bitmap array
    16, 16,           // Width, Height
    SSD1306_WHITE     // Color
  );

  display.display();
}

void loop() {
  // nothing
}