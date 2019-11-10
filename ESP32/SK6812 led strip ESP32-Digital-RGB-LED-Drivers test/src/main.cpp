#include <Arduino.h>

/* 
 * Demo code for driving multiple digital RGB(W) strands using esp32_digital_led_lib
 *
 * Modifications Copyright (c) 2017-2019 Martin F. Falatic
 *
 * Based on public domain code created 19 Nov 2016 by Chris Osborn <fozztexx@fozztexx.com>
 * http://insentricity.com
 *
 */

/* 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#if defined(ARDUINO) && ARDUINO >= 100
  // No extras
#elif defined(ARDUINO) // pre-1.0
  // No extras
#elif defined(ESP_PLATFORM)
  #include "arduinoish.hpp"
#endif

#include "esp32_digital_led_lib.h"
#include "esp32_digital_led_funcs.h"

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

// **Required** if debugging is enabled in library header
// TODO: Is there any way to put this in digitalLeds_addStrands() and avoid undefined refs?
#if DEBUG_ESP32_DIGITAL_LED_LIB
  int digitalLeds_debugBufferSz = 1024;
  char * digitalLeds_debugBuffer = static_cast<char*>(calloc(digitalLeds_debugBufferSz, sizeof(char)));
#endif


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"  

strand_t STRANDS[] = 
{
  {.rmtChannel = 0, .gpioNum = 4, .ledType = LED_SK6812W_V1, .brightLimit = 255, .numPixels =  30},
};

#pragma GCC diagnostic pop

int STRANDCNT = COUNT_OF(STRANDS);


//**************************************************************************//
int getMaxMalloc(int min_mem, int max_mem) 
{
  int prev_size = min_mem;
  int curr_size = min_mem;
  int max_free = 0;

  while (1) 
  {
    void * foo1 = malloc(curr_size);
    if (foo1 == nullptr) {  // Back off
      max_mem = std::min(curr_size, max_mem);

      curr_size = (int)(curr_size - (curr_size - prev_size) / 2.0);

    }
    else 
    {  // Advance
      free(foo1);
      max_free = curr_size;
      prev_size = curr_size;
      curr_size = std::min(curr_size * 2, max_mem);
    }
    if (abs(curr_size - prev_size) == 0) {
      break;
    }
  }
  Serial.print("checkmem: max free heap = ");
  Serial.print(esp_get_free_heap_size());
  Serial.print(" bytes, max allocable = ");
  Serial.print(max_free);
  Serial.println(" bytes");
  return max_free;
}


void dumpSysInfo() 
{
  esp_chip_info_t sysinfo;
  esp_chip_info(&sysinfo);
  Serial.print("Model: ");
  Serial.print((int)sysinfo.model);
  Serial.print("; Features: 0x");
  Serial.print((int)sysinfo.features, HEX);
  Serial.print("; Cores: ");
  Serial.print((int)sysinfo.cores);
  Serial.print("; Revision: r");
  Serial.println((int)sysinfo.revision);
}

void dumpDebugBuffer(int id, char * debugBuffer)
{
  Serial.print("DEBUG: (");
  Serial.print(id);
  Serial.print(") ");
  Serial.println(debugBuffer);
  debugBuffer[0] = 0;
}


//**************************************************************************//
bool initStrands()
{

  digitalLeds_initDriver();

  for (int i = 0; i < STRANDCNT; i++) 
  {
    gpioSetup(STRANDS[i].gpioNum, OUTPUT, LOW);
  }

  strand_t * strands[8];
  for (int i = 0; i < STRANDCNT; i++) 
  {
    strands[i] = &STRANDS[i];
  }
  int rc = digitalLeds_addStrands(strands, STRANDCNT);
  if (rc) 
  {
    Serial.print("Init rc = ");
    Serial.println(rc);
    return false;
  }

  for (int i = 0; i < STRANDCNT; i++) {
    strand_t * pStrand = strands[i];
    Serial.print("Strand ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print((uint32_t)(pStrand->pixels), HEX);
    Serial.println();
    #if DEBUG_ESP32_DIGITAL_LED_LIB
      dumpDebugBuffer(-2, digitalLeds_debugBuffer);
    #endif
  }

  return true;
}

//**************************************************************************//
void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");
  dumpSysInfo();
  getMaxMalloc(1*1024, 16*1024*1024);

  if (!initStrands()) {
    Serial.println("Init FAILURE: halting");
    while (true) {
      delay(100);
    }
  }
  delay(100);
  Serial.println("Init complete");
}


//**************************************************************************//
void loop()
{
  strand_t * strands [STRANDCNT];
  for (int i = 0; i < STRANDCNT; i++) {
    strands[i] = &STRANDS[i];
  }

  digitalLeds_resetPixels(strands, STRANDCNT);

  int m1 = getMaxMalloc(1*1024, 16*1024*1024);

  for (int i = STRANDCNT; i > 0; i--) {
    randomStrands(strands, i, 0, 1000);
  }

  for (int i = STRANDCNT; i > 0; i--) {
    randomStrands(strands, i, 100, 3000);
  }

  for (int i = STRANDCNT; i > 0; i--) {
    scanners(strands, i, 0, 2000);
  }

  for (int i = STRANDCNT; i >= 0; i--) {
    rainbows(strands, i, 0, 4000);
  }

  int m2 = getMaxMalloc(1*1024, 16*1024*1024);
  assert(m2 >= m1); // Sanity check

  digitalLeds_resetPixels(strands, STRANDCNT);
}
//**************************************************************************//