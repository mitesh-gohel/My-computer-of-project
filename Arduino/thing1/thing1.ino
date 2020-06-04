
#include <ESP8266WiFi.h>



const char* ssid     = "mitesh";
const char* password = "12345678";

const char* host = "api.thingspeak.com";


void setup() {
  Serial.begin(9600);
  delay(10);
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

float value = 0;

void loop() {
  delay(5000);
  value = analogRead(A0);

  Serial.print("connecting..");
  

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println("connection done");

  String postStr = "GET https://api.thingspeak.com/update?api_key=ODSHJSJV0H7SS2YM&field1=";
         postStr += String(value);
         postStr += "\r\n\r\n";


  client.print(postStr);
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  
}


