#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCDADDR 0x27
#define NUMPIXELS 67
#define NUMCOLS 16
#define NUMROWS 2

#define TEXTDELAY 500
#define LEDDELAY 250

int textOffset = 0-NUMCOLS;
int ledOffset = 0;

char message[] = "Merry Christmas Everybody!";
int length = 26;

Adafruit_NeoPixel pixels(NUMPIXELS, 13, NEO_GRB);
LiquidCrystal_I2C lcd(LCDADDR, NUMCOLS, NUMROWS);

unsigned long textElapsed = 0;
unsigned long ledElapsed = 0;

void setup() {
  Serial.begin(115200);
  delay(3000);
  
  Serial.println("ESP32");

  pixels.begin();
  pixels.setBrightness(20);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("* * * *  * * * *");
}

void doText() {
  lcd.setCursor(0, 0);
  for (int i = 0; i < NUMCOLS; i++) {
    if (i+textOffset >= length || i+textOffset < 0) {
      lcd.print(' ');
    } else {
      lcd.print(message[i+textOffset]);
    }
  }
  
  textOffset++;
  if (textOffset>length) {
    textOffset = 0-NUMCOLS;
  }
}

void doLed() {
  for (int i = 0; i < NUMPIXELS; i++) {
    switch ((ledOffset+i) % 3) {
      case 0:
        pixels.setPixelColor(i, 255, 0, 0);
        break;
      case 1:
        pixels.setPixelColor(i, 0, 255, 0);
        break;
      case 2:
        pixels.setPixelColor(i, 0, 0, 255);
        break;
    }
  }
  pixels.show();

  ledOffset++;
  if (ledOffset>2) {
    ledOffset = 0;
  }
}

void loop() {
  unsigned long m = millis();

  if (m-textElapsed > TEXTDELAY) {
    doText();
    textElapsed = m;
  }

  if (m-ledElapsed > LEDDELAY) {
    doLed();
    ledElapsed = m;
  }
}
