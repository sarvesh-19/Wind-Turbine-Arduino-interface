#include <stdio.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A5, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  float CurrentVal = 0.0;
  float AvgCurrent = 0.0;
  float VoltageVal = 0.0;
  float resistance = 190000.0;
  for (int i=0; i<150; i++) {
    CurrentVal = analogRead(A0);
    VoltageVal = analogRead(A5);
    CurrentVal = CurrentVal*(3.3/1024.0)*1000.0;
    VoltageVal += VoltageVal*(3.3/1024.0);
    AvgCurrent += CurrentVal;
   
  }
  AvgCurrent = AvgCurrent/150.0;
  VoltageVal/=150.0;
  Serial.print("Current = ");
  Serial.println(AvgCurrent);
  Serial.print("Voltage = ");
  Serial.println(VoltageVal);
  delay(1000);
}
