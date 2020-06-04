#include <ESP8266WiFi.h>
 
const char* ssid = "mitesh";
const char* password = "12345678";
 
int ledPin1 = D0;
int ledPin2 = D4;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);

  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);
 
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
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
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
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/D0LED=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
  }
  if (request.indexOf("/D0LED=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
  }

  if (request.indexOf("/D4LED=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
  }
  if (request.indexOf("/D4LED=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  
  client.println("<br><br>");
  client.println("<a href=\"/D0LED=ON\"\"><button>D0 Turn On </button></a>");
  client.println("<a href=\"/D0LED=OFF\"\"><button>D0 Turn Off </button></a>");
  client.println("<a href=\"/D4LED=ON\"\"><button>D4 Turn On </button></a>");
  client.println("<a href=\"/D4LED=OFF\"\"><button>D4Turn Off </button></a>");
 
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
