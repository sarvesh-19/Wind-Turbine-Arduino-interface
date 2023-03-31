int value = 0;
float voltage;
float R1 = 180000; // change this
float R2 = 10000; // change this

void setup(){
  Serial.begin(9600);
}

void loop(){
  value = analogRead(A0);
  // Voltage divider formula required to get actual voltage value at output
  voltage = value * (5.0/1024)*((R1 + R2)/R2);
  Serial.print("Voltage =");
  Serial.println(voltage * 19);
  delay(500);
}
