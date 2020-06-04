int value;          
void setup()
{
  
  Serial.begin(9600);
  pinMode(6,OUTPUT);  //A1 of motor driver
  pinMode(7,OUTPUT);  //A2 of motor driver
  pinMode(13,OUTPUT);  //LED or buzzer
  pinMode(8,OUTPUT);  //LED
  pinMode(9,OUTPUT);  //LED
  pinMode(10,OUTPUT);  //LED
  pinMode(11,OUTPUT);  //LED
  digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(13,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
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
      digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    
  }
  else if (value>330 && value<=430){ 
    Serial.println("Water level is  Medium"); 
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
     digitalWrite(13,LOW);
     digitalWrite(8,LOW);
     digitalWrite(9,LOW);
     digitalWrite(10,LOW);
     digitalWrite(11,LOW);
  }
  
  else if (value>430){ 
    Serial.println("Water level is High"); 
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(13,HIGH);   //LED is on
     digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  } 
  

  delay(1000); 
}

