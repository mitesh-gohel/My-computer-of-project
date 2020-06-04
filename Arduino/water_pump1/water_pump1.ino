int value;          
void setup()
{
  
  Serial.begin(9600);
  pinMode(6,OUTPUT);  //A1 of motor driver
  pinMode(7,OUTPUT);  //A2 of motor driver
  pinMode(13,OUTPUT);  //LED or buzzer

  digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(13,LOW);

    delay(2000);
}

void loop()
{
  value = analogRead(A0); 
  Serial.println(value);
  if (value<=330){ 
    Serial.println("Water level is Low"); 
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
     digitalWrite(13,LOW);

    
  }
  else if (value>330 && value<=430){ 
    Serial.println("Water level is  Medium"); 
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
     digitalWrite(13,LOW);

  }
  
  else if (value>430){ 
    Serial.println("Water level is High"); 
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(13,HIGH);   //LED is on

  } 
  

  delay(1000); 
}

