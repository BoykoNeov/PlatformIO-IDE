#include <NeoPixelBrightnessBus.h>

const int LED_PIN = 4;
const int LED_COUNT = 100;

NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp32Rmt0Sk6812Method> strip(LED_COUNT, LED_PIN);

RgbColor black(0);
RgbwColor currentColor[LED_PIN];
RgbwColor nextColor[LED_PIN];

void InitializeStrip()
{
    strip.Begin();
    strip.SetBrightness(255);
    strip.ClearTo(black);
    strip.Show();
}

void SetStripColorFromBT(char inputChar)
{
    char green = 0;
    char red = 0;
    char blue = 0;
    char white = 0;

    if (inputChar == 'g')
    {
        green = 255;
    }

    if (inputChar == 'r')
    {
        red = 255;
    }

        if (inputChar == 'b')
    {
        blue = 255;
    }

        if (inputChar == 'w')
    {
        white = 255;
    }

    for (size_t i = 0; i < LED_COUNT; i++)
    {
        RgbwColor currentColor = {red, green, blue, white};
        strip.SetPixelColor(i, currentColor);
    }

    strip.Show();
    
}