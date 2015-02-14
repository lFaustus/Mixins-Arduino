
#include <Stepper.h>
#include <Servo.h>

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

Servo myservo;

const int servoRelayPin = 2;
const int stepperRelayPin = 3; 
const int stepperEnableDriverPinA = 6;
const int stepperEnableDriverPinB = 7;

void setup() {
  myservo.attach(5,1000,2000);
  myservo.writeMicroseconds(1000);
  // set the speed at 60 rpm:
  //myStepper.setSpeed(60);
  
  // initialize the serial port:
  Serial.begin(9600);
  
  // initialize pins as OUTPUT
  //pinMode(stepperEnableDriverPin,OUTPUT);
  pinMode(stepperEnableDriverPinA,OUTPUT);
  pinMode(stepperEnableDriverPinB,OUTPUT);
  pinMode(servoRelayPin,OUTPUT);
  pinMode(stepperRelayPin,OUTPUT);
  digitalWrite(stepperRelayPin,LOW);
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
    
    String tempString = String(incomingByte);
    if(Constraint(incomingByte,0,7) == true) // constraint for bottle
    {
      //digitalWrite(6,HIGH);
      digitalWrite(stepperRelayPin,HIGH);
      //digitalWrite(stepperEnableDriverPin,HIGH);
      //stepperEnable_Disable();
      tempString.concat(" ingredient");
      Serial.println(tempString);
      linearTravelStart(incomingByte);
      //digitalWrite(stepperRelayPin,LOW);
      //analogWrite(stepperEnableDriverPinA,60);
      //analogWrite(stepperEnableDriverPinB,60);
    }
    else if(Constraint(incomingByte,0,100) == true) // constraint for ml
    {
          //stepperEnable_Disable();//turns off the stepper driver when it is already enabled
         // servoEnable_Disable(); // turns on servo motor
         
         digitalWrite(servoRelayPin,HIGH);
         Serial.println(incomingByte);
         int push = map(incomingByte,0,100,0,13200);
          myservo.write(130);
          Serial.println(push);
          delay(push);
          myservo.writeMicroseconds(1000);
           delay(500);
          digitalWrite(servoRelayPin,LOW);
          //Serial.println(incomingByte);
         // servoEnable_Disable();//turns off servo motor if it is already enabled
    }
  }
  else
    carriage_back_to_origin = true;
  
  if(carriage_back_to_origin == true)
  {
    // stepperEnable_Disable();
    
      //digitalWrite(stepperEnableDriverPin,HIGH);
   
    for(int counter = 0; counter <(lastIngredient*4) - 3; counter ++)
    {
      digitalWrite(stepperRelayPin,HIGH);
      if(counter == 0)
      {
         myStepper.setSpeed(150);
         analogWrite(stepperEnableDriverPinA,150);
         analogWrite(stepperEnableDriverPinB,150);
      }
      else
      {
         myStepper.setSpeed(300);
         analogWrite(stepperEnableDriverPinA,255);
         analogWrite(stepperEnableDriverPinB,255);
      }
      if(lastIngredient == 1)
      {
         myStepper.step(-((steps/4)+28));
         Serial.println("nakasud");
      }
      else
        myStepper.step(-((steps/2)+85));
       // myStepper.step(-(steps/2));
    }
    
    // Reset
    carriage_back_to_origin = false;
    lastIngredient = 0;
   
   // stepperEnable_Disable();
  } 
   delayMicroseconds(2000);
      //digitalWrite(stepperEnableDriverPin,LOW);
      analogWrite(stepperEnableDriverPinA,0);
      analogWrite(stepperEnableDriverPinB,0);
      digitalWrite(stepperRelayPin,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
  // End of main
}

int rotateComputation(int bottle)
{
  int looper = 0;

  if(lastIngredient == 0)
    looper = bottle;
    
  else
  {
     if(backstep == true)
        looper = lastIngredient - bottle;
     else
        looper = bottle - lastIngredient;
  } 
  
  backstep = lastIngredient > bottle ? true : false;
  
  looper = looper < 0 ? looper * (-1) : looper;
  //Serial.println(looper);
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
      
      /*if(count <1 && pos == 0)
      {
          myStepper.setSpeed(120);
           analogWrite(stepperEnableDriverPinA,120);
           analogWrite(stepperEnableDriverPinB,120);
      }
      else
      {
           myStepper.setSpeed(200);
           analogWrite(stepperEnableDriverPinA,200);
           analogWrite(stepperEnableDriverPinB,200);
      }*/
      
      if(backstep == true)
      {
          if((count == 0 && pos == 0) || (count ==1 && pos == linearTravel -1)){
            myStepper.setSpeed(150);
           analogWrite(stepperEnableDriverPinA,150);
           analogWrite(stepperEnableDriverPinB,150);
           myStepper.step(-(steps/2));
          }
          else
          {
            myStepper.setSpeed(200);
           analogWrite(stepperEnableDriverPinA,255);
           analogWrite(stepperEnableDriverPinB,255);
           myStepper.step(-((steps/2)-3));
          } 
          
          
      }
      else
      {
        if(lastIngredient == 0 && pos == 0)
        {
          
            //if(count == 0){
              myStepper.setSpeed(150);
             analogWrite(stepperEnableDriverPinA,150);
             analogWrite(stepperEnableDriverPinB,150);
           // }
           // else
           // {
            //  myStepper.setSpeed(200);
            // analogWrite(stepperEnableDriverPinA,255);
            //}
              myStepper.step(steps/6);
          
           
           
        }
         
        else  
       {
         if((count == 0 && pos == 0) || (count ==1 && pos == linearTravel -1)){
            myStepper.setSpeed(150);
           analogWrite(stepperEnableDriverPinA,150);
           analogWrite(stepperEnableDriverPinB,150);
           myStepper.step((steps/2));
          }
          else
          {
           myStepper.setSpeed(200);
           analogWrite(stepperEnableDriverPinA,255);
           analogWrite(stepperEnableDriverPinB,255);
            myStepper.step((steps/2)-1);
          }
          
       }
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
    
    linearTravel = 0;
    delayMicroseconds(2000);
    analogWrite(stepperEnableDriverPinA,0);
    analogWrite(stepperEnableDriverPinB,0);
    digitalWrite(stepperRelayPin,LOW);

    
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

/*void stepperEnable_Disable()
{
  int val = digitalRead(stepperRelayPin);
  
  if(val == HIGH)
  {
    digitalWrite(stepperRelayPin,LOW);
    digitalWrite(stepperEnableDriverPin,LOW);
    
  }
  else
  {
      digitalWrite(stepperRelayPin,HIGH);
      digitalWrite(stepperEnableDriverPin,HIGH);
  }
   
}

void servoEnable_Disable()
{
  int valServo = digitalRead(servoRelayPin);
  
  if(valServo == HIGH)
     digitalWrite(servoRelayPin,LOW);
  else
     digitalWrite(servoRelayPin,HIGH);
}*/




