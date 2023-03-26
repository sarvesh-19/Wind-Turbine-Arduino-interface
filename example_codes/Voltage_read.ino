int value = 0;
float voltage;
float R1 = 47000.0; // change this
float R2 = 33000.0; // change this

void setup(){
  Serial.begin(9600);
}

void loop(){
  value = analogRead(A0);
  // Voltage divider formula required to get actual voltage value at output
  voltage = value * (5.0/1024)*((R1 + R2)/R2);
  Serial.print("Voltage =");
  Serial.println(voltage);
  delay(500);
}
