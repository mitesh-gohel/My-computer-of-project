const int A = 8;
const int B = 9;
const int C = 10;
int read;
void setup() {
  Serial.begin(9600);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  digitalWrite(A,0);
  digitalWrite(B,0);
  digitalWrite(C,0);
}

void loop() {

  if(Serial.available())
  {
    read=Serial.read();
    if(read=='0'){
      Serial.println(analogRead(A0));
    }
  }
 
 delay(200);

}
