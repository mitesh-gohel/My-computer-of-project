

void setup()
{
  pinMode(8,OUTPUT);  //A1 of motor driver
  pinMode(9,OUTPUT);  //A2 of motor driver
   digitalWrite(8,LOW);
    digitalWrite(9,LOW);
}

void loop()
{
   //digitalWrite(8,LOW); //for clockwise
    //digitalWrite(9,HIGH);
  
  digitalWrite(8,HIGH);  //for anticlockwise
   digitalWrite(9,LOW);
  }

