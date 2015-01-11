
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
int stepMultiplier = 0;
int lastIngredientWent = 0;
int looper = 0;
//int wineloop = 0;
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
      if(lastIngredientWent == 0)
      {
         stepMultiplier = stepsPerRevolution;
         looper = 1;
         backstep = false;
      }  
       
      else
      {
        if(lastIngredientWent > bottle_1) //backward rotation
        {
          rotateComputation(backstep,bottle_1);
          backstep = true;       
        }
        else //forward rotation
        {
          rotateComputation(backstep,bottle_1);
          backstep = false;
        }
        
      }
       lastIngredientWent = order[i]; 
    }

    else if(order[i] == bottle_2)//ingredient 2
    {
      if(lastIngredientWent == 0)
      {
        stepMultiplier = 2*stepsPerRevolution;
        looper = 2;
        backstep = false;
      }
      else
      {
        if(lastIngredientWent > bottle_2) //backward rotation
        {
           rotateComputation(backstep,bottle_2);
           backstep = true; 
        }
          
        else //forward rotation
        {
          rotateComputation(backstep,bottle_2);
          backstep = false;
        }
          
      }
      lastIngredientWent = order[i];
    }

    else if(order[i] == bottle_3)//ingredient 3
    {
      if(lastIngredientWent == 0)
      {
        looper = 3;
        stepMultiplier =3*stepsPerRevolution;
        backstep = false;
      }
      else
      {
        if(lastIngredientWent > bottle_3) //backward rotation
        {
           rotateComputation(backstep,bottle_3);           
           backstep = true; 
        }
          
        else //forward rotation
        {
          rotateComputation(backstep,bottle_3);
          backstep = false;
        }
      }
      lastIngredientWent = order[i];
    }

    else if(order[i] == bottle_4)
    {
      if(lastIngredientWent == 0)
      {
        looper = 4;
        stepMultiplier = 4*stepsPerRevolution;
        backstep = false;
      }
      else
      {
        if(lastIngredientWent > bottle_4) //backward rotation
        {
           rotateComputation(backstep,bottle_4);
           backstep = true; 
        }
          
        else //forward rotation
        {
          rotateComputation(backstep,bottle_4);
          backstep = false;
        }
      }
      lastIngredientWent = order[i];
    }

    else if(order[i] == bottle_5)
    {
      if(lastIngredientWent == 0)
      {
       looper = 5;
       stepMultiplier = 5*stepsPerRevolution;
       backstep = false;
      }
      else
      {
        if(lastIngredientWent > bottle_5) //backward rotation
        {
           rotateComputation(backstep,bottle_5);
           backstep = true; 
        }
          
        else //forward rotation
        {
          rotateComputation(backstep,bottle_5);
          backstep = false;
        }
      }
      lastIngredientWent = order[i];
    }

    else if(order[i] == bottle_6)
    {
      if(lastIngredientWent == 0)
      {
       looper = 6;
       stepMultiplier = 6*stepsPerRevolution;
       backstep = false;
      }
      else
      {
        if(lastIngredientWent > bottle_6) //backward rotation
        {
           rotateComputation(backstep,bottle_6);
           backstep = true; 
        }
          
        else //forward rotation
        {
          rotateComputation(backstep,bottle_6);
          backstep = false;
        }
      }
      lastIngredientWent = order[i];
    }
    int count = 0,x = 0;
    Serial.print("NEW loop: ");
    Serial.println(looper*2);
    Serial.println();
    
    while(count < 2 && x < (looper*2))
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
      //wineloop++;
      if(count == 2)
      {
        count == 0;
        x++;
      }
      
      //Serial.print("NEW count: ");
       //Serial.println(count);
       //Serial.println();
        Serial.print("NEW wineloop: "); 
       Serial.println(x);
       Serial.println();
       /*Serial.print("NEW count: ");
       Serial.println(count);
      
      if(count == 2)
      {
      
        wineloop++;
        Serial.print("NEW wineloop: "); 
       Serial.println(wineloop);
       
        if(wineloop != looper*2)
        {
          count == 0;
          Serial.println("count is zero");
        }          
      }*/
          
       
    }
    /*for(wineloop;wineloop<(looper*2)+1;wineloop++)
    {     
        if(backstep == true)
        {
          
           myStepper.step(-stepsPerRevolution+30);
        }
         
        else
        {
            if(order[i]==1)
              myStepper.step(stepsPerRevolution-25);
            else
              myStepper.step(stepsPerRevolution+30);
              
        } 
        Serial.println(wineloop);      
    }*/
      
      /*Serial.print("Last Ingredient Went: ");
      Serial.println(lastIngredientWent);
      Serial.print("Backstep State: ");
      Serial.println(backstep);*/
      //Serial.print("looper: ");
      //Serial.println(looper);
      delay(1000);
    looper = 0;  
    //wineloop = 0;
    //End of For Loop
  }
  lastIngredientWent = 0;
  digitalWrite(13,LOW);
  //End of main
  
}

void rotateComputation(boolean bstep,int bottle)
{
  if(bstep == true)
    stepMultiplier = (stepsPerRevolution * (lastIngredientWent - bottle));
  else
    stepMultiplier = (stepsPerRevolution * (bottle - lastIngredientWent));
    
  looper = stepMultiplier / stepsPerRevolution;
  
  if(looper < 0)
      looper = looper * (-1);
      //Serial.print("looper: ");
      //Serial.println(looper);
}






