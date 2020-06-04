
#include <ESP8266WiFi.h>

const char* ssid = "mitesh";
const char* password = "12345678";

String s,x;
int value; 

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D0, OUTPUT);

  digitalWrite(D4,HIGH);  
  digitalWrite(D0,HIGH);
  
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
    digitalWrite(D4,LOW);  //D4 is on for 2sec
    delay(2000);
     digitalWrite(D4,HIGH);
     delay(2000);
  }
  else if (value>160 && value<=290){ 
    Serial.println("Water level: Medium"); 
    x="Medium";
    digitalWrite(D0,LOW);  //D0 is on for 2sec
    delay(2000);
    digitalWrite(D0,HIGH);
    delay(2000);
  }
  else if (value>290){ 
    Serial.println("Water level: High"); 
    x="High";
    digitalWrite(D4,LOW);  //D0 and D4 are on for 2sec
    digitalWrite(D0,LOW);
    delay(2000);
    digitalWrite(D4,HIGH);  
    digitalWrite(D0,HIGH);
    delay(2000);
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
   s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><head></head><body><table border= 1px; bordercolor=\"/white\"; style=\"/width: 100%; background-color: Cyan; color: blue;\" ><tr style=\"/text-align: center\"><td ><h1 >Water level sensor </h1><font size=\"/5\"> <strong>water level :</strong>";
   s= s+ String(x);
   s= s+ "<br /> <br></font><div style=\"/float: center; margin-left: 120px\"><img src=\"/https://lh6.ggpht.com/AyI5C0xP9_Gpoic98l5W0zCpTM5t37KMh9Q8wUwlIiUMl4relilVQhpqsosFMRACu9g=w300\" width=\"/180\" height=\"/180\"></div></td><br/></td></tr></table></body><br/></td></tr></table></body>";

  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}


