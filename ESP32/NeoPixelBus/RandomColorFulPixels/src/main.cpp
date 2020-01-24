#include <Arduino.h>
#include "hw.h"

#include <NeoPixelBrightnessBus.h>
NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp32Rmt0Sk6812Method> strip(LED_COUNT, LED_PIN);

RgbColor black(0);

RgbwColor currentColor[100];
RgbwColor nextColor[100];

void setup() {
    Serial.begin(115200);
    strip.Begin();
    strip.SetBrightness(255);
    strip.ClearTo(black);
    strip.Show();

    for (size_t i = 0; i < LED_COUNT; i++)
    {
      currentColor[i] = {(char)random(0,256), (char)random(0,256), (char)random(0,256), 0};
      strip.SetPixelColor(i, currentColor[i]);
    }

    strip.Show();
    delay(5000);
}

void loop() 
{
    for (size_t i = 0; i < LED_COUNT; i++)
    {
      nextColor[i] = {(char)random(0,256), (char)random(0,256), (char)random(0,256), 0};

      uint8_t randomizer = (uint8_t)random(0, 100);

      if (randomizer < 20)
      {
        nextColor[i].Darken((uint8_t)random(0,256));
      }

      randomizer = (uint8_t)random(0, 100);
      if (randomizer < 20 && nextColor[i].B >= 70)
      {
        nextColor[i].B = nextColor[i].B - 70;
      }

      randomizer = (uint8_t)random(0, 100);
      if (randomizer < 20 && nextColor[i].R <= 70)
      {
        nextColor[i].R = nextColor[i].R + 140;
      }
    }

    float currentColorMixRatio = 0.01;

    for (size_t i = 0; i < 100; i++)
    {
      for (size_t i = 0; i < LED_COUNT; i++)
      {
        strip.SetPixelColor(i, currentColor[i].LinearBlend(currentColor[i], nextColor[i], currentColorMixRatio));
      }

      strip.Show();
      delay(20);
      currentColorMixRatio += 0.01;
    }

    for (size_t i = 0; i < LED_COUNT; i++)
    {
      currentColor[i] = nextColor[i];
    }

    delay(500);

    // Print RAM usage
    Serial.println(ESP.getFreeHeap());
}