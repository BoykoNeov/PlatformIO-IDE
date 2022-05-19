#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;
uint16_t dataNumber = 0;             // new for this version
bool firstSerialDataIn = false;

char displaybuffer[4] = {' ', ' ', ' ', ' '};
uint16_t displaybufferRAW[4] = {0,0,0,0};


void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
  //      dataNumber = 0;             // new for this version
        dataNumber = atoi(receivedChars);   // new for this version
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        Serial.print("Data as Number ... ");    // new for this version
        Serial.println(dataNumber);     // new for this version
        newData = false;
    }
}

void setup() {
  Serial.begin(9600);
  
  alpha4.begin(0x70);  // pass in the address

  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  
  alpha4.clear();
  alpha4.writeDisplay();

  // display every character, 
  for (uint8_t i='!'; i<='z'; i++) {
    alpha4.writeDigitAscii(0, i);
    alpha4.writeDigitAscii(1, i+1);
    alpha4.writeDigitAscii(2, i+2);
    alpha4.writeDigitAscii(3, i+3);
    alpha4.writeDisplay();
    
    delay(50);
  }
  Serial.println("Start typing to display!");
}

void loop() {
  while (!Serial.available())
  {
    if (firstSerialDataIn == false)
    {
      alpha4.writeDigitRaw(0, (uint16_t)random(32768) & (uint16_t)random(32768));
      alpha4.writeDigitRaw(1, (uint16_t)random(32768) & (uint16_t)random(32768));
      alpha4.writeDigitRaw(2, (uint16_t)random(32768) & (uint16_t)random(32768));
      alpha4.writeDigitRaw(3, (uint16_t)random(32768) & (uint16_t)random(32768));
      alpha4.writeDisplay();
      delay(50);
    }

    return;
  }
  
    firstSerialDataIn = true;
    recvWithEndMarker();
    showNewNumber();
  
// char c = Serial.read();
// if (! isprint(c)) return; // only printable!
  
 // scroll down display
//  displaybuffer[0] = displaybuffer[1];
//  displaybuffer[1] = displaybuffer[2];
//  displaybuffer[2] = displaybuffer[3];
//  displaybuffer[3] = c;

  //  scroll down display
  delay(50);

    if (displaybufferRAW[2] != displaybufferRAW[3])
  {
  displaybufferRAW[0] = displaybufferRAW[1];
  displaybufferRAW[1] = displaybufferRAW[2];
  displaybufferRAW[2] = displaybufferRAW[3];
  }

  displaybufferRAW[3] = dataNumber;
 
    // set every digit to the buffer
 alpha4.writeDigitRaw(0, displaybufferRAW[0]);
 alpha4.writeDigitRaw(1, displaybufferRAW[1]);
 alpha4.writeDigitRaw(2, displaybufferRAW[2]);
 alpha4.writeDigitRaw(3, displaybufferRAW[3]);
  
  // set every digit to the buffer
  //  alpha4.writeDigitAscii(0, displaybuffer[0]);
  //  alpha4.writeDigitAscii(1, displaybuffer[1]);
  //  alpha4.writeDigitAscii(2, displaybuffer[2]);
  //  alpha4.writeDigitAscii(3, displaybuffer[3]);
 
  // write it out!
  alpha4.writeDisplay();
}