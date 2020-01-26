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

void SetStripColorFromBT(char* str)
{
    // do nothing if receive empty
    if (*str == '\0')
    {
        return;
    }

    char *splittedInputs[sizeof(strtok(str, " "))];

    int8_t countWhiteSpaces = 0;

    char currentChar = 1;
    uint8_t currentCharCounter = 0;

    // Counts white spaces in the input in order to determine the number of resulting variables
    while (currentChar != '\0')
    {
        currentChar = *(str + currentCharCounter);

        if (currentChar == ' ')
        {
            countWhiteSpaces++;
        }

        currentCharCounter++;
    }
    

    if(sizeof(splittedInputs) > 0)
    {
        splittedInputs[0] = strtok(str, " "); // Splits spaces between words in str

        for(int i = 1; i < sizeof(strtok(str, " ")); i++)
        {
            splittedInputs[i] = strtok (NULL, " ");
        }
    }

    char green = 0;
    char red = 0;
    char blue = 0;
    char white = 0;

    char inputChar = splittedInputs[0][0];

    if (!(inputChar >= 48 && inputChar <= 57))
    {
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
    else
    {
        // Serial.println(sizeof(&str));  // the pointer itself = 4 bytes
        // Serial.println(sizeof(*str)); // the first char element? 1 byte

        // If you dont do this check and try to do atol on a non existing element, the microcontroller crashes
        if (countWhiteSpaces >= 0)
        {
            red = (char)atoi(splittedInputs[0]);
            countWhiteSpaces--;
        }

        if (countWhiteSpaces >= 0)
        {
            green = (char)atoi(splittedInputs[1]);
            countWhiteSpaces--;
        }

        if (countWhiteSpaces >= 0)
        {
            blue = (char)atoi(splittedInputs[2]);
            countWhiteSpaces--;
        }

        if (countWhiteSpaces >= 0)
        {
            white = (char)atoi(splittedInputs[3]);
            countWhiteSpaces--;
        }

        for (size_t i = 0; i < LED_COUNT; i++)
        {
            RgbwColor currentColor = {red, green, blue, white};
            strip.SetPixelColor(i, currentColor);
        }

        strip.Show();
    }
  }