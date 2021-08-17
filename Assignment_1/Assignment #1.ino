#define Red_Sw 12
#define Yellow_Sw 11
#define Green_Sw 10

#define Red 4
#define Yellow 3
#define Green 2

int StateRed = 0;
int StateYellow = 0;
int StateGreen = 0;

int OrderRed = 0;
int OrderYellow = 0;
int OrderGreen = 0;

long TimeRedPush;
long TimeYellowPush;
long TimeGreenPush;

long DebounceDelay = 250;
long LastDebounceTime = 0;

void setup()
{
   Serial.begin(9600);
  
   pinMode(Red_Sw,INPUT);
   pinMode(Yellow_Sw,INPUT);
   pinMode(Green_Sw,INPUT_PULLUP);
  
   pinMode(Red,OUTPUT);
   pinMode(Yellow,OUTPUT);
   pinMode(Green,OUTPUT);
}

void ReadInput()
{
  if(digitalRead(Red_Sw)==HIGH)
  {
    OrderRed=1;
  }
  else
  {
    OrderRed=0;
  }
	
  if(digitalRead(Yellow_Sw)==LOW)
  {
    OrderYellow=1;
  }
  else
  {
    OrderYellow=0;
  }
  
  if(digitalRead(Green_Sw)==LOW)
  {
    OrderGreen=1;
  }
  else
  {
    OrderGreen=0;
  }
  
  if(OrderRed!=StateRed || OrderYellow!=StateYellow || OrderGreen!=StateGreen)
  {
    LastDebounceTime = millis();
  }
  delay(200);
}

void RedLight()
{
  if(OrderRed==1)
  {
    if(StateRed==0)
    {
      Serial.println("Red ON");
      digitalWrite(Red,HIGH);
      TimeRedPush=millis();
      StateRed=1;
    }
    else
    {
      Serial.println("Red OFF");
      digitalWrite(Red,LOW);
      TimeRedPush=-9999;
      StateRed=0;
    }
  }
  if(millis()-TimeRedPush>=3000)
  {
    digitalWrite(Red,LOW);
    TimeRedPush=-9999;
    StateRed=0;
  }
}

void GreenLight()
{
  if(OrderGreen==1)
  {
    if(StateGreen==0)
    {
      Serial.println("Green On");
      StateGreen=1;
      digitalWrite(Green,HIGH);
      TimeGreenPush=millis();
    }
    else
    {
      Serial.println("Green OFF");
      StateGreen=0;
      digitalWrite(Green,LOW);
      TimeGreenPush=-9999;
    }
  }
  if(millis()-TimeGreenPush>=3000)
  {    
    StateGreen=0;
    digitalWrite(Green,LOW);
	TimeGreenPush=-9999;
  }
}

void YellowLight()
{
  if(OrderYellow==1)
  {
    Serial.println("Yellow ON");
    digitalWrite(Yellow,HIGH);
    delay(280);
    digitalWrite(Yellow,LOW);
    delay(280);
    digitalWrite(Yellow,HIGH);
    delay(280);
    digitalWrite(Yellow,LOW);
    delay(280);
    digitalWrite(Yellow,HIGH);
    delay(280);
    digitalWrite(Yellow,LOW);
    delay(280);
    digitalWrite(Yellow,HIGH);
    delay(280);
    digitalWrite(Yellow,LOW);
  }
}

void loop()
{
  ReadInput();
  RedLight();
  
  if(StateRed==0)
  {
    GreenLight();
  }
  if(StateRed==0 && StateGreen==0)
  {
    YellowLight();
  }
  
}

