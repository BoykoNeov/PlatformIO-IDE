#include <NeoPixelBrightnessBus.h>

#if !defined(pixelStrip)
#define pixelStrip

int LED_PIN;
int LED_COUNT;

// extern NeoPixelBrightnessBus<NeoGrbwFeature, NeoEsp32Rmt0Sk6812Method> strip();

void SetStripColorFromBT(char);

void InitializeStrip();

#endif // pixelStrip