#include <stdio.h>

void setup() {
  // put your setup code here, to run once:
  //pinMode(A0, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  float CurrentVal = 0.0;
  float AvgCurrent = 0.0;
  for (int i=0; i<150; i++) {
    CurrentVal = analogRead(A0);
    //Serial.print("instantaneous current = ");
    //Serial.println (CurrentVal);
    CurrentVal = CurrentVal*(5.0/1024.0)*1000.0;
    AvgCurrent += CurrentVal;
  }
  AvgCurrent = AvgCurrent/150.0;
  Serial.print("Current = ");
  Serial.println(AvgCurrent);
}
