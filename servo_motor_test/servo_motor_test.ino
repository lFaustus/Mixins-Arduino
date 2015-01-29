#include <Servo.h>

Servo myservo;
int i=0;

void setup(){
  Serial.begin(9600);
  myservo.attach(9,1000,2000);
  myservo.writeMicroseconds(1000);
}
void loop()
{
  if(i == 0)
  {
    delay(1200);
     myservo.write(105);
     //delay(15);
    Serial.println("pos == 0");  
    i++;
  }
   else if(i == 1)
  {
    delay(1200);
   myservo.write(0);
    Serial.println("pos == 1");
    i = 0;
  }
  /*else if(i == 2)
  {
    delay(500);
    myservo.write(45);
    Serial.println("pos == 2");
  }*/
  
  Serial.println(i);
}
