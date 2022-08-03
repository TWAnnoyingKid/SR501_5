/*************************************************
*** The Motion Following Motorized Camera Base ***
***               by Lindsay Fox               ***
*************************************************/

// Servor motor
#include <Servo.h>
Servo camServo; // name the servo motor controlling the camera base
int currentPIRposition = 0; // set current angle of servo

// PIR sensors
int PIRpin[] = {16,14,12,13,15}; // PIR pin numbers : D0 D5 D6 D7 D8
int currentPIRpin = 16; // the current PIR pin; begin with the first in the sequence above : D0
int PIRprevState[] = {1,1,1,1,1}; // the previous state of the PIR (0 = LOW, 1 = HIGH)
int PIRposition[] = {157,117.75,78.5,39.25,0}; // assign angles for servo motor (0-157 distributed equally between 5 PIR sensors)
boolean PIRstatus; // Set status of PIR sensor as either true or false



///// SETUP //////////////////////////////////////
void setup()  {
  
  Serial.begin(9600);
  camServo.attach(5); // assign servo pin : D1
  
  for (int p = 0; p < 5; p++)  { // set all PIR sensors as INPUTS
  pinMode(PIRpin[p], INPUT);
    } // end 'p' for
  
  /////// CALIBRATE PIR SENSORS ///////
  Serial.print("Calibrating PIR Sensors ");
    for(int c = 0; c < 15; c++){ // calibrate PIR sensors for 15 seconds (change from 10-60 sec depending on your sensors)
      Serial.println(".");
      delay(1000); // wait 1 second
      } // end calibration for
    Serial.println("PIR Sensors Ready");
  
  camServo.write(78.5); // move the servo to the center position to begin
  
  } // end setup



///// MAIN LOOP //////////////////////////////////
void loop()  {
  
  for (int PIR = 0; PIR < 5; PIR++) { // start this loop for each PIR sensor
    currentPIRpin = PIRpin[PIR]; // set current PIR pin to current number in 'for' loop
    PIRstatus = digitalRead(currentPIRpin);
    
    if (PIRstatus == HIGH) { // if motion is detected on current PIR sensor
      if(PIRprevState[PIR] == 0) { // if PIR sensor's previous state is LOW
        if (currentPIRposition != currentPIRpin && PIRprevState[PIR] == 0) { // if high PIR is different than current position PIR then move to new position
          camServo.write(PIRposition[PIR]);
          Serial.print("Current angle : ");
          Serial.println(PIRposition[PIR]);
          delay(50);
          currentPIRposition = currentPIRpin; // reset current PIR position to active [PIR] pin
          PIRprevState[PIR] = 1; // set previous PIR state to HIGH
          }
        PIRprevState[PIR] = 1; // set previous PIR state to HIGH if the current position is the same as the current PIR pin
        } // end PIRprevState if  
      } // end PIRstatus if
    
    else  { //
      PIRprevState[PIR] = 0;   // set previous PIR state to LOW
      } // end else
      
    } // end [PIR] for loop
  } // end main loop
