/*
Adafruit Arduino - Lesson 16. Stepper
*/

#include <Stepper.h>

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

int in5Pin = 7;
int in6Pin = 6;
int in7Pin = 5;
int in8Pin = 4;

Stepper motor1(512, in1Pin, in2Pin, in3Pin, in4Pin);  
Stepper motor2(512, in5Pin, in6Pin, in7Pin, in8Pin);  
void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(in5Pin, OUTPUT);
  pinMode(in6Pin, OUTPUT);
  pinMode(in7Pin, OUTPUT);
  pinMode(in8Pin, OUTPUT);
  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
  while (!Serial);
  
  Serial.begin(9600);
  motor1.setSpeed(2);
  motor2.setSpeed(2);
}

void loop()
{
  if (Serial.available())
  {
    int steps = Serial.parseInt();
        motor2.step(steps);

    motor1.step(steps);
 
//    motor1.step(-100); //up
    
  }
}

//hardcode stepper movements
//make it work with arduino 
// 

//tutorial and explains how stepper motors work
//https://learn.adafruit.com/adafruit-arduino-lesson-16-stepper-motors/arduino-code

