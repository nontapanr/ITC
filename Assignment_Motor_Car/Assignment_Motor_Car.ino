int enA = 10; //  Left Wheel
int in1 = 9;
int in2 = 8;

int in3 = 5;  // Righ Wheel
int in4 = 4;
int enB = 3;

int count = 0;  // Count for limit car loop

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() 
{
  delay(1000);
  if(count<8) //  loop for draw square 2 round 
  { 
      //  Set speed range 0~255
    analogWrite(enA,180); //Speed Control
    analogWrite(enB,150); //Speed Control
    forward();
    stopMotor();    
    delay(500);
    turn();
    count++;
  }
  stopMotor();    
}

void forward(){   //  Car Forward
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(1000);
}

void turn(){      //  Change motor direction
  analogWrite(enA,150);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  delay(380);
}

void stopMotor(){   // Turn off motor A, B
  digitalWrite(in1,LOW);
  digitalWrite(in4,LOW);
}
