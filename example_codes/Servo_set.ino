#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (Serial.available() > 0) {  // if there's data in the serial buffer
    int angle = Serial.parseInt();  // read the input value as an integer
    myservo.write(angle);  // set the servo position based on the input value
    Serial.print("Servo angle set to ");  // print a message to the serial monitor
    Serial.println(angle);
  }
}
