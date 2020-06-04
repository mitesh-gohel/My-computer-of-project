/* Arduino Tutorial - Watel Level Sensor 40mm
   More info: */

const int read = A0; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data

void setup()
{
  //Begin serial communication
  Serial.begin(9600);
  
}

void loop()
{
  value = analogRead(read); //Read data from analog pin and store it to value variable
  Serial.println(value);
  if (value==0){ 
    Serial.println("Water level: 0mm - Empty!"); 
  }
  else if (value>0 && value<=510){ 
    Serial.println("Water level: 0mm to 10mm"); 
  }
  
  else if (value>510 && value<=600){ 
    Serial.println("Water level: 10mm to 20mm"); 
  } 
  
  else if (value>600 && value<=620){ 
    Serial.println("Water level: 20mm to 30mm"); 
  }
  
  else if (value>620){ 
    Serial.println("Water level: 30mm to 40mm"); 
  }

  delay(5000); // Check for new value every 5 sec
}

