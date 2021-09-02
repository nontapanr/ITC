#include <LedControl.h>
#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_E 6
#define BUTTON_F 7

int DIN = 13;
int CS = 12;
int CLK = 11;

int randNumber;
LedControl lc = LedControl(DIN, CLK, CS, 0);

int roundrand = 0 ;
int roundshow = 0;
int randvalues = 0 ;

int examine ;

int button1 ;
int button2 ;
int button3 ;
int button4 ;

int maxmark =10;
int mark =0;


byte one[8] = {0x00, 0x18, 0x18, 0x38, 0x18, 0x18, 0x18, 0x7E};
byte two[8] = {0x00, 0x3C, 0x66, 0x06, 0x0C, 0x30, 0x60, 0x7E};
byte three[8] = {0x00, 0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C};

byte above[8] = {0x00, 0x10, 0x38, 0x7C, 0xFE, 0x38, 0x38, 0x38};
byte below[8] = {0x38, 0x38, 0x38, 0x38, 0xFE, 0x7C, 0x38, 0x10};
byte Left[8] = {0x00, 0x10, 0x30, 0x7F, 0xFF, 0x7F, 0x30, 0x10};
byte right[8] = {0x00, 0x08, 0x0C, 0xFE, 0xFF, 0xFE, 0x0C, 0x08};

byte exclamation[8] = {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00};
byte love[8] ={0x00,0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18};
byte nolove[8] = {0xFF,0x99,0x00,0x00,0x00,0x81,0xC3,0xE7};

byte sm[8]={0x42,0xE7,0x42,0x18,0x18,0x81,0x42,0x3C};
byte nosm[8]={0x00,0x66,0x66,0x00,0x00,0x3C,0x42,0x00};

void printByte(byte character[]){
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }
}

void start(){
  printByte(three);
  delay(500);
  printByte(two);
  delay(500);
  printByte(one);
  delay(500);
}

void randomnumber(){
 while ( roundrand ==0 ){
 randNumber = random(1,5);
 roundrand = 1 ;
 roundshow = 0 ;
 Serial.println(randNumber);
 }
}

void randshow(){
 while ( roundrand ==1 && roundshow ==0 )
 {
 if (randNumber == 1 )
  {
    printByte(above);
    roundshow = 1;
    randvalues = 0;
  }

  else if (randNumber == 2)
  {
    printByte(below);
    roundshow = 1;
    randvalues = 0;

  }

  else if (randNumber == 3)
  {
    printByte(Left);
    roundshow = 1;
    randvalues = 0;
  }

  else if (randNumber == 4)
  {
    printByte(right);
    roundshow = 1;
    randvalues = 0;
  }
 }
}

void setvalues(){
 while (roundrand ==1 && roundshow ==1 && randvalues == 0)
  {
   button1 = digitalRead(BUTTON_UP);
   button2 = digitalRead(BUTTON_RIGHT);
   button3 = digitalRead(BUTTON_DOWN);
   button4 = digitalRead(BUTTON_LEFT);
 if (button1==LOW)
  {
    examine = 1 ; randvalues =1 ;
  }
 if (button2==LOW)
  {
    examine = 4 ; randvalues =1 ;

  }
 if (button3==LOW)
 {
  examine = 2 ; randvalues =1 ;
 }
 if (button4==LOW)
 {
  examine = 3 ; randvalues =1 ;
 }
 }
}

void valuesshow(){
  while (roundrand ==1 && roundshow ==1 && randvalues == 1){
    if (randNumber == examine)
    {
      printByte(sm);
      delay(300);
      roundrand =0;
      mark ++ ;
      Serial.println(mark);
    }

    else
    {
      printByte(nosm);
      delay(300);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_UP, INPUT);
  digitalWrite(BUTTON_UP, HIGH);

  pinMode(BUTTON_RIGHT, INPUT);
  digitalWrite(BUTTON_RIGHT, HIGH);

  pinMode(BUTTON_DOWN, INPUT);
  digitalWrite(BUTTON_DOWN, HIGH);

  pinMode(BUTTON_LEFT, INPUT);
  digitalWrite(BUTTON_LEFT, HIGH);

  pinMode(BUTTON_E, INPUT);
  digitalWrite(BUTTON_E, HIGH);

  pinMode(BUTTON_F, INPUT);
  digitalWrite(BUTTON_F, HIGH);

  lc.shutdown(0, false); //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 1); // Set the brightness to default value
  lc.clearDisplay(0);    // and clear the display
  start();
}

void loop() {
  while (mark<maxmark){ 
  randomnumber();
  randshow();
  setvalues();
  valuesshow();
  } 
    printByte(love);
    delay(300);
    printByte(nolove);
    delay(300);
    printByte(love);
    delay(300);
    printByte(nolove);
    delay(300);
    printByte(love);
    delay(300);
    printByte(nolove);
    delay(300);
    
    
    
    maxmark+=10;
    mark=0;

}
