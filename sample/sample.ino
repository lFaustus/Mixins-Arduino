int incomingByte;  // incoming data

void setup() {
  Serial.begin(9600); // initialization
  
}

void loop() {
  
  if (Serial.available() > 0) {  // if the data came
    incomingByte = Serial.read()-48; // read byte
     
    switch(incomingByte)
    {
      case 0:
        Serial.println(incomingByte);
        break;
        
      case 1:
        Serial.println(incomingByte);
        break;
        
      case 2:
        Serial.println(incomingByte);
        break;
        
      case 3:
        Serial.println(incomingByte);
        break;
        
      case 4:
        Serial.println(incomingByte);
        break;
        
      case 5:
        Serial.println(incomingByte);
        break;
        
      case 6:
        Serial.println(incomingByte);
        break;
        
      case 7:
        Serial.println(incomingByte);
        break;
        
      case 8:
        Serial.println(incomingByte);
        break;
        
      case 9:
        Serial.println(incomingByte);
        break;
    }
  }
}
