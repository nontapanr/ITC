#include <SoftwareSerial.h>
#include "FontLEDClock.h" // Font library
#include "LedControl.h"

SoftwareSerial mySerial(2, 3); // SoftwareSerial(rxPin, txPin)
String inputString = "";
String curInput = "";
String Axis = "X:";
String Input = "";

LedControl lc=LedControl(12,11,10,4);  // DIN,CLK,CS,Number of LED Module
unsigned long delaytime=50;  // time to updates of the display
void plot (uint8_t xx, uint8_t yy, uint8_t value) {

  //select which matrix depending on the x coord
  uint8_t address;
  if (xx >= 0 && xx <= 7)   { address = 3; }
  if (xx >= 8 && xx <= 15)  { address = 2; xx = xx - 8; }
  if (xx >= 16 && xx <= 23) { address = 1; xx = xx - 16;}
  if (xx >= 24 && xx <= 31) { address = 0; xx = xx - 24;}

  if (value == 1) {
    lc.setLed(address, yy, xx, true);
  } else {
    lc.setLed(address, yy, xx, false);
  }
}

void print_normal_char(uint8_t x, uint8_t y, char c)
{
  uint8_t dots;
  if (c >= 'A' && c <= 'Z' ) { c &= 0x1F; }  // A-Z maps to 1-26
  else if (c >= 'a' && c <= 'z') { c = (c - 'a') + 41; }  // A-Z maps to 41-67
  else if (c >= '0' && c <= '9') { c = (c - '0') + 31; }
  else if (c == ' ') { c = 0; } // space
  else if (c == '.') { c = 27; } // full stop
  else if (c == '\'') { c = 28; } // single quote mark
  else if (c == ':') { c = 29; } // clock_mode selector arrow
  else if (c == '>') { c = 30; } // clock_mode selector arrow
  else if (c >= -80 && c <= -67) { c *= -1; }

  for (uint8_t col = 0; col < 5; col++) {
    dots = pgm_read_byte_near(&myfont[c][col]);
    for (uint8_t row = 0; row < 7; row++) {
      if (dots & (64 >> row)) {   // only 7 rows.
        plot(x + col, y + row, 1);
      } else {
        plot(x + col, y + row, 0);
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  mySerial.begin(2400);

  int devices=lc.getDeviceCount();
  for(int address=0;address<devices;address++) {
    lc.shutdown(address,false);
    lc.setIntensity(address,8);
    lc.clearDisplay(address);
  }
}

void loop()
{
  int i = 0;
  if (mySerial.available()) {
    Input = mySerial.readStringUntil('#');
    curInput = Axis + Input;
  }
  while (curInput[i] != '\0') {
    print_normal_char((i * 6), 1, curInput[i]);
    i++;
  }
  Serial.println(curInput);
}

bool isReceiving = false;

void serialEvent() {
  while (Serial.available()) // recheck serial is available
  {
    char inChar = (char) Serial.read(); // get the new byte:
    inputString += inChar; // add it to the inputString:     
  }
}
