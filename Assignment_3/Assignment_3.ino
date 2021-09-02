#include <ButtonDebounce.h>
#define buttomC 6
#define buttomD 7
#define buttomE 8
#define buttomF 9
#define buttomG 11
#define rec 12
#define play_rec 13
#define speaker 10

#define C 262
#define D 294
#define E 330
#define F 349
#define G 392

int i=0;
int rec_state, last_note;
int notes[500] = {0,0,0,'x'};

void sound();
void play();

ButtonDebounce button1(13, 20);
void buttonChanged1(int state){
  Serial.println("Changed: " + String(state));
  if(state == HIGH && rec_state == 0){
    Serial.println("--------- Playing");
    play();
  }
}
ButtonDebounce button2(12 , 20);
void buttonChanged2(int state){
  Serial.println("Changed: " + String(state));
  if(state == HIGH && rec_state == 0){
    rec_state = 1;
    i = 0;
    Serial.println("--------- Start Recording");
  }
  else if(state == HIGH && rec_state == 1){
    rec_state = 0;
    notes[i]='x';
    i = 0;
    Serial.println("--------- Stop Recording");
  }
}

void setup(){
   button1.setCallback(buttonChanged1);
   button2.setCallback(buttonChanged2);
   Serial.begin(9600);
   pinMode(buttomC, INPUT);
   pinMode(buttomD, INPUT);
   pinMode(buttomE, INPUT);
   pinMode(buttomF, INPUT);
   pinMode(buttomG, INPUT);
   pinMode(rec, INPUT);
   pinMode(play_rec, INPUT);
   pinMode(speaker, OUTPUT);
}



void loop(){
  int rec_button = digitalRead(rec);
  int play_button = digitalRead(play_rec);
  button1.update();
  button2.update();
  sound();
  
//  if(rec_button == HIGH && rec_state == 0){
//    rec_state = 1;
//    i = 0;
//    Serial.println("--------- Start Recording");
//  }
//  else if(rec_button == HIGH && rec_state == 1){
//    rec_state = 0;
//    notes[i]='x';
//    i = 0;
//    Serial.println("--------- Stop Recording");
//  }
//  if(play_button == HIGH && rec_state == 0){
//    Serial.println("--------- Playing");
//    play();
//  }
//  delay(50);
}

void sound()
{
  if(digitalRead(buttomC) == 1){
    tone(speaker,C);
    Serial.println("pressed C");
    if(rec_state == 1){
      notes[i] = C;
    }
  }
  else if(digitalRead(buttomD) == 1){
    tone(speaker,D);
    Serial.println("pressed D");
    if(rec_state == 1){
      notes[i] = D;
    }
  }
  else if(digitalRead(buttomE) == 1){
    tone(speaker,E);
    Serial.println("pressed E");
    if(rec_state == 1){
      notes[i] = E;
    }
  }
  else if(digitalRead(buttomF)==1){
    tone(speaker,F);
    Serial.println("pressed F");
    if(rec_state == 1){
      notes[i] = F;
    }
  }
  else if(digitalRead(buttomG) == 1){
    tone(speaker,G);
    Serial.println("pressed G");
    if(rec_state == 1){
      notes[i] = G;
    }
  }
  else{
    if(rec_state == 1){
      notes[i] = 0;
    }
    noTone(speaker);
  }
  delay(50);
  ++i;
}

void play(){
  for(int i=0; notes[i]!='x'; i++){
    if(notes[i]!=0)
    {
      tone(speaker, notes[i]);
    }
    delay(50);
    noTone(speaker);
  }  
}
