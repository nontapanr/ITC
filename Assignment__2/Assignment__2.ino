#define guess_sw 11
#define start_sw 12
#define pressed 1

int read_sw1, read_sw2;
int random_num, guess_num=0;

int No[][8]={
  {0,1,1,0,0,0,0,0},
  {1,1,0,0,1,1,1,0},
  {1,1,1,0,1,0,1,0},
  {0,1,1,0,0,0,1,1},
  {1,0,1,0,1,0,1,1},
    {1,0,1,0,1,1,1,1}};

void setup()
{
  Serial.begin(9600);
  for(int i=2;i<=9;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  
}

void display(int num)
{
  for(int i=0;i<8;i++)
  {
    if(No[num-1][i]==1)
    {
      digitalWrite(i+2,LOW);
    }
    else
    {
      digitalWrite(i+2,HIGH);
    }
  }
}

void off()
{
  for(int i=2;i<=9;i++)
  {
    digitalWrite(i,HIGH);
  }
}

void lose()
{
  for(int i=0; i<4; i++)
  {
     off();
     for(int i=2;i<10;i++)
     {
        if(i!=5&&i!=8)
        {
          digitalWrite(i,LOW);
          delay(250);
          digitalWrite(i,HIGH);
        }
     }
  }
}

void display_random(int guess_num)
{
    random_num=random(1,6);
    off();
    delay(500);
  
    Serial.print("Random Number : ");
    Serial.print(random_num);
  
    if(random_num==guess_num)
    {
      Serial.println("   Win !!!");
      for(int i=0;i<8;i++)
      {
        display(random_num);
        delay(250);
        off();
        delay(250);
      }
    }
    else
    {
      Serial.println("   Lose !!!");
      display(random_num);
      delay(500);
      lose();
    }
}

void loop()
{
  read_sw1=digitalRead(guess_sw);
  read_sw2=digitalRead(start_sw);  
  if(read_sw1==pressed)
  {
      guess_num++;
    if(guess_num>6)
    {
        guess_num=1;
    } 
    display(guess_num);
      Serial.print("Guess Number : ");
      Serial.println(guess_num);
  }
  if(read_sw2==pressed && guess_num!=0)
  {
      display_random(guess_num);
      guess_num=0;
  }
  delay(200);
}
  
