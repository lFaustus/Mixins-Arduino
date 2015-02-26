
#include <AccelStepper.h>
#include <Servo.h>

AccelStepper myStepper(AccelStepper::FULL4WIRE,8,9,10,11,true);            

int lastIngredient = 0;

int incomingByte;

boolean moveServo = false;

Servo myservo;

const int servoRelayPin = 2;
const int stepperRelayPin = 3;
const int stepperEnableDriverPinA = 5;
const int stepperEnableDriverPinB = 6;

long stepperCurrentPosition = 0;

void setup() {
  myservo.attach(4,1000,2000);
  myservo.writeMicroseconds(1000);
  
  myStepper.setMaxSpeed(5000);
  myStepper.setAcceleration(1000);
  
  Serial.begin(9600);
  
  pinMode(stepperEnableDriverPinA,OUTPUT);
  pinMode(stepperEnableDriverPinB,OUTPUT);
  pinMode(servoRelayPin,OUTPUT);
  pinMode(stepperRelayPin,OUTPUT);
  digitalWrite(stepperRelayPin,LOW);
  digitalWrite(servoRelayPin,LOW);
}

void loop() {

  if(Serial.available() > 0) // if the data came
  {
    incomingByte = Serial.parseInt(); //read single byte from serial buffer
    
    String tempString = String(incomingByte);
    //Serial.println(tempString);
    if(moveServo == false) // constraint for bottle
    {
      digitalWrite(stepperRelayPin,HIGH);
      digitalWrite(stepperEnableDriverPinA,HIGH);
      digitalWrite(stepperEnableDriverPinB,HIGH);
      tempString.concat(" ingredient");
      //Serial.println(tempString);
      /*Serial.print("Current Position");
      Serial.println(myStepper.currentPosition());*/
      
       switch(incomingByte)
       {
         case 1:
            //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 150));
            myStepper.runToNewPosition(195);
            //Serial.println("ENTERED");
           break;
         
         case 2:
            //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 498));
            //myStepper.runToNewPosition(myStepper.currentPosition() + (incomingByte - lastIngredient) * 340);    
            myStepper.runToNewPosition(incomingByte * 345);  
            
           break;
           
         case 3:
            //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 405));
            myStepper.runToNewPosition(incomingByte * 398);     
            
           break;
           
         case 4:
              //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 428));
              myStepper.runToNewPosition(incomingByte * 423);          
           break;
         
         case 5:
             //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 440));
             myStepper.runToNewPosition(incomingByte * 434);
           break;
           
         case 6:
            myStepper.runToNewPosition(incomingByte * 448);
           break;
       }
       
      myStepper.stop(); // Stop as fast as possible: sets new target
      lastIngredient = incomingByte;
      digitalWrite(stepperRelayPin,LOW);
      digitalWrite(stepperEnableDriverPinA,LOW);
      digitalWrite(stepperEnableDriverPinB,LOW);
      moveServo = true;
    }
    
    else if( moveServo == true) // constraint for ml
    {
         digitalWrite(stepperRelayPin,LOW);
         digitalWrite(stepperEnableDriverPinA,LOW);
         digitalWrite(stepperEnableDriverPinB,LOW);
         digitalWrite(servoRelayPin,HIGH);
         //Serial.println("adsadsad");
         int mlToPush = incomingByte;
         if(mlToPush/50 !=0 && (lastIngredient >=1 && lastIngredient <=4))
         {
           int temp = mlToPush / 50;
           for(int i = 0; i<temp ; i++)
           {
             
             int push = map(50,0,50,0,3810);
             myservo.write(120);
             delay(push);
             myservo.write(0);
             mlToPush = mlToPush - 50;
             delay(push+200);
             //Serial.println("nakasud");
           }
           
         }
         if(mlToPush != 0 && (lastIngredient >=1 && lastIngredient <=4))
         {
           //Serial.println("nakasud2");
             int push = map(mlToPush,0,49,0,4150);
             //Serial.println(push);
             myservo.write(120);
             delay(push);
             myservo.write(0);
             delay(push);
             
         }
         
         if(mlToPush/25  != 0 && (lastIngredient >= 5 && lastIngredient <=6))
           {
             /*int push2 = map(25,0,25,0,3500);
             myservo.write(116);
             delay(push2);
             myservo.writeMicroseconds(1000);
             mlToPush = mlToPush - 25;
             delay(push2);*/
             int temp = mlToPush / 25;
             for(int i = 0; i<temp ; i++)
             {
             
             int push = map(25,0,25,0,2750);
             myservo.write(125);
             delay(push);
             myservo.write(0);
             mlToPush = mlToPush - 25;
             delay(push);
             }
           }
           
          if(mlToPush  != 0 && (lastIngredient >= 5 && lastIngredient <=6))
         {
             int push = map(mlToPush,0,24,0,3200);
             //Serial.println(mlToPush);
             //Serial.println(push);
               myservo.write(125);
             delay(push);
             myservo.write(0);
             delay(push);
             //Serial.println("nakasud4");
         }
          myservo.write(0);
         digitalWrite(servoRelayPin,LOW);
         moveServo = false;
    }
    
  }
  if(lastIngredient != 0 && Serial.available() <= 0)
  {    
    digitalWrite(stepperRelayPin,HIGH);
    digitalWrite(stepperEnableDriverPinA,HIGH);
    digitalWrite(stepperEnableDriverPinB,HIGH);
    Serial.write("done");
    Serial.flush();
    myStepper.runToNewPosition(5);
    myStepper.stop();
    
    // Reset
    lastIngredient = 0;
    digitalWrite(stepperRelayPin,LOW);
    digitalWrite(stepperEnableDriverPinA,LOW);
    digitalWrite(stepperEnableDriverPinB,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  // End of main
}

boolean Constraint(int value, int lowerlimit, int upperlimit)
{
  if(value > lowerlimit && value < upperlimit)
    return true;
    
    return false;
}







