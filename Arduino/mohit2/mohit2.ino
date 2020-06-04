const int A = 8;
const int B = 9;
const int C = 10;

//(MSB) CBA (LSB)

void setup() {
  Serial.begin(9600);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
   
}

void loop() {

        digitalWrite(A,0);
        digitalWrite(B,0);
         digitalWrite(C,0);
         Serial.print("sensor value1 is ");
       Serial.println(analogRead(A0));
       

   delay(200);
       
        digitalWrite(A,1);
        digitalWrite(B,0);
         digitalWrite(C,0);
          Serial.print("sensor value2 is ");
       Serial.println(analogRead(A0));
       

    delay(200);
    
       digitalWrite(A,0);
        digitalWrite(B,1);
         digitalWrite(C,0);
          Serial.print("sensor value3 is ");
       Serial.println(analogRead(A0));
       

    delay(200);
    
        digitalWrite(A,1);
        digitalWrite(B,1);
         digitalWrite(C,0);
          Serial.print("sensor value4 is ");
       Serial.println(analogRead(A0));
       
  
 
 delay(200);

}
