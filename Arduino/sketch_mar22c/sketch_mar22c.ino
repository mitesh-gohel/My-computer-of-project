#include <ESP8266WiFi.h>

const char* ssid = "PATEL'S iPHONE";    // ur hotspot name
const char* password = "patel123"; // ur hotspot pword
String s,x;
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);

  
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
  int value = LOW;
  if (req.indexOf("/LED=OFF") != -1)  {
    digitalWrite(D0, HIGH);
    value = HIGH;
  }
  else if (req.indexOf("/LED=ON") != -1)  {
    digitalWrite(D0, LOW);
    client.println("ave koi vat vivaad nai aa reseved che.......");

  }
  
if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  // Prepare the response
   s =s+ "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html><html><html lang=\"/en\"><head></head><body><table border= 5px; bordercolor=\"/white\"; style=\"/width: 100%; background-color: purple; color: yellow;\" ><tr style=\"/text-align: center\"><td ><h4 >Parking Spot-1</h4><strong>ID Number :</strong><input type=\"/text\" /></br><input type =\"radio\" button type=\"/button\">500</button><input type =\"radio\"button type=\"button\">300</button><input type =\"radio\"button type=\"button\">200</button></br>""";
   s= s+ String(x);
   s= s+ "<br><br>";
   s= s+("<a href=\"/LED=ON\"\"><button>reserve </button></a>");
   s= s+("<a href=\"/LED=OFF\"\"><button>unreserved </button></a><br />"); 
 //  s= s+ "<br /> <br></font><div style=\"/float: center; margin-left: 120px\"><img src=\"/https://lh6.ggpht.com/AyI5C0xP9_Gpoic98l5W0zCpTM5t37KMh9Q8wUwlIiUMl4relilVQhpqsosFMRACu9g=w300\" width=\"/180\" height=\"/180\"></div></td><br/></td></tr></table></body><br/></td></tr></table></body>";

// s = s + "<head><meta http-equiv='refresh' content='5'></head>";  //for auto refresh

 
  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
