int value1,value2;         
void setup()
{
  //Begin serial communication
  Serial.begin(9600);
  
}

void loop()
{
float  value = analogRead(A0);
  Serial.print(value);
  Serial.print("       ");
  Serial.println(value1);
  if (value<=330){ 
    Serial.println("Water level is Low"); 
  }
  else if (value>330 && value2<=430){ 
    Serial.println("Water level is  Medium"); 
  }
  
  else if (value>430){ 
    Serial.println("Water level is High"); 
  } 
  


  delay(1000); 
}

