
/* 
 Stepper Motor Control - one revolution
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.  
 
  
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 
 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
                                     // for your motor

// initialize the stepper library on pins 8 through 11:
int x=0;
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
 // myStepper.setSpeed(200);
  // step one revolution  in one direction:
  /*for(i;i<8;i++)
  {
    digitalWrite(13,HIGH);
     Serial.println("clockwise");
    if(i==7)
    delay(1000);
    myStepper.step(250);
    
    
    
  }*/
  int i=0;
  while(i<2 && x<4)
  {
   digitalWrite(13,HIGH);
   Serial.println("clockwise");
   
  
   myStepper.step(490/2);
    
   i++;
   if(i == 2)
   {
     x++;
     if(x==3)
       delay(500);
       
   }
  };
      digitalWrite(13,LOW);  
  
}

