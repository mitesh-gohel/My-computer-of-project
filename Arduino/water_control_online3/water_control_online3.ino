#include <ESP8266WiFi.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE

const char* ssid = "mitesh"; // put your router name
const char* password = "12345678";// put your password 
 
const char* host = "mitesh690.000webhostapp.com";

#define LED D0
 
void setup() {
  Serial.begin(9600);
   Serial.println();
   
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  delay(2000);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
 Serial.println();
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
  String url = "/my2.html";
 
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  int i=0;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){i++;
   String line = client.readStringUntil('\n');

  if(i==13){
  Serial.print(i);
  Serial.print("==");
  Serial.println(line);
    if(line="on")
    {
      Serial.println("yes");
    digitalWrite(LED,LOW);
    }
    else
    
    {
      Serial.println("no");
      digitalWrite(LED,HIGH);
    }
  }


  }


   }
