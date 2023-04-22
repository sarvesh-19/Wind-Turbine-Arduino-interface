#include <Wire.h>
#include <Servo.h>

float rpm = 0; // variable to store calculated RPM
float maxRpm = 0; // variable to store maximum RPM observed so far
unsigned long millisBefore; // variable to store the millis() value when the previous RPM calculation was done
volatile int holes; // variable to store the number of holes detected by the interrupt

Servo actuator; // create Servo object to control the linear actuator
int position = 10; // variable to store the position/angle of the linear actuator

Servo brake; // create Servo object to control brake
int brake_pos = 10; // variable to store brake position/angle

void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 baud
  pinMode(2, INPUT); // set digital pin 2 as input
  attachInterrupt(digitalPinToInterrupt(2), count, FALLING); // attach interrupt to pin 2, triggered on falling edge (when hole is detected)
  actuator.attach(9); // attach the linear actuator to digital pin 9
  brake.attach(10); // attach the brake actuator to digital pin 10
  delay(1000); // wait for 1 second before starting to allow the interrupt to settle
}

void loop()
{
  print_to_Serial(); // print RPM and max RPM to serial monitor
  if (millis() - millisBefore > 400) { // check if 0.4 seconds have elapsed since the last RPM calculation
    rpm = (holes / 24.0) * 60; // calculate RPM using the number of holes detected in the last 0.4 seconds
    if (rpm > maxRpm) { // check if new RPM is higher than current max
      maxRpm = rpm; // update max RPM if new RPM is higher
    }
    // Determine position of the linear actuator based on RPM
    if (rpm > 1100) {
      position = 84;
      brake_pos = 95;
    } else if (rpm < 400) {
      position = 10;
      brake_pos = 10;
    } else {
      position = 65;
      brake_pos = 10;
    }
    actuator.write(position); // set the position/angle of the linear actuator
    brake.write(brake_pos); // set the brake angle
    
    holes = 0; // reset the hole counter
    millisBefore = millis(); // store the current millis() value for the next RPM calculation
  }
  delay(100); // wait 100 milliseconds before checking again
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

void count() {
  holes++; // increment hole counter whenever an interrupt is triggered
}
