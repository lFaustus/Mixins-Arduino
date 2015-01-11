int incomingByte;  // incoming data

void setup() {
  Serial.begin(9600); // initialization
  
}

void loop() {
  
  if (Serial.available() > 0) {  // if the data came
    incomingByte = Serial.read()-48; // read byte
     String tempString = String(incomingByte);
    switch(incomingByte)
    {
      case 0:
        tempString.concat(" 0 ingredient");
        Serial.println(tempString);
        break;
        
      case 1:
        tempString.concat(" - 1st ingredient");
        Serial.println(tempString);
        break;
        
      case 2:
        tempString.concat(" - 2nd ingredient");
        Serial.println(tempString);
        break;
        
      case 3:
        tempString.concat(" - 3rd ingredient");
        Serial.println(tempString);
        break;
        
      case 4:
        tempString.concat(" - 4th ingredient");
        Serial.println(tempString);
        break;
        
      case 5:
        tempString.concat(" - 5th ingredient");
        Serial.println(tempString);
        break;
        
      case 6:
        tempString.concat(" - 6th ingredient");
        Serial.println(tempString);
        break;
        
      case 7:
        tempString.concat(" - 7th ingredient");
        Serial.println(tempString);
        break;
        
      case 8:
        tempString.concat(" - 8th ingredient");
        Serial.println(tempString);
        break;
        
      case 9:
        tempString.concat(" - 9th ingredient");
        Serial.println(tempString);
        break;
        
      default:
        if(incomingByte >=0)
        {
          tempString.concat("ml");
          Serial.println(tempString);
        }

        break;
    }
  }
}

