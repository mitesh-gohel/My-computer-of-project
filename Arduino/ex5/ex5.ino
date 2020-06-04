const int read = 5; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data

void setup()
{
  //Begin serial communication
  Serial.begin(9600);
  
}

void loop()
{
  value = digitalRead(read); //Read data from analog pin and store it to value variable
  delay(1000); // Check for new value every 5 sec
}

