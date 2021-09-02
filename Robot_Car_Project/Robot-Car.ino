int med[5];
int maxsen[5];
int sums[5];
int minsen[5];
int sens[5]={0,0,0,0,0};
int e=0;
int sen1=0,sen2=0,sen3=0,sen4=0,sen5=0;
int ari1=0,ari2=0,ari3=0,ari4=0,ari5=0;
int enA = 9; 
int in1 = 4;
int in2 = 5; 

int enB = 6; 
int in3 = 3;
int in4 = 2 ;

int timestart;
int timeend;
int start = 1;
void setup() {
  timestart = millis();
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
//เซ็ทค่าขาวดำใหม่ทุกรอบจากสีสนาม เริ่มว่าที่สีดำ5จุดก่อนแล้วให้เดินหน้าไปอ่านสีขาว5จุดเก็บในตัวแปร
/////////////////////////////////////////////////////////////อ่านค่าจากเซ็นเซอร์(ดำ5จุด)ตัวที่1-5 10รอบ+กัน
  for(int i=0 ; i<10 ; i++ ){
    sens[0]=analogRead(A0);sens[1]=analogRead(A1);sens[2]=analogRead(A2);sens[3]=analogRead(A3);sens[4]=analogRead(A4);
    for(int j=0 ; j<5 ; j++ ){
      sums[j]+= sens[j];
      delay(30);
    }
  }
//////////////////////////////////////////////////////////// เอาค่าที่ได้มาหาค่าเฉลี่ยเก็บในตัวแปร
   for(int j=0 ; j<5 ; j++ ){
      minsen[j]=sums[j]/10;
    }
//////////////////////////////////////////////////////////// หลังจากนั้นเดินหน้า
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 160); 
  analogWrite(enB, 158);
  delay(220);
  analogWrite(enA, 0); 
  analogWrite(enB, 0);
//////////////////////////////////////////////////////////// อ่านค่าใหม่อีกรอบ(ขาว5จุด)
  for(int i=0 ; i<10 ; i++ ){
    sens[0]=analogRead(A0);sens[1]=analogRead(A1);sens[2]=analogRead(A2);sens[3]=analogRead(A3);sens[4]=analogRead(A4);
    for(int j=0 ; j<5 ; j++ ){
      sums[j]+= sens[j];
      delay(30);
    }
  }
   for(int j=0 ; j<5 ; j++ ){ นำค่าที่ได้มาหาค่าเฉลี่ยเหมือนเดิม เก็บในตัวแปร
      maxsen[j]=sums[j]/10;
    } 
//////////////////////////////////////////////////////////// เอาค่าสีขาวและดำมา+กันแล้วหาร2เพื่อหาค่ากลาง หลังจากนั้น-100เพื่อให้เจอค่าขาวมากขึ้น
    for(int i =0; i<5 ; i++){
  med[i]=(maxsen[i]+minsen[i])/2-100;
  Serial.println(med[i]);
  }
//////////////////////////////////////////////////////////// เดินหน้า
    digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 160); 
  analogWrite(enB, 158);
  delay(180);
  analogWrite(enA, 0); 
  analogWrite(enB, 0);
}    

