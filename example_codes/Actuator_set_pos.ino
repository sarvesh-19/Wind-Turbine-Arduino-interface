// Simple code to extend/retract actuator
// This is for testing the actuator pitching angles - create new file for PID feedback control later - should have PID, hall effect read, current and voltage read, and actuator control as shown
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
const int buttonA = 3; // button 1 to extend actuator
const int buttonB = 4; // button 2 to retract actuator
int previous = 0; 

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(buttonA, INPUT_PULLUP); // set input A to pin 3
  pinMode(buttonB, INPUT_PULLUP); // set input B to pin 4
}

void loop() {
  if (digitalRead(buttonA) == LOW){
    for (pos = previous; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      
      Serial.print("Current Pos: ");
      Serial.println(pos);
      previous = pos;
      
      // break 
      if (digitalRead(buttonA) == HIGH) {
         break;
        }
      delay(30);                       // waits 30ms for the servo to reach the position
    }
  }
  if (digitalRead(buttonB) == LOW) {
    for (pos = previous; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      
      Serial.print("Current Pos: ");
      Serial.println(pos);
      previous = pos;

      // break
      if (digitalRead(buttonB) == HIGH) {
        break;
       }
      
      delay(30);                       // waits 30ms for the servo to reach the position
    }
  }
}
