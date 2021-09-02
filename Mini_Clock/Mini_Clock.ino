#include "LedControl.h"
#include "FontLEDClock.h"

#define PWM_Pin 3 // Look at '~' pins 11,10,9,6,5,3
#define PWM_off LOW
int duty = 200;

LedControl lc = LedControl(11, 13, 10, 4);              // DIN,CLK,CS,Number of LED Module

unsigned long long int times ;
unsigned long long int timee ;

int s = 1 ;

uint8_t intensity = 8;
uint8_t hour  = 0, minute = 0, second = 0; //Variable Clock mode
uint8_t hour2  = 12, minute2 = 10, second2 = 50; 
int ss=0;
int p=0;

void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);  
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);  

  int devices = lc.getDeviceCount();                    /* find no of LED modules */
  for (int address = 0; address < devices; address++)   /* set up each device         */
  { /* set up each device         */
    lc.shutdown(address, false);                        /* turn off power saving mode */
    lc.setIntensity(address, 2);                        /* set intensity=2 of 8       */
    lc.clearDisplay(address);                           /* clear screen               */
  }                                                     /* set up each device         */
  Serial.begin(9600);
  noInterrupts();           /* disable all interrupts             */
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 3036;           /* preload timer 65536-16MHz/256/1Hz  */
  TCCR1B |= (1 << CS12);    /* 256 prescaler                      */
  TIMSK1 |= (1 << TOIE1);   /* enable timer overflow interrupt    */
  interrupts();             /* enable all interrupts              */
}

void clear_display()
{
  for (uint8_t address = 0; address < 4; address++)
    lc.clearDisplay(address);
}

void fade_down()
{
  for (uint8_t i = intensity; i > 0; i--) //fade from global intensity to 1
  {
    for (uint8_t address = 0; address < 4; address++)
      lc.setIntensity(address, i);
    delay(30); //change this to change fade down speed
  }
}

void fade_up()
{
  for (uint8_t i = 1; i < intensity; i++) //fade from global intensity to 1
  {
    for (uint8_t address = 0; address < 4; address++)
      lc.setIntensity(address, i);
    delay(30); //change this to change fade down speed
  }
  for (uint8_t address = 0; address < 4; address++)
    lc.setIntensity(address, intensity);  //reset intentsity to global value
}

void plot (uint8_t x, uint8_t y, bool value)
{
  uint8_t address;                                      /* select which matrix depending on the x coord  */
  if (x >= 0  && x <= 7)  {
    address = 3;
  }
  if (x >= 8  && x <= 15) {
    address = 2;
    x = x - 8;
  }
  if (x >= 16 && x <= 23) {
    address = 1;
    x = x - 16;
  }
  if (x >= 24 && x <= 31) {
    address = 0;
    x = x - 24;
  }

  if (value == 1)
    lc.setLed(address, y, x, true);
  else
    lc.setLed(address, y, x, false);
}

void print_tiny_char(uint8_t x, uint8_t y, char c)
{
  uint8_t dots;
  if (c >= 'A' && c <= 'Z' || (c >= 'a' && c <= 'z') )  c &= 0x1F;              /* A-Z maps to 1-26  */
  else if (c >= '0' && c <= '9')                        c  = (c - '0') + 32;
  else if (c == ' ' )                                   c  =  0;                /* space             */
  else if (c == '.' )                                   c  = 27;                /* full stop         */
  else if (c == ':' )                                   c  = 28;                /* colon             */
  else if (c == '\'')                                   c  = 29;                /* single quote mark */
  else if (c == '!' )                                   c  = 30;                /* single quote mark */
  else if (c == '?' )                                   c  = 31;                /* question mark     */

  for (uint8_t col = 0; col < 3; col++)
  {
    dots = pgm_read_byte_near(&mytinyfont[c][col]);
    for (uint8_t row = 0; row < 5; row++)
    {
      if (dots & (16 >> row))     plot(x + col, y + row, 1);
      else                      plot(x + col, y + row, 0);
    }
  }
}

void clocks()
{
  print_tiny_char( 2, 1,  hour / 10 + '0'); //print hour
  print_tiny_char( 6, 1,  hour % 10 + '0');
  print_tiny_char(12, 1, minute / 10 + '0'); //print minute
  print_tiny_char(16, 1, minute % 10 + '0');
  print_tiny_char(22, 1, second / 10 + '0'); //print second
  print_tiny_char(26, 1, second % 10 + '0');

  // blink : for each minute
  if (second == 0)
  {
    plot(10, 2, 0);
    plot(10, 4, 0);
    plot(20, 2, 0);
    plot(20, 4, 0);
  }
  else
  {
    plot(10, 2, 1);
    plot(10, 4, 1);
    plot(20, 2, 1);
    plot(20, 4, 1);
  }

  // display second count line
  if (second < 30)
  {
    plot(second + 1, 7, 1);
  }
  else
  {
    plot(60 - second, 7, 0);
  }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine
{
  TCNT1 = 3036;             /* preload timern */
  Serial.println(second++);
  if (second > 59) {
    second = 0; minute++;
  }
  if (minute > 59) {
    minute = 0; hour++;
  }
  if (hour > 23) {
    hour = 0;
  }
}

void loop() {
    int LDR= analogRead(A0);
 
    int button2= digitalRead(2); 
    int button3= digitalRead(3);
    int button4= digitalRead(4); 
    int button5= digitalRead(5);
    int button6= digitalRead(6); 
    int button7= digitalRead(7);
    

  clocks();
    if(hour  == 0 && minute == 0 && second == 10 && LDR > 500 && p==0){
  analogWrite(PWM_Pin,duty);
  p=1;
  }
    if( LDR < 500 ){
  analogWrite(PWM_Pin,0);
  }
   if( p == 1 && LDR > 500 ){
   analogWrite(PWM_Pin,duty);
  }
  if(button2 == 0){
    hour++;second = 0;
    
  }
  if(button4 == 0){
    hour--;second = 0;
  }
  if(button3 == 0){
    minute++;second = 0;
  }
  if(button5 == 0){
    minute--;second = 0;
  }
}
