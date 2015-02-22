// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::FULL4WIRE,8,9,10,11,true); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
   const int stepperRelayPin = 3;
const int stepperEnableDriverPinA = 6;
const int stepperEnableDriverPinB = 7;
void setup()
{  
   stepper.setMaxSpeed(5000);
  stepper.setAcceleration(1000);
  //stepper.setSpeed(500);
  
  
    pinMode(stepperEnableDriverPinA,OUTPUT);
  pinMode(stepperEnableDriverPinB,OUTPUT);
  pinMode(stepperRelayPin,OUTPUT);
  digitalWrite(stepperRelayPin,HIGH);
      digitalWrite(stepperEnableDriverPinA,HIGH);
      digitalWrite(stepperEnableDriverPinB,HIGH);
	
}

void loop()
{  
   stepper.moveTo(500);
  while (stepper.currentPosition() != 300) // Full speed up to 300
    stepper.run();
 // stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop

  // Now go backwards
  stepper.moveTo(-500);
  while (stepper.currentPosition() != 0) // Full speed basck to 0
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop(
  /*stepper.moveTo(500);
  while (stepper.currentPosition() != 300) // Full speed up to 300
    stepper.run();
  stepper.runToNewPosition(0); // Cause an overshoot then back to 0*/
  
}
