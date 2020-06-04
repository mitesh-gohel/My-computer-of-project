#include "DHT.h"

#define DHTPIN D3     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE); // instantiate a DHT object



#include <ESP8266WiFi.h>

#define LED 0
#define LED1 2


int val,val1,level;
const char* ssid = "Airtel-E8231-e5c3"; //WiFiSSID
const char* password = "nei6eayj"; //PASSWORD

const char* host = "api.thingspeak.com";
// Data URL: https://thingspeak.com/channels/XXXXX/
const char* privateKey = "Z8YB8F0FTYZ75QW8"; //ENTER_YOUR_PRIVATE_KEY

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin(); 
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
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


void loop()
{
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);
  level= 1024-analogRead(A0);
  level=level*100/1024;
  delay(1000); //wait a sec (recommended for DHT11)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

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
   const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println("connection done");
  // We now create a URI for the request
  String url = "/update?";
  url += "key=";
  url += privateKey;
  url += "&field1=";
  url += level;
   url += "&field2=";
  url += h;
   url += "&field3=";
  url += t;
  

  Serial.print("Requesting URL: ");
  Serial.println(url);

   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  //s += (val)?"high":"low";
    s+= "<h1>ESP8266 WEB SERVER</h1>\r\n";
    s+= "<h3>Program Created for : AUTOMATED IRRIGATION USING IOT</h3>\r\n";
    s+= "<p>motor <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF1\"><button>OFF</button></a></p>\r\n";
    s+= "<p>sprinklers<a href=\"?pin=ON2\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF2\"><button>OFF</button></a></p>\r\n";
    s+="<hr>";
    s+="<p>soil moisture level :</p>";
  s+=String(level);
    if(level<=35)
    {
      s+="<p> Too dry, need adequate water </p>";
    }
    else if(level>=35 && level<=85)
    {
      s+="<p> Soil has adequate moisture:</p>";
    }
    else
    {
      s+="<p> Soil may be water logged</p>";
    }
      s+="<hr>";

    s+="<p>temperature in celcius:</p>";
    s+=String(t);
    s+="<p>temperature in fahreheit:</p>";
    s+=String(f);
    s+="<p>humidity:</p>";
        s+=String(h);
  if(h<25)
  {
    s+="<p> Weather is dry, good for kharif crops </p>";
   }
  else if(h>25 && h<60)
   {
      s+="<p> Weather is wet, perfect for Rabi crops </p>";
   }
  else
   {
       s+="<p> Weather is stormy, Cover the fields </p>"; 
   }
      if(t<25)
  {
      s+="<p> Weather is cool,bad for summer fruits</p>";
   }
  else if(t>25 && t<40)
   {
      s+="<p> Weather is perfect  for crops </p>";
   }
  else
   {
      s+="<p> Weather is too hot , initiate the sprinklers</p>"; 
   }
      s+="<hr>";
      s+= "</html>\n";

  // Send the response to the client
  client.print(s);
  // Read the first line of the request
      String req = client.readStringUntil('\r');
      Serial.println(req);
      client.flush();

  // Match the request

    if (req.indexOf("?pin=ON1") != -1)
    val = 0;
    else if (req.indexOf("?pin=OFF1") != -1)
    val = 1; 
    else if (req.indexOf("?pin=ON2") != -1)
    val1 = 0;
    else if (req.indexOf("?pin=OFF2") != -1)
    val1 = 1;
    else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
    digitalWrite(LED, val);
    digitalWrite(LED1, val1);
    client.flush();


  // Prepare the response
  /*String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  //s += (val)?"high":"low";
s+= "<h1>ESP8266 WEB SERVER</h1>\r\n";
s+= "<h3>Program Created for : Workshop on IOT</h3>\r\n";
  s+= "<p>GPIO0 <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF1\"><button>OFF</button></a></p>\r\n";
  s+= "<p>GPIO2 <a href=\"?pin=ON2\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF2\"><button>OFF</button></a></p>\r\n";
  s += "</html>\n";

  // Send the response to the client
client.print(s);*/
    delay(1);
    Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}




