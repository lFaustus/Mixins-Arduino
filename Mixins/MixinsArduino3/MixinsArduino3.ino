
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
const int bottle_1 = 1;
const int bottle_2 = 2;
const int bottle_3 = 3;
const int bottle_4 = 4;
const int bottle_5 = 5;
const int bottle_6 = 6;
int i=0;
int order[] = {
  1,4,5,3,2};
int orderSize = sizeof(order)/sizeof(order[6]);
//int stepMultiplier = 0;
int lastIngredient = 0;
//int looper = 0;
boolean backstep = false;
void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  // step one revolution  in one direction:
  //Serial.println("clockwise");

  for(i;i<orderSize;i++)
  {
    digitalWrite(13,HIGH);
    if(order[i] == bottle_1) //ingredient 1
    {
      if(lastIngredient == 0)
      {
         //stepMultiplier = stepsPerRevolution;
         //looper = 1;
         backstep = false;
      }  
       
      else
      {
        if(lastIngredient > bottle_1) //backward rotation
        {
          //rotateComputation(backstep,bottle_1);
          backstep = true;       
        }
        else //forward rotation
        {
          //rotateComputation(backstep,bottle_1);
          backstep = false;
        }
        
      }
       lastIngredient = order[i]; 
    }

    else if(order[i] == bottle_2)//ingredient 2
    {
      if(lastIngredient == 0)
      {
        //stepMultiplier = 2*stepsPerRevolution;
        //looper = 2;
        backstep = false;
      }
      else
      {
        if(lastIngredient > bottle_2) //backward rotation
        {
           //rotateComputation(backstep,bottle_2);
           backstep = true; 
        }
          
        else //forward rotation
        {
          //rotateComputation(backstep,bottle_2);
          backstep = false;
        }
          
      }
      lastIngredient = order[i];
    }

    else if(order[i] == bottle_3)//ingredient 3
    {
      if(lastIngredient == 0)
      {
        //looper = 3;
        //stepMultiplier =3*stepsPerRevolution;
        backstep = false;
      }
      else
      {
        if(lastIngredient > bottle_3) //backward rotation
        {
           //rotateComputation(backstep,bottle_3);           
           backstep = true; 
        }
          
        else //forward rotation
        {
          //rotateComputation(backstep,bottle_3);
          backstep = false;
        }
      }
      lastIngredient = order[i];
    }

    else if(order[i] == bottle_4)
    {
      if(lastIngredient == 0)
      {
        //looper = 4;
        //stepMultiplier = 4*stepsPerRevolution;
        backstep = false;
      }
      else
      {
        if(lastIngredient > bottle_4) //backward rotation
        {
           //rotateComputation(backstep,bottle_4);
           backstep = true; 
        }
          
        else //forward rotation
        {
          //rotateComputation(backstep,bottle_4);
          backstep = false;
        }
      }
      lastIngredient = order[i];
    }

    else if(order[i] == bottle_5)
    {
      if(lastIngredient == 0)
      {
       //looper = 5;
       //stepMultiplier = 5*stepsPerRevolution;
       backstep = false;
      }
      else
      {
        if(lastIngredient > bottle_5) //backward rotation
        {
           //rotateComputation(backstep,bottle_5);
           backstep = true; 
        }
          
        else //forward rotation
        {
          //rotateComputation(backstep,bottle_5);
          backstep = false;
        }
      }
      lastIngredient = order[i];
    }

    else if(order[i] == bottle_6)
    {
      if(lastIngredient == 0)
      {
       //looper = 6;
       //stepMultiplier = 6*stepsPerRevolution;
       backstep = false;
      }
      else
      {
        if(lastIngredient > bottle_6) //backward rotation
        {
           //rotateComputation(backstep,bottle_6);
           backstep = true; 
        }
          
        else //forward rotation
        {
          //rotateComputation(backstep,bottle_6);
          backstep = false;
        }
      }
      lastIngredient = order[i];
    }
    int count = 0,wineloop = 0,x = rotateComputation(backstep,order[i]);
    Serial.print("NEW loop: ");
    Serial.println(x*2);
    Serial.println();
    
    while(count < 2 && wineloop < x*2)
    {
      /*if(backstep == true)
      {
        myStepper.step(-(490/2));
      }
      else
      {
        if(order[i] == 1)
          myStepper.step((490/2)/2);
        else
          myStepper.step(490/2);  
      }*/
      
      count++;
      if(count == 2)
      {
        count = 0;
       
        Serial.print("NEW wineloop: "); 
        Serial.println(wineloop);
        Serial.println();
         wineloop++;
      }
    }
      delay(15);
    //End of For Loop
  }
  lastIngredient = 0;
  digitalWrite(13,LOW);
  //End of main
  
}

int rotateComputation(boolean bstep,int bottle)
{
  int looper = 0;
  int stepMultiplier = stepsPerRevolution * bottle;
  
  if(bstep == true)
    looper = (stepsPerRevolution * (lastIngredient - bottle));
  else
    looper = (stepsPerRevolution * (bottle - lastIngredient));
    
  looper = stepMultiplier / stepsPerRevolution;
  
  if(looper < 0)
      looper = looper * (-1);
      
  return looper;
}






