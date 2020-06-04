#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "PATEL'S iPHONE";  
const char* password = "patel123";

const char* host     = "mitesh690.000webhostapp.com"; // Your domain  
String path          = "/State.json";  




#define LED D0


//const int pin        = 2;
//static const uint8_t pin   = 2;
//static const uint8_t D0   = 16;
const int d1   = 5;//left(red)
const int d2   = 4;//left(black)
const int d3   = 0;//right(red)
const int d4   = 2;//right(black)
/*static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
*/

void setup() {  
  pinMode(d1, OUTPUT); 
  pinMode(d1, HIGH);
  pinMode(d2, OUTPUT); 
  pinMode(d2, HIGH);
  pinMode(d3, OUTPUT); 
  pinMode(d3, HIGH);
  pinMode(d4, OUTPUT); 
  pinMode(d4, HIGH);

  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  Serial.begin(9600);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  
  Serial.println("IP address: " + WiFi.localIP());
}

void loop() {  
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");

  delay(500); // wait for server to respond

  // read response
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    // Serial.print(line);
    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      Serial.print(".");
      if (line=="\n") { // skips the empty space at the beginning 
        section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);
      
      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["State"], "Forward") == 0) 
      {
        digitalWrite(d1, LOW);
        digitalWrite(d2, HIGH);
        digitalWrite(d3, LOW);
        digitalWrite(d4, HIGH); 
        digitalWrite(LED,LOW);
      }
      else if (strcmp(json_parsed["State"], "Left") == 0) 
      {  
        digitalWrite(d1, HIGH);
        digitalWrite(d2, HIGH);
        digitalWrite(d3, LOW);
        digitalWrite(d4, HIGH);
        digitalWrite(LED,HIGH);
      
      }
      else if (strcmp(json_parsed["State"], "Stop") == 0) 
      { 
        digitalWrite(d1, HIGH);
        digitalWrite(d2, HIGH);
        digitalWrite(d3, HIGH);
        digitalWrite(d4, HIGH); 
       
      }
      else if (strcmp(json_parsed["State"], "Right") == 0) 
      {  
        digitalWrite(d1, LOW);
        digitalWrite(d2, HIGH);
        digitalWrite(d3, HIGH);
        digitalWrite(d4, HIGH); 
        Serial.println("Car turn to Right");
      }
      else if (strcmp(json_parsed["State"], "Backward") == 0) 
      {
        digitalWrite(d1, HIGH);
        digitalWrite(d2, LOW);
        digitalWrite(d3, HIGH);
        digitalWrite(d4, LOW); 
        Serial.println("Car going to Backward");
      }/*
      else {
        digitalWrite(pin, LOW);
        Serial.println("led off");
      }*/
    }
  }
  Serial.print("closing connection. ");
}
