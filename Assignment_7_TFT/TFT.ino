#include "ST7735_TEE.h"
#define Up 2
#define Down 4

TEE_ST7735 lcd(9, 10, 11, 12, 13);

int timer1_counter;
int t1 = 0;
int hour = 0;
int minute = 0;
int second = 0;

int check_hour = 0;
int check_minute = 0;
int check_t1 = 0;

unsigned long currenttime, previoustime = 0;
unsigned long currenttimefortransfer, previoustimefortransfer = 0 ;
uint16_t background=BLACK;
uint16_t timecolor=WHITE ;
uint16_t adjusttimestatecolor=BLUE;
uint16_t clockstatecolor=GREEN;

char mins[3] = " ";
char secs[3] = " ";
char hrs[3] = " ";

String Times = "00:00:00";

String input = "";
int state=0;
bool checkerase=0;

void setup() {
  lcd.init(lcd.VERTICAL);   // put your setup code here, to run once:
  pinMode(Up,INPUT_PULLUP);
  pinMode(Down,INPUT_PULLUP);
  Serial.begin(9600);
  lcd.fillScreen(background);
  timer1_counter = 2946; // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0; TCCR1B = 0;   // preload timer 65536-16MHz/256/1Hz
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine
{ TCNT1 = timer1_counter; // preload timer
t1 = t1 + 1;
}

void loop() {
  Serial.println("Time Mode");
  if(digitalRead(Up)!=1){ state=0;
  }
  else if(digitalRead(Down)!=1){ state=1;
  }
  adjusttimestate();
  clockstate();
}

int calculatehour(int time1) {

  if (time1 == 3600) {
    hour = (hour + 1) % 24;
    t1 = 0;
  }
  return hour;
}

int calculateminute(int time1) {
  minute = (time1 / 60) % 60;
  return minute;

}

int calculatesecond(int time1) {
  second = time1 % 60;
  return second;
}

void inttochar() {
  sprintf(secs, "%d", second);
  sprintf(mins, "%d", minute);
  sprintf(hrs, "%d", hour);
}

void assigntime() {
  Times[0] = hrs[0];
  Times[1] = hrs[1];
  Times[3] = mins[0];
  Times[4] = mins[1];
  Times[6] = secs[0];
  Times[7] = secs[1];

  if (hour < 10)
  {
    Times[0] = '0';
    Times[1] = hrs[0];
  }
  if (minute < 10) {
    Times[3] = '0';
    Times[4] = mins[0];
  }
  if (second < 10) {
    Times[6] = '0';
    Times[7] = secs[0];
  }
}

void drawtime() {
  lcd.drawChar(5, 50, Times[0], timecolor, 3);
  lcd.drawChar(25, 50, Times[1], timecolor, 3);
  lcd.drawChar(37, 50, Times[2], timecolor, 3);
  lcd.drawChar(50, 50, Times[3], timecolor, 3);
  lcd.drawChar(70, 50, Times[4], timecolor, 3);
  lcd.drawChar(83, 50, Times[5], timecolor, 3);
  lcd.drawChar(93, 50, Times[6], timecolor, 3);
  lcd.drawChar(113, 50, Times[7], timecolor, 3);

}
void erasetime_t1() {
 
  if(t1!=check_t1) {
    second = calculatesecond(t1);
    minute = calculateminute(t1);
    hour = calculatehour(t1);
    cleartime();
    check_t1=t1;
  }
}

void cleartime(){
    if (check_hour != hour) {
      lcd.drawChar(5, 50, Times[0], background, 3);
      lcd.drawChar(25, 50, Times[1], background, 3);
      check_hour = hour;
    }

    if (check_minute != minute) {
      lcd.drawChar(50, 50, Times[3], background, 3);
      lcd.drawChar(70, 50, Times[4], background, 3);
      check_minute = minute;
    }
    lcd.drawChar(93, 50, Times[6], background, 3);
    lcd.drawChar(113, 50, Times[7], background, 3);
  
}

void SerialEvent() {
  while (Serial.available()) // recheck serial is available
  { char inChar = (char)Serial.read(); // get the new byte:
    input += inChar; // add it to the input:
    if (inChar == 10) // check received 'enter' (0x0D)
    {
      adjusttime();
      input = "";
    }
  }
}

int hourtemp=0,minutetemp=0,secondtemp=0;

void adjusttime(){
  if(input[0]>=48&&input[0]<=57&&input[1]>=48&&input[1]<=57&&input[3]>=48&&input[3]<=57&&input[4]>=48&&input[4]<=57&&input[6]>=48&&input[6]<=57&&input[7]>=48&&input[7]<=57)
  {
    hourtemp=((input[0]-'0')*10)+(input[1]-'0');
    minutetemp=(((input[3]-'0')*10)+(input[4]-'0'));
    secondtemp=(((input[6]-'0')*10)+(input[7]-'0'));
  }
  if((hourtemp<24&&minutetemp<60&&secondtemp<60)&&(hourtemp>=0&&minutetemp>=0&&secondtemp>=0)){
      hour =hourtemp;
      t1=minutetemp*60+secondtemp;
      second = calculatesecond(t1);
      minute = calculateminute(t1);
      hour = calculatehour(t1);
      cleartime(); 
  }
}

char clockmode[]="State Clock Mode";
char clockmodetag[]="Smart Watch";
char adjusttimemodetag[]="Modurate Time Mode";
char adjusttimemode[]="Modurate Time";

void clockstate(){
if(state==0){
   
 if (checkerase==1){
    timecolor = BLUE;
  lcd.drawString(15,5,adjusttimemode,background,1);
  checkerase=0;
 }
  lcd.drawString(20,5,clockmode,clockstatecolor,1);
  lcd.drawString(25,100,clockmodetag,clockstatecolor,1);
  currenttimefortransfer=millis();
   if(currenttimefortransfer-previoustimefortransfer>=1200){
    lcd.drawString(25,100,clockmodetag,background,1);
    previoustimefortransfer=currenttimefortransfer;
   }
  lcd.drawString(15,120,adjusttimemodetag,adjusttimestatecolor,1);
  inttochar();
  assigntime();
  drawtime();
  erasetime_t1();
}
}

String recyclebin="";

void adjusttimestate(){
if(state==1){
 if (checkerase==0){
    timecolor = YELLOW;
  lcd.drawString(20,5,clockmode,background,1);
  while (Serial.available()) // recheck serial is available
  { char inChar2 = (char)Serial.read(); // get the new byte:
    recyclebin += inChar2; // add it to the input:
    if (inChar2 == 10){ recyclebin = "";
    }
  }
  checkerase=1;
 }
    currenttimefortransfer=millis();
    lcd.drawString(25,100,clockmodetag,clockstatecolor,1);
    lcd.drawString(15,120,adjusttimemodetag,adjusttimestatecolor,1);
 if(currenttimefortransfer-previoustimefortransfer>=1200){
    lcd.drawString(15,120,adjusttimemodetag,background,1);
    previoustimefortransfer=currenttimefortransfer;
    lcd.drawChar(5, 50, Times[0], background, 3);
    lcd.drawChar(25, 50, Times[1], background, 3);
    lcd.drawChar(37, 50, Times[2], background, 3);
    lcd.drawChar(50, 50, Times[3], background, 3);
    lcd.drawChar(70, 50, Times[4], background, 3);
    lcd.drawChar(83, 50, Times[5], background, 3);
    lcd.drawChar(93, 50, Times[6], background, 3);
    lcd.drawChar(113, 50, Times[7], background, 3);
   }
   lcd.drawString(15,5,adjusttimemode,adjusttimestatecolor,1);
   SerialEvent() ;
   inttochar();
   assigntime();
   drawtime();
   erasetime_t1();
}
}
