#include <ESP8266WiFi.h>

const char* ssid = "JioFi3_6A44F3";
const char* password = "te2jcanw69";

const char* host = "watermanagementsystem.000webhostapp.com";

#define TRIGGER_1 D0 // for tank 1
#define ECHO_1   D1 // for tank 1

#define buzzer D8 //buzzer to nodeMCU pin D8

#define TRIGGER_2 D5 // for tank 2
#define ECHO_2   D6 // for tank 2

#define A1 D2      //A1 of motor driver      // connect +ve of pump to 1 of MA AND,connect -ve of pump to 2 of MA
#define A2 D3      //A2 of motor driver

const int  flow_sensor = D7; // flow sensor output
volatile byte pulses = 0;   // number of pulses
float calibrationFactor = 4.5;    // The hall-effect flow sensor outputs approximately 4.5 pulses per second per litre/minute of flow.
float flowrate = 0.0;


WiFiServer server(80);

 String line = " ";     //for mode
 String line2 = " ";     //for mode

 String line3 = " ";     //for pump
 String line4 = " ";     //for pump

 String responde = " ";  //when we send some data through HTTP, It gives some responde

  long duration_1, distance_1;  // for tank 1
  long duration_2, distance_2;  // for tank 2

  int height_1;
  int height_2;

  float percentage_1;  // for tank 1
  float percentage_2;  // for tank 2

   String level_1 = " ";  // for tank 1     
   String level_2 = " ";  // for tank 2

   
 void setup() {

   Serial.begin(9600);
   delay(10);

  pinMode(TRIGGER_1, OUTPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(TRIGGER_2, OUTPUT);
  pinMode(ECHO_2, INPUT);

  pinMode(A1,OUTPUT);  //A1 of motor driver
  pinMode(A2,OUTPUT);  //A2 of motor driver
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);

  pinMode(buzzer, OUTPUT); // Set buzzer - pin D4 as an output
   noTone(buzzer);     // Stop sound...

  pinMode(flow_sensor, INPUT);
  digitalWrite(flow_sensor, HIGH);  
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
 }



 void loop() {

 // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
  }
  
  // We now create a URI for the request
  String url = "/mode.html";
 
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  int i=0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){i++;
   line = client.readStringUntil('\n');

  if(i==13){

  line2 = line; 
  Serial.print(i);
  Serial.print("==");
  Serial.println(line2);
  
  }
    
  }

    if(line2 == "Automatic\r")
    {
      Serial.println("Automatic mode is selected");
      automatic();
    }
    
    else if(line2 == "Manually\r")
    {
      Serial.println("Manually mode is selected");
      manually();
  
    }

 }

 
void automatic()
{
  check_tank1();
  check_tank2();

  noTone(buzzer);     // Stop sound...

        if((level_1 == "High") && (level_2 == "Low"))
       {
         digitalWrite(A1,HIGH);     // connect +ve of pump to 1 of MA AND,connect -ve of pump to 2 of MA
         digitalWrite(A2,LOW);
         check_flowrate();
        }
         else if((level_1 == "High") && (level_2 == "Medium"))
       {
         digitalWrite(A1,HIGH);     
         digitalWrite(A2,LOW);
         check_flowrate();
        }
         else if((level_2 == "Low") && (level_1 == "Medium"))
       {
         digitalWrite(A1,HIGH);     
         digitalWrite(A2,LOW);
         check_flowrate();
        }
         else if((level_1 == "Medium") && (level_2 == "Medium"))
       {
         digitalWrite(A1,HIGH);     
         digitalWrite(A2,LOW);
         check_flowrate();
        }
        else
        {
         digitalWrite(A1,LOW);     
         digitalWrite(A2,LOW);
         flowrate = 0.0;
        }
        
         send_data();
}

void manually()
{
  check_tank1();
  check_tank2();
  check_flowrate();
  send_data();

 // if(level_2 == "High")
    //   {
     //    tone(buzzer, 1000); 
     //  }
 // else
 // {
  //   noTone(buzzer);     // Stop sound...
 // }
  
    // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
   
  }
  
  // We now create a URI for the request
  String url = "/pump.html";
 
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  int i=0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){i++;
   line3 = client.readStringUntil('\n');

  if(i==13){

  line4 = line3; 
  Serial.print(i);
  Serial.print("==");
  Serial.println(line4);
  
  }
     
  }
 
    if(line4 == "On\r")
    {
      Serial.println("Water Pump is on");
      digitalWrite(A1,HIGH);     
      digitalWrite(A2,LOW);
      check_flowrate();
        if(level_2 == "High")
        {
          tone(buzzer, 1000); // Send 1KHz sound signal...
          Serial.println("buzzer is on");
        }
    }
   
    else if(line4 == "Off\r")
    {
      Serial.println("Water pump is off");
      digitalWrite(A1,LOW);     
      digitalWrite(A2,LOW);
      flowrate = 0.0;
      noTone(buzzer);     // Stop sound...
    }

      send_data();
}



