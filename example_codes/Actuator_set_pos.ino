// 5 stages of position for the actuator
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const int buttonA = 3; // button 1 to cycle through actuator extension stages
const int buttonB = 4; // button 2 to cycle through actuator retraction stages
int currentPos = 0; // variable to store the current actuator position
int stageIndex = 0; // variable to store the current stage index
const int numStages = 5; // total number of stages
const int stagePos[numStages] = {0, 45, 90, 135, 180}; // actuator position for each stage
const int minPos = 0; // minimum actuator position
const int maxPos = 180; // maximum actuator position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(buttonA, INPUT_PULLUP); // set input A to pin 3
  pinMode(buttonB, INPUT_PULLUP); // set input B to pin 4
  myservo.write(currentPos); // set initial position to 0
}

void loop() {
  if (digitalRead(buttonA) == LOW) {
    stageIndex++; // increment stage index
    if (stageIndex >= numStages) { // if at last stage, loop back to first stage
      stageIndex = 0;
    }
    currentPos = stagePos[stageIndex]; // set current position to the next stage position
    myservo.write(currentPos); // move the actuator to the current position
    Serial.print("Current Pos: ");
    Serial.println(currentPos);
    delay(200); // debounce delay to prevent button bounce
  }

  if (digitalRead(buttonB) == LOW) {
    stageIndex--; // decrement stage index
    if (stageIndex < 0) { // if at first stage, loop back to last stage
      stageIndex = numStages - 1;
    }
    currentPos = stagePos[stageIndex]; // set current position to the previous stage position
    myservo.write(currentPos); // move the actuator to the current position
    Serial.print("Current Pos: ");
    Serial.println(currentPos);
    delay(200); // debounce delay to prevent button bounce
  }
}
