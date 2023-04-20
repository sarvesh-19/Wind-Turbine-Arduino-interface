#include <Wire.h>

float rpm = 0; // variable to store calculated RPM
float maxRpm = 0; // variable to store maximum RPM observed so far
unsigned long millisBefore; // variable to store the millis() value when the previous RPM calculation was done
volatile int holes; // variable to store the number of holes detected by the interrupt

void setup()
{
  Serial.begin(9600); // initialize serial communication at 9600 baud
  pinMode(2, INPUT); // set digital pin 2 as input
  attachInterrupt(digitalPinToInterrupt(2), count, FALLING); // attach interrupt to pin 2, triggered on falling edge (when hole is detected)
  delay(1000); // wait for 1 second before starting to allow the interrupt to settle
}

void loop()
{
  print_to_Serial(); // print RPM and max RPM to serial monitor
  if (millis() - millisBefore > 1000) { // check if 1 second has elapsed since the last RPM calculation
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
