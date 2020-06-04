#include <Stepper.h>

const int stepsPerMotorRevolution = 32;  //No of steps per internal revolution of motor,
                                        //4-step mode as used in Arduino Stepper library
                                    
const int stepsPerOutputRevolution = 32*64; //no of steps per revolution of the output shaft

const int motorpin1 = 8;                    //Assign motor (ie board) pins to Arduino pins
const int motorpin2 = 9;                    //
const int motorpin3 = 10;                   //
const int motorpin4 = 11;                   //

// initialize the stepper library on pins 8 through 11, Motor rev steps, "Firing" sequence 1-3-2-4, 
Stepper myStepper(stepsPerMotorRevolution, motorpin1,motorpin3,motorpin2,motorpin4);            

void setup() {
// Stepper library sets pins as output

 myStepper.setSpeed(200);                 //Set the speed
 Serial.begin(9600);                      // initialize the serial port:

}
//                                          MAIN LOOP +++++++++++++++++++
void loop() {

  // Quarter revolution clockwise
  Serial.println("clockwise 1/3 rev");
  myStepper.step(stepsPerOutputRevolution/3);                           
  delay(5000);
  
 
}
//  

