      
  const int  buttonPin = D2; // flow sensor output
  
  volatile byte contagem = 0;   // number of pulses
 
  // The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

  //Interrupt function, so that the counting of pulse â€œrise upsâ€ dont interfere with the rest of the code  (attachInterrupt)
  void pin_ISR()
  {   
      contagem++;
  }

void setup() {
   // Serial Comunication init
   Serial.begin(9600);
   delay(10);

   // Initialization of the variable â€œbuttonPinâ€ as INPUT (D2 pin)
   pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  contagem = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
   
  
  // Attach an interrupt to the ISR vector
  attachInterrupt(digitalPinToInterrupt(buttonPin), pin_ISR, FALLING);

}


void loop() {
  //Serial.print("pulse are   ");
  // Serial.println(contagem);
  
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(buttonPin);
        
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * contagem) / calibrationFactor;
    
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space


  Serial.print(long(flowRate*1000)); //flowrate in millilitres/minute
  Serial.print("ml/min");
   Serial.print("         ");
   
    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres);
    Serial.print("mL"); 
    Serial.print("\t");       // Print tab space
  Serial.print(totalMilliLitres/1000);
  Serial.println("L");
    

    // Reset the pulse counter so we can start incrementing again
    contagem = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(digitalPinToInterrupt(buttonPin), pin_ISR, FALLING);
  }


}

