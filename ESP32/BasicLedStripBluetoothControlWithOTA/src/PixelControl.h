#include <NeoPixelBrightnessBus.h>

#if !defined(pixelStrip)
#define pixelStrip

int LED_PIN;
int LED_COUNT;

void SetStripColorFromBT(char* inputChar);

void InitializeStrip();

#endif // pixelStrip