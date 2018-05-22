//Default baud speed for communication
#define BAUD 9600
//led 

void setup(){
  Serial.begin(BAUD);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  String input;
  //If any input is detected in arduino
  if(Serial.available() > 0){
    //read the whole string until '\n' delimiter is read
    input = Serial.readStringUntil('\n');
    //If input == "ON" then turn on the led 
    //and send a reply
    if (input.equals("ON")){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.println("Led is on");
    } 
    //If input == "OFF" then turn off the led 
    //and send a reply
    else if (input.equals("OFF")){
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      Serial.println("Led is off");
    }
  }
}
