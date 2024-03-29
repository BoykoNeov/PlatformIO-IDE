//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD or CS
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

// Go to https://xantorohara.github.io/led-matrix-editor to make or configure what you want to see on your LED matrix.


void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[8]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
  byte b[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
  byte c[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
  byte d[8]={B00000000,B00000000,B00011000,B00011000,B00011000,B00011000,B00000000,B00000000};
  byte e[8]={B00000000,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00000000};
  byte f[8]={B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000};
  byte g[8]={B00111100,B00100100,B00100100,B00100100,B00100100,B00100100,B00100100,B00111100};
  byte h[8]={B01111110,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B01111110};
  byte i[8]={B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111};
  byte j[8]={B00000000,B11111111,B10000001,B10000001,B10000001,B10000001,B11111111,B00000000};
  byte k[8]={B00000000,B00000000,B11111111,B10000001,B10000001,B11111111,B00000000,B00000000};
  byte l[8]={B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000};
  byte m[8]={B00000000,B00000000,B00000000,B01111110,B01111110,B00000000,B00000000,B00000000};
  byte n[8]={B00000000,B00000000,B00000000,B00111100,B00111100,B00000000,B00000000,B00000000};
  byte o[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};
  byte p[8]={B00000000,B00000000,B00111100,B00100100,B00100100,B00111100,B00000000,B00000000};
  byte q[8]={B00000000,B01111110,B01000010,B01000010,B01000010,B01000010,B01111110,B00000000};
  byte r[8]={B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111};
  byte s[8]={B00000000,B01111110,B01000010,B01000010,B01000010,B01000010,B01111110,B00000000};
  byte t[8]={B00000000,B00000000,B00111100,B00100100,B00100100,B00111100,B00000000,B00000000};
  byte u[8]={B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000};

  /* now display them one by one with a small delay */
  lc.setRow(0,0,a[0]);
  lc.setRow(0,1,a[1]);
  lc.setRow(0,2,a[2]);
  lc.setRow(0,3,a[3]);
  lc.setRow(0,4,a[4]);
  lc.setRow(0,5,a[5]);
  lc.setRow(0,6,a[6]);
  lc.setRow(0,7,a[7]);
  delay(delaytime);
  lc.setRow(0,0,b[0]);
  lc.setRow(0,1,b[1]);
  lc.setRow(0,2,b[2]);
  lc.setRow(0,3,b[3]);
  lc.setRow(0,4,b[4]);
  lc.setRow(0,5,b[5]);
  lc.setRow(0,6,b[6]);
  lc.setRow(0,7,b[7]);
  delay(delaytime);
  lc.setRow(0,0,c[0]);
  lc.setRow(0,1,c[1]);
  lc.setRow(0,2,c[2]);
  lc.setRow(0,3,c[3]);
  lc.setRow(0,4,c[4]);
  lc.setRow(0,5,c[5]);
  lc.setRow(0,6,c[6]);
  lc.setRow(0,7,c[7]);
  delay(delaytime);
  lc.setRow(0,0,d[0]);
  lc.setRow(0,1,d[1]);
  lc.setRow(0,2,d[2]);
  lc.setRow(0,3,d[3]);
  lc.setRow(0,4,d[4]);
  lc.setRow(0,5,d[5]);
  lc.setRow(0,6,d[6]);
  lc.setRow(0,7,d[7]);
  delay(delaytime);
  lc.setRow(0,0,e[0]);
  lc.setRow(0,1,e[1]);
  lc.setRow(0,2,e[2]);
  lc.setRow(0,3,e[3]);
  lc.setRow(0,4,e[4]);
  lc.setRow(0,5,e[5]);
  lc.setRow(0,6,e[6]);
  lc.setRow(0,7,e[7]);
  delay(delaytime);
  lc.setRow(0,0,f[0]);
  lc.setRow(0,1,f[1]);
  lc.setRow(0,2,f[2]);
  lc.setRow(0,3,f[3]);
  lc.setRow(0,4,f[4]);
  lc.setRow(0,5,f[5]);
  lc.setRow(0,6,f[6]);
  lc.setRow(0,7,f[7]);
  delay(delaytime);
  lc.setRow(0,0,g[0]);
  lc.setRow(0,1,g[1]);
  lc.setRow(0,2,g[2]);
  lc.setRow(0,3,g[3]);
  lc.setRow(0,4,g[4]);
  lc.setRow(0,5,g[5]);
  lc.setRow(0,6,g[6]);
  lc.setRow(0,7,g[7]);
  delay(delaytime);
  lc.setRow(0,0,h[0]);
  lc.setRow(0,1,h[1]);
  lc.setRow(0,2,h[2]);
  lc.setRow(0,3,h[3]);
  lc.setRow(0,4,h[4]);
  lc.setRow(0,5,h[5]);
  lc.setRow(0,6,h[6]);
  lc.setRow(0,7,h[7]);
  delay(delaytime);
  lc.setRow(0,0,i[0]);
  lc.setRow(0,1,i[1]);
  lc.setRow(0,2,i[2]);
  lc.setRow(0,3,i[3]);
  lc.setRow(0,4,i[4]);
  lc.setRow(0,5,i[5]);
  lc.setRow(0,6,i[6]);
  lc.setRow(0,7,i[7]);
  delay(delaytime);
  lc.setRow(0,0,j[0]);
  lc.setRow(0,1,j[1]);
  lc.setRow(0,2,j[2]);
  lc.setRow(0,3,j[3]);
  lc.setRow(0,4,j[4]);
  lc.setRow(0,5,j[5]);
  lc.setRow(0,6,j[6]);
  lc.setRow(0,7,j[7]);
  delay(delaytime);
  lc.setRow(0,0,k[0]);
  lc.setRow(0,1,k[1]);
  lc.setRow(0,2,k[2]);
  lc.setRow(0,3,k[3]);
  lc.setRow(0,4,k[4]);
  lc.setRow(0,5,k[5]);
  lc.setRow(0,6,k[6]);
  lc.setRow(0,7,k[7]);
  delay(delaytime);
  lc.setRow(0,0,l[0]);
  lc.setRow(0,1,l[1]);
  lc.setRow(0,2,l[2]);
  lc.setRow(0,3,l[3]);
  lc.setRow(0,4,l[4]);
  lc.setRow(0,5,l[5]);
  lc.setRow(0,6,l[6]);
  lc.setRow(0,7,l[7]);
  delay(delaytime);
  lc.setRow(0,0,m[0]);
  lc.setRow(0,1,m[1]);
  lc.setRow(0,2,m[2]);
  lc.setRow(0,3,m[3]);
  lc.setRow(0,4,m[4]);
  lc.setRow(0,5,m[5]);
  lc.setRow(0,6,m[6]);
  lc.setRow(0,7,m[7]);
  delay(delaytime);
  lc.setRow(0,0,n[0]);
  lc.setRow(0,1,n[1]);
  lc.setRow(0,2,n[2]);
  lc.setRow(0,3,n[3]);
  lc.setRow(0,4,n[4]);
  lc.setRow(0,5,n[5]);
  lc.setRow(0,6,n[6]);
  lc.setRow(0,7,n[7]);
  delay(delaytime);
  lc.setRow(0,0,o[0]);
  lc.setRow(0,1,o[1]);
  lc.setRow(0,2,o[2]);
  lc.setRow(0,3,o[3]);
  lc.setRow(0,4,o[4]);
  lc.setRow(0,5,o[5]);
  lc.setRow(0,6,o[6]);
  lc.setRow(0,7,o[7]);
  delay(delaytime);
  lc.setRow(0,0,p[0]);
  lc.setRow(0,1,p[1]);
  lc.setRow(0,2,p[2]);
  lc.setRow(0,3,p[3]);
  lc.setRow(0,4,p[4]);
  lc.setRow(0,5,p[5]);
  lc.setRow(0,6,p[6]);
  lc.setRow(0,7,p[7]);
  delay(delaytime);
  lc.setRow(0,0,q[0]);
  lc.setRow(0,1,q[1]);
  lc.setRow(0,2,q[2]);
  lc.setRow(0,3,q[3]);
  lc.setRow(0,4,q[4]);
  lc.setRow(0,5,q[5]);
  lc.setRow(0,6,q[6]);
  lc.setRow(0,7,q[7]);
  delay(delaytime);
  lc.setRow(0,0,r[0]);
  lc.setRow(0,1,r[1]);
  lc.setRow(0,2,r[2]);
  lc.setRow(0,3,r[3]);
  lc.setRow(0,4,r[4]);
  lc.setRow(0,5,r[5]);
  lc.setRow(0,6,r[6]);
  lc.setRow(0,7,r[7]);
  delay(delaytime);
  lc.setRow(0,0,s[0]);
  lc.setRow(0,1,s[1]);
  lc.setRow(0,2,s[2]);
  lc.setRow(0,3,s[3]);
  lc.setRow(0,4,s[4]);
  lc.setRow(0,5,s[5]);
  lc.setRow(0,6,s[6]);
  lc.setRow(0,7,s[7]);
  delay(delaytime);
  lc.setRow(0,0,t[0]);
  lc.setRow(0,1,t[1]);
  lc.setRow(0,2,t[2]);
  lc.setRow(0,3,t[3]);
  lc.setRow(0,4,t[4]);
  lc.setRow(0,5,t[5]);
  lc.setRow(0,6,t[6]);
  lc.setRow(0,7,t[7]);
  delay(delaytime);
  lc.setRow(0,0,u[0]);
  lc.setRow(0,1,u[1]);
  lc.setRow(0,2,u[2]);
  lc.setRow(0,3,u[3]);
  lc.setRow(0,4,u[4]);
  lc.setRow(0,5,u[5]);
  lc.setRow(0,6,u[6]);
  lc.setRow(0,7,u[7]);
  delay(delaytime);
}

void loop() { 
  writeArduinoOnMatrix();
}