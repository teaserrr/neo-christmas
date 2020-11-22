#include <Adafruit_NeoPixel.h>
#include "Pixel.h"
#include "PixelCreator.h"

#define PIN      8
#define N_LEDS 100

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_RGB + NEO_KHZ800);
Pixel* sparklePixels[N_LEDS];
AllColoursCreator allColoursCreator;
RedAndGreenCreator redAndGreenCreator;

unsigned long timeToRun = 6 * 3600000;
unsigned long timeToSleep = 24 * 3600000 - timeToRun;
unsigned long startTime;

void setup() {
  //Serial.begin(19200);
  strip.begin();
  startTime = millis();

  for (int i = 0; i < N_LEDS; i++)
  {
    sparklePixels[i] = NULL;
  }
}

void loop() {
  if (millis() - startTime > timeToRun) {
      setAll(0, 0, 0);
      delay(timeToSleep);
      startTime = millis();
  }
  sparkle(redAndGreenCreator, 100, 1);
  delay(2);
}

void sparkle(const PixelCreator& creator, int newPixelDelayTime, int fadeSpeed) {
  static long lastNewPixel = 0;
  
  long currentMillis = millis();
  if (currentMillis - lastNewPixel > newPixelDelayTime)
  {
    lastNewPixel = currentMillis;
    int newPixel = random(N_LEDS);
    
    while (sparklePixels[newPixel] != NULL)
      newPixel = random(N_LEDS);

    //Serial.print("new pixel: ");
    //Serial.print(newPixel);
    //Serial.println();
   
    sparklePixels[newPixel] = creator.create(newPixel);
  }

  for (int i = 0; i < N_LEDS; i++)
  {
    Pixel* pixel = sparklePixels[i];
    if (pixel == NULL)
      continue;
    
    pixel->fade(fadeSpeed);
    setPixel(i, pixel->red(), pixel->green(), pixel->blue());
    if (pixel->done())
    {
      delete pixel;
      sparklePixels[i] = NULL;
      //Serial.print("pixel ");
      //Serial.print(i);
      //Serial.println(" is done");
    }
  }
  
  showStrip();  
}

void setPixel(int pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[pixel].r = red;
   leds[pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < N_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}
