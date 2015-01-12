
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
//typedef int bool;
//#define true 1
//#define false 0

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

int i=0;

int order[] = {
  1,4,5,3,2 };
int orderSize = sizeof(order)/sizeof(order[6]);
int lastIngredient = 0;
boolean backstep = false;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {

  for(i;i<orderSize;i++)
  {
    digitalWrite(13,HIGH);
    int count = 0, pos = 0, linearTravel = rotateComputation(order[i]);
    Serial.print("\nBACKSTEP? ");
    Serial.println(backstep);
    Serial.println();
    Serial.print("NEW loop: ");
    Serial.println(linearTravel*2);

    
    while(count < 2 && pos < linearTravel * 2)
    {
      if(backstep == true)
      {
        myStepper.step(-(490/2));
      }
      else
      {
        if(order[i] == 1)
          myStepper.step((490/2)/2);
        else
          myStepper.step(490/2);  
      }
      
      count++;
      if(count == 2)
      {
        count = 0;
       
        Serial.print("NEW position: "); 
        Serial.println(pos);
        pos++;
      }
    }
      delay(15);
    //End of For Loop
  }
  lastIngredient = 0;
  digitalWrite(13,LOW);
  //End of main
  
}

int rotateComputation(int bottle)
{
  int looper = 0;

  if(lastIngredient == 0)
    looper = bottle * stepsPerRevolution;
    
  else
  {
     if(backstep == true)
        looper = (stepsPerRevolution * (lastIngredient - bottle));
     else
        looper = (stepsPerRevolution * (bottle - lastIngredient));
  } 
  
  backstep = lastIngredient > bottle ? true : false;
  
  looper = looper / stepsPerRevolution;
  
  if(looper < 0)
      looper = looper * (-1);
      
  lastIngredient = bottle;
  
  return looper;
}






