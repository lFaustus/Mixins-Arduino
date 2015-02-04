#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

const int steps = 503;
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

int lastIngredient = 0;

boolean backstep = false;

int incomingByte;

boolean carriage_back_to_origin = false;

boolean moveServo = false;


void setup() {
  
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  
  // initialize the serial port:
  Serial.begin(9600);
  
  // initialize pin 13 as OUTPUT
  pinMode(13,OUTPUT);
}

void loop() {

  /*for(i;i<orderSize;i++)
  {
    digitalWrite(13,HIGH);
    linearTravelStart(order[i],i);
   // End of For Loop
  }*/
  if(Serial.available() > 0) // if the data came
  {
    incomingByte = Serial.read() - 48; //read single byte from serial buffer
    digitalWrite(13,HIGH);
    String tempString = String(incomingByte);
    if(Constraint(incomingByte,0,7) == true) // constraint for bottle
    {
      tempString.concat(" ingredient");
      Serial.println(tempString);
      linearTravelStart(incomingByte);
    }
    else if(Constraint(incomingByte,0,100) == true) // constraint for ml
    {
      Serial.println(incomingByte);
    }
     
      //Serial.println(incomingByte);
  }
  else
    carriage_back_to_origin = true;
  
  if(carriage_back_to_origin == true)
  {
    for(int counter = 0; counter <(lastIngredient*2) - 1; counter ++)
    {
       myStepper.step(-((steps/2)/2));
    }
    
    // Reset
    carriage_back_to_origin = false;
    lastIngredient = 0;
    digitalWrite(13,LOW);
  }
  // End of main
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
      
  //lastIngredient = bottle;
  
  return looper;
}

void linearTravelStart(int bottle)
{
    int count = 0, pos = 0, linearTravel = rotateComputation(bottle);
   /* Serial.print("\nBACKSTEP? ");
    Serial.println(backstep);
    Serial.println();
    Serial.print("NEW loop: ");
    Serial.println(linearTravel);*/

    
    while(count < 2 && pos < linearTravel)
    {
      if(backstep == true)
      {
          myStepper.step(-(steps/2));
          
      }
      else
      {
        if(lastIngredient == 0 && pos == 0)
        {
           myStepper.step(((steps/2)/2)/2);
          // Serial.println("nakasud");
        }
         
        else
          myStepper.step(steps/2);  
      }
      
      count++;
      if(count == 2)
      {
        count = 0;
       
        //Serial.print("NEW position: "); 
        //Serial.println(pos);
        pos++;
      }
    }
    lastIngredient = bottle;
    
    delay(1000);
    
    // Checks if it is on last bottle 
    // If it is, it returns to starting point
    //if(bottleCursor == orderSize - 1) 
   // {
       
    //}
}

boolean Constraint(int value, int lowerlimit, int upperlimit)
{
  if(value > lowerlimit && value < upperlimit)
    return true;
    
    return false;
}



