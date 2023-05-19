#include <Wire.h>
#include <Servo.h>

Servo myservo;

float rpm = 0; // variable to store calculated RPM
float maxRpm = 0; // variable to store maximum RPM observed so far
unsigned long millisBefore; // variable to store the millis() value when the previous RPM calculation was done
volatile int holes; // variable to store the number of holes detected by the interrupt
const int stagePos[5] = {10, 60, 90, 120, 180}; // actuator position for each stage
int currentpos = 0;

Servo actuator; // create Servo object to control the linear actuator
int position = 45; // variable to store the position/angle of the linear actuator

Servo brake; // create Servo object to control brake
int brake_pos = 10; // variable to store brake position/angle

const int estopPin = 3; // set the pin number for the emergency stop button
boolean estopPressed = false; // initialize the emergency stop button state to false

void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 baud
  myservo.attach(9);
  pinMode(2, INPUT); // set digital pin 2 as input
  attachInterrupt(digitalPinToInterrupt(2), count, FALLING); // attach interrupt to pin 2, triggered on falling edge (when hole is detected)
  delay(1000); // wait for 1 second before starting to allow the interrupt to settle
  actuator.attach(9); // attach the linear actuator to digital pin 9
  brake.attach(10); // attach the brake actuator to digital pin 10
  pinMode(estopPin, INPUT_PULLUP); // set the emergency stop button pin as input with pull-up resistor
  delay(1000); // wait for 1 second before starting to allow the interrupt to settle
}

void loop()
{
  estopPressed = digitalRead(estopPin) == LOW; // check if the emergency stop button is pressed
  
  if (estopPressed) { // if the emergency stop button is pressed, stop the motor and activate the brake
    position = 10;
    brake_pos = 40;
    actuator.write(position);
    brake.write(brake_pos);
    Serial.println("E-stop activated!");
  } 
  
  else { // otherwise, run the motor as usual
    print_to_Serial(); // print RPM and max RPM to serial monitor

    if (millis() - millisBefore > 400) { // check if 0.4 seconds have elapsed since the last RPM calculation
      rpm = (holes / 24.0) * 60; // calculate RPM using the number of holes detected in the last 0.4 seconds
      if (rpm > maxRpm) { // check if new RPM is higher than current max
        maxRpm = rpm; // update max RPM if new RPM is higher
      }
      holes = 0; // reset the hole counter
      millisBefore = millis(); // store the current millis() value for the next RPM calculation
    }
    delay(40);

    // Determine position of the pitch based on RPM
    if (maxRpm > 300) {
      position = 10;
    } 
    
    // if (maxRpm >= 100 && rpm <= 2500) {
    //   position = 30;
    // }

    // if (maxRpm > 2500) {
    //   position = 45;
    // } 
    
    actuator.write(position); // set the position/angle of the linear actuator
    brake.write(brake_pos); // set the brake angle     
  
    // if (maxRpm <= 2000) {
    //   currentpos = stagePos[0];
    //   myservo.write(currentpos);
    //   Serial.print("Current Pitch Position: ");
    //   Serial.println(currentpos);
    // }

    delay(40); // wait 100 milliseconds before checking again
  }
}

void print_to_Serial() {
  Serial.print("RPM   : ");
  Serial.print(rpm);
  Serial.print("    Max RPM: ");
  Serial.print(maxRpm);
  Serial.print("    Holes: ");
  Serial.print(holes);
  Serial.print("    Pitch Pos: ");
  Serial.print(position);
  Serial.print("    Brake pos: ");
  Serial.println(brake_pos);
}

void pitchstop() {
  currentpos = stagePos[2];
  actuator.write(currentpos);
  Serial.print("Current Pitch Position: ");
  Serial.println(currentpos);
}

void count() {
  holes++; // increment hole counter whenever an interrupt is triggered
}
