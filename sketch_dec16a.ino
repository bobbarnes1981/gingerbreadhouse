#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NUMPIXELS 67

int ledOffset = 0;
char message[] = "Merry Christmas Everybody! Ho Ho Ho";

Adafruit_NeoPixel pixels(NUMPIXELS, 13, NEO_GRB);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  delay(3000);
  
  Serial.println("ESP32");

  pixels.begin();
  pixels.setBrightness(20);

  lcd.init();
  lcd.backlight();
  lcd.print(message);
}

void loop() {
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
  
  lcd.scrollDisplayLeft();

  sleep(1);
}
