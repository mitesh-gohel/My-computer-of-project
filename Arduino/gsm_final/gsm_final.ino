 #include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 13);



#include <Stepper.h>

const int stepsPerMotorRevolution = 32;  //No of steps per internal revolution of motor,
                                        //4-step mode as used in Arduino Stepper library
                                    
const int stepsPerOutputRevolution = 32*64; //no of steps per revolution of the output shaft

const int motorpin1 = 8;                    //Assign motor (ie board) pins to Arduino pins
const int motorpin2 = 9;                    //
const int motorpin3 = 10;                   //
const int motorpin4 = 11;                   //

int i=0;

// initialize the stepper library on pins 8 through 11, Motor rev steps, "Firing" sequence 1-3-2-4, 
Stepper myStepper(stepsPerMotorRevolution, motorpin1,motorpin3,motorpin2,motorpin4); 



void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

   myStepper.setSpeed(200);                 //Set the speed
}


void loop()
{

    Serial.println("clockwise 1/3 rev");
  myStepper.step(stepsPerOutputRevolution/3);                           
  delay(5000);
  if(i<3)
  {
    SendMessage();
  }

  
  
  Serial.println("ready");
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());


   i++;
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918347261808\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 

