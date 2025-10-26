// Name: Amna
// Roll No: 23-NTU-CS-1013
// Assignment No.1 Task A
// Title: Multiple LED Mode

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display setup
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// Pin connections
#define LED1 18
#define LED2 19
#define LED3 23
#define BUZZER 27
#define BTN_MODE 25
#define BTN_RESET 26

// Variables for LED control
int mode = 0; // 0=OFF, 1=Alternate Blink, 2=Both ON, 3=PWM Fade
unsigned long prevMillis = 0;
int pwmVal = 0;
bool fadeUp = true; // used for fade direction

// Function to show current mode on OLED
void showMode() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.print("LED Mode: ");

  // Display mode name
  if (mode == 0) display.print("OFF");
  else if (mode == 1) display.print("Alternate Blink");
  else if (mode == 2) display.print("Both ON");
  else if (mode == 3) display.print("PWM Fade");

  display.display();
}

void setup() {
  // Set pin modes
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  // Start OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showMode(); // show initial mode
}

void loop() {
  // When mode button is pressed, go to next mode
  if (!digitalRead(BTN_MODE)) {
    delay(200); // debounce delay
    mode = (mode + 1) % 4;
    showMode();
  }

  // When reset button is pressed, go back to OFF
  if (!digitalRead(BTN_RESET)) {
    delay(200); // debounce delay
    mode = 0;
    showMode();
  }

  // Mode 0: Both LEDs OFF
  if (mode == 0) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }

  // Mode 1: Alternate blinking LEDs
  else if (mode == 1) {
    if (millis() - prevMillis > 400) {
      prevMillis = millis();
      digitalWrite(LED1, !digitalRead(LED1));
      digitalWrite(LED2, !digitalRead(LED2));
    }
  }

  // Mode 2: Both LEDs ON
  else if (mode == 2) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }

  // Mode 3: LED3 fades using PWM
  else if (mode == 3) {
    analogWrite(LED3, pwmVal);
    if (fadeUp) pwmVal += 5; else pwmVal -= 5;

    // Change fade direction at limits
    if (pwmVal >= 255) fadeUp = false;
    if (pwmVal <= 0) fadeUp = true;

    delay(15); // smooth fading
  }
}
