#include <Wire.h>
#include <Servo.h>

Servo servo1;  // create servo object to control servo on pin 9
Servo servo2;  // create servo object to control servo on pin 10

float rpm = 0; // variable to store calculated RPM
float maxRpm = 0; // variable to store maximum RPM observed so far
unsigned long millisBefore; // variable to store the millis() value when the previous RPM calculation was done
volatile int holes; // variable to store the number of holes detected by the interrupt

void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 baud
  servo1.attach(9); // attaches the servo on pin 9 to the servo object
  servo2.attach(10); // attaches the servo on pin 10 to the servo object
  pinMode(2, INPUT); // set digital pin 2 as input
  attachInterrupt(digitalPinToInterrupt(2), count, FALLING); // attach interrupt to pin 2, triggered on falling edge (when hole is detected)
  delay(1000); // wait for 1 second before starting to allow the interrupt to settle
}

void loop()
{
  if (Serial.available() > 0) {  // if there's data in the serial buffer
    String input = Serial.readStringUntil('\n');  // read the input value as a string until newline character is received
    input.trim();  // remove any leading or trailing whitespaces from the input string
    if (input.startsWith("s1")) {  // check if the input string starts with "s1"
      int angle = input.substring(2).toInt();  // extract the angle value from the input string (excluding the "s1" prefix)
      servo1.write(angle);  // set the servo1 position based on the input angle value
      Serial.print("Servo1 angle set to ");  // print a message to the serial monitor
      Serial.println(angle);
    } else if (input.startsWith("s2")) {  // check if the input string starts with "s2"
      int angle = input.substring(2).toInt();  // extract the angle value from the input string (excluding the "s2" prefix)
      servo2.write(angle);  // set the servo2 position based on the input angle value
      Serial.print("Servo2 angle set to ");  // print a message to the serial monitor
      Serial.println(angle);
    }
  }
  
  print_to_Serial(); // print RPM and max RPM to serial monitor
  if (millis() - millisBefore > 400) { // check if 0.4 second has elapsed since the last RPM calculation
    rpm = (holes / 24.0)*60; // calculate RPM using the number of holes detected in the last second
    if (rpm > maxRpm) { // check if new RPM is higher than current max
      maxRpm = rpm; // update max RPM if new RPM is higher
    }
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
  Serial.println(holes);
}

void count() {
  holes++; // increment hole counter whenever an interrupt is triggered
}
