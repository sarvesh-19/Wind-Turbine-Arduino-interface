#include <stdio.h>
const int a1 = A1;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  Serial.begin(19200);
}


void loop() {
  // put your main code here, to run repeatedly:
  CurrentVal = 0;
  AvgCurrent = 0;
  for (int i=0; i<150; i++) {
    CurrentVal = analogRead(A0);
    CurrentVal = CurrentVal*(5/1024)
    AvgCurrent += CurrentVal;
  }
  Serial.println(AvgCurrent);
}
