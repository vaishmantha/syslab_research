#include <Stepper.h>

//Default baud speed for communication
#define BAUD 9600
//stepper motor stuff 

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

void setup(){
  Serial.begin(BAUD);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(in5Pin, OUTPUT);
  pinMode(in6Pin, OUTPUT);
  pinMode(in7Pin, OUTPUT);
  pinMode(in8Pin, OUTPUT);

  motor1.setSpeed(2);
  motor2.setSpeed(2);
}

void loop(){
  String input;
  String direc;
  int steps;
  int magnitude;
  //If any input is detected in arduino
  if(Serial.available() > 0){
    //read the whole string until '\n' delimiter is read
    input = Serial.readStringUntil('\n');
    direc = input.substring(0,1);
    magnitude = input.substring(1).toInt();

    
    if (direc.equals("L")){
      Serial.println(magnitude);
      steps = int(magnitude * double(55)/75);
      Serial.println(steps);
      motor2.step(-1 * steps); 
      Serial.println("Moving LEFT");
    } 
    
    if (direc.equals("R")){
            steps = int(magnitude * double(55)/75);
      motor2.step(steps); 
      Serial.println("Moving RIGHT");
    } 
    if (direc.equals("U")){
      steps = int(magnitude * double(55)/75);
      motor1.step(-1*steps); 
      Serial.println("Moving UP");
    } 
    if (direc.equals("D")){
            steps = int(magnitude * double(55)/75);
      motor1.step(steps); 
      Serial.println("Moving DOWN");
    } 
  }
}