void loop() {
  timeend = millis();
  //ส่วนของการเครื่อนที่ต่างๆตามสถานการณ์
  sens[0]=analogRead(A0);sens[1]=analogRead(A1);sens[2]=analogRead(A2);sens[3]=analogRead(A3);sens[4]=analogRead(A4); //อ่านค่าเซ็นเซอร์แต่ละตัว
  /////////////////////////////// 
  if(timestart-timeend<35){
    if(start == 1){
  //////////////////////////////////////// เซ็นเซอร์ตัวที่3อ่านค่าได้มากกว่าค่ากลางที่หาได้แสดงว่าเจอขาวให้ตรงไป
  if (sens[0]<med[0] && sens[1]<med[1] && sens[2]>=med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 0 0 1 0 0
 {
   digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 80); 
  analogWrite(enB, 80);
 }
 ///////////////////////// ถ้าเซ็นเซอร์ด้านขวามีการเจอขวาแปลว่ารถกำลังเอียงซ้าย ให้รถกลับเข้าหาเซ็นด้วยการเลี้ยวขวา
  if (sens[0]<med[0] && sens[1]<med[1] && sens[2]<med[2] && sens[3]>=med[3] &&sens[4]<med[4] ) // 0 0 0 1 0
 {
     digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 150); 
  analogWrite(enB, 140);
 } 
 ////////////////////////ถ้าเซ็นเซอร์ด้านขวามีการเจอขวาแปลว่ารถกำลังเอียงขวา ให้รถกลับเข้าหาเซ็นด้วยการเลี้ยวซ้าย
  if (sens[0]<med[0] && sens[1]>=med[1] && sens[2]<med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 0 1 0 0 0
 {
     digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 140);
 }
 //////////////////////// หลังจากนี้เป็นโค๊ดคล้ายเดิมเพียงแต่แบ่งไปตามสถานการณ์
   if (sens[0]<med[0] && sens[1]<med[1] && sens[2]<med[2] && sens[3]>=med[3] &&sens[4]>=med[4] ) // 0 0 0 1 1
 {
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 180); 
  analogWrite(enB, 170);
 } 
 ////////////////////////
  if (sens[0]>=med[0] && sens[1]>=med[1] && sens[2]<med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 1 1 0 0 0
 {

   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 200); 
  analogWrite(enB, 190);
  
 }
 ///////////////////////////////////////////
     if (sens[0]<med[0] && sens[1]<med[1] && sens[2]>=med[2] && sens[3]>=med[3] &&sens[4]>=med[4] ) // 0 0 1 1 1
 {
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 200); 
  analogWrite(enB, 190);
 } 
 ///////////////////////////////////////////
      if (sens[0]>=med[0] && sens[1]>=med[1] && sens[2]>=med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 1 1 1 0 0
 {
   digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 80); 
  analogWrite(enB, 80);
  delay(100);
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 200); 
  analogWrite(enB, 190);
 } 
 /////////////////////////////////////////////////////////////////////
       if (sens[0]>=med[0] && sens[1]>=med[1] && sens[2]<med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 0 1 1 0 0
 {
 digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 80); 
  analogWrite(enB, 80);
  delay(50);
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 180); 
  analogWrite(enB, 170);

 } 
 //////////////////////////////////////////////////////////////////
      if (sens[0]<med[0] && sens[1]<med[1] && sens[2]>=med[2] && sens[3]>=med[3] &&sens[4]<med[4] ) // 0 0 1 1 0
 {
 digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 80); 
  analogWrite(enB, 80);
  delay(50);
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 180); 
  analogWrite(enB, 170);

 } 
 /////////////////////////////////////////////////////////
        if (sens[0]<med[0] && sens[1]>=med[1] && sens[2]>=med[2] && sens[3]>=med[3] &&sens[4]>=med[4] ) // 0 1 1 1 1
 {
    digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 140); 
  analogWrite(enB, 130);
  delay(50);
    digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 180); 
  analogWrite(enB, 170);
    delay(50);
 } 
 ///////////////////////////////////////////////////////
       if (sens[0]>=med[0] && sens[1]>=med[1] && sens[2]>=med[2] && sens[3]>=med[3] &&sens[4]<med[4] ) // 1 1 1 1 0
 {
     digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 140); 
  analogWrite(enB, 130);
  delay(50);
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 180); 
  analogWrite(enB, 170);
    delay(50);
 }
 //////////////////////////////////////////////////
        if (sens[0]>=med[0] && sens[1]>=med[1] && sens[2]>=med[2] && sens[3]>=med[3] &&sens[4]>=med[4] ) // 1 1 1 1 1
 {
 }
    }
  }
  else if(e==0){
    e=1;
      analogWrite(enA, 0); 
      analogWrite(enB, 0);
       delay(500);
      start = 2;
           digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 80); 
  analogWrite(enB, 80);
   delay(600);
    }
    
   if(start ==2){
      if (sens[0]<med[0] && sens[1]<med[1] && sens[2]>=med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 0 0 1 0 0
 {
   digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 80); 
  analogWrite(enB, 80);
 }
 /////////////////////////
  if (sens[0]<med[0] && sens[1]<med[1] && sens[2]<med[2] && sens[3]>=med[3] &&sens[4]<med[4] ) // 0 0 0 1 0
 {
     digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 150); 
  analogWrite(enB, 140);
 } 
 ////////////////////////
  if (sens[0]<med[0] && sens[1]>=med[1] && sens[2]<med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 0 1 0 0 0
 {
     digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 150); 
  analogWrite(enB, 140);
 }
 ////////////////////////
   if (sens[0]<med[0] && sens[1]<med[1] && sens[2]<med[2] && sens[3]>=med[3] &&sens[4]>=med[4] ) // 0 0 0 1 1
 {
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 180); 
  analogWrite(enB, 170);
 } 
 ////////////////////////
  if (sens[0]>=med[0] && sens[1]>=med[1] && sens[2]<med[2] && sens[3]<med[3] &&sens[4]<med[4] ) // 1 1 0 0 0
 {
   digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH); 
  digitalWrite(in4, LOW); 
  analogWrite(enA, 200); 
  analogWrite(enB, 190);
  
 }
 ////////////////////////
     if (sens[0]<med[0] && sens[1]<med[1] && sens[2]>=med[2] && sens[3]>=med[3] &&sens[4]>=med[4] ) // 0 0 1 1 1
 {
     digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, LOW);
    analogWrite(enA, 80); 
  analogWrite(enB, 70);
  delay(400);
   digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 220); 
  analogWrite(enB, 190);
  delay(1000);
 } 
   }
 }
