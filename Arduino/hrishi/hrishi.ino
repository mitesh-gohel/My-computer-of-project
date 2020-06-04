
#include <ESP8266WiFi.h>

const char* ssid = "mitesh";
const char* password = "12345678";

String s,x;
int value; 

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  
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

value = analogRead(A0); //Read data from analog pin and store it to value variable
  Serial.println(value);
  if (value<=160){ 
    Serial.println("Water level: Low"); 
    x="Low";
    delay(1000);
  }
  else if (value>160 && value<=290){ 
    Serial.println("Water level: Medium"); 
    x="Medium";
    delay(1000);
  }
  else if (value>290){ 
    Serial.println("Water level: High"); 
    x="High";
    delay(1000);
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
    
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
 

  // Prepare the response

  s = "<!DOCTYPE html><html><frameset cols=\"/25%,*,25%\"><frame src=<!DOCTYPE HTML<html>Led pin is now:On/Off<br><a href=\"/D0LED=ON\"\"><button>D0 Turn On </button></a><a href=\"/D0LED=OFF\"\"><button>D0 Turn Off </button></a><a href=\"/D4LED=OFF\"\"><button>D4 Turn On </button></a><a href=\"/D4LED=OFF\"\"><button>D4Turn Off </button></a></html>><frame src=\"/frame_b.htm\"></html>";


  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}


