#include <Arduino.h>
#include "hw.h"

#include <NeoPixelBrightnessBus.h>
NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp32Rmt0Sk6812Method> strip(LED_COUNT, LED_PIN);

void setup() {
    Serial.begin(115200);

    strip.Begin();
    strip.SetBrightness(255);
    strip.Show();
}

RgbColor green(0, 0x80, 0);
RgbColor black(0);
RgbwColor p;

void loop() 
{
    strip.ClearTo(black);
    strip.Show();
    delay(100);

    uint32_t startOfCycle;
    uint32_t endOfCycle;

    startOfCycle = micros();
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        strip.SetPixelColor(i, {255, 0, 0, 0});
    }
    strip.Show();
    endOfCycle = micros();

    // Display time in micros of one cycle
    Serial.println(endOfCycle - startOfCycle);

    delay(5000);

    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        strip.SetPixelColor(i, {0, 255, 0, 0});
    }
    strip.Show();
    delay(5000);

    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        strip.SetPixelColor(i, {0, 0, 255, 0});
    }
    strip.Show();
   delay(5000);

    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        strip.SetPixelColor(i, {0, 0, 0, 255});
    }
    strip.Show();
   delay(5000);

    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        strip.SetPixelColor(i, {255, 255, 255, 255});
    }
    strip.Show();
   delay(5000);

       for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        strip.SetPixelColor(i, {(char)random(0,256), (char)random(0,256), (char)random(0,256), 0});
    }
    strip.Show();
    delay(5000);

    strip.ClearTo(black);
    strip.Show();

    // Print RAM usage
    Serial.println(ESP.getFreeHeap());
}