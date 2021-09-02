int med[5];
int maxsen[5]={972,404,527,890,713};
int minsen[5]={552,192,290,480,360};

int sen1=0,sen2=0,sen3=0,sen4=0,sen5=0;
int ari1=0,ari2=0,ari3=0,ari4=0,ari5=0;
int enA = 9; 
int in1 = 4;
int in2 = 5; 

int enB = 6; 
int in3 = 3;
int in4 = 2 
; 

void setup() {
   Serial.begin(9600);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
  
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(in3, OUTPUT);
for(int i =0; i<5 ; i++){
  med[i]=(maxsen[i]+minsen[i])/2-100;
  Serial.println(med[i]);
}

} 

void loop() { 
 sen1=analogRead(A0);sen2=analogRead(A1);sen3=analogRead(A2);sen4=analogRead(A3);sen5=analogRead(A4);
//
//
 Serial.print(sen5);
 Serial.print(" ");
 Serial.print(sen4);
 Serial.print(" ");
 Serial.print(sen3);
 Serial.print(" ");
 Serial.print(sen2);
 Serial.print(" ");
 Serial.println(sen1);

 if (sen5<med[0] && sen4<med[1] && sen3>=med[2] && sen2<med[3] &&sen1<med[4] ) // 0 0 1 0 0
 {
  
   digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 105); 
  analogWrite(enB, 105);
 }
  if (sen5<med[0] && sen4<med[1] && sen3<med[2] && sen2>=med[3] &&sen1<med[4] ) // 0 0 0 1 0
 {
  
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 100); 
  analogWrite(enB, 100);
 }
 if (sen5<med[0] && sen4>=med[1] && sen3<med[2] && sen2<med[3] &&sen1<med[4] ) // 0 1 0 0 0
 {
  
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 100); 
  analogWrite(enB, 100);
 }
  if (sen5>=med[0] && sen4<med[1] && sen3<med[2] && sen2<med[3] &&sen1<med[4] ) // 1 0 0 0 0
 {
  
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
 }
   if (sen5<med[0] && sen4<med[1] && sen3<med[2] && sen2<med[3] &&sen1>=med[4] ) // 0 0 0 0 1
 {
  
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
 }
   if (sen5>=med[0] && sen4>=med[1] && sen3<med[2] && sen2<med[3] &&sen1<med[4] ) // 1 1 0 0 0
 {
    
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  
 }
   if (sen5>=med[0] && sen4>=med[1] && sen3>=med[2] && sen2>=med[3] &&sen1<med[4] ) // 1 1 1 1 0
 {
     digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(500);
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(200);
 }
   if (sen5<med[0] && sen4<med[1] && sen3<med[2] && sen2>=med[3] &&sen1>=med[4] ) // 0 0 0 1 1
 {
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(50);
 digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);

 }
   if (sen5<med[0] && sen4<med[1] && sen3>=med[2] && sen2>=med[3] &&sen1<med[4] ) // 0 0 1 1 0
 {
     
 digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 200); 
  analogWrite(enB, 200);
 
 }
    if (sen5<med[0] && sen4<med[1] && sen3>=med[2] && sen2>=med[3] &&sen1>=med[4] ) // 0 0 1 1 1
 {
     digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(50);
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 180); 
  analogWrite(enB, 180);
  delay(200);
 }
     if (sen5<med[0] && sen4>=med[1] && sen3>=med[2] && sen2>=med[3] &&sen1>=med[4] ) // 0 1 1 1 1
 {
        digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(60);
 digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 180); 
  analogWrite(enB, 180);
  delay(200);
 }
 if (sen5>=med[0] && sen4<med[1] && sen3>=med[2] && sen2<med[3] &&sen1>=med[4] ) // 0 0 1 0 1
 {
        digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(60);
 digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 180); 
  analogWrite(enB, 180);
  delay(200);
 }
  if (sen5>=med[0] && sen4>=med[1] && sen3>=med[2] && sen2>=med[3] &&sen1>=med[4] ) // 1 1 1 1 1
 {
     digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 150);
  delay(800);
  
 digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 100); 
  analogWrite(enB, 100);
  delay(100);
 }
