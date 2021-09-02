#define goW 0
#define waitW 1
#define goS 2
#define waitS 3
#define walk 4

#define peopleWalk1 5
#define peopleWalk2 6
#define peopleWalk3 7
#define peopleWalk4 8

#define westButton 10
#define southButton 11
#define peopleButton 12

struct State {
  unsigned long Out;
  unsigned long Time;
  unsigned long next[8];
};
typedef const struct State SType;

SType FSM[9] = {
  {B00110010, 2000,{goW, waitW, waitW, waitW, goW, waitW, waitW, waitW}}, // go West
  {B01010010, 500, {goS, walk, goS, goS, goS, walk, goS, goS}},           // wait for West
  
  {B10000110, 2000,{goS, waitS, goS, waitS, waitS, waitS, waitS, waitS}}, // go South
  {B10001010, 500, {goW, walk, goW, walk, goW, goW, goW, walk}},          // wait for South
  
  {B10010001, 2000,{walk, walk, peopleWalk1, peopleWalk1, peopleWalk1, peopleWalk1, peopleWalk1, peopleWalk1}}, // walk
  {B10010000, 500, {peopleWalk2, peopleWalk2, peopleWalk2, peopleWalk2, peopleWalk2, peopleWalk2, peopleWalk2, peopleWalk2}}, // walk Lighting
  {B10010001, 500, {peopleWalk3, peopleWalk3, peopleWalk3, peopleWalk3, peopleWalk3, peopleWalk3, peopleWalk3, peopleWalk3}},
  {B10010000, 500, {peopleWalk4, peopleWalk4, peopleWalk4, peopleWalk4, peopleWalk4, peopleWalk4, peopleWalk4, peopleWalk4}},
  {B10010001, 500, {goW, goW, goS, goS, goW, goW, goW, goW}}, // walk return
};

void setup()  
{
  Serial.begin(9600);
  for(int LED=2; LED<10; LED++) //LED Pin Setup Loop
  { 
    pinMode(LED, OUTPUT);     
  }
  pinMode(10, INPUT_PULLUP);  //West Button
  pinMode(11, INPUT_PULLUP);  //South Button
  pinMode(12, INPUT_PULLUP);  //People Button
}

int stateSouth, stateWest, stateWalk;
int S = 0, input;

void loop()
{
  digitalWrite(2, !(FSM[S].Out & B10000000)); //West Light
  digitalWrite(3, !(FSM[S].Out & B01000000));
  digitalWrite(4, !(FSM[S].Out & B00100000));

  digitalWrite(5, !(FSM[S].Out & B00010000)); //South Light
  digitalWrite(6, !(FSM[S].Out & B00001000));
  digitalWrite(7, !(FSM[S].Out & B00000100));
  
  digitalWrite(8, !(FSM[S].Out & B00000010)); //People Light
  digitalWrite(9, !(FSM[S].Out & B00000001));
 
  delay(FSM[S].Time);
  
  stateWest  = digitalRead(westButton)   == 0 ? 1 : 0;
  stateSouth = digitalRead(southButton)  == 0 ? 1 : 0;
  stateWalk  = digitalRead(peopleButton) == 0 ? 1 : 0;

  input = stateSouth*4+stateWest*2+stateWalk; //Input Calculate
  S = FSM[S].next[input];
}
