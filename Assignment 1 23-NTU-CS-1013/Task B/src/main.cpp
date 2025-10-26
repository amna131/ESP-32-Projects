// Name: Amna
// Roll No: 23-NTU-CS-1013   BSCS-5A
// Assignment No.1 
// Task B
// Title: Buzzer Tone + LED Toggle

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// pin connections
#define LED1 18
#define LED2 19
#define LED3 23
#define BUZZER 27
#define BTN_MODE 25   //  button in yellow color

#define LONG_PRESS_TIME 1500  // 1.5 sec for long press


bool ledState = false;
bool isPressed = false;
unsigned long pressStart = 0;

void setup() {
  Serial.begin(115200);   // start serial monitor for debugging

  // setting up pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_MODE, INPUT_PULLUP);   // using pull-up since button goes to GND

  // initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found :(");
    while (1);  // stop here if display not connected
  }

  // show startup message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("System Ready...");
  display.display();

  // make sure everything starts off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(BUZZER, LOW);
}

void loop() {
  bool buttonPressed = (digitalRead(BTN_MODE) == LOW);  // check if button pressed

  // when button is pressed
  if (buttonPressed && !isPressed) {
    isPressed = true;
    pressStart = millis();   // record time when pressed
  }

  // when button is released
  if (!buttonPressed && isPressed) {
    unsigned long pressDuration = millis() - pressStart;
    isPressed = false;

    // check if it was long or short press
    if (pressDuration >= LONG_PRESS_TIME) {
      handleLongPress();
    } else {
      handleShortPress();
    }
  }
}

// function for short press
// toggles LEDs on/off and shows it on screen
void handleShortPress() {
  ledState = !ledState;   // change LED state

  digitalWrite(LED1, ledState);
  digitalWrite(LED2, ledState);
  digitalWrite(LED3, ledState);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Short Press");
  display.println(ledState ? "LEDs turned ON" : "LEDs turned OFF");
  display.display();
  Serial.println("Short press detected");
}

// function for long press
// plays buzzer sound for 0.5 second
void handleLongPress() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Long Press");
  display.println("Buzzer playing...");
  display.display();

  Serial.println("Long press detected");

  tone(BUZZER, 1000);   // 1kHz tone
  delay(500);           // play for half second
  noTone(BUZZER);       // stop buzzer
}
