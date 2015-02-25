
#include <AccelStepper.h>
#include <Servo.h>

AccelStepper myStepper(AccelStepper::FULL4WIRE,8,9,10,11,true);            

int lastIngredient = 0;

int incomingByte;

boolean moveServo = false;

Servo myservo;

const int servoRelayPin = 2;
const int stepperRelayPin = 3;
const int stepperEnableDriverPinA = 6;
const int stepperEnableDriverPinB = 7;

long stepperCurrentPosition = 0;

void setup() {
  myservo.attach(5,1000,2000);
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
    if(Constraint(incomingByte,0,7) == true && moveServo == false) // constraint for bottle
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
            myStepper.runToNewPosition(180);
            //Serial.println("ENTERED");
           break;
         
         case 2:
            //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 498));
            //myStepper.runToNewPosition(myStepper.currentPosition() + (incomingByte - lastIngredient) * 340);    
            myStepper.runToNewPosition(incomingByte * 328);  
            
           break;
           
         case 3:
            //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 405));
            myStepper.runToNewPosition(incomingByte * 385);     
            
           break;
           
         case 4:
              //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 428));
              myStepper.runToNewPosition(incomingByte * 415);          
           break;
         
         case 5:
             //myStepper.runToNewPosition(myStepper.currentPosition() + ((incomingByte - lastIngredient) * 440));
             myStepper.runToNewPosition(incomingByte * 425);
           break;
           
         case 6:
            myStepper.runToNewPosition(incomingByte * 440);
           break;
       }
       
      myStepper.stop(); // Stop as fast as possible: sets new target
      lastIngredient = incomingByte;
      digitalWrite(stepperRelayPin,LOW);
      digitalWrite(stepperEnableDriverPinA,LOW);
      digitalWrite(stepperEnableDriverPinB,LOW);
      moveServo = true;
    }
    
    else if(Constraint(incomingByte,0,181) == true && moveServo == true) // constraint for ml
    {
         digitalWrite(stepperRelayPin,LOW);
         digitalWrite(stepperEnableDriverPinA,LOW);
         digitalWrite(stepperEnableDriverPinB,LOW);
         digitalWrite(servoRelayPin,HIGH);
         //Serial.println(incomingByte);
         int mlToPush = incomingByte;
         if(mlToPush/50 !=0 && (lastIngredient >=1 && lastIngredient <=4))
         {
           int temp = mlToPush / 50;
           for(int i = 0; i<temp ; i++)
           {
             
             int push = map(50,0,50,0,3450);
             myservo.write(170);
             delay(push);
             myservo.writeMicroseconds(1000);
             mlToPush = mlToPush - 50;
             delay(push+200);
             //Serial.println("nakasud");
           }
           
         }
         if(mlToPush != 0 && (lastIngredient >=1 && lastIngredient <=4))
         {
           //Serial.println("nakasud2");
             int push = map(mlToPush,0,49,0,3850);
             //Serial.println(push);
             myservo.write(170);
             delay(push);
             myservo.writeMicroseconds(1000);
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
             
             int push = map(25,0,25,0,2450);
             myservo.write(170);
             delay(push);
             myservo.writeMicroseconds(1000);
             mlToPush = mlToPush - 25;
             delay(push);
             }
           }
           
          if(mlToPush  != 0 && (lastIngredient >= 5 && lastIngredient <=6))
         {
             int push = map(mlToPush,0,24,0,2600);
             //Serial.println(mlToPush);
             //Serial.println(push);
             myservo.write(170);
             delay(push);
             myservo.writeMicroseconds(1000);
             delay(push);
             //Serial.println("nakasud4");
         }
           
         digitalWrite(servoRelayPin,LOW);
         moveServo = false;
    }
    
  }
  if(lastIngredient != 0 && Serial.available() <= 0)
  {    
      digitalWrite(stepperRelayPin,HIGH);
      //digitalWrite(stepperEnableDriverPin,LOW);
    digitalWrite(stepperEnableDriverPinA,HIGH);
    digitalWrite(stepperEnableDriverPinB,HIGH);
       Serial.write("done");
    //Serial.println("SERIAL EMPTY");
    //Serial.print("CURRENT POS : ");
      //Serial.println(stepperCurrentPosition - (500 * 4));
      myStepper.runToNewPosition(12);
      myStepper.stop();
      
   /* for(int counter = 0; counter <(lastIngredient*4) - 3; counter ++)
    {
      digitalWrite(stepperRelayPin,HIGH);
      digitalWrite(stepperEnableDriverPinA,HIGH);
      digitalWrite(stepperEnableDriverPinB,HIGH);
      //Serial.println((lastIngredient*4) - 3);
      Serial.print("last Ingredient");
      Serial.println(lastIngredient);
       myStepper.step(-((steps/2/2)+6));
       // myStepper.step(-(steps/2));
    }*/
    
    
    // Reset
    lastIngredient = 0;
    digitalWrite(stepperRelayPin,LOW);
      //digitalWrite(stepperEnableDriverPin,LOW);
    digitalWrite(stepperEnableDriverPinA,LOW);
    digitalWrite(stepperEnableDriverPinB,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);

  }
    /*int counter = 0, tempPos = 0,backtobase = lastIngredient - incomingByte;
    backtobase = backtobase < 0 ? backtobase * (-1) : backtobase;
    Serial.print("back to base");
    Serial.println(backtobase);
    if(backtobase != 0 ){
    while(tempPos < 6)
    {
      digitalWrite(stepperRelayPin,HIGH);
      //digitalWrite(stepperEnableDriverPin,HIGH);
    digitalWrite(stepperEnableDriverPinA,HIGH);
    digitalWrite(stepperEnableDriverPinB,HIGH);
      myStepper.step(-(steps/2/2));

        tempPos++;
     
    }
    
    
    
      
   // stepperEnable_Disable();
  } */
  // End of main
}

boolean Constraint(int value, int lowerlimit, int upperlimit)
{
  if(value > lowerlimit && value < upperlimit)
    return true;
    
    return false;
}







