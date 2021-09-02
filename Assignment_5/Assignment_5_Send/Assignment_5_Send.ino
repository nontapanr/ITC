#include <SoftwareSerial.h>
#include <math.h>

const unsigned int X_AXIS_PIN = A1;
const unsigned int BUFFER_SIZE = 8;
const unsigned int BAUD_RATE = 9600;
int buffers[1][BUFFER_SIZE];
int buffer_pos[1] = {1};
int temp_X;

const int max_X = 401;
const int mid_X = 337;
const int min_X = 269;

String inputString = ""; // a string to hold incoming data
SoftwareSerial mySerial(2, 3); // SoftwareSerial(rxPin, txPin)

void setup() {
  mySerial.begin(2400);
  pinMode(A0, OUTPUT);
  pinMode(A4, OUTPUT);
}

void loop() {
  digitalWrite(A0, HIGH);
  digitalWrite(A4, LOW);
  mySerial.print(value_X(get_axis(0)));
  //mySerial.print(get_axis(0)); // Tester Number
  mySerial.print("    #");
  delay(180);
}

int value_X(int num){
  if(num <= mid_X) {
    return (constrain(map(num,mid_X,min_X,0,90),0,90) * -1);
  }
  else if(num > mid_X){
    return (constrain(map(num,max_X,mid_X,-90,0),-90,0) * -1);
  }
}

int get_axis(const int axis) {
  delay(1);
  buffers[axis][buffer_pos[axis]] = analogRead(X_AXIS_PIN);
  buffer_pos[axis] = (buffer_pos[axis] + 1) % BUFFER_SIZE;
  long sum = 0;
  for (unsigned int i = 0; i < BUFFER_SIZE; i++) sum += buffers[axis][i];
  return round(sum / BUFFER_SIZE);
}

void serialEvent()
{
  while (Serial.available()) // recheck serial is available
  {
    char inChar = (char) Serial.read(); // get the new byte:
    inputString += inChar; // add it to the inputString:
  }
}
