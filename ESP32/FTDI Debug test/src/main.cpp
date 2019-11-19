#include <Arduino.h>
 
uint32_t loopCounter = 0;
 
void setup() 
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("loop ");
  Serial.println(loopCounter++);
  vTaskDelay(2000);
}