void check_tank1()
{
    digitalWrite(TRIGGER_1, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER_1, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER_1, LOW);
  duration_1 = pulseIn(ECHO_1, HIGH);
  distance_1 = ((duration_1)/2) / 29.1;

  height_1 = 16 - distance_1;   // when tank1 is empty at that time distance_1 is 16cm

  percentage_1 =(height_1/15.0)*(100.0);  //at highest level,  hight of water level is 13cm in tank1
  Serial.print(distance_1);
   Serial.print("Amount of water in tank 1 is ");
  Serial.print(percentage_1);
  Serial.println("%");
  delay(1000);

  if(height_1 <= 5)
  {
    level_1 = "Low";
    Serial.println("Water level of tank 1 is Low");
  }
  else if((height_1 > 5) && (height_1 <= 10))
  {
    
    level_1 = "Medium";
    Serial.println("Water level of tank 1 is Medium");
  }
  else if(height_1 > 10)
  {
    level_1 = "High";
    Serial.println("Water level of tank 1 is High");
  }

}


void check_tank2()
{
    digitalWrite(TRIGGER_2, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER_2, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER_2, LOW);
  duration_2 = pulseIn(ECHO_2, HIGH);
  distance_2 = ((duration_2)/2) / 29.1;
  

  height_2 = 16 - distance_2;   // when tank2 is empty at that time distance_2 is 13cm

  percentage_2 =((height_2)/15.0)*(100.0);  //at highest level,  hight of water level is 11cm in tank2
  Serial.print(distance_2);
   Serial.print("Amount of water in tank 2 is ");
  Serial.print(percentage_2);
  Serial.println("%");
  delay(1000);

  if(height_2 <= 5)
  {
    level_2 = "Low";
    Serial.println("Water level of tank 2 is Low");
  }
  else if((height_2 > 5) && (height_2 <= 10))
  {
    level_2 = "Medium";
    Serial.println("Water level of tank 2 is Medium");
  }
  else if(height_2 > 10)
  {
    level_2 = "High";
    Serial.println("Water level of tank 2 is High");
  }
}

void pulse_counter()
  {   
      pulses++;
  }

void check_flowrate()
{
    // Attach an interrupt
  attachInterrupt(digitalPinToInterrupt(flow_sensor), pulse_counter, FALLING);

  delay(1000);    //delay for measure pulses of flow sensor

  detachInterrupt(flow_sensor);
  flowrate = (((1000.0 / (1000)) * pulses) / calibrationFactor)*1000;   //flowrate in millilitres/minute
   
   Serial.print("Flow rate: ");
  Serial.print(long(flowrate));   
  Serial.println("ml/min");

   // Reset the pulse counter so we can start incrementing again
    pulses = 0;
    
}

void send_data()
{
  Serial.println(level_1);
  Serial.println(level_2);
  Serial.println(percentage_1);
  Serial.println(percentage_2);
  Serial.println(flowrate);

  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
   
  }

 
  // Prepare the response
   String s = "GET /index.php?level_1=";
   s += String("1");        //we don't send to level because level_1 is string, And in php level_1 is string.
   s += "&level_2=";
   s += String("2");        //we don't send to level because level_2 is string, And in php level_2 is string.
   s += "&percentage_1=";
   s += String(percentage_1);
   s += "&percentage_2=";
   s += String(percentage_2);
   s += "&flowrate=";
   s += String(int(flowrate));
   s += " HTTP/1.1\r\nHost: watermanagementsystem.000webhostapp.com\r\n\r\n";

 
  // Send the response to the client
  client.print(s);
  delay(500);

  int a=0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){a++;
   String responde = client.readStringUntil('\n');

  //if(a==9){
  Serial.print(a);
  Serial.print("==");
  Serial.println(responde);
  //}
   
  }
}












