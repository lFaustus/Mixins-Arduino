#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

int i=0;

int order[] = {
  1,4,5,3,2};
  
int orderSize = sizeof(order)/sizeof(order[6]);

int lastIngredient = 0;

boolean backstep = false;

void setup() {
  
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  
  // initialize the serial port:
  Serial.begin(9600);
  
  // initialize pin 13 as OUTPUT
  pinMode(13,OUTPUT);
}

void loop() {

  for(i;i<orderSize;i++)
  {
    digitalWrite(13,HIGH);
    
    linearTravelStart(order[i],i);
    
    
   // End of For Loop
  }
  
  // Reset
  lastIngredient = 0;
  digitalWrite(13,LOW);
  
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

void linearTravelStart(int bottle,int bottleCursor)
{
    int count = 0, pos = 0, linearTravel = rotateComputation(bottle);
    Serial.print("\nBACKSTEP? ");
    Serial.println(backstep);
    Serial.println();
    Serial.print("NEW loop: ");
    Serial.println(linearTravel);

    
    while(count < 2 && pos < linearTravel)
    {
      if(backstep == true)
      {
          myStepper.step(-(490/2));
      }
      else
      {
        if(lastIngredient == 0 && pos == 0)
        {
           myStepper.step((490/2)/2);
           Serial.println("nakasud");
        }
         
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
    lastIngredient = bottle;
    
    delay(1000);
    
    // Checks if it is on last bottle 
    // If it is, it returns to starting point
    if(bottleCursor == orderSize - 1) 
    {
       for(int counter = 0; counter <(lastIngredient*2) - 1; counter ++)
       {
         myStepper.step(-(490/2));
       }
    }
}